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

    _tree = new BSPTree(1000.0f, 1000.0f, 10.0f);
    //_tree->enableDebug();


    _gameState.addComponent(_tree);
    _gameState.addComponent(&_gameObjects);

    _gameState.addComponent(&_cursorlayer);
    _cursorlayer.addComponent(_selector= new Selector());

    _fixedLayer = new FixedLayer();
    _fixedLayer->addComponent(_rtsCamera = new RtsCamera());
    _gameState.addComponent(_fixedLayer);

    parseJson();
    addSoldiers();


    Enemy* e = ObjectFactory::GetInstance()->createFromStringT<Enemy*>("enemy");
    e->setX(200); e->setY(300);
    _gameObjects.addComponent(e);

    //_cursorlayer.addComponent(new Pathfinding(*_tree));
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

        //cout << "Creating a '" << type << "' at x:" << x << ", y:" << y << "." << endl;

        GameObject* newObject = factory->createFromString(type);
        newObject->setPosition(Vector3(x, y));

        _gameObjects.addComponent(newObject);
    }
}

void Game::addSoldiers(void) {
    for(float i = 1; i <= 20; ++i) {
        Soldier* soldier = ObjectFactory::GetInstance()->createFromStringT<Soldier*>("soldier");
        soldier->setX(i * 30);
        soldier->setY(i * 30);
        soldier->setTarget(soldier->getPosition());

        _selector->addSoldier(soldier);

        _gameObjects.addComponent(soldier);
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
