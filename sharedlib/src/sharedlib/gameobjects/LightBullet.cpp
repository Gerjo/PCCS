#include "LightBullet.h"

#include "behaviours/StandardBullet.h"
#include "behaviours/Rocket.h"

LightBullet::LightBullet() :
    _velocity(500, 500, 0),
    _ttl(1),
    _damage(50.0f),
    _hasAuthority(false),
    owner(0) {

        setType("Bullet");
        _boundingBox.size.x = 10;
        _boundingBox.size.y = 10;
        _creationTime       = phantom::Util::getTime();
        _bulletBehaviour = nullptr;
        setBehaviour(new Rocket());

}

LightBullet::~LightBullet() {
    delete _bulletBehaviour;
    _bulletBehaviour = 0;
}

void LightBullet::setBehaviour(BulletBehaviour* newBehaviour){
    delete _bulletBehaviour;

    _bulletBehaviour = newBehaviour;
}

void LightBullet::fromData(Data& data) {
    GameObject::fromData(data);
    _creationTime = data("creationtime");
    _direction.x  = data("d-x");
    _direction.y  = data("d-y");
    _direction.z  = data("d-z");

    setDirection(_direction);
    // strategy = StrategyFactory::create(data("strategy"));
}

void LightBullet::toData(Data& data) {
    GameObject::toData(data);
    data("creationtime") = static_cast<float>(_creationTime);
    data("d-x")          = _direction.x;
    data("d-y")          = _direction.y;
    data("d-z")          = _direction.z;

    //data("strategy") = StrategyFactory::reverseLookup(strategy);
}
void LightBullet::onDestruction(){
    if(_bulletBehaviour->getType() == "Rocket"){

    }
}
void LightBullet::setDirection(Vector3& direction) {
    //_direction = direction;
    _direction = _bulletBehaviour->setDirection(direction);
}

void LightBullet::update(const PhantomTime& time) {
    GameObject::update(time);

    _position += _velocity * _direction * time.getElapsed();

    _ttl -= time.getElapsed();

    if(_ttl < 0) {
        destroy();
    }
}

void LightBullet::setAuthority(bool hasAutority) {
    _hasAuthority = hasAutority;
}

void LightBullet::killList(vector<string> killList) {
    _killList = killList;
}