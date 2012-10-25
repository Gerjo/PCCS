#include "Loader.h"
#include "../components/PreloaderLogo.h"
#include "../components/PreloaderText.h"

Loader::Loader() {
    setType("Loader");
    
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
