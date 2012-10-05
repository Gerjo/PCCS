#include "RtsCamera.h"

RtsCamera::RtsCamera() {
    addComponent(_phantomCamera = getDriver()->createCamera());
    _input    = getDriver()->getInput();
    _edgeSize = 50;

    for(int i = 0; i < 4; ++i) {
        _hasMouse[i] = false;
    }

    _normals[0].y = 1;
    _normals[1].x = 1;
    _normals[2].y = -1;
    _normals[3].x = -1;

    matchScreen();
    draw();
}

void RtsCamera::update(const float& elapsed) {
    Composite::update(elapsed);
    Vector3 mousePosition = _input->getMouseState()->getMousePosition();


    bool hasChange = false;

    for(int i = 0; i < 4; ++i) {
        bool newState = 0;

        if(_edges[i].contains(mousePosition)) {
            newState = true;

            _position += _normals[i];
        }

        if(_hasMouse[i] != newState) {
            hasChange = true;
        }

        _hasMouse[i] = newState;
    }

    if(hasChange) {
        draw();
    }
}

void RtsCamera::matchScreen(void) {

    int width  = getGame()->getWidth();
    int height = getGame()->getHeight();

    _edges[0].origin.x = 0.0f;
    _edges[0].origin.y = 0.0f;
    _edges[0].size.x   = width;
    _edges[0].size.y   = _edgeSize;

    _edges[1].origin.x = width - _edgeSize;
    _edges[1].origin.y = 0.0f;
    _edges[1].size.x   = _edgeSize;
    _edges[1].size.y   = height;

    _edges[2].origin.x = 0.0f;
    _edges[2].origin.y = height - _edgeSize;
    _edges[2].size.x   = width;
    _edges[2].size.y   = _edgeSize;

    _edges[3].origin.x = 0.0f;
    _edges[3].origin.y = 0.0f;
    _edges[3].size.x   = _edgeSize;
    _edges[3].size.y   = height;
}

void RtsCamera::draw(void) {

    Graphics& g = getGraphics().clear();

    for(int i = 0; i < 4; ++i) {
        g.beginPath();

        if(_hasMouse[i]) {
            g.setFillStyle(Color(0, 0, 0, 100));
        } else {
            g.setFillStyle(Color(0, 0, 0, 30));
        }

        g.rect(_edges[i].origin.x, _edges[i].origin.y, _edges[i].size.x, _edges[i].size.y);
        g.fill();
    }


}
