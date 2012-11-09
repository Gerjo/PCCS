#include "GameObject.h"
#include "sharedlib/networking/NetworkRegistry.h"
#include "sharedlib/networking/PacketType.h"

GameObject::GameObject() :
    residence(CLIENT), // NB: The network factory will override this.
    _canHover(false),
    UID_local(UID::generate())
{
    _health = 100.0f;
    _totalHealth = 100.0f;
}

GameObject::~GameObject() {
    NetworkRegistry::remove(this);
    cout << getType() << " destructor. (UID_network: " << UID_network << ")" << endl;
}

void GameObject::onDestruction(void) {

    // Prevent recursion, only the server may propegate this event to other
    // connected clients:
    if(residence == SERVER) {
        Data data;
        auto message = new Message<Data>("destroy", data);
        Services::broadcast(this, message);
    }

    // Destroy thouself:
    destroy();
}

void GameObject::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
    // To be overridden.
}

bool GameObject::canHover(void) {
    return _canHover;
}

void GameObject::onSelect() {

}

void GameObject::onDeselect() {

}

float GameObject::distanceTo(GameObject* gob) {
    return _position.distanceTo(gob->_position);
}

float GameObject::distanceToSq(GameObject* gob) {
    return _position.distanceToSq(gob->_position);
}

Vector3 GameObject::directionTo(GameObject* gob) {
    Vector3 direction = (gob->_position + Vector3(gob->_boundingBox.size.x / 2, gob->_boundingBox.size.y / 2)) - (_position + Vector3(_boundingBox.size.x / 2, _boundingBox.size.y / 2));
    direction.normalize();
    return direction;
}

void GameObject::paint(void) {
    // Your painting code here.
}

void GameObject::repaint(void) {
    paint(); // TODO: chain multiple calls till vblank?
}

void GameObject::fromData(Data& data) {

    // Sorry for this style of coding, it's a POC! *sigh* -- Gerjo
    if(residence == CLIENT) {
        UID_network = data("UID_network").toString();
    }

    _position.x = data("x");
    _position.y = data("y");
}

void GameObject::toData(Data& data) {
    data("UID_network") = UID_network;
    data("UID_local")   = UID_local;
    data("type")        = getType();
    data("x")           = _position.x;
    data("y")           = _position.y;
}

MessageState GameObject::handleMessage(AbstractMessage* message) {
    if(message->isType("take-damage")) {
        Data data = message->getPayload<Data>();

        removeHealth(data("damage"));

        cout << "TEEHEEEE BAR FUNKLE THE SHIT WORKED. health:" << _health << endl;
        return CONSUMED;

    // RIP :(
    } else if(message->isType("destroy")) {
        onDestruction();
        return CONSUMED;
    }

    return Entity::handleMessage(message);
}


void GameObject::setHealth(float value) {
    _health = value;
    _totalHealth = value;
}

bool GameObject::removeHealth(float amount) {
    cout << "Removing: " << amount << "hp from " << _health << "hp" << endl;
    _health -= amount;

    if(_health <= 0) {
        _health = max(0.0f, _health);

        onDestruction();
    }

    return _health > 0;
}