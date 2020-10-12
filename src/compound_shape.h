#ifndef COMPOUNDSHAPE_H
#define COMPOUNDSHAPE_H
#include "shape.h"

class CompoundShape : public Shape {
public:
    CompoundShape(std::string id, std::vector<Shape*>* shapes):Shape(id) {
        _shape = *shapes;
        for(Shape * shapePtr : _shape){
            if(shapePtr->color()=="white"){
                shapePtr->_color="transparent";
            }
        }
        if(_shape.size()==0){
            throw(std::string) "This is not a compound shape!";
        }
    }

    double area() const {
        double result;
        for(Shape * shapePtr : _shape){
            result += shapePtr->area();
        }
        return result;
    }

    double perimeter() const { 
        double result;
        for(Shape * shapePtr : _shape){
            result += shapePtr->perimeter();
        }
        return result;
    }

    std::string info() const {
        std::string result;
        for(std::vector<Shape *>::const_iterator i = _shape.begin(); i != _shape.end(); ++i){
            if(i==_shape.begin()){
                result += (*i) ->info();
            }else{
                result += ", "+ (*i)->info();
            }
        }
        return "Compound Shape {" + result + "}";
    }
    
    void addShape(Shape* shape) {
        _shape.push_back(shape);
    }
    
    void deleteShapeById(std::string id) {
        // search and delete a shape through id,
        try{
            Shape * shapePtr = getShapeById(id);
            if(shapePtr){
                std::vector<Shape *>::iterator itr = std::find(_shape.begin(), _shape.end(), shapePtr);
                _shape.erase(itr);
            }else{
                throw(std::string)"Expected delete shape but shape not found";
            }
        }catch(std::string e){
            throw(std::string)"Expected delete shape but shape not found";
        }
        // search all the containing shapes and the tree structure below,
    }
    
    Shape* getShapeById(std::string id) {
        // search all the containing shapes and the tree structure below,
        Shape * result;
        int num =0;
        for(Shape * shapePtr: _shape){
            if(shapePtr->id()==id){
                result = shapePtr;
                num++;
            }
        }
        if(num==0){
            throw(std::string)"Expected get shape but shape not found";
        }
        return result;
    }

    std::vector<Shape*> _shape;
private:
};
#endif