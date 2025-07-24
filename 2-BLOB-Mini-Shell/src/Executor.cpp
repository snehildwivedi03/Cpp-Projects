#include "Executor.h"
#include "Parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <cstring>

void executeSingleCommand(const Command& cmd, bool isBackground = false) {
    pid_t pid = fork();

    if (pid == 0) {
        // ---- Child Process ----

        // Input Redirection
        if (!cmd.inputRedirect.empty()) {
            int in = open(cmd.inputRedirect.c_str(), O_RDONLY);
            if (in < 0) {
                perror("open input file failed");
                exit(EXIT_FAILURE);
            }
            dup2(in, STDIN_FILENO);
            close(in);
        }

        // Output Redirection
        if (!cmd.outputRedirect.empty()) {
            int out;
            if (cmd.appendOutput) {
                out = open(cmd.outputRedirect.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                out = open(cmd.outputRedirect.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }

            if (out < 0) {
                perror("open output file failed");
                exit(EXIT_FAILURE);
            }

            dup2(out, STDOUT_FILENO);
            close(out);
        }

        // Convert args to char*[]
        std::vector<char*> args;
        for (const std::string& arg : cmd.args) {
            args.push_back(const_cast<char*>(arg.c_str()));
        }
        args.push_back(nullptr);

        execvp(cmd.cmd.c_str(), args.data());
        perror("exec failed");
        exit(EXIT_FAILURE);

    } else if (pid > 0) {
        // ---- Parent Process ----
        if (!isBackground) {
            waitpid(pid, nullptr, 0);  // Foreground
        } else {
            std::cout << "[background pid " << pid << "]" << std::endl;
        }
    } else {
        // ---- Fork Failed ----
        perror("fork failed");
    }
}


void executePipeline(const Pipeline& pipeline) {
    const std::vector<Command>& commands = pipeline.commands;
    size_t n = commands.size();
    int prev_fd[2] = {-1, -1};

    for (size_t i = 0; i < n; ++i) {
        int pipe_fd[2];
        if (i < n - 1) {
            if (pipe(pipe_fd) < 0) {
                perror("pipe failed");
                return;
            }
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child

            // Input redirection or read from previous pipe
            if (!commands[i].inputRedirect.empty()) {
                int in = open(commands[i].inputRedirect.c_str(), O_RDONLY);
                if (in < 0) {
                    perror("open input file failed");
                    exit(EXIT_FAILURE);
                }
                dup2(in, STDIN_FILENO);
                close(in);
            } else if (i > 0) {
                dup2(prev_fd[0], STDIN_FILENO);
            }

            // Output redirection or write to next pipe
            if (!commands[i].outputRedirect.empty()) {
                int out;
                if (commands[i].appendOutput) {
                    out = open(commands[i].outputRedirect.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
                } else {
                    out = open(commands[i].outputRedirect.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }

                if (out < 0) {
                    perror("open output file failed");
                    exit(EXIT_FAILURE);
                }

                dup2(out, STDOUT_FILENO);
                close(out);
            } else if (i < n - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO);
            }

            // Close unused pipe ends
            if (prev_fd[0] != -1) close(prev_fd[0]);
            if (prev_fd[1] != -1) close(prev_fd[1]);
            if (i < n - 1) {
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // Exec command
            std::vector<char*> argv;
            for (const auto& arg : commands[i].args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            argv.push_back(nullptr);

            execvp(commands[i].cmd.c_str(), argv.data());
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent

            if (prev_fd[0] != -1) close(prev_fd[0]);
            if (prev_fd[1] != -1) close(prev_fd[1]);

            if (i < n - 1) {
                prev_fd[0] = pipe_fd[0];
                prev_fd[1] = pipe_fd[1];
                close(pipe_fd[1]); // Parent doesn’t write
            }
        } else {
            perror("fork failed");
            return;
        }
    }

    // Wait for all children unless last is background
    if (!commands.back().background) {
        for (size_t i = 0; i < n; ++i) {
            wait(nullptr);
        }
    }
}
