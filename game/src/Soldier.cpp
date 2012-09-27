#include "Soldier.h"

Soldier::Soldier() {
    getGraphics()->beginPath();
    getGraphics()->setFillStyle(phantom::Color(127, 0, 0, 127));
    getGraphics()->setLineStyle(phantom::Color(0, 127, 0, 127));

    getGraphics()->arc(500, 250, 100, 0, (2 * M_PI));
    getGraphics()->arc(500, 100, 50, 0, (2 * M_PI));

    getGraphics()->beginPath();
}

Soldier::Soldier(const Soldier& orig) {

}

Soldier::~Soldier() {

}
