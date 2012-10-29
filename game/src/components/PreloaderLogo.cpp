#include "PreloaderLogo.h"

PreloaderLogo::PreloaderLogo() {

    Vector3 splashSize(1318, 678, 0);
    Vector3 splashPos = (getPhantomGame()->getWorldSize() - splashSize) * 0.5;// * 0.5 +  * 0.5;

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::BLACK)
            .rect(0, 0, getPhantomGame()->getWorldSize().x, getPhantomGame()->getWorldSize().y)
            .fill()

            .beginPath()
            .setFillStyle(Colors::WHITE)
            .image("images/splashscreen.png", splashPos.x, splashPos.y, splashSize.x, splashSize.y)
            .fill()
            ;
}
