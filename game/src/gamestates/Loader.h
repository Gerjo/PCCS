#ifndef PRELOADER_H
#define	PRELOADER_H

#include <phantom.h>

using namespace phantom;

class Loader : public GameState {
public:
    Loader();
    virtual ~Loader();
    void init(void);

    Camera* camera;
private:
    Layer* content;
};

#endif	/* PRELOADER_H */

