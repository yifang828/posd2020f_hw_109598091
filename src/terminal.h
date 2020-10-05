#include <string>
#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"

class Terminal {
public:
    Terminal(std::string input) {
        _input = input;
    }
    std::string showResult(){
        std::vector<std::vector<std::string>> splitByOpenParen;
        std::vector<std::string> splitByCloseParen;
        std::string result;
        splitByCloseParen = splitInput(_input, ')');
        for(auto x: splitByCloseParen){
            splitByOpenParen.push_back(splitInput(x, '('));
        }
        std::vector<Shape * > shapeV = genShapeV(splitByOpenParen);
        std::vector<std::string> featureNOrder = splitByOpenParen.back();
        std::cout<<featureNOrder[0]<<std::endl;

        if(featureNOrder[0] == " area inc"){
            quickSort(shapeV.begin(), shapeV.end(), areaAscendingCompare);
            result = genResult(shapeV, "area");
        }else if(featureNOrder[0] == " area dec"){
            quickSort(shapeV.begin(), shapeV.end(), areaDescendingCompare);
            result = genResult(shapeV, "area");
        }else if(featureNOrder[0] == " perimeter inc"){
            quickSort(shapeV.begin(), shapeV.end(), perimeterAscendingCompare);
            result = genResult(shapeV, "perimeter");
        }else if(featureNOrder[0] == " perimeter dec"){
            quickSort(shapeV.begin(), shapeV.end(), perimeterDescendingCompare);
            result = genResult(shapeV, "perimeter");
        }else{
            throw featureNOrder[0]+" is invalid input";
        }

        return result;
    }
private:
    std::string _input;
    
    std::vector<std::string> splitInput(std::string & input, char delimiter){
        std::vector<std::string> v;
        std::string str;
        std::istringstream iss(input);
        while (std::getline(iss, str, delimiter)){
            v.push_back(str);
        }
        return v;
    }

    std::vector<Shape * > genShapeV(std::vector<std::vector<std::string>> vectors){
        std::vector<Shape *> shapeVectors;

        for (int i = 0; i < vectors.size(); i++){
            std::string shapeType= vectors[i].front();
            if(shapeType == "Rectangle" || shapeType == " Rectangle"){
                std::vector<std::string> v = vectors[i];
                std::string widthNLength = v.back();
                std::vector<std::string> splitByComma = splitInput(widthNLength, ',');
                Shape * rectangle = new Rectangle(std::stod(splitByComma[0]), std::stod(splitByComma[1]));
                shapeVectors.push_back(rectangle);
            }else if(shapeType == "Triangle"){

            }else if(shapeType == "Ellipse"){
                std::string widthNLength = vectors[i].back();
                std::vector<std::string> splitByComma = splitInput(widthNLength, ',');
                Shape * ellipse = new Ellipse(std::stod(splitByComma[0]), std::stod(splitByComma[1]));
                shapeVectors.push_back(ellipse);
            }else{
                throw shapeType+" is invalid input";
            }
        }
        return shapeVectors;
    }
    std::string genResult(std::vector<Shape *> shapes, std::string feature){
        std::string result="";
        if(feature == "area"){
            for(int i = 0; i < shapes.size(); i++){
                if(i == (shapes.size()-1)){
                    result = result + std::to_string(shapes[i]->area());
                }else{
                    result = result + std::to_string(shapes[i]->area())+"\n";
                } 
            }
        }else if (feature == "perimeter"){
            for(int i = 0; i < shapes.size(); i++){
                if(i == (shapes.size()-1)){
                    result = result + std::to_string(shapes[i]->perimeter());
                }else{
                    result = result + std::to_string(shapes[i]->perimeter())+"\n";
                }
            }
        }else{
            throw feature+" is invalid input";
        }

        return result;
    }
};
