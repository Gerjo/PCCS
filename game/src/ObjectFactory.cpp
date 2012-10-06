#include "ObjectFactory.h"

#include "gameobjects/Soldier.h"
#include "gameobjects/Tree.h"

ObjectFactory* ObjectFactory::INSTANCE = 0;

ObjectFactory* ObjectFactory::GetInstance() {
    if(ObjectFactory::INSTANCE == 0) {
        ObjectFactory::INSTANCE = new ObjectFactory();
    }

    return ObjectFactory::INSTANCE;
}

ObjectFactory::ObjectFactory() {

}

ObjectFactory::ObjectFactory(const ObjectFactory& origin) {
    // Thou shalt not clone.
}

GameObject* ObjectFactory::createFromString(string objectName) {

    string nameLowerCase = objectName;

    transform(nameLowerCase.begin(), nameLowerCase.end(), nameLowerCase.begin(), ::tolower);

    if(nameLowerCase == "soldier") {
        return new Soldier();
    } else if(nameLowerCase == "tree") {
        return new Tree();
    }

    throw GameException(
            "Unable to create a '" + objectName + "' instance, it "
            "is not a known type in the factory. ");
}
