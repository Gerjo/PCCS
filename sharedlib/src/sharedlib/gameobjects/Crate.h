#ifndef CRATE_H
#define CRATE_H

#include "GameObject.h"

class LIBEXPORT Crate : public GameObject{
public:
    Crate();
    void toData(Data& data);
    void fromData(Data& data);

private:
    GameObject* _content;
};

#endif /* CRATE_H */