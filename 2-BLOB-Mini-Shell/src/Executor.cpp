#include "Executor.h"
#include "Error.h"     // optional: for error printing
#include <unistd.h>    // fork, execvp
#include <sys/wait.h>  // waitpid
#include <iostream>
#include <vector>
#include <cstring>     // for c_str

void executeSingleCommand(const Command& cmd) {
    pid_t pid = fork();

    if (pid == 0) {
        // Convert args to char* array
        std::vector<char*> argv;
        for (const auto& arg : cmd.args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);  // execvp requires null-terminated array

        execvp(cmd.cmd.c_str(), argv.data());
        // If execvp returns, there was an error
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        if (!cmd.background) {
            waitpid(pid, nullptr, 0);  // Wait only if not a background process
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
