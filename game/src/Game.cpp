#include "Game.h"
#include <iostream>
#include <fstream>
#include "components/RtsCamera.h"
#include "gameobjects/Tree.h"
#include "pathfinding/Pathfinding.h"
#include "gameobjects/Enemy.h"
using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    pushGameState(&_gameState);

    _gameState.addComponent(&_gridLayer);

    _tree = new BSPTree(
            2000.0f,    // Width
            2000.0f,    // Height

            // Quite important settings: (ask Gerjo for documenation)
            20.0f,      // Minimal room height and width.
            50          // Prefered maximum collisions per room.
            );

    // If you fancy lag:
    //_tree->enableDebug();

    _gameState.addComponent(_tree);
    _gameState.addComponent(&_gameObjects);

    _gameState.addComponent(&_cursorlayer);


    _fixedLayer = new FixedLayer();
    _fixedLayer->addComponent(_rtsCamera = new RtsCamera());
    _gameState.addComponent(_fixedLayer);

    _cursorlayer.addComponent(_selector= new Selector(*_tree));

    parseJson();

    Enemy* e = ObjectFactory::GetInstance()->createFromStringT<Enemy*>("enemy");
    e->setX(200); e->setY(300);
    addGameObject(e);

    _cursorlayer.addComponent(_pathfinding = new Pathfinding(*_tree));

    addSoldiers();
}

Game::~Game(){
    delete getDriver();
}

void Game::parseJson() {
    ObjectFactory* factory = ObjectFactory::GetInstance();

    rapidjson::Document doc;

    ifstream jsonFile("conf/world.json");
    string jsonStr, jsonLine;
    while(std::getline(jsonFile, jsonLine)) {
        jsonStr += jsonLine + "\n";
    }

    if (doc.Parse<0>(jsonStr.c_str()).HasParseError()) {
        throw new PhantomException("Invalid JSON file.");
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

        addGameObject(newObj);
    }
}

void Game::addSoldiers(void) {
    for(float i = 1; i <= 10; ++i) {
        Soldier* soldier = ObjectFactory::GetInstance()->createFromStringT<Soldier*>("soldier");
        soldier->setX(i * 30 + 100);
        soldier->setY(i * 30 + 100);
        soldier->setTarget(soldier->getPosition());

        _selector->addSoldier(soldier);

        addGameObject(soldier);
    }
}

RtsCamera& Game::getRtsCamera(void) {
    return *_rtsCamera;
}

void Game::addGameObject(Composite* comp) {
    _tree->addComponent(comp);
    //_gameObjects.addComponent(comp);
}

Pathfinding* Game::getPathfinding() {
    return _pathfinding;
}