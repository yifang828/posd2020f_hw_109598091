#include "shape.h"

Shape * getShapeById(Shape* shape, std::string id){
    Iterator* itr = shape->createIterator();
    if(itr->isDone()){
        throw (std::string) "Only compound shape can get shape!";
    }
    for(itr->first(); !itr->isDone(); itr->next()){
        Shape* s = itr->currentItem();
        if(s->id()==id){
            return s;
        }
        Iterator* innerItr = s->createIterator();
        if(!innerItr->isDone()){
            Shape* ss = itr->currentItem();
            //!!
            Shape* result = getShapeById(ss, id);
            if(result)
                return result;
        }
    }
    if(itr->isDone()){
        throw (std::string) "Expected get shape but shape not found";
    }
    return nullptr;
}