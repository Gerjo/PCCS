#include "HeavyFactory.h"
#include "HeavySoldier.h"
#include "HeavyTank.h"
#include "HeavyTankMech.h"
#include "HeavyHelicopter.h"
#include "HeavyCrate.h"
#include "HeavyTrigger.h"
#include "HeavyWater.h"
#include "HeavyEnemy.h"
#include <sharedlib/missions/Mission.h>

HeavyFactory* HeavyFactory::INSTANCE = 0;

HeavyFactory::HeavyFactory() {

}

HeavyFactory::HeavyFactory(const HeavyFactory& origin) {
    // Thou shalt not clone.
}

GameObject* HeavyFactory::createFromString(string objectName, string subname) {
    yaxl::file::File file("enemies.json");
    Data enemies;
    if(file.exists()) {
        enemies = Data::fromJson(file.readAll());
    }

    string nameLowerCase = objectName;

    transform(nameLowerCase.begin(), nameLowerCase.end(), nameLowerCase.begin(), ::tolower);

    if(nameLowerCase == "tree") {
        return new HeavyTree();
    } else if(nameLowerCase == "water") {
        return new HeavyWater();
    } else if(nameLowerCase == "soldier") {
        HeavySoldier* hs = new HeavySoldier();
        hs->weapon = static_cast<LightWeapon*>(create("weapon"));
        hs->addComponent(hs->weapon);
        return hs;

    } else if(nameLowerCase == "enemy") {
        HeavyEnemy* hs = new HeavyEnemy(enemies(subname));
        hs->weapon = static_cast<LightWeapon*>(create("weapon"));
        hs->addComponent(hs->weapon);
        return hs;
    } else if(nameLowerCase == "weapon") {
        return new HeavyWeapon();
    } else if(nameLowerCase == "bullet") {
        return new HeavyBullet();
    } else if(nameLowerCase == "tank") {
        HeavyTank* hs = new HeavyTank();
        hs->weapon = static_cast<LightWeapon*>(create("weapon"));
        hs->addComponent(hs->weapon);
        return hs;
    } else if(nameLowerCase == "mechtank") {
        HeavyTankMech* hs = new HeavyTankMech();
        hs->weapon = static_cast<LightWeapon*>(create("weapon"));
        hs->addComponent(hs->weapon);
        return hs;
    } else if(nameLowerCase == "crate"){
        return new HeavyCrate();
    } else if(nameLowerCase == "mission"){
        return new Mission("somemission");
    } else if(nameLowerCase == "trigger") {
        return new HeavyTrigger();
    } else if(nameLowerCase == "helicopter") {
        HeavyHelicopter* hs = new HeavyHelicopter();
        hs->weapon = static_cast<LightWeapon*>(create("weapon"));
        hs->addComponent(hs->weapon);
        return hs;
    }

    throw SharedException(
            "Unable to create a '" + objectName + "' instance, it "
            "is not a known type in the HeavyFactory. ");
}