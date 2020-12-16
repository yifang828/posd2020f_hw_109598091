#pragma once
#include <regex>
#include <vector>
#include <stack>

class NodeParser {
public:
    NodeParser(std::string input) {
        scanner = new NodeScanner(input);
        nb = new NodeBuilder();
    }
    
    void parser() {
        std::regex continueToken("[\\,\\)]");
        std::vector<std::string> data; 
        while (!scanner->isDone()){
            std::string token = scanner->nextToken();
            if("(" == token){
                std::vector<std::string> appArg = getAppArg();
                if(1 == appArg.size()){
                    nb->buildApp(data.back(), std::stod(appArg.front()));
                    data.pop_back();
                }else{
                    data.pop_back();
                }
            }else if(std::regex_search(token, sm, continueToken)){
                continue;
            }else if ("{" == token){
                if(!data.empty()){
                    nb->buildFolderBegin(data.back());
                    data.pop_back();
                    folderState.push(true);
                }
            }else if ("}" == token && (folderState.size()>0 && folderState.top())){
                nb->buildFolderEnd();
                folderState.pop();
            }else{
                data.push_back(token);
            }
        } 
    }
    
    std::deque<Node*> getResult() {
        return nb->getResult();
    }
private:
    NodeScanner * scanner;
    NodeBuilder * nb;
    std::smatch sm;
    std::stack<bool> folderState;

    std::vector<std::string> getAppArg(){
        std::vector<std::string> result;
        if(!scanner->isDone()){
            std::string next = scanner->nextToken();
            while(")" != next){
                result.push_back(next);
                next = scanner->nextToken();
            }
        }
        return result;
    }
};