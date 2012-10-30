#ifndef OBJECTFACTORY_H
#define	OBJECTFACTORY_H

#include <phantom.h>
#include <string>
#include <algorithm>

#include "GameObject.h"
#include "../SharedException.h"
#include "../CompileConfig.h"

// All lightweight gameobjects:
#include "LightTree.h"
#include "LightSoldier.h"
#include "LightBullet.h"
#include "LightWeapon.h"

using namespace phantom;
using namespace std;

class LIBEXPORT LightFactory {
public:
    static GameObject* create(string objectName);
private:
    LightFactory();
    LightFactory(const LightFactory& origin);
    GameObject* createFromString(string objectName);
    static LightFactory* INSTANCE;
};

#endif	/* OBJECTFACTORY_H */
