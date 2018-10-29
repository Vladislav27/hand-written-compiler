#include "LineHandler.h"

unsigned int Comp::LineHandler::getPosition(unsigned int step)
{
    unsigned int old = position;
    position += step;
    return old;
}

void Comp::LineHandler::refreshValues()
{
    position = 1;
    currentLine++;
}

unsigned int Comp::LineHandler::getLine()
{
    return currentLine;
}