#include "shape.h"
#include <deque>

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
            //!!
            Shape* result = getShapeById(s, id);
            if(result)
                return result;
        }
    }
    if(itr->isDone()){
        throw (std::string) "Expected get shape but shape not found";
    }
    return nullptr;
}

template<class Filter>
std::deque<Shape*> filterShape(Shape* shape, Filter filter){
    Iterator* itr = shape->createIterator();
    if(itr->isDone()){
        throw(std::string)"Only compound shape can filter shape!";
    }
    std::deque<Shape*> result;//cannot recursive solution
    for(itr->first(); !itr->isDone(); itr->next()){
        Shape * s = itr->currentItem();
        std::cout<<"id:"+s->id()<<std::endl;
        // std::cout<<"area:"+std::to_string(s->area())<<std::endl;
        if(filter(s)){
            std::cout<<"in filter"<<std::endl;
            result.push_back(s);
        }
        Iterator * innerItr = s->createIterator();
        if(!innerItr->isDone()){
            std::cout<<"is compound shape, id:"+s->id()<<std::endl;
            // filterShape(s, filter);
            filterInnerShape(innerItr, filter, &result);
        }
    }
    std::cout<<"finish"<<std::endl;
    return result;
}

template<class Filter>
void filterInnerShape(Iterator * itr, Filter filter, std::deque<Shape*> *result){
    for(itr->first(); !itr->isDone(); itr->next()){
        Shape * s = itr->currentItem();
        std::cout<<"Inner, id:"+s->id()<<std::endl;
        // std::cout<<"Inner, area:"+std::to_string(s->area())<<std::endl;
        if(filter(s)){
            std::cout<<"Inner, in filter"<<std::endl;
            result->push_back(s);
        }
        Iterator * innerItr = s->createIterator();
        if(!innerItr->isDone()){
            std::cout<<"Inner, is compound shape, id:"+s->id()<<std::endl;
            filterInnerShape(innerItr, filter, result);
        }
    }
}

class AreaFilter {
public:
    AreaFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound){}
    bool operator()(Shape* shape) const {
        std::cout<<"Area filter, is compound shape, id:"+shape->id()<<std::endl;
        std::cout<<"Area filter, is compound shape, area:"+std::to_string(shape->area())<<std::endl;
        return (shape->area() <= _upperBound && shape->area() >= _lowerBound);
    }
private:
    double _upperBound=0.0, _lowerBound=0.0;
};

class PerimeterFilter{
public:
    PerimeterFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound){}
    bool operator()(Shape* shape) const {
        std::cout<<"Perimeter filter, is compound shape, id:"+shape->id()<<std::endl;
        std::cout<<"Perimeter filter, is compound shape, perimeter:"+std::to_string(shape->perimeter())<<std::endl;
        return (shape->perimeter() <= _upperBound && shape->perimeter() >= _lowerBound);
    }
private:
    double _upperBound=0.0, _lowerBound=0.0;
};

class ColorFilter{
public:
    ColorFilter(std::string color):_color(color){}
    bool operator()(Shape* shape) const{
        std::cout<<"Color filter, is compound shape, id:"+shape->id()<<std::endl;
        std::cout<<"Color filter, is compound shape, color:"+shape->color()<<std::endl;
        return (shape->color() == _color);
    }
private:
    std::string _color;
};

class TypeFilter{
public:
    TypeFilter(std::string t):_t(t){}
    bool operator()(Shape* shape)const{
        std::cout<<"Type filter, is compound shape, id:"+shape->id()<<std::endl;
        std::cout<<"Type filter, is compound shape, type:"+shape->type()<<std::endl;
        return (shape->type() == _t);
    }
private:
    std::string _t;
};