#include "HeavyTree.h"

HeavyTree::HeavyTree() {

}

HeavyTree::~HeavyTree() {

}

void HeavyTree::paint(void) {
    const string filename("images/tree64.png");

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            //.rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
            .image(filename, 0, 0, _boundingBox.size.x, _boundingBox.size.y)
            .fill()
            .stroke()
        ;
}