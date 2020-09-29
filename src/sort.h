#include "shape.h"

template <class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator first, RandomAccessIterator last, Compare compare){
    if (std::distance(first, last)>1){
        RandomAccessIterator bound = _partition(first, last, compare);
        quickSort(first, bound, compare);
        quickSort(bound+1, last, compare);
    }
};
template <class RandomAccessIterator, class Compare>
RandomAccessIterator _partition(RandomAccessIterator first, RandomAccessIterator last, Compare compare){
    auto pivot = std::prev(last, 1);
    auto i = first;
    for (auto j = first; j != pivot; ++j){
        if (compare(*j, *pivot)){
            std::swap(*i++, *j);
        }
    }
    std::swap(*i, *pivot);
    return i;
};
// class Sort {
//   public:
    // template <class RandomAccessIterator, class Compare>
    // void quickSort(RandomAccessIterator first, RandomAccessIterator last, Compare compare){
    //     if (std::distance(first, last)>1){
    //         RandomAccessIterator bound = partition(first, last, compare);
    //         quickSort(first, bound, compare);
    //         quickSort(bound+1, last, compare);
    //     }
    // }
    

//   private:
//     template <class RandomAccessIterator, class Compare>
//     RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last, Compare compare){
//         auto pivot = std::prev(last, 1);
//         auto i = first;
//         for (auto j = first; j != pivot; ++j){
//             if (compare(*j, *pivot)){
//                 std::swap(*i++, *j);
//             }
//         }
//         std::swap(*i, *pivot);
//         return i;
//     }
// };
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
