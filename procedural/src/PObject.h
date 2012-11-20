#ifndef PROCOBJECT_H
#define PROCOBJECT_H

#include <CompileConfig.h> 
#include <sharedlib/gameobjects/GameObject.h>
#include "structures/Voronoi.h"


using namespace PGC;

class LIBEXPORT PObject : public GameObject{
public:
    PObject();
    void init();
    virtual void paint();
    virtual void update(const Time& time);
private:
    double w;
    Voronoi* v;
    PGC::Vertices* vertices;
    PGC::Vertices* dir;
    Edges* edges;
};

#endif /* PROCOBJECT_H */