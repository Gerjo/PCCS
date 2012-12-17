#include "LightCrate.h"

#include "behaviours/AssaultRifle.h"
#include "behaviours/StandardBullet.h"
#include "LightSoldier.h"
#include "LightWeapon.h"

LightCrate::LightCrate() {
    setType("Crate");

    _content = new AssaultRifle();
    _boundingBox.size.x = 50;
    _boundingBox.size.y = 50;
}

void LightCrate::toData(Data& data) {
    GameObject::toData(data);
    string s = "assaultrifle";
    data("typename") = s;
}

void LightCrate::fromData(Data& data) {
    GameObject::fromData(data);
    _content = createFromString(data("typename"));
}

void LightCrate::update(const PhantomTime& time) {
    GameObject::update(time);
}

void LightCrate::onCollision(Composite* entity, CollisionData& collisionData) {
    GameObject::onCollision(entity, collisionData);

    return;

    if (entity->isType("Soldier")) {
        LightSoldier* soldier = dynamic_cast<LightSoldier*> (entity);
        soldier->weapon->setWeaponBehaviour((WeaponBehaviour*) _content);
        destroy();
    }
}

AbstractBehaviour* LightCrate::createFromString(string typeName) {
    string lowerCase = typeName;
    transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower);

    if (lowerCase == "assaultrifle") {
        return new AssaultRifle();
    }
    if (lowerCase == "standardbullet") {
        return new StandardBullet;
    }
    return nullptr;
}