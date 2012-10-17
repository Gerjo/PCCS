#include "Game.h"
#include <iostream>
#include <fstream>
#include "components/RtsCamera.h"
#include "gameobjects/Tree.h"
#include "pathfinding/Pathfinding.h"
#include "gameobjects/Enemy.h"
#include <input/Input.h>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    _console     = new Console();
    _gameState   = new GameState();
    _gridLayer   = new Layer();
    _cursorlayer = new Layer();
    _bulletLayer = new Layer();
    _fixedLayer  = new FixedLayer();
    _gameObjects = new EntityLayer();
    _rtsCamera   = new RtsCamera();
    _cursor      = new Cursor();


    pushGameState(_gameState);

    _gameState->addComponent(_gridLayer);

    _tree = new BSPTree(
            2000.0f,    // Width
            2000.0f,    // Height

            // Quite important settings: (ask Gerjo for documenation)
            20.0f,      // Minimal room height and width.
            50          // Prefered maximum collisions per room.
            );

    _selector = new Selector(*_tree);
    _pathfinding = new Pathfinding(*_tree);
    // If you fancy lag:
    //_tree->enableDebug();

    _gameState->addComponent(_tree);
    _gameState->addComponent(_gameObjects);
     _gameState->addComponent(_bulletLayer);
    _gameState->addComponent(_cursorlayer);
    _fixedLayer->addComponent(_console);
    _fixedLayer->addComponent(_cursor);
    _fixedLayer->addComponent(_rtsCamera);
    _gameState->addComponent(_fixedLayer);
    _cursorlayer->addComponent(_selector);

    parseJson();

    Enemy* e = ObjectFactory::GetInstance()->createFromStringT<Enemy*>("enemy");
    e->setX(210);
    e->setY(310);
    addGameObject(e);

    _cursorlayer->addComponent(_pathfinding);

    addSoldiers();

    stringstream ss;
    ss << "Loaded " << _tree->getComponents().size() << " gameobjects." << endl;
    Console::log(ss.str());
}

Game::~Game(){
    delete _gameState;
    /*
    delete _cursor;
    delete _gridLayer;
    delete _cursorlayer;
    delete _fixedLayer;
    delete _gameObjects;
    delete _rtsCamera;*/
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

        addGameObject(newObj);
    }
}

void Game::update(float elapsed) {
    PhantomGame::update(elapsed);
    // Allows us to quick exit the game.
    if(getDriver()->getInput()->getKeyboardState()->isKeyDown(27)) {
        this->_running = false;
    }
}

void Game::addSoldiers(void) {
    for(float i = 1; i <= 10; ++i) {
        Soldier* soldier = ObjectFactory::GetInstance()->createFromStringT<Soldier*>("soldier");
        soldier->setX(i * 30 + 100);
        soldier->setY(i * 30 + 100);

        _selector->addSoldier(soldier);

        addGameObject(soldier);
    }
}

RtsCamera& Game::getRtsCamera(void) {
    return *_rtsCamera;
}

Cursor* Game::getCursor(void) {
    return _cursor;
}

void Game::addGameObject(Composite* comp) {
    _tree->addComponent(comp);
    //_gameObjects.addComponent(comp);
}

Pathfinding* Game::getPathfinding() {
    return _pathfinding;
}

Layer* Game::getBulletLayer(void) {
    return _bulletLayer;
}