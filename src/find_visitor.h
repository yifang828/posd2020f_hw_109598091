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
        if(_name == app->name()){
            if(getResult()!=""){
                _result = app->route();
            }else{
                _result = app->route();
            }
        }
    }
    
    void visitFolder(Folder* folder) {
        std::list<Node*> _nodes = folder->getNodes();
        Iterator* itr = folder->createIterator();
        if( _name == folder->name()){
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