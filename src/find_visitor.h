#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H
#include "app.h"
#include "folder.h"
#include "iterator.h"

class FindVisitor : public Visitor {
public:
    FindVisitor(std::string name) {
        _name = name;
    }
    
    void visitApp(App* app) {
        // find app when app's name matches given name,
        // add app's route as result.
        std::cout<<"app name: "<<app->name()<<" , target name: "<<_name<<std::endl;
        if(_name == app->name()){
            std::cout<<"app name match"<<std::endl;
            std::cout<<"app route=================="<<app->route()<<std::endl;
            if(getResult()!=""){
                _result = app->route();
            }else{
                _result = app->route();
            }
        }
    }
    
    void visitFolder(Folder* folder) {
        // find folder when folder's name matches given name,
        // add folder's route as result.
        // And find the tree structure bellow,
        // add the other match result with `\n`.
        std::cout<<"folder name: "<<folder->name()<<std::endl;
        std::list<Node*> _nodes = folder->getNodes();
        Iterator* itr = folder->createIterator();
        if( _name == folder->name()){
            std::cout<<"1"<<std::endl;
            if(getResult()!=""){
                _result += "\n"+folder->route();
            }else{
                _result = folder->route();
            }
        }
        for(std::list<Node *>::const_iterator i = _nodes.begin(); i != _nodes.end(); ++i){
            FindVisitor * findVstr = new FindVisitor(_name);
            (*i)->accept(findVstr);
            if(findVstr->getResult()!="" && _result!=""){
                std::cout<<"get result: "<<findVstr->getResult()<<std::endl;
                _result += "\n"+findVstr->getResult();
            }else if(findVstr->getResult()!="" && _result==""){
                _result = findVstr->getResult();
            }
        }
    }
    
    std::string getResult() const {
        return _result;
    }

private:
    std::string _result;
    std::string _name;
};
#endif