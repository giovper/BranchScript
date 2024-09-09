#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <memory>  // Aggiungi per std::unique_ptr

class Terminal {
public:
    bool ReplyToCLI(const std::string& input);
    void ListenToCLI();
};

#endif // TERMINAL_H
