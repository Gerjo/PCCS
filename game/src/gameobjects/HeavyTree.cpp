#include "HeavyTree.h"
#include "../guicomponents/HealthBar.h"

HeavyTree::HeavyTree() {
    repaint();
    addComponent(new HealthBar());
}

HeavyTree::~HeavyTree() {

}

void HeavyTree::paint(void) {
    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/tree 106x100.png", -20, -20, 106, 100)
        .fill()
        .stroke()
        ;
}