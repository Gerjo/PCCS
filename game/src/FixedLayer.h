#ifndef FIXEDLAYER_H
#define	FIXEDLAYER_H

#include <phantom.h>
#include "RtsCamera.h"

class Game;

using namespace phantom;

class FixedLayer : public Layer {
public:
    FixedLayer();

    virtual void update(const float& elapsed);

private:
    //RtsCamera& _rtsCamera;

};

#endif	/* FIXEDLAYER_H */

