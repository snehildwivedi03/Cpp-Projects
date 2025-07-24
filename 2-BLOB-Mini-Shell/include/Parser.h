#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct Command {
    std::string cmd;
    std::vector<std::string> args;
    std::string inputRedirect;   // For '<'
    std::string outputRedirect;  // For '>'
    bool appendOutput = false;   // For '>>'
    bool background = false;
};


struct Pipeline {
    std::vector<Command> commands;
};

// Tokenizes raw user input like: echo "hello" > file.txt
std::vector<std::string> tokenizeInput(const std::string& input);

// Parses a single command from tokenized input
Command parseCommand(const std::vector<std::string>& tokens);

// Parses full pipeline from raw input (handles pipes, etc.)
Pipeline parsePipeline(const std::string& input);

#endif // PARSER_H
