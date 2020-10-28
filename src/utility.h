#include "node.h"
#include <deque>

template<class Filter>
std::deque<Node*> filterNode(Node* node, Filter filter) {
    // access the node with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the nodes under the input node tree sturctur that match the given filter.
    // throw std::string "Only folder can filter node!" when the input node is not iterable.
    Iterator* itr = node->createIterator();
    if(itr->isDone()){
        throw(std::string)"Only folder can filter node!";
    }
    std::deque<Node*> result = {};
    for(itr->first(); !itr->isDone(); itr->next()){
        Node * s = itr->currentItem();
        std::deque<Node*> recurResult;
        if(filter(s)){
            std::cout<<"in if: "+s->name()<<std::endl;
            result.push_back(s);
        }
        Iterator * innerItr = s->createIterator();
        if(!innerItr->isDone()){
            // std::deque<Node*> r_s =filterNode(s, filter);
            // if(r_s.size()!=0){
            //     for(std::deque<Node*>::iterator i = r_s.begin(); i!= r_s.end(); ++i){
            //         result.push_back((*i));
            //     }
            // }
            // return result;
            filterInnerNode(innerItr, filter, &result);
        }
    }
    return result;
}
template<class Filter>
void filterInnerNode(Iterator * itr, Filter filter, std::deque<Node*> *result){
    for(itr->first(); !itr->isDone(); itr->next()){
        Node * s = itr->currentItem();
        if(filter(s)){
            result->push_back(s);
        }
        Iterator * innerItr = s->createIterator();
        if(!innerItr->isDone()){
            filterInnerNode(innerItr, filter, result);
        }
    }
}
class SizeFilter {
public:
    SizeFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound){}
    bool operator() (Node* node) const {
        return (node->size() <= _upperBound && node->size() >= _lowerBound);
    }
private:
    double _upperBound=0.0, _lowerBound=0.0;

};
