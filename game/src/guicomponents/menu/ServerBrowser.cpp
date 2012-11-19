#include "ServerBrowser.h"
#include "../../Game.h"
#include "../../gamestates/MenuState.h"

#include <functional>

ServerBrowser::ServerBrowser() : _repaint(false) {
    Vector3 btnSize(370.0f, 100.0f);

    for(unsigned int i = 0; i < 3; ++i) {
        MenuButton *b = new MenuButton();
        _buttons.push_back(b);
        _labels.push_back(new MenuLabel());
        addComponent(b);
    }

    int offset = 0;
    for(std::vector<MenuLabel *>::iterator label = _labels.begin(); label != _labels.end(); ++label) {
        (*label)->setPosition(Vector3(350.0f, 400.0f + (30 * offset)));
        (*label)->setBoundingBox(Box3(Vector3(), Vector3(1250.0f, 30.0f)));
        (*label)->setText("Some awesome server is here!");
        // For now we only have 15 servers at most.
        if(offset < 15) ++offset;
        addComponent(*label);
    }

    _buttons[BTNBACK]->setText("Back");
    _buttons[BTNBACK]->setPosition(Vector3(1270.0f, 800.0f));
    _buttons[BTNBACK]->setBoundingBox(Box3(_buttons[BTNBACK]->getPosition(), btnSize));

    _buttons[BTNREFRESH]->setText("Refresh");
    _buttons[BTNREFRESH]->setPosition(Vector3(900.0f, 800.0f));
    _buttons[BTNREFRESH]->setBoundingBox(Box3(_buttons[BTNREFRESH]->getPosition(), btnSize));

    _buttons[BTNJOIN]->setText("Join");
    _buttons[BTNJOIN]->setPosition(Vector3(530.0f, 800.0f));
    _buttons[BTNJOIN]->setBoundingBox(Box3(_buttons[BTNJOIN]->getPosition(), btnSize));

    addActions();
    paint();
}

ServerBrowser::~ServerBrowser() {
}

void ServerBrowser::paint() {
    getGraphics().clear().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/bg.png", 0.0f, 0.0f, getPhantomGame()->getWorldSize().x, getPhantomGame()->getWorldSize().y).
        stroke();

    for(MenuButton *button : _buttons)
        button->paint();

    for(MenuLabel *label : _labels)
        label->paint();
}

void ServerBrowser::update(const phantom::Time& time) {
    if(_repaint) {
        paint();
        _repaint = false;
    }

    Composite::update(time);
}

void ServerBrowser::addActions() {
    std::function<void()> join = [this] { getGame<Game*>()->launchLoader(); };
    std::function<void()> refresh = [this] { };
    std::function<void()> back = [this] { static_cast<MenuState*>(getParent())->navigate("/"); };

    _buttons[BTNBACK]->onClickFunction = back;
    _buttons[BTNREFRESH]->onClickFunction = refresh;
    _buttons[BTNJOIN]->onClickFunction = join;
}