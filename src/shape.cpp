#include "shape.h"

Shape::Shape(std::string id){
    _id = id;
    _color = "white";
}// interface for default color "white".
Shape::Shape(std::string id, std::string color){
    _id = id;
    _color = color;
}
