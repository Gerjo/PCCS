#ifndef LIGHTSOLDIER_H
#define	LIGHTSOLDIER_H

#include <phantom.h>
#include "GameObject.h"
#include "../CompileConfig.h"

using namespace phantom;

using std::string;
using std::cout;
using std::endl;

class LIBEXPORT LightSoldier : public GameObject {
public:
    LightSoldier();
    virtual ~LightSoldier();

    virtual void fromData(Data& data);
    virtual void toData(Data& data);

    int getPlayerId(void);

    int playerId;
private:

};

#endif	/* LIGHTSOLDIER_H */

