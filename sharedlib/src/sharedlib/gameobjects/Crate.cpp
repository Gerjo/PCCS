#include "Crate.h"

#include "behaviours/AssaultRifle.h"
#include "behaviours/StandardBullet.h"
#include "LightSoldier.h"
#include "LightWeapon.h"
Crate::Crate(){
    _content = new AssaultRifle();
    setBoundingBox(Box3(0,0,150,150));
    setType("Crate");
}
void Crate::toData(Data& data){
    GameObject::toData(data);
    string s = "assaultrifle";
    data("typename") = s;
}

void Crate::fromData(Data& data){
    GameObject::fromData(data);
    _content = createFromString(data("typename"));
}
void Crate::update(const Time& time){
    GameObject::update(time);
}
void Crate::onCollision(Composite* entity){
    GameObject::onCollision(entity);
    if(entity->isType("Soldier")){
        LightSoldier* soldier = dynamic_cast<LightSoldier*>(entity);
        soldier->weapon->setWeaponBehaviour((WeaponBehaviour*)_content);
        destroy();
    }
}

AbstractBehaviour* Crate::createFromString(string typeName){
    string lowerCase = typeName;
    transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower);

    if(lowerCase == "assaultrifle"){
        return new AssaultRifle();
    }
    if(lowerCase == "standardbullet"){
        return new StandardBullet;
    }
    return nullptr;
}