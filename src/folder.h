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
    
    // implement any functions inherit from Node that you think is suitable.
    double size()const{
        double result=0.0;
        for(std::list<Node *>::const_iterator i = _nodes.begin(); i != _nodes.end(); ++i){
            result += (*i)->size();
        }
        return result;
    }

    void updatePath(std::string path){
        // std::cout<<path<<std::endl;
        if(_nodes.size()==0){
            _path = path+_path;
        }
        Iterator* itr = this->createIterator();
        // std::cout<<"in update path: "+itr->currentItem()->name()<<std::endl;
        for(itr->first(); !itr->isDone(); itr->next()){
            Node* s = itr->currentItem();
            //  std::cout<<"in for: "+itr->currentItem()->name()<<std::endl;
            s->_path = path+_path;
            Iterator* innerItr = s->createIterator();
            if(!innerItr->isDone()){
                //!!
                // std::cout<<"in innr: "+itr->currentItem()->name()<<std::endl;
                updatePath(path);
            }
        }
    }

    void addNode(Node* node){
        _nodes.push_back(node);
        updatePath(route());
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