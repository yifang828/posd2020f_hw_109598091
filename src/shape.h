#ifndef SHAPE_H
#define SHAPE_H
class Shape{
    public:
        virtual double area()const = 0;
        virtual double perimeter()const = 0;
        virtual std::string info() const = 0;
        virtual ~Shape(){};

        Shape(std::string id){
            _id = id;
            _color = "white";
        }
        Shape(std::string id, std::string color){
            _id = id;
            _color = color;
        } 
        std::string id() const{
            return _id;
        } 
        std::string color() const{
            return _color;
        } 
        virtual void addShape(Shape *shape){
            throw(std::string)"Only compound shape can add shape!";
        }
        virtual void deleteShapeById(std::string id){
            throw(std::string)"Only compound shape can delete shape!";
        }
        virtual Shape* getShapeById(std::string id){
            throw(std::string)"Only compound shape can get shape!";
        }
        std::string _color;
    private:
        std::string _id;
};

#endif