#ifndef  SHAPE_PARSER_H
#define  SHAPE_PARSER_H

#include "shape_builder.h"
#include "scanner.h"
#include "shape.h"
#include <deque>

class ShapeParser{
public:
    ShapeParser(std::string input){
        scanner = new Scanner(input);
        sb = new ShapeBuilder();
    }

    void parser(){
        std::string token;
        do{
            token = scanner->nextToken();
            if("Rectangle"==token){
                std::vector<double>values = getValue();
                if(values.size()==2){
                    sb->buildRectangle(values[0], values[1]);
                }
            }else if ("Triangle" == token){
                std::vector<double>values = getValue();
                if(values.size()==6){
                    sb->buildTriangle(values[0], values[1], values[2], values[3], values[4], values[5]);
                }
            }else if ("Ellipse" == token){
                std::vector<double>values = getValue();
                if(values.size()==2){
                    sb->buildEllipse(values[0], values[1]);
                }
            }else if ("CompoundShape" == token){
                sb->buildCompoundShapeBegin();
                scanner->nextToken();
                parser();
            }
            else if ("}" == token){
                sb->buildCompoundShapeEnd();
            }
            try {
                token = scanner->nextToken();
                if("}" == token){
                    sb->buildCompoundShapeEnd();
                }
            }
            catch(const std::string e) {
                if(e == "next char doesn't exist."){
                    return;
                }
            }
        } while ("," == token);
    }

    std::deque<Shape*> getResult(){
        return sb->getResult();
    }
private:
    Scanner * scanner;
    ShapeBuilder * sb;

    std::vector<double> getValue(){
        std::vector<double> result;
        std::string token = scanner->nextToken();
        do{
            if("(" == token || "," == token){
                result.push_back(std::stod(scanner->nextToken()));
            }
            token = scanner->nextToken();
        }while(")" != token);
        return result;
    }
};
#endif