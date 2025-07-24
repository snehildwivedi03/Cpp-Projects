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
#include <readline/readline.h>
#include <readline/history.h>

#include "Parser.h"
#include "Executor.h"

using namespace std;

void showWelcome() {
    cout << "\n";
    cout << "🫧 ~ Welcome to BLOB-shell ~\n";
    cout << "   Lightweight Unix Shell in C++\n";
    cout << "   Type 'exit' to quit.\n";
    cout << "--------------------------------\n\n";
}

void printPrompt() {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    const char* username = getpwuid(getuid())->pw_name;

    char cwd[4096];
    getcwd(cwd, sizeof(cwd));

    const char* home = getenv("HOME");

    std::string displayPath = cwd;
    if (home && displayPath.find(home) == 0) {
        displayPath.replace(0, std::strlen(home), "~");
    }

    std::cout << username << "@" << hostname << ":" << displayPath << "$ " << std::flush;
}

int main() {
    showWelcome();

    while (true) {
        printPrompt();
        char* inputCStr = readline("");
        if (!inputCStr) break; // Ctrl+D

        std::string input(inputCStr);
        free(inputCStr);

        if (input.empty()) continue;
        add_history(input.c_str());

        if (input == "exit") break;

        Pipeline pipeline = parsePipeline(input);
        if (pipeline.commands.empty()) continue;

        const Command& cmd = pipeline.commands[0];

        // Built-in command: cd
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
        if (pipeline.commands.size() == 1)
            executeSingleCommand(pipeline.commands[0]);
        else
            executePipeline(pipeline);
    }

    return 0;
}
