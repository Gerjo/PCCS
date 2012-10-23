#ifndef PLAYERPOOL_H
#define	PLAYERPOOL_H

#include <deque>
#include <iostream>
#include <string>
#include <yaxl.h>

class Player;
class GameHub;

class PlayerPool {
public:
    PlayerPool(GameHub* gamehub);
    ~PlayerPool();
    void addPlayer(Player* player);

private:
    deque<Player*> _players;
    GameHub* _gamehub;
    yaxl::concurrency::Mutex _playersMutex;
    
};

#endif	/* PLAYERPOOL_H */

