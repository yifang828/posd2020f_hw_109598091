#include "shape.h"

template <class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator begin, RandomAccessIterator end, Compare compare){
    if (std::distance(begin, end)>1){
        RandomAccessIterator bound = _partition(begin, end, compare);
        quickSort(begin, bound, compare);
        quickSort(bound+1, end, compare);
    }
};
template <class RandomAccessIterator, class Compare>
RandomAccessIterator _partition(RandomAccessIterator begin, RandomAccessIterator end, Compare compare){
    auto p = std::prev(end, 1);
    auto i = begin;
    for (auto j = begin; j != p; j++){
        if (compare(*j, *p)){
            std::swap(*i++, *j);
        }
    }
    std::swap(*i, *p);
    return i;
};
bool areaAscendingCompare(Shape *a, Shape *b) {
    return a->area() < b->area();
};

bool areaDescendingCompare(Shape *a, Shape *b) {
    return (a->area() > b->area());
};

bool perimeterAscendingCompare(Shape *a, Shape *b) {
    return a->perimeter() < b->perimeter();
};

bool perimeterDescendingCompare(Shape *a, Shape *b) {
    return a->perimeter() > b->perimeter();
};

class AscendingCompare{
  public:
    AscendingCompare(std::string feature): _feature(feature) {}
    bool operator()(Shape * a, Shape * b){
        if(_feature == "area"){
            return a->area() < b->area();
        }else if(_feature == "perimeter"){
            return a->perimeter() < b->perimeter();
        }else{
            throw "wrong parameter";
        }
    }
  private:
    std::string _feature;
};

class DescendingCompare{
  public:
    DescendingCompare(std::string feature): _feature(feature) {}
    bool operator()(Shape * a, Shape * b){
        if(_feature == "area"){
            return a->area() > b->area();
        }else if(_feature == "perimeter"){
            return a->perimeter() > b->perimeter();
        }else{
            throw "wrong parameter";
        }
    }
  private:
    std::string _feature;
};
