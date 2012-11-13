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
        .image("images/tree 106x100.png", -10, -10, 106, 100)
        .fill()
        .stroke()
        ;

    getGraphics()
        .beginPath()
        .setFillStyle(Color(128, 128, 128, 20))
        .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y, false)
        .fill();
}