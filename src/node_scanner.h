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
        // std::regex validChar("[A-Za-z0-9]");

        for(int i = 0; i<_input.length(); ++i){
            char now = _input.at(i);
            // std::cout<<"now: "<<now<<std::endl;
            if(' ' == now||'!'==now||'@'==now||'#'==now||'$'==now||'%'==now||'^'==now||'&'==now||\
                '*'==now||'+'==now||'_'==now||'?'==now||'~'==now||'<'==now||'>'==now||'/'==now||\
                '-'==now||'='==now||'['==now||']'==now||'|'==now){
                continue;
            }else if('(' == now || ')' == now || ',' == now\
                || '{' == now || '}' ==  now){
                if(!str.empty()){
                    _resultVector.push_back(str);
                    str.clear();
                }
                str.push_back(now);
                _resultVector.push_back(str);
                str.clear();
            }else {
                str+=now;
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

private:
    std::string _input;
    std::vector<std::string> _resultVector;
};
#endif