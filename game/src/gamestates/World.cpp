#include "World.h"

#include "../FixedLayer.h"
#include "../components/RtsCamera.h"
#include "../components/Console.h"
#include "../pathfinding/BSPTree.h"
#include "src/pathfinding/Pathfinding.h"
#include "src/components/Selector.h"
#include "src/components/Cursor.h"
#include "../gameobjects/Soldier.h"


World::World() {

}

World::~World() {

}

void World::init(void) {
    fixedLayer = new FixedLayer();
    tree       = new BSPTree(2000.0f, 2000.0f, 20.0f, 50);
    overlay    = new Layer();

    fixedLayer->addComponent(camera   = new RtsCamera());
    fixedLayer->addComponent(cursor   = new Cursor());
    fixedLayer->addComponent(console  = new Console());
       overlay->addComponent(selector = new Selector(*tree));

    pathfinding = new Pathfinding(*tree);
    addComponent(tree);
    addComponent(fixedLayer);
    addComponent(overlay);

    loadJson();
    addSoldiers();
}

void World::addSoldiers(void) {
    for(float i = 1; i <= 10; ++i) {
        Soldier* soldier = ObjectFactory::GetInstance()->createFromStringT<Soldier*>("soldier");
        soldier->setX(i * 30 + 100);
        soldier->setY(i * 30 + 100);

        selector->addSoldier(soldier);

        tree->addComponent(soldier);
    }
}

void World::loadJson(void) {
        ObjectFactory* factory = ObjectFactory::GetInstance();

    rapidjson::Document doc;

    ifstream jsonFile("conf/world.json");
    string jsonStr, jsonLine;
    while(std::getline(jsonFile, jsonLine)) {
        jsonStr += jsonLine + "\n";
    }

    if (doc.Parse<0>(jsonStr.c_str()).HasParseError()) {
        throw GameException("Invalid JSON file.");
    }

    const rapidjson::Value& gameObjects = doc["gameobjects"];
    assert(gameObjects.IsArray());

    for(rapidjson::SizeType i = 0; i < gameObjects.Size(); ++i) {
        const rapidjson::Value &gob = gameObjects[i];

        string type = gob["type"].GetString();
        double x = gob["x"].GetDouble();
        double y = gob["y"].GetDouble();

        GameObject* newObj = factory->createFromString(type);
        newObj->setPosition(Vector3(x, y));

        tree->addComponent(newObj);
    }
}