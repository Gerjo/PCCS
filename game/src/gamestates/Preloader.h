#ifndef PRELOADER_H
#define	PRELOADER_H

#include <phantom.h>

using namespace phantom;

class Preloader : public GameState {
public:
    Preloader();
    virtual ~Preloader();
    void init(void);

    Camera* camera;
private:
    Layer* content;
};

#endif	/* PRELOADER_H */

