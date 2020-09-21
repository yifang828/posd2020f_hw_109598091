#define _USE_MATH_DEFINES
#include "shape.h"
#include <cmath>

class Ellipse: public Shape {
public:
  Ellipse(double semiMajorAxes, double semiMinorAxes){
    if(semiMajorAxes <= 0 || semiMinorAxes <= 0)
        throw ellipseErrorMsg;
    else{
        _originMj = semiMajorAxes;
        _originMn = semiMinorAxes;
        if(semiMajorAxes != semiMinorAxes){
            if(semiMinorAxes < semiMajorAxes){
                _semiMajorAxes = semiMajorAxes;
                _semiMinorAxes = semiMinorAxes;
            }else{
                _semiMinorAxes = semiMajorAxes;
                _semiMajorAxes = semiMinorAxes;
            }
        }else{
            _semiMajorAxes = semiMajorAxes;
            _semiMinorAxes = semiMinorAxes;
        }
    }
  }

  double area() const{
      double result = M_PI * _semiMajorAxes * _semiMinorAxes;
      return round(result, 3);
  }

  double perimeter() const{
      double result = 2*M_PI*_semiMinorAxes+4*(_semiMajorAxes-_semiMinorAxes);
      return round(result, 3);
  }

  std::string info() const{
      std::stringstream semiMjStream;
      semiMjStream<<std::fixed<<std::setprecision(3)<<_originMj;
      std::stringstream semiMnStream;
      semiMnStream<<std::fixed<<std::setprecision(3)<<_originMn;
      return "Ellipse ("+ semiMjStream.str() + ", " + semiMnStream.str()+")";
  }

private:
  double _semiMajorAxes, _semiMinorAxes, _originMj, _originMn;
  const std::string ellipseErrorMsg = "This is not a ellipse!";

  double round(double x, int n) const{
      return floor(x*pow(10, n)+0.5)/pow(10, 3);
  }
};