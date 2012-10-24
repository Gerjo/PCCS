#ifndef HEAVYSOLDIER_H
#define	HEAVYSOLDIER_H

#include "LightSoldier.h"

class HeavySoldier : public LightSoldier {
public:
    HeavySoldier();
    virtual ~HeavySoldier();
    virtual void paint();

    virtual void fromData(Data& data);
    virtual void toData(Data& data);
private:

};

#endif	/* HEAVYSOLDIER_H */
