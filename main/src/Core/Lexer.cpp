#include "Lexer.h"
#include "../Utilities/Utilities.h"

std::map<std::string, tokenParent> Lexer::KEYWORDS = {
	{},
    {"var", var},
    {"=", equals},
    {">", condition},
    {"<", condition},
    {"<=", condition},
    {">=", condition},
    {"==", condition},
    {"!", negation},
    {"enum", _enum},
    {"struct", _struct},
    {"class", _class},
    {"include", include},
    {"as", as},
    {"function", _function},
    {"return", returnExpr},
    {"lastreturn", returnExpr},
    {"addreturn", returnExpr},
    {"macroreturn", returnExpr},
    {"extends", extends},
    {"event", _event},
    {"macro", _macro},
    {"public", modifier},
    {"private", modifier},
    {"living", modifier},
    {"instant", modifier},
    {"async", modifier},
    {"const", modifier},
    {"complex", modifier},
    {"int", dataClass},
    {"float", dataClass},
    {"string", dataClass},
    {"bool", dataClass},
};

tokenParentElem::tokenParentElem(tokenParent t, std::string s, std::string v){
	token = t;
	subclass = s;
	value = v;
}

tokenizeLineOutput::tokenizeLineOutput(int a, std::vector<tokenParentElem> t){
	additive = a;
	tokens = t;
}

tokenParentElem Lexer::Token(tokenParent token, std::string subclass, std::string value){
	return tokenParentElem{token, subclass, value};
}

std::vector<std::vector<tokenParentElem>> Lexer::tokenizeMultiLine(const std::vector<std::string>& file){
	std::vector<std::vector<tokenParentElem>> multiLineOutput;
	for (int i=0; i<file.size(); i++){
		tokenizeLineOutput singleLineOutput = tokenizeSingleLine(i, file);
		i = i+singleLineOutput.additive;
		multiLineOutput.push_back(singleLineOutput.tokens);
	}
	multiLineOutput.push_back({Token(_EOF, "", "")});
	return multiLineOutput;
}

