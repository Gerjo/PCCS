#include "Loader.h"
#include "../components/PreloaderLogo.h"
#include "../components/PreloaderText.h"
#include <core/Console.h>

Loader::Loader() {
    setType("Loader");
    
    Console::log("Initializing loader...");

    addComponent(content = new Layer());
    content->addComponent(camera = getDriver()->createCamera());
    content->addComponent(new PreloaderLogo());
    content->addComponent(_preloaderText = new PreloaderText());

    getPhantomGame()->getDriver()->enableCamera(camera);

    Console::log("Initialization complete.");
}

Loader::~Loader() {

}

void Loader::init(void) {

}
