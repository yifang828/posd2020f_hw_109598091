#include "shape.h"

Shape * getShapeById(Shape* shape, std::string id){
    Iterator* itr = shape->createIterator();
    try{
        for(itr->first(); !itr->isDone(); itr->next()){
            Shape* s = itr->currentItem();
            if(s->id()==id){
                return s;
            }
            try{
                Shape* ss = s->createIterator()->currentItem();
                getShapeById(ss, id);
            }catch(std::string e){}
        }
    }catch(std::string e){
        throw (std::string) "Only compound shape can get shape!";
    }
    if(itr->isDone()){
        throw (std::string) "Expected get shape but shape not found";
    }
}