#include "RtsCamera.h"

RtsCamera::RtsCamera() {
    addComponent(_phantomCamera = getDriver()->createCamera());
    _input = getDriver()->getInput();
    _edgeSize = 50;

    matchScreen();
    draw();
}

void RtsCamera::update(const float& elapsed) {
    Composite::update(elapsed);
    Vector3 mousePosition = _input->getMouseState()->getMousePosition();

    for(int i = 0; i < 4; ++i) {
        if(_edges[i].contains(mousePosition)) {
            cout << i << endl;
        }
    }

    //cout << mousePosition.toString() << endl;

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

    // Interesting syntax :o
    Graphics& g = getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Color(0, 0, 0, 40));

    for(int i = 0; i < 4; ++i) {
        g.rect(_edges[i].origin.x, _edges[i].origin.y, _edges[i].size.x, _edges[i].size.y);
    }

    g.fill();
}
