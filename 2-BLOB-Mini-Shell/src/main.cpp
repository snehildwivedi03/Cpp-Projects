#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <fcntl.h>
#include <vector>
#include <cstring>
#include <sys/wait.h>
#include <cstdlib>
#include <filesystem>
#include <readline/readline.h>
#include <readline/history.h>

#include "Parser.h"
#include "Executor.h"

using namespace std;

// Display welcome banner
void showWelcome() {
    cout << "\n";
    cout << "🫧 ~ Welcome to BLOB-shell ~\n";
    cout << "   Lightweight Unix Shell in C++\n";
    cout << "   Type 'exit' to quit.\n";
    cout << "--------------------------------\n\n";
}

// Generate formatted prompt string: username@hostname:~/path$
std::string getPrompt() {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    const char* username = getpwuid(getuid())->pw_name;

    char cwd[4096];
    getcwd(cwd, sizeof(cwd));

    const char* home = getenv("HOME");
    std::string displayPath = cwd;

    // Replace /home/user with ~
    if (home && displayPath.find(home) == 0) {
        displayPath.replace(0, strlen(home), "~");
    }

    return username + std::string("@") + hostname + ":" + displayPath + "$ ";
}

int main() {
    showWelcome();

    // Load command history from ~/.blob_history
    std::string historyPath = std::string(getenv("HOME")) + "/.blob_history";
    read_history(historyPath.c_str());

    while (true) {
        // Show prompt and read input using readline
        char* inputCStr = readline(getPrompt().c_str());
        if (!inputCStr) break; // Handle Ctrl+D to exit

        std::string input(inputCStr);
        free(inputCStr);

        if (input.empty()) continue;

        // Save input to history
        add_history(input.c_str());

        // Exit command
        if (input == "exit") break;

        // Parse the command into pipeline
        Pipeline pipeline = parsePipeline(input);
        if (pipeline.commands.empty()) continue;

        const Command& cmd = pipeline.commands[0];

        // Handle 'cd' as a built-in command
        if (cmd.cmd == "cd") {
            if (cmd.args.size() > 1) {
                if (chdir(cmd.args[1].c_str()) != 0) {
                    perror("cd failed");
                }
            } else {
                std::cerr << "cd: missing argument\n";
            }
            continue;
        }

        // Execute command(s)
        if (pipeline.commands.size() == 1) {
            executeSingleCommand(pipeline.commands[0]);
        } else {
            executePipeline(pipeline);
        }
    }

    // Save history on exit
    write_history(historyPath.c_str());
    return 0;
}
