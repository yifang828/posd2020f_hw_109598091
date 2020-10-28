#ifndef APP_H
#define APP_H

#include "node.h"
#include <string>

// class APP : public Node {
// public:
//     App(std::string id, std::string name, double size):Node(id, name, size) {
//     }
// private:
// };
class App : public Node {
public:
    App(std::string id, std::string name, double size):Node::Node(id, name, size) {}
    
    // implement any functions inherit from Node that you think is suitable.

    void updatePath(std::string path){
        _path = path;
    }
};

#endif