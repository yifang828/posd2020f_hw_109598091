#ifndef NODE_PARSER_H
#define NODE_PARSER_H
class NodeParser {
public:
    NodeParser(std::string input) {
        scanner = new NodeScanner(input);
        nb = new NodeBuilder();
    }
    
    void parser() {
        std::string token;
        token = scanner->nextToken();
        do{
            if(token!=""){
                std::vector<double>values = getValue();
                if(values.size()==2){
                    nb->buildApp(values[0], values[1]);
                }
            }
            // else if ("CompoundShape" == token){
            //     nb->buildCompoundShapeBegin();
            // }
            // else if ("}" == token){
            //     nb->buildCompoundShapeEnd();
            // }
            // try {
            //     token = scanner->nextToken();
            // }
            // catch(const std::string e) {
            //     if(e == "next token doesn't exist."){
            //         return;
            //     }
            // }
        } while ("" != token);
    }
    
    std::deque<Node*> getResult() {
        return nb->getResult();
    }
private:
    NodeScanner * scanner;
    NodeBuilder * nb;

    std::vector<double> getValue(){
        std::vector<double> result;
        std::string token = scanner->nextToken();
        do{
            if("(" == token || "," == token){
                result.push_back(std::stod(scanner->nextToken()));
            }
            token = scanner->nextToken();
        }while(")" != token);
        return result;
    }
};
#endif