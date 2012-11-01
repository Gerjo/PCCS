#include "HeavyFactory.h"
#include "HeavySoldier.h"
HeavyFactory* HeavyFactory::INSTANCE = 0;

HeavyFactory::HeavyFactory() {

}

HeavyFactory::HeavyFactory(const HeavyFactory& origin) {
    // Thou shalt not clone.
}

GameObject* HeavyFactory::createFromString(string objectName) {

    string nameLowerCase = objectName;

    transform(nameLowerCase.begin(), nameLowerCase.end(), nameLowerCase.begin(), ::tolower);

    if(nameLowerCase == "tree") {
        return new HeavyTree();

    } else if(nameLowerCase == "soldier") {
        HeavySoldier hs;
        hs.weapon = static_cast<LightWeapon*>(create("weapon"));
        hs.addComponent(hs.weapon);
        return new HeavySoldier();

    } else if(nameLowerCase == "weapon") {
        return new HeavyWeapon();

    } else if(nameLowerCase == "bullet") {
        return new HeavyBullet();
    }

    throw SharedException(
            "Unable to create a '" + objectName + "' instance, it "
            "is not a known type in the HeavyFactory. ");
}