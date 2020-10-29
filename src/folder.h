#ifndef FOLDER_H
#define FOLDER_H
#include "node.h"
#include <list>
#include <string>
#include "iterator.h"
#include "node_iterator.h"

class Folder : public Node {
public:
    Folder(std::string id, std::string name):Node::Node(id, name, 0.0) {} // the default size of folder is zero.
    
    double size()const{
        double result=0.0;
        for(std::list<Node *>::const_iterator i = _nodes.begin(); i != _nodes.end(); ++i){
            result += (*i)->size();
        }
        return result;
    }

    void addNode(Node* node){
        _nodes.push_back(node);
        node->updatePath(route());//whose route() favorite or chrome?
    }

    Node* getNodeById(std::string id) const{
        Node * result;
        for(std::list<Node *>::const_iterator i = _nodes.begin(); i != _nodes.end(); ++i){
            try{
                if((*i)->id()!=id){
                    result = (*i)->getNodeById(id);
                    return result;
                }else{
                    if((*i)->id()==id){
                        return result = (*i);
                    }
                }
            }catch(std::string e){

            }
        }
        throw(std::string)"Expected get node but node not found.";
    }

     void deleteNodeById(std::string id) {
        try{
            Node * shapePtr = getNodeById(id);
            for(std::list<Node *>::iterator i = _nodes.begin(); i != _nodes.end(); ++i){
                try{
                    if((*i)->id()==id){
                        _nodes.erase(i);
                        break;
                    }
                    else if((*i)->id()!=id){
                        (*i)->deleteNodeById(id);
                    }
                }catch(std::string e){
                }
            }
        }catch(std::string e){
            throw(std::string)"Expected delete node but node not found.";
        }
    }

    Iterator * createIterator() const {
        return new NodeIterator<std::list<Node*>::const_iterator>(_nodes.begin(), _nodes.end());
    }

private:
    std::list<Node*> _nodes;
};
#endif