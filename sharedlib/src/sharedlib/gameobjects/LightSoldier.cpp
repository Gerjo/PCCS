#include "LightSoldier.h"

LightSoldier::LightSoldier() : playerId(-1) {
    setType("Soldier");

}

LightSoldier::~LightSoldier() {

}

void LightSoldier::fromData(Data& data) {
    GameObject::fromData(data);
    playerId = data("player_id");
}

void LightSoldier::toData(Data& data) {
    GameObject::toData(data);
    data("player_id") = playerId;
}
