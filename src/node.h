#ifndef NODE_H
#define NODE_H
#include <string>
#include "iterator.h"

class Node {
public:
    Node(std::string id, std::string name, double size):_id(id), _name(name), _size(size){}

    std::string id() const;

    std::string name() const;
    
    virtual std::string route() const; // the "virtual" of this funtion is optional.

    virtual double size() const;

    virtual void updatePath(std::string path);
    
    virtual void addNode(Node* node);
    
    virtual Node* getNodeById(std::string id) const;
    
    virtual void deleteNodeById(std::string id);

    virtual Iterator* createIterator() const;

    virtual ~Node(){};
    std::string _path;
private:
    std::string _id, _name;
    double _size=0.0;
};
#endif