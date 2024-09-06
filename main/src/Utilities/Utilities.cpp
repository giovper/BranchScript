// Utilities.cpp
#include "Utilities.h"

std::string Utilities::divideBySpacing(const std::string& text, int index) {
    int counter = 0;
    std::string output = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            counter++;
        }
        if (counter == index && text[i] != ' ') {
            output.push_back(text[i]);
        }
    }
    return output;
}

std::vector<std::string> Utilities::readFile(const std::string& path){
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) { 
        std::cerr << "Error opening the file!" << std::endl;
        return {};
    } else {
        std::string line;
        std::vector<std::string> output;
        while (getline(inputFile, line)) {
            output.push_back(line);
        }
        return output;
    }
}

bool Utilities::isFileExisting(const std::string& path){
    std::ifstream file(path);
    return file.good();
}

std::string Utilities::getExePath(){
    char path[MAX_PATH]; 
    GetModuleFileName(NULL, path, MAX_PATH);
    return path;
}

bool Utilities::isAlphaNum(std::string str){
    std::string lowerStr = str;
    std::string upperStr = str;
    
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return (lowerStr!=upperStr);
}

bool Utilities::isDigit(std::string str){
    return std::isdigit(str[0]);
}

bool Utilities::isSkippable(std::string str){
    if (str[0] == ' '){
        return true;
    }
    return false;
}