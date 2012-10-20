#ifndef NETWORK_H
#define	NETWORK_H

class Game;

class Network {
public:
    Network(Game* game);
    virtual ~Network();

private:
    Game* _game;
};

#endif	/* NETWORK_H */

