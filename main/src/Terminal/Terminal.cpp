#include <iostream>
#include <string>
#include <cstdlib>
#include "../Utilities/Utilities.h"  // Include il percorso corretto
#include "../Core/Runtime.h"      // Include il percorso corretto
#include "Terminal.h"

using namespace std;

string Version = "0.0.1";
string input;

bool Terminal::ReplyToCLI(const string& input) {
    Runtime runtime;
    string main_input = Utilities::divideBySpacing(input, 0);
    if (main_input == "exit") {
        exit(1);
    } else if (main_input == "run" || main_input == "ast") {
        std::string fullPath;
        std::string relPath = Utilities::divideBySpacing(input, 1);
        fullPath = (((relPath[1] == ':') && (relPath[2] == '\\')) ? relPath : (runtime.startingPath + "\\" + relPath));
        cout << "Running File: " << fullPath << std::endl;
        if (Utilities::isFileExisting(fullPath)){
            if (main_input == "run"){
                runtime.run(Utilities::readFile(fullPath));
            } else if (main_input == "ast"){
                runtime.ast(Utilities::readFile(fullPath));
            }
        } else {
            cout << "File not found :("<<std::endl;
            if (fullPath.find('/') != std::string::npos){
                cout << "You should use \\ instead of /";
            } else if (fullPath == relPath) {
                cout << "Check full path";
            } else {
                cout << "Check relative path. Relative starting path: " << runtime.startingPath;
            }
            
        }
    } else if (main_input == "help") {
        cout << "Help page" << endl
                  << "BranchScript from BranchScriptTerminal (v" << Version << ")" << endl
                  << "Type: ";
        cout << " - help -> Help page";
        cout << " - run *file path* -> Run File";
    } else {
    	cout<< main_input << " is not recognized as command. Please type help or visit BranchScript documentation";
    }
    cout << endl;
    return true;
}

void Terminal::ListenToCLI() {
    cout << "BranchScript v" << Version << endl;
    while(true){
    	cout << ">";
    	getline(cin, input);
    	ReplyToCLI(input);
    }
}
