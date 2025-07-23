#include "Parser.h"
#include <vector>
#include <string>
#include <cctype>
#include<iostream>
#include <sstream>

std::vector<std::string> tokenize(const std::string& input){
  std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
std::vector<std::string> splitByPipe(const std::string& input) {
    std::vector<std::string> parts;
    std::string temp;
    std::istringstream iss(input);

    while (std::getline(iss, temp, '|')) {
        parts.push_back(temp);
    }

    return parts;
}


std::vector<std::string> tokenizeInput(const std::string &input) {
    std::vector<std::string> tokens;
    std::string current;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        // Handle operators
        if (c == '|' || c == '<' || c == '>' || c == '&') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }

            // Handle double >> (append)
            if (c == '>' && i + 1 < input.length() && input[i + 1] == '>') {
                tokens.push_back(">>");
                ++i;
            } else {
                tokens.push_back(std::string(1, c));
            }
        }
        // Handle space
        else if (isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        }
        // Normal characters
        else {
            current += c;
        }
    }

    // Push last token
    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}

Command parseCommand(const std::vector<std::string> &tokens) {
    Command cmd;
    bool expectInput = false, expectOutput = false;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string &tok = tokens[i];

        if (tok == "<") {
            expectInput = true;
        } else if (tok == ">" || tok == ">>") {
            expectOutput = true;
            cmd.append = (tok == ">>");

            if (i + 1 >= tokens.size()) {
                std::cerr << "Syntax error: expected output file after " << tok << "\n";
                break;
            }
        } else if (tok == "&") {
            cmd.background = true;
        } else if (expectInput) {
            cmd.inputFile = tok;
            expectInput = false;
        } else if (expectOutput) {
            cmd.outputFile = tok;
            expectOutput = false;
        } else {
            if (cmd.cmd.empty()) {
                cmd.cmd = tok;
            }
            cmd.args.push_back(tok);
        }
    }

    return cmd;
}
std::vector<Command> parsePipeline(const std::vector<std::string> &tokens) {
    std::vector<Command> pipeline;
    std::vector<std::string> currentCmdTokens;

    for (const auto &tok : tokens) {
        if (tok == "|") {
            if (!currentCmdTokens.empty()) {
                pipeline.push_back(parseCommand(currentCmdTokens));
                currentCmdTokens.clear();
            }
        } else {
            currentCmdTokens.push_back(tok);
        }
    }

    // Add the last command after the final |
    if (!currentCmdTokens.empty()) {
        pipeline.push_back(parseCommand(currentCmdTokens));
    }

    return pipeline;
}
Pipeline parsePipeline(const std::string& input) {
    std::vector<std::string> tokens = tokenizeInput(input);
    std::vector<Command> commands = parsePipeline(tokens);
    return { commands };
}

