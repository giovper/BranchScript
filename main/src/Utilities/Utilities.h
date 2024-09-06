// Utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h> 
#include <algorithm>
#include <cctype>

class Utilities {
public:
    static std::string divideBySpacing(const std::string& text, int index);
    static std::vector<std::string> readFile(const std::string& path);
    static std::string getExePath();
    static bool isAlphaNum(std::string str);
    static bool isDigit(std::string str);
    static bool isSkippable(std::string str);
    static bool isFileExisting(const std::string& path);
};

#endif // UTILITIES_H
