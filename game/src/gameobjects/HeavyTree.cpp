#include "HeavyTree.h"

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
            .image("images/tree 106x100.png", 0, 0, _boundingBox.size.x, _boundingBox.size.y)
            .fill()
            .stroke()
        ;
}