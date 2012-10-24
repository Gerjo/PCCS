#ifndef FIXEDLAYER_H
#define	FIXEDLAYER_H

#include <phantom.h>
#include "components/RtsCamera.h"

class Game;

using namespace phantom;

class FixedLayer : public Layer {
public:
    FixedLayer();
    virtual void update(const float& elapsed);
    void setCamera(Camera* cam);

private:
    Camera* _camera;
};

#endif	/* FIXEDLAYER_H */

