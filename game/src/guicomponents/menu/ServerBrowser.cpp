#include "ServerBrowser.h"
#include "../../Game.h"
#include "../../gamestates/MenuState.h"
#include "../../networking/Master.h"

#include <functional>

#include <graphics/particles/Particles.h>

ServerBrowser::ServerBrowser() : _repaint(false) {
    Vector3 btnSize(370.0f, 100.0f);

    for(unsigned int i = 0; i < 3; ++i) {
        MenuButton *b = new MenuButton();
        _buttons.push_back(b);
        addComponent(b);
    }

    _buttons[BTNBACK]->setText("Back");
    _buttons[BTNBACK]->setPosition(Vector3(1270.0f, 800.0f));
    _buttons[BTNBACK]->setBoundingBox(Box3(_buttons[BTNBACK]->getPosition(), btnSize));

    _buttons[BTNREFRESH]->setText("Refresh");
    _buttons[BTNREFRESH]->setPosition(Vector3(670.0f, 800.0f));
    _buttons[BTNREFRESH]->setBoundingBox(Box3(_buttons[BTNREFRESH]->getPosition(), btnSize));

    _buttons[BTNJOIN]->setText("Join");
    _buttons[BTNJOIN]->setPosition(Vector3(280.0f, 800.0f));
    _buttons[BTNJOIN]->setBoundingBox(Box3(_buttons[BTNJOIN]->getPosition(), btnSize));

    Particles *p = new Particles(500, "images/projectiles/teslabolt.png");
    p->setPosition(Vector3(500,500));
    addComponent(p);

    addActions();
    paint();

}

ServerBrowser::~ServerBrowser() {
}

void ServerBrowser::servers(vector<DedicatedModel> servers) {
    int offset = 0;
    const double now = phantom::Util::getTime();


#ifdef _DEBUG
    DedicatedModel newModel;
    newModel.ipv4 = "127.0.0.1";
    newModel.name = "localhost";
    newModel.port = 8070;
    newModel.lastPing = now;

    servers.push_back(newModel);
#endif

    for(const DedicatedModel& server : servers) {
        MenuLabel *label = new MenuLabel();
        double delta = floor(now - server.lastPing);

        stringstream ss;
        ss << "[" << server.ipv4 << "] [" << delta << "] " << server.name;


        label->setText(ss.str());
        label->setPosition(Vector3(350.0f, 400.0f + (30 * offset)));
        label->setBoundingBox(Box3(Vector3(), Vector3(1250.0f, 30.0f)));

        label->onClickFunction = [this, server] {
            this->selectedServer = server;
        };

        label->onDoubleClickFunction = [this, server] {
            getGame<Game*>()->dedicated->init(server);
            getGame<Game*>()->launchLoader();
        };

        _labels.push_back(label);

        // For now we only have 15 servers at most.
        if(offset < 15) ++offset;
        addComponent(label);
    }

    paint();
}

void ServerBrowser::paint() {
    getGraphics().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/bg.png", 0.0f, 0.0f, getPhantomGame()->getWorldSize().x, getPhantomGame()->getWorldSize().y).
        stroke();

    for(MenuButton *button : _buttons)
        button->paint();

    for(MenuLabel *label : _labels)
        label->paint();
}

void ServerBrowser::update(const phantom::PhantomTime& time) {

    if(_repaint) {
        paint();
        _repaint = false;
    }

    Composite::update(time);
}

void ServerBrowser::addActions() {
    std::function<void()> join = [this] {
        getGame<Game*>()->dedicated->init(selectedServer); getGame<Game*>()->launchLoader();
    };


    std::function<void()> refresh = [this] {
        for(MenuLabel *l : _labels)
            l->destroy();
        _labels.clear();
        getGame<Game*>()->master->requestAvailableDedicated();
    };

    std::function<void()> back = [this] {
        static_cast<MenuState*>(getParent())->navigate("/");
    };

    _buttons[BTNBACK]->onClickFunction = [this] {

        DedicatedModel tmpModel;
        tmpModel.ipv4 = "127.0.0.1";
        tmpModel.name = "Hack-o-matic";
        tmpModel.port = 8070;
        tmpModel.lastPing = 99;

        getGame<Game*>()->dedicated->init(tmpModel);
        getGame<Game*>()->launchLoader();

    };
    _buttons[BTNREFRESH]->onClickFunction = refresh;
    _buttons[BTNJOIN]->onClickFunction = join;
}