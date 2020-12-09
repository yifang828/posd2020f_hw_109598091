#ifndef NODE_PARSER_H
#define NODE_PARSER_H
class NodeParser {
public:
    NodeParser(std::string input) {
        scanner = new NodeScanner(input);
        nb = new NodeBuilder();
    }
    
    void parser() {
        // using NodeScanner::nextToken() to get all information to determine what to build,
        // and provide the argument the node needed.
        // use functions in NodeBuilder to build out the node.
        // the node with invalid argument should be ignored.
    }
    
    std::deque<Node*> getResult() {
        // return result.
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