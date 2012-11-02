#include "Crate.h"

#include "behaviours/AssaultRifle.h"
#include "behaviours/StandardBullet.h"

Crate::Crate(){

}
void Crate::toData(Data& data){
    GameObject::toData(data);
    data("typename") = _content->getType();
}

void Crate::fromData(Data& data){
    GameObject::fromData(data);
    _content = createFromString(data("typename"));
}
void Crate::paint(){
    GameObject::paint();

    
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
}