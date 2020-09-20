#include "Shape.h"
#include <string.h>
#include <cmath>

class Rectangle: public Shape {
public:
  Rectangle(double length, double width){
    if(length<=0 || width<=0)
        throw rectangleErrorMsg; 
    else
    {
        _length = length;
        _width = width;
    }   
  }
  double area() const{
      return round(_length * _width, 3);
  }
  double perimeter() const{
      return round(_length*2 + _width*2, 3);
  }
  std::string info() const{
      std::stringstream roundedlength;
      roundedlength<<std::fixed<<std::setprecision(3)<<_length;
      std::stringstream roundedwidth;
      roundedwidth<<std::fixed<<std::setprecision(3)<<_width;
      return "Rectangle (" + roundedlength.str() + ", " + roundedwidth.str() + ")";//到小數點第三位
  }

private:
    double _length, _width;
    const std::string rectangleErrorMsg = "This is not a rectangle!";
    double round(double x, int n) const{
      return floor(x*pow(10, n)+0.5)/pow(10, 3);
  }
};