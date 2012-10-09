#include "Game.h"
#include <iostream>
#include <fstream>
#include "components/RtsCamera.h"
#include "gameobjects/Tree.h"
#include "json/elements.h"
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
    _cursorlayer.addComponent(_selector= new Selector());

    _fixedLayer = new FixedLayer();
    _fixedLayer->addComponent(_rtsCamera = new RtsCamera());
    _gameState.addComponent(_fixedLayer);

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

    json::Object root;

    ifstream bar("conf/world.json");

    json::Reader::Read(root, bar);
    json::Array gameObjects;
    json::Array::iterator it;

    gameObjects = root["gameobjects"];

    for(it = gameObjects.Begin(); it != gameObjects.End(); ++it) {
        json::Object gob = *it;

        string type  = static_cast<json::String>(gob["type"]);
        double x     = static_cast<json::Number>(gob["x"]);
        double y     = static_cast<json::Number>(gob["y"]);

        GameObject* newObject = factory->createFromString(type);
        newObject->setPosition(Vector3(x, y));

        addGameObject(newObject);
    }
}

void Game::addSoldiers(void) {
    for(float i = 1; i <= 1; ++i) {
        Soldier* soldier = ObjectFactory::GetInstance()->createFromStringT<Soldier*>("soldier");
        soldier->setX(i * 30 + 100);
        soldier->setY(i * 30 + 100);
        soldier->setTarget(soldier->getPosition());

        _selector->addSoldier(soldier);

        addGameObject(soldier);
    }
}

void Game::createGrid(void) {
    int tileSize = 50;
    int width    = 2000; // getWidth();
    int height   = 1000; //getHeight();

    for(int y = 0; y < height - tileSize; y += tileSize) {
        for(int x = 0; x < width - tileSize; x += tileSize) {
            Ground* ground = new Ground();

            ground->setX(static_cast<float>(x));
            ground->setY(static_cast<float>(y));

            _gridLayer.addComponent(ground);
        }
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