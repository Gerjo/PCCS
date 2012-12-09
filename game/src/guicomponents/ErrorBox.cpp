#include "ErrorBox.h"

ErrorBox::ErrorBox(string message) : _repaint(true) {
    const Vector3 &ws = getPhantomGame()->getWorldSize();
    Box3 bb = Box3(0, 0, 725, 396);
    this->setBoundingBox(bb);
    this->setPosition(Vector3((ws.x / 2) - (bb.size.x / 2), (ws.y / 2) - (bb.size.y / 2), 0.0f));
    this->_message = message;
    this->_okButton = new MenuButton();
    this->_okButton->setBoundingBox(Box3(0, 0, 525, 100));
    this->_okButton->setPosition(Vector3(100, 250, 0));
    this->_okButton->setText("Okay");
    addComponent(this->_okButton);
}

ErrorBox::~ErrorBox() {
    delete this->_okButton;
}

void ErrorBox::paint() {
    const Box3 &bb = this->getBoundingBox();
    unsigned fsize = 20;

    getGraphics().clear().beginPath().setFillStyle(Colors::WHITE).
        image("images/menu/Error.png", 0, 0, bb.size.x, bb.size.y).fill().
        text(20, 10, fsize, "fonts/waree.ttf", this->_message).fill().
        text(20, 60, fsize, "fonts/waree.ttf", "A bug report has been sent.").fill();

    this->_okButton->paint();

    _repaint = false;
}

void ErrorBox::update(const phantom::PhantomTime &time) {
    if(_repaint)
        paint();
}