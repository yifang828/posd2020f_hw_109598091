#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <regex>
#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "sort.h"
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
        std::vector<std::string> featureNOrder = splitByOpenParen.back();
        splitByOpenParen.pop_back();
        std::vector<Shape * > shapeV = genShapeV(splitByOpenParen);
        if(shapeV.size() == 0){
            throw (std::string)"invalid input";
        }

        std::regex areaIncReg("^\\s*area\\s+inc\\s*$");
        std::regex areaDecReg("^\\s*area\\s+dec\\s*$");
        std::regex perimeterIncReg("^\\s*perimeter\\s+inc\\s*$");
        std::regex perimeterDecReg("^\\s*perimeter\\s+dec\\s*$");
        std::smatch m;
        std::ssub_match ssm;

        if(regex_match(featureNOrder[0], m, areaIncReg)){
            quickSort(shapeV.begin(), shapeV.end(), areaAscendingCompare);
            result = genResult(shapeV, "area");
        }else if(regex_match(featureNOrder[0], m, areaDecReg)){
            quickSort(shapeV.begin(), shapeV.end(), areaDescendingCompare);
            result = genResult(shapeV, "area");
        }else if(regex_match(featureNOrder[0], m, perimeterIncReg)){
            quickSort(shapeV.begin(), shapeV.end(), perimeterAscendingCompare);
            result = genResult(shapeV, "perimeter");
        }else if(regex_match(featureNOrder[0], m, perimeterDecReg)){
            quickSort(shapeV.begin(), shapeV.end(), perimeterDescendingCompare);
            result = genResult(shapeV, "perimeter");
        }else{
            throw (std::string)"invalid input";
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
            if(!str.empty()){
                v.push_back(str);
            }
        }
        return v;
    }

    std::vector<Shape * > genShapeV(std::vector<std::vector<std::string>> vectors){
        std::vector<Shape *> shapeVectors;
        std::regex rectangleReg("^\\s*Rectangle\\s*$");
        std::regex triangleReg("^\\s*Triangle\\s*$");
        std::regex ellipseReg("^\\s*Ellipse\\s*$");
        std::regex argReg("^\\s*\\d+\\.{0,1}\\d{0,3}\\s*,\\s*\\d+\\.{0,1}\\d{0,3}\\s*$");
        std::smatch m;
        std::ssub_match ssm;

        for (int i = 0; i < vectors.size(); i++){
            std::string shapeType= vectors[i].front();
            if(regex_match(shapeType, m, rectangleReg)){
                std::vector<std::string> v = vectors[i];
                std::string widthNLength = v.back();
                if(regex_match(widthNLength, m, argReg)){
                    std::vector<std::string> splitByComma = splitInput(widthNLength, ',');
                    Shape * rectangle = new Rectangle(std::stod(splitByComma[0]), std::stod(splitByComma[1]));
                    shapeVectors.push_back(rectangle);
                }else{
                    continue;
                }
            }else if(regex_match(shapeType, m, triangleReg)){
                std::vector<std::string> v = vectors[i];
                std::string coordinate = v.back();
                std::vector<TwoDimensionalCoordinate*> triangleVector = genCoordinateVector(coordinate);
                Shape * triangle = new Triangle(triangleVector);
                shapeVectors.push_back(triangle);
            }else if(regex_match(shapeType, m, ellipseReg)){
                std::string widthNLength = vectors[i].back();
                if(regex_match(widthNLength, m, argReg)){
                    std::vector<std::string> splitByComma = splitInput(widthNLength, ',');
                    Shape * ellipse = new Ellipse(std::stod(splitByComma[0]), std::stod(splitByComma[1]));
                    shapeVectors.push_back(ellipse);
                }else{
                    continue;
                }
            }else{
                throw (std::string)"invalid input";
            }
        }
        return shapeVectors;
    }

    std::vector<TwoDimensionalCoordinate*> genCoordinateVector(std::string coordinate){//[0,0], [0,3], [4, 0]
        std::vector<TwoDimensionalCoordinate*> result;
        std::regex cReg("\\s*]\\s*,*");
        std::string replaced = regex_replace(coordinate, cReg, "");//[0,0[0,3[4, 0
        std::vector<std::string> splitByBracket = splitInput(replaced, '[');
        for(auto x: splitByBracket){
            std::vector<std::string> splitByComma = splitInput(x, ',');
            result.push_back(new TwoDimensionalCoordinate(std::stod(splitByComma[0]), std::stod(splitByComma[1])));
        }
        return result;
    }

    std::string genResult(std::vector<Shape *> shapes, std::string feature){
        std::string result="";
        if(feature == "area"){
            for(int i = 0; i < shapes.size(); i++){
                std::stringstream rounded;
                rounded<<std::fixed<<std::setprecision(3)<<shapes[i]->area();
                if(i == (shapes.size()-1)){
                    result = result + rounded.str();
                }else{
                    result = result + rounded.str()+"\n";
                } 
            }
        }else if (feature == "perimeter"){
            for(int i = 0; i < shapes.size(); i++){
                std::stringstream rounded;
                rounded<<std::fixed<<std::setprecision(3)<<shapes[i]->perimeter();
                if(i == (shapes.size()-1)){
                    result = result + rounded.str();
                }else{
                    result = result + rounded.str()+"\n";
                }
            }
        }else{
            throw (std::string)"invalid input";
        }

        return result;
    }
};
#endif