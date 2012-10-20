#include "Loader.h"
#include "src/components/PreloaderLogo.h"

Loader::Loader() {
    addComponent(content = new Layer());
    content->addComponent(camera = getDriver()->createCamera());
    content->addComponent(new PreloaderLogo());

    getGame()->getDriver()->setActiveCamera(camera);
}

Loader::~Loader() {

}

void Loader::init(void) {

}
