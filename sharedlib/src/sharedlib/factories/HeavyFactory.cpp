#include "HeavyFactory.h"

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
    }

    throw SharedException(
            "Unable to create a '" + objectName + "' instance, it "
            "is not a known type in the HeavyFactory. ");
}