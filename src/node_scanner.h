#ifndef NODE_SCANNER_H
#define NODE_SCANNER_H
#include <string>
#include <vector>
#include <iostream>
#include <regex>

class NodeScanner {
public:
    NodeScanner(std::string input) {
        _input = input;
        std::string str = "";
        std::cout<<_input<<std::endl;
        std::regex validChar("[A-Za-z0-9\\.\\(\\)\\,\\{\\}]");
        std::regex validToken("[\\(\\)\\,\\{\\}]");
        std::smatch sm;

        for(int i = 0; i<_input.length(); ++i){
            char now = _input.at(i);
            std::string s = std::string(1, now);
            if(!std::regex_search(s, sm, validChar)){
                continue;
            }else if(std::regex_search(s, sm, validToken)){
                if(!str.empty()){
                    _resultVector.push_back(str);
                    str.clear();
                }
                str+=s;
                _resultVector.push_back(str);
                str.clear();
            }else {
                str+=s;
            }
        }
    }
    std::string nextToken() {
        if(!_resultVector.empty()){
            std::string result;
            result = _resultVector.front();
            _resultVector.erase(_resultVector.begin());
            return result;
        }else{
            throw (std::string)"next token doesn't exist.";
        }
    }
    bool isDone(){
        return _resultVector.empty();
    }

private:
    std::string _input;
    std::vector<std::string> _resultVector;
};
#endif