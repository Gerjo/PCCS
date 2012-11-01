#ifndef FIXEDLAYER_H
#define	FIXEDLAYER_H

#include <phantom.h>
#include "components/ScrollBehaviour.h"

class Game;

using namespace phantom;

class FixedLayer : public Layer {
public:
    FixedLayer();
    virtual void update(const Time& time);
    void setCamera(Camera* cam);

private:
    Camera* _camera;
};

#endif	/* FIXEDLAYER_H */

