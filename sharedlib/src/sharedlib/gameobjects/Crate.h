#ifndef CRATE_H
#define CRATE_H

#include <string>
#include <algorithm>
#include "GameObject.h"
#include "behaviours/AbstractBehaviour.h"

class LIBEXPORT Crate : public GameObject{
public:
    Crate();
    void toData(Data& data);
    void fromData(Data& data);
    void paint();
private:
    AbstractBehaviour* createFromString(string typeName);
    AbstractBehaviour* _content;
};

#endif /* CRATE_H */