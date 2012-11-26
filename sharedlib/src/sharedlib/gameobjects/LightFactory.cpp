#include "LightFactory.h"
#include "LightSoldier.h"
#include "LightTank.h"
#include "LightHelicopter.h"
#include "LightCrate.h"
#include "LightTrigger.h"

LightFactory* LightFactory::INSTANCE = 0;

LightFactory::LightFactory() {

}

LightFactory::LightFactory(const LightFactory& origin) {
    // Thou shalt not clone.
}

GameObject* LightFactory::create(string objectName) {
    if(INSTANCE == 0) {
        INSTANCE = new LightFactory();
    }

    return INSTANCE->createFromString(objectName);
}

GameObject* LightFactory::createFromString(string objectName) {

    string nameLowerCase = objectName;

    transform(nameLowerCase.begin(), nameLowerCase.end(), nameLowerCase.begin(), ::tolower);

    if(nameLowerCase == "tree") {
        return new LightTree();

    } else if(nameLowerCase == "soldier") {
        LightSoldier* ls = new LightSoldier();
        ls->weapon = static_cast<LightWeapon*>(create("weapon"));
        ls->addComponent(ls->weapon);
        return ls;

    } else if(nameLowerCase == "weapon") {
        return new LightWeapon();
    } else if(nameLowerCase == "bullet") {
        return new LightBullet();
    } else if(nameLowerCase == "tank") {
        LightTank* lt = new LightTank();
        lt->weapon = static_cast<LightWeapon*>(create("weapon"));
        lt->addComponent(lt->weapon);
        return lt;
    } else if (nameLowerCase == "crate") {
        return new LightCrate();
    } else if (nameLowerCase == "trigger") {
        return new LightTrigger();
    } else if (nameLowerCase == "helicopter") {
        LightHelicopter *lh = new LightHelicopter();
        lh->weapon = static_cast<LightWeapon*>(create("weapon"));
        lh->addComponent(lh->weapon);
        return lh;
    }
    throw SharedException(
        "Unable to create a '" + objectName + "' instance, it "
        "is not a known type in the LightFactory. ");
}