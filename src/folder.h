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
        Iterator * itr = createIterator();
        for(itr->first(); !itr->isDone(); itr->next()){
            Node * node = itr->currentItem();
            if(node->id()==id){
                std::cout<<"find node: "+ id <<std::endl;
                return node;
            }
            Iterator * innerItr = node->createIterator();
            if(!innerItr->isDone()){
                Node * result = node->getNodeById(id);
                if(result){
                    return result;
                }
            }
        }if(itr->isDone()){
            throw(std::string)"Expected get node but node not found."; 
        }
    }

     void deleteNodeById(std::string id) {
        int beginSize = size();//after delete, size will be different
        Iterator * itr = createIterator();
        for(itr->first(); !itr->isDone(); itr->next()){
            Node * n = itr->currentItem();
            if(n->id() == id){
                _nodes.remove(n);
                return;
            }
            Iterator * innerItr = n->createIterator();
            if(!innerItr->isDone()){
                n->deleteNodeById(id);
                int endSize = size();
                if(beginSize != endSize){
                    return;
                }
            }
        }
        if(itr->isDone()){
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