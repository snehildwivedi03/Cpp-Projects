#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include "Parser.h"
#include "Executor.h"
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

void showWelcome() {
    cout << "\n";
    cout << "🫧 ~ Welcome to BLOB-shell ~\n";
    cout << "   Lightweight Unix Shell in C++\n";
    cout << "   Type 'exit' to quit.\n";
    cout << "--------------------------------\n\n";
}

void showPrompt() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    cout << "blob:" << cwd << "$ ";
    
}

int main() {
    showWelcome();

    while (true) {
        // Display prompt
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        string prompt = "blob:" + string(cwd) + "$ ";

        // Read user input
        char* inputCStr = readline(prompt.c_str());
        if (!inputCStr) break; // Ctrl+D
        if (*inputCStr == '\0') {
            free(inputCStr);
            continue;
        }
        

        add_history(inputCStr); // Save to history

        string input(inputCStr);
        free(inputCStr);

        if (input == "exit") {
            cout << "👋 Exiting blob-shell...\n";
            break;
        }

        Pipeline pipeline = parsePipeline(input);
        executePipeline(pipeline);
    }

    return 0;
}
