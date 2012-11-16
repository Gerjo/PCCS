#include "SettingsMenu.h"
#include "../../gamestates/MenuState.h"

SettingsMenu::SettingsMenu() {
    for(unsigned int i = 0; i < 4; ++i) {
        MenuInputField *field = new MenuInputField(800.0f, 370.0f + (100 * i), 0.0f, 0.0f, Colors::WHITE);
        Box3 inputFieldSize(0.0f, 0.0f, 600.0f, 75.0f);
        field->setBoundingBox(inputFieldSize);
        _inputFields.push_back(field);
        addComponent(field);
    }

    for(unsigned int i = 0; i < 2; ++i) {
        MenuButton *button = new MenuButton();
        _buttons.push_back(button);
        addComponent(button);
    }

    Box3 sizeBox(0.0f, 0.0f, 600.0f, 100.0f);

    _buttons[FULLSCREENBTN]->setText("Fullscreen: off");
    _buttons[FULLSCREENBTN]->setPosition(Vector3(300.0f, 820.0f));
    _buttons[FULLSCREENBTN]->setBoundingBox(sizeBox);
    _buttons[BACKBTN]->setText("Back");
    _buttons[BACKBTN]->setPosition(Vector3(1000.0f, 820.0f));
    _buttons[BACKBTN]->setBoundingBox(sizeBox);

    addActions();
    paint();
}

SettingsMenu::~SettingsMenu() {
}

void SettingsMenu::paint() {
    getGraphics().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/bgsettings.png", 0.0f, 0.0f, getPhantomGame()->getWorldSize().x, getPhantomGame()->getWorldSize().y).
        stroke();

    for(MenuButton *button : _buttons)
        button->paint();

    for(MenuInputField *field : _inputFields)
        field->paint();
}

void SettingsMenu::update(const phantom::Time& time) {
    if(_repaint)
        paint();
    
    Composite::update(time);
}

void SettingsMenu::addActions() {
    std::function<void()> fullscreen, back;

    fullscreen = [this] () { };
    back = [this] () { saveToFile(); static_cast<MenuState*>(getParent())->navigate("/"); };

    _buttons[FULLSCREENBTN]->onClickFunction = fullscreen;
    _buttons[BACKBTN]->onClickFunction = back;
}

void SettingsMenu::saveToFile() {
}