#include "LightFactory.h"
#include "LightEnemy.h"
#include "LightTree.h"
#include "LightSoldier.h"
#include "LightTank.h"
#include "LightTankMech.h"
#include "LightHelicopter.h"
#include "LightCrate.h"
#include "LightTrigger.h"
#include "LightWater.h"
#include <yaxl.h>

LightFactory* LightFactory::INSTANCE = 0;

LightFactory::LightFactory() {

}

LightFactory::LightFactory(const LightFactory& origin) {
    // Thou shalt not clone.
}

GameObject* LightFactory::create(string objectName, string subname) {
    if (INSTANCE == 0) {
        INSTANCE = new LightFactory();
    }

    return INSTANCE->createFromString(objectName, subname);
}

GameObject* LightFactory::createFromString(string objectName, string subname) {
    yaxl::file::File file("enemies.json");
    
    Data enemies;
    if(file.exists()) {
        enemies = Data::fromJson(file.readAll());
    }

    string nameLowerCase = objectName;

    transform(nameLowerCase.begin(), nameLowerCase.end(), nameLowerCase.begin(), ::tolower);

    if (nameLowerCase == "tree") {
        return new LightTree();

    } else if (nameLowerCase == "water") {
        return new LightWater();

    } else if (nameLowerCase == "weapon") {
        return new LightWeapon();

    } else if (nameLowerCase == "bullet") {
        return new LightBullet();

    } else if (nameLowerCase == "crate") {
        return new LightCrate();

    } else if (nameLowerCase == "trigger") {
        return new LightTrigger();

    } else if (nameLowerCase == "enemy") {
        LightEnemy *enemy = new LightEnemy(enemies(subname));
        enemy->weapon = static_cast<LightWeapon*> (create("weapon"));
        enemy->addComponent(enemy->weapon);
        return enemy;
    } else if (nameLowerCase == "helicopter") {
        LightHelicopter *lh = new LightHelicopter();
        lh->weapon = static_cast<LightWeapon*> (create("weapon"));
        lh->addComponent(lh->weapon);
        return lh;

    } else if (nameLowerCase == "tank") {
        LightTank* lt = new LightTank();
        lt->weapon = static_cast<LightWeapon*> (create("weapon"));
        lt->addComponent(lt->weapon);
        return lt;

    } else if (nameLowerCase == "mechtank") {
        LightTankMech* lt = new LightTankMech();
        lt->weapon = static_cast<LightWeapon*> (create("weapon"));
        lt->addComponent(lt->weapon);
        return lt;

    } else if (nameLowerCase == "soldier") {
        LightSoldier* ls = new LightSoldier();
        ls->weapon = static_cast<LightWeapon*> (create("weapon"));
        ls->addComponent(ls->weapon);
        return ls;
    }

    throw SharedException(
            "Unable to create a '" + objectName + "' instance, it "
            "is not a known type in the LightFactory. ");
}