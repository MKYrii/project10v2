#include "Character.h"

void Character::draw(RenderTarget &target, RenderStates states) const {
    target.draw(mSprite);
}

void Character::move(int x, int y) {
    mPosition = Vector2f(mPosition.x + x, mPosition.y + y);
    mSprite.setPosition(mPosition);
    if (y < 0) {
        mScale.x *= 0.994;
        mScale.y *= 0.994;
        mSprite.setScale(mScale.x, mScale.y);
    }
    if (y > 0) {
        mScale.x *= 1.006;
        mScale.y *= 1.006;
        mSprite.setScale(mScale.x, mScale.y);
    }
}

int Character::getSpeed() const {
    return mSpeed;
}

Vector2f Character::getPosition() const {
    return mPosition;
}

Vector2f Character::getScale() const {
    return mScale;
}

Rect<float> Character::getBounds() {
    return mSprite.getGlobalBounds();
}

void Character::setPosition(Vector2f position) {
    mPosition = position;
    mSprite.setPosition(mPosition);
    mScale = Vector2f(0.12, 0.12);
    mSprite.setScale(mScale);
}
