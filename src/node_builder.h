#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H
#include "folder.h"
#include "app.h"
#include "node.h"
#include <deque>
#include <stack>


class NodeBuilder {
public:
    void buildApp(std::string name, double size) {
        // build a app with an unique id and push in a std::stack.
        Node * app = new App(std::to_string(_pushdown.size()), name, size);
        _pushdown.push(app);
    }
    
    void buildFolderBegin(std::string name) {
        // notify begin of folder.
        Node * n = new Folder(std::to_string(_pushdown.size()), name);
        _pushdown.push(n);
        _state.push(false);

    }
    
    void buildFolderEnd() {
        // notify end of folder.
        std::deque<Node*> deque;
        while (!dynamic_cast<Folder*>(_pushdown.top()) || (dynamic_cast<Folder*>(_pushdown.top()) && \
            _state.top())){
            deque.push_front(_pushdown.top());
            if(dynamic_cast<Folder*>(_pushdown.top())&&_state.top()){
                _state.pop();
            }
            _pushdown.pop();
        }
        for(std::deque<Node*>::iterator itr = deque.begin(); itr != deque.end(); itr++){
            _pushdown.top()->addNode(*itr);
        }
        _state.top()=true;
    }

    std::deque<Node*> getResult() {
        std::deque<Node *> result;
        while (!_pushdown.empty())
        {
            result.push_back(_pushdown.top());
            _pushdown.pop();
        }
        return std::deque<Node*>(result.rbegin(), result.rend());
    }
private:
    std::stack<Node*> _pushdown;
    std::stack<bool> _state;
};
#endif