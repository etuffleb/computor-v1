#pragma once

#include "computorv1.h"

class ParserError
{
public:
    ParserError(ParsableString& parsableString, std::string message);
    ParserError(const ParserError& parserError) = default;
    ~ParserError();
private:
    char* rest;
    char* original;
    std::string message;

    friend std::ostream& operator<<(std::ostream& os, const ParserError& dt);
};