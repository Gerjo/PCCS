#ifndef PRELOADER_H
#define	PRELOADER_H

#include <phantom.h>

using namespace std;
using namespace phantom;

class PreloaderText;

class Loader : public GameState {
public:
    Loader();
    virtual ~Loader();
    void init(void);

    Camera* camera;

    void addText(string text);
private:
    Layer* content;
    PreloaderText* _preloaderText;
};

#endif	/* PRELOADER_H */
