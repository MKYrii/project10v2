

#include "Bullet.h"

Vector2f Bullet::getPosition() const {
    return mCircle->getPosition();
}

void Bullet::update() {
    if (mCircle->getFillColor() == Color::Blue)
        mCircle->move(mSpeed);
    else
        mCircle->move(-mSpeed.x * 0.6, -mSpeed.y * 0.6);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*mCircle, states);
}

Color Bullet::getColor() {
    return mCircle->getFillColor();
}