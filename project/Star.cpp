
#include "Star.h"

void Star::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*mCircle, states);
}

void Star::update() {
    mCircle->move(mSpeed);
}

Vector2f Star::getPosition() {
    return mCircle->getPosition();
}