#include "HeavyTree.h"
#include "../guicomponents/HealthBar.h"

HeavyTree::HeavyTree() {
    repaint();
}

HeavyTree::~HeavyTree() {

}

void HeavyTree::paint(void) {
    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/environment/tree 106x100 shadow.png", -10, -10, 106, 100)
        .fill()
        .stroke()
        ;
}