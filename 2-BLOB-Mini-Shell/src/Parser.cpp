#include "Parser.h"
#include <vector>
#include <string>
#include <cctype>
#include<iostream>

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