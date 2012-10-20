#include "Preloader.h"
#include "src/components/PreloaderLogo.h"

Preloader::Preloader() {
    addComponent(content = new Layer());
    content->addComponent(camera = getDriver()->createCamera());
    content->addComponent(new PreloaderLogo());

    getGame()->getDriver()->setActiveCamera(camera);
}

Preloader::~Preloader() {

}

void Preloader::init(void) {

}
