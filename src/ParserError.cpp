#include "../lib/computorv1.h"

ParserError::ParserError(ParsableString& parsableString, std::string message) :
    rest(parsableString.restStr),
    original(parsableString.originalStr),
    message(message)
{}

ParserError::~ParserError()
{}

std::ostream& operator<<(std::ostream& os, const ParserError& pe)
{
    int oLen = strlen(pe.original);
    int rLen = strlen(pe.rest);
    std::string padding(oLen - rLen, ' ');

    os << "\033[1m\033[31m" // bold red
       << "Error: "
       << "\033[0m" // reset
       << "Stopped parsing here with message: "
       << "\033[31m" // red
       << pe.message
       << "\033[0m" // reset
       << ": \n"
       << pe.original << '\n'
       << "\033[31m" // red
       << padding << "^\n"
       << "\033[0m" // reset
       ;
    return os;
}
