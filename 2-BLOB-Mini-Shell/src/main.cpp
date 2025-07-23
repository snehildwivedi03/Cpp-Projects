#include <iostream>
#include <string>
#include <unistd.h>     
#include <limits.h>   
#include <cstdlib>   
#include <vector>
#include "Parser.h"

using namespace std;

// Show welcome screen
void showWelcome() {
    cout << "\n";
    cout << "🫧 ~ Welcome to blob-shell ~\n";
    cout << "   Lightweight Unix Shell in C++\n";
    cout << "   Type 'exit' to quit.\n";
    cout << "--------------------------------\n\n";
}

// Show the prompt: blob:/current/path$
void showPrompt() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    cout << "blob:" << cwd << "$ ";
}

int main() {
    showWelcome();

    string input;
    while (true) {
        showPrompt();

        getline(cin, input);

        if (input.empty()) continue;

        if (input == "exit") {
            cout << "👋 Exiting blob-shell...\n";
            break;
        }

        cout << "[placeholder] You entered: " << input << "\n";
         auto tokens = tokenizeInput(input);
         cout<<"[Parsed Tokens]: ";
         for(const auto& token : tokens) {
             cout <<"[ "<< token <<" ]";
         }
         cout << "\n";
        
    }

    return 0;
}
