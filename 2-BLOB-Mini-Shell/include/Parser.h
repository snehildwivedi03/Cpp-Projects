#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>

struct Command{
std::string cmd;
std::vector<std::string> args;    // arguments (including cmd)
    std::string inputFile;            // if '<' used
    std::string outputFile;           // if '>' or '>>' used
    bool append = false;              // >> vs >
    bool background = false;
};

struct Pipeline {
  std::vector<Command> commands; // List of commands in the pipeline

};
Pipeline parsePipeline(const std::vector<std::string>& tokens);


std::vector<std::string> tokenizeInput(const std::string& input);
Command parseCommand(const std::vector<std::string>& tokens);

#endif