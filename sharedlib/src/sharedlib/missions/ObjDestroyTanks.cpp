#include "ObjDestroyTanks.h"

ObjDestroyTanks::ObjDestroyTanks() {
    for(unsigned i = 0; i < 5; ++i) {
        LightTank *tank = new LightTank();
        tank->setPosition(Vector3(10*i, 10*i, 0));
        _composites.push_back(tank);
    }
}

ObjDestroyTanks::~ObjDestroyTanks() {
}

bool ObjDestroyTanks::conditionsMet() {
    std::vector<Composite*>::iterator tanks;
    int c;
    for(tanks = _composites.begin(); tanks != _composites.end(); ++tanks) {
        LightTank *tank = static_cast<LightTank*>(*tanks);
        c += tank->isDestroyed();
    }
    if(c == 5)
        return true;
    else
        return false;
}