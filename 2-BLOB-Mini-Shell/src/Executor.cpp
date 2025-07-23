#include "Executor.h"
#include "Error.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <limits.h>
#include <filesystem>

void handleBuiltin(const Command& cmd) {
    const std::string& command = cmd.cmd;

    if (command == "cd") {
        const char* path = cmd.args.size() > 1 ? cmd.args[1].c_str() : getenv("HOME");
        if (chdir(path) != 0) {
            perror("cd failed");
        }
    } else if (command == "exit") {
        std::cout << "Exiting BLOB Shell...\n";
        exit(0);
    } else if (command == "clear") {
        std::cout << "\033[2J\033[1;1H";  // ANSI escape to clear screen
    } else {
        std::cerr << "Unknown builtin command: " << command << std::endl;
    }
}

bool isBuiltin(const std::string& cmd) {
    return cmd == "cd" || cmd == "exit" || cmd == "clear";
}

void executeSingleCommand(const Command& cmd) {
    if (isBuiltin(cmd.cmd)) {
        handleBuiltin(cmd);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Convert args to char* array
        std::vector<char*> argv;
        for (const auto& arg : cmd.args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);  // execvp requires null-terminated array

        execvp(cmd.cmd.c_str(), argv.data());
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        if (!cmd.background) {
            waitpid(pid, nullptr, 0);
        } else {
            std::cout << "Running in background with PID " << pid << std::endl;
        }
    } else {
        perror("fork failed");
    }
}

void executePipeline(const Pipeline& pipeline) {
    if (pipeline.commands.size() == 1) {
        executeSingleCommand(pipeline.commands[0]);
    } else {
        std::cout << "Pipelines with '|' are not implemented yet!" << std::endl;
    }
}
