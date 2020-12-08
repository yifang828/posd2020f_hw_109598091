#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H

#include "node.h"
#include "iterator.h"

template<class ForwardIterator>
class NodeIterator : public Iterator{
public:
    NodeIterator (ForwardIterator begin, ForwardIterator end){
        _begin = begin;
        _end = end;
        first();
    }
    void first(){
        _current = _begin;
    }
    void next(){
        if(isDone()){
            throw(std::string)"Moving past the end!";
        }else{
            _current ++;
        }
    }
    bool isDone() const {
        return _current == _end;
    }
    Node * currentItem() const{
        return * _current;
    }

private:
    ForwardIterator _begin, _end, _current;
};
#endif
