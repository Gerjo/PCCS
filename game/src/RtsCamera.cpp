#include "RtsCamera.h"

RtsCamera::RtsCamera() {
    addComponent(_phantomCamera = getDriver()->createCamera());
    _input = getDriver()->getInput();
    _scrollAreaSize = 50;

    draw();
}

void RtsCamera::update(const float& elapsed) {
    Composite::update(elapsed);
    const Vector3f mousePosition = _input->getMouseState()->getMousePosition();
}

void RtsCamera::draw(void) {
    float width  = static_cast<float>(getGame()->getWidth());
    float height = static_cast<float>(getGame()->getHeight());

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Color(0, 0, 0, 40))

            // Top:
            .rect(0, 0, width, _scrollAreaSize)

            // Bottom:
            .rect(0, height - _scrollAreaSize, width, _scrollAreaSize)

            // Left:
            .rect(0, 0, _scrollAreaSize, height)

            // Right:
            .rect(width - _scrollAreaSize, 0, _scrollAreaSize, height)

            .fill();
}