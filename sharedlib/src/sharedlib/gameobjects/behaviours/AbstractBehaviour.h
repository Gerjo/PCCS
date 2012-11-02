#ifndef ABSTRACTBEHAVIOUR_H
#define ABSTRACTBEHAVIOUR_H

#include <phantom.h>
#include <common/CompileConfig.h>
#include <sharedlib/SharedException.h>

class LIBEXPORT AbstractBehaviour{
public:
    virtual void render(phantom::Graphics* g) =0;
    string getType(){
        checkType();
        return _typeName;
    }
protected:
    virtual void checkType(){
        if(_typeName == "");
        throw new SharedException("please implement setType()");
    }
    string _typeName;
};


#endif /* ABSTRACTBEHAVIOUR_H */