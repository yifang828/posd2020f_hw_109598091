#ifndef COMPOUNDSHAPE_H
#define COMPOUNDSHAPE_H
#include "shape.h"

class CompoundShape : public Shape {
public:
    CompoundShape(std::string id, std::vector<Shape*>* shapes):Shape(id) {
        _shape = *shapes;
        _color = "transparent";
        if(_shape.size()==0){
            throw(std::string) "This is not a compound shape!";
        }
    }

    double area() const {
        double result;
        for(std::vector<Shape *>::const_iterator i = _shape.begin(); i!= _shape.end(); ++i){
            result += (*i)->area();
        }
        return result;
    }

    double perimeter() const { 
        double result;
        for(std::vector<Shape *>::const_iterator i = _shape.begin(); i!= _shape.end(); ++i){
            result += (*i)->perimeter();
        }
        return result;
    }

    void addShape(Shape* shape) {
        _shape.push_back(shape);
    }
    
    void deleteShapeById(std::string id) {
        try{
            Shape * shapePtr = getShapeById(id);
            for(std::vector<Shape *>::const_iterator i = _shape.begin(); i < _shape.end(); ++i){
                if((*i)->_color == "transparent"){
                    (*i)->deleteShapeById(id);
                }else{
                    if((*i)->id()==id){
                        _shape.erase(i);
                    }
                }
            }
        }catch(std::string e){
            throw(std::string)"Expected delete shape but shape not found";
        }
    }

    std::string info() const {
        std::string result;
        for(std::vector<Shape *>::const_iterator i = _shape.begin(); i < _shape.end(); ++i){
            if(i==_shape.begin()){
                result += (*i) ->info();
            }else{
                result += ", "+ (*i)->info();
            }
        }
        return "Compound Shape {" + result + "}";
    }
    
    Shape* getShapeById(std::string id) {
        Shape * result;
        for(std::vector<Shape *>::const_iterator i = _shape.begin(); i < _shape.end(); ++i){
            if((*i)->_color == "transparent"){
                result = (*i)->getShapeById(id);
                return result;
            }else{
                if((*i)->id()==id){
                    return result = (*i);
                }
            }
        }
        throw(std::string)"Expected get shape but shape not found";
    }

    std::vector<Shape*> _shape;
private:
};
#endif