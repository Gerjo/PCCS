#include "HeavyTree.h"
#include "../guicomponents/HealthBar.h"

HeavyTree::HeavyTree() {
    imagelocation << "images/environment/tree 106x100 shadow-"
        << (rand() % 4) + 1
        << ".png";

    repaint();
}

HeavyTree::~HeavyTree() {

}

void HeavyTree::paint(void) {
    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image(imagelocation.str(), -10, -10, 106, 100)
        .fill()
        .stroke()
        ;
}