tokenizeLineOutput Lexer::tokenizeSingleLine(int index, const std::vector<std::string>& file){ //bello
	int startingIndex = index;
    std::string currentLine = file[index];
    std::vector<tokenParentElem> lineTokens;
    
    while (currentLine.size() > 0) {
    	char curCh = currentLine.front();
        if (curCh == '(') {
            lineTokens.push_back(Token(openParen, "(", "("));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == ')') {
            lineTokens.push_back(Token(closeParen, ")", ")"));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '{') {
            lineTokens.push_back(Token(openBrac, "{", "{"));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '}') {
            lineTokens.push_back(Token(closeBrac, "}", "}"));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '[') {
            lineTokens.push_back(Token(openSq, "[", "["));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == ']') {
            lineTokens.push_back(Token(closeSq, "]", "]"));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == ',') {
            lineTokens.push_back(Token(comma, ",", ","));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '.') {
            lineTokens.push_back(Token(dot, ".", "."));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '+' || curCh == '-' || curCh == '*' || curCh == '/'){
            lineTokens.push_back(Token(closeParen, std::string(1, curCh), std::string(1, curCh)));
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '='){
        	if (currentLine[1] == '='){
        		lineTokens.push_back(Token(condition, "==", "=="));
        		currentLine.erase(currentLine.begin());
        	} else {
            	lineTokens.push_back(Token(equals, "=", "="));
        	}
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '>' || curCh == '<'){
        	if (currentLine[1] == '='){
        		if (curCh == '>'){
        			lineTokens.push_back(Token(condition, ">=", ">="));
        		} else if (curCh == '<'){
        			lineTokens.push_back(Token(condition, "<=", "<="));
        		}
        		currentLine.erase(currentLine.begin());
        	} else {
        		if (curCh == '>'){
        			lineTokens.push_back(Token(condition, ">", ">"));
        		} else if (curCh == '<'){
        			lineTokens.push_back(Token(condition, "<", "<"));
        		}
        	}
        	currentLine.erase(currentLine.begin());
        } else if (curCh == '\\' && currentLine.size() == 1){
        	index++;
			std::string nextLine = file[index];
			currentLine.erase(currentLine.begin());
			currentLine.insert(currentLine.end(), nextLine.begin(), nextLine.end());
        } else {
        	bool skip = false;
        	if ((Utilities::isDigit(std::string(1, curCh)) || curCh == '.') && !skip){
        		skip = true;
        		bool canBeDot = true;
        		if (curCh=='.'){
        			canBeDot = false;
        		}
        		std::string num = "";
        		std::string tempcurline = currentLine;
        		while (tempcurline.size()>0 && (Utilities::isDigit(std::string(1, tempcurline.front())) || tempcurline.front() == '.')){
        			if (tempcurline.front() == '.'){
        				if (canBeDot){
        					canBeDot = false;
        				} else {
        					skip = false;
        					break;
        				}
        			}
        			//std::cout<<"Char: "<<tempcurline.front()<<"\n";
        			num += std::string(1, tempcurline.front());
        			tempcurline.erase(tempcurline.begin());
        		}
        		if (skip == true){
        			lineTokens.push_back(Token(dataValue, (canBeDot ? "int" : "float"), num));
        			currentLine = tempcurline;
        		}
        		//std::cout<<"New one \n";
        	}
        	if (Utilities::isAlphaNum(std::string(1, curCh)) && !skip){
        		skip = true;
        		std::string an = "";
        		bool isFirst = true;
        		while (currentLine.size()>0 
        			&& (Utilities::isAlphaNum(std::string(1, currentLine.front())) 
        				|| (isFirst ? false : (
        					Utilities::isDigit(std::string(1, currentLine.front())) || currentLine.front() == '_'
        					)
        				)
        			)
        				) {
        			isFirst = false;
        			an += std::string(1, currentLine.front());
        			currentLine.erase(currentLine.begin());
        		}
        		auto tp = KEYWORDS[an];
        		if (tp!=0){ //found
        			if (tp!=dataClass){
        				lineTokens.push_back(Token(tp, "", an));
        			} else if (tp == modifier){
        				lineTokens.push_back(Token(tp, an, an));
        			} else if (tp == dataClass){
						lineTokens.push_back(Token(tp, an, an));
        			} else {}
        		} else {
        			lineTokens.push_back(Token(other, "", an));
        		}
        	}
			if (curCh == '"' && !skip) {
			    skip = true;
			    bool success = false;
			    std::string str;
			    currentLine.erase(currentLine.begin()); // Rimuovi l'apertura del " carattere
			    
			    while (currentLine.size() > 0) {

			        // Controlla se è un backslash di escape
			        if (currentLine.front() == '\\') {
			            currentLine.erase(currentLine.begin()); // Rimuovi il backslash
			            
			            if (currentLine.size() > 0) {
			                char nextCh = currentLine.front();
			                switch (nextCh) {
			                    case '\\': str += '\\'; break;
			                    case '"': str += '"'; break;
			                    // Gestione di altri caratteri di escape (es. \t, \n, etc.)
			                    case 't': str += '\t'; break;
			                    case 'n': str += '\n'; break;
			                    // Altri casi specifici possono essere aggiunti qui
			                    default:
			                        // Se non è uno specifico carattere di escape, aggiungilo direttamente
			                        str += '\\';
			                        str += nextCh;
			                        break;
			                }
			                currentLine.erase(currentLine.begin()); // Rimuovi il carattere gestito
			            } else {
			            	index++;
			            	if (index+1 >= file.size()){ // Stringa non chiusa
			            		success = true;
			            		break;
			            	} else {
			            		std::string nextLine = file[index];
			            		currentLine.insert(currentLine.end(), nextLine.begin(), nextLine.end());
			            	}
			            }
			        } else if (currentLine.front() == '"') {
			            // Se trova una virgoletta doppia senza backslash, la stringa è terminata
			            currentLine.erase(currentLine.begin()); // Rimuovi la chiusura del " carattere
			            success = true;
			            break;
			        } else {
			            // Aggiungi il carattere normale alla stringa
			            str += currentLine.front();
			            currentLine.erase(currentLine.begin());
			            if (currentLine.size() <= 0) {
			            	index++;
			            	if (index+1 >= file.size()){ // Stringa non chiusa
			            		success = true;
			            		break;
			            	} else {
			            		std::string nextLine = file[index];
			            		currentLine.insert(currentLine.end(), nextLine.begin(), nextLine.end());
			            	}
			            }
			        }
			    }
			    // Aggiungi il token con il tipo dataValue e la stringa acquisita
			    lineTokens.push_back(Token(dataValue, "string", str));
			}
        	if (Utilities::isSkippable(std::string(1, curCh)) && !skip){
        		skip = true;
        		currentLine.erase(currentLine.begin());
        	}
        	if (!skip){
        		std::cout<<"Non recognized token: "<<curCh;
        		currentLine.erase(currentLine.begin());
        	}
        }
        curCh = currentLine.front();
    }
    
    return {(index-startingIndex), lineTokens};
}