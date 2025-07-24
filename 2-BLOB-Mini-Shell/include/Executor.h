#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "Parser.h"

void executePipeline(const Pipeline& pipeline);
void executeSingleCommand(const Command& cmd, bool isBackground );

#endif