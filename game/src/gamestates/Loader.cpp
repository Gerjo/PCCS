#include "Loader.h"
#include "src/components/PreloaderLogo.h"
#include "src/components/PreloaderText.h"

Loader::Loader() {
    addComponent(content = new Layer());
    content->addComponent(camera = getDriver()->createCamera());
    content->addComponent(new PreloaderLogo());
    content->addComponent(_preloaderText = new PreloaderText());

    getPhantomGame()->getDriver()->setActiveCamera(camera);
}

Loader::~Loader() {

}

void Loader::init(void) {

}
