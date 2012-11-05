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
        .image("images/tree 106x100.png", -20, -20, 106, 100)
#ifdef _DEBUG
        .rect(_boundingBox, false)
#endif
        .fill()
        .stroke()
        ;
}