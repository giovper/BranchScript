// Terminal.h
#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

class Terminal {
public:
    bool ReplyToCLI(const std::string& input);
    void ListenToCLI();
};

#endif // BRANCH_SCRIPT_TERMINAL_H
