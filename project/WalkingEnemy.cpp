
#include "WalkingEnemy.h"

void WalkingEnemy::draw(RenderTarget &target, RenderStates states) const {
    target.draw(mSprite);
}



void WalkingEnemy::move(Vector2f windowSize, double y) {
    mPosition = Vector2f(mPosition.x + mSpeed.x, mPosition.y + mSpeed.y);
    mSpeed.y = mSpeed.y - 0.1 + (double(rand()) / double(RAND_MAX) / 50.0);
    if (mPosition.y < 200) {
        mSpeed.y = 10;
    }
    if (mPosition.x + mScale.x * 655 > (windowSize.x - y) / 2 + y + (windowSize.x - y) / 2 * mPosition.y / windowSize.y
        or mPosition.x < (windowSize.x - y) / 2 - (windowSize.x - y) / 2 * mPosition.y / windowSize.y) {
        mSpeed = -mSpeed;
        mPosition = Vector2f(mPosition.x + mSpeed.x, mPosition.y);
        mPosition = Vector2f(mPosition.x + mSpeed.x, mPosition.y);
    }
    if (mSpeed.y < 0)
        mScale = Vector2f(mScale.x * 0.998, mScale.y * 0.998);
    else
        mScale = Vector2f(mScale.x * 1.002, mScale.y * 1.002);
    mSprite.setScale(mScale);
    mSprite.setPosition(mPosition);
}





