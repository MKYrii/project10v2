
#include "TargetEnemy.h"

void TargetEnemy::draw(RenderTarget &target, RenderStates states) const {
    target.draw(mSprite);
}

void TargetEnemy::move() {
    if (mPosition.x < mCharacter->getPosition().x)
    mPosition.x += mSpeed / sqrt((mCharacter->getPosition().x - mPosition.x) * (mCharacter->getPosition().x -
                mPosition.x) + (mCharacter->getPosition().y - mPosition.y) * (mCharacter->getPosition().y -
                        mPosition.y)) * (mCharacter->getPosition().x - mPosition.x);
    else
        mPosition.x += mSpeed / sqrt((mCharacter->getPosition().x - mPosition.x) * (mCharacter->getPosition().x -
                mPosition.x) + (mCharacter->getPosition().y - mPosition.y) * (mCharacter->getPosition().y -
                        mPosition.y)) * (mCharacter->getPosition().x - mPosition.x);
    if (mPosition.y < mCharacter->getPosition().y) {
        mScale = Vector2f(mScale.x * 1.001, mScale.y * 1.001);
        mPosition.y += mSpeed / sqrt((mCharacter->getPosition().x - mPosition.x) * (mCharacter->getPosition().x -
                mPosition.x) + (mCharacter->getPosition().y - mPosition.y) * (mCharacter->getPosition().y -
                        mPosition.y)) * (mCharacter->getPosition().y - mPosition.y);
    }
    else {
        mScale = Vector2f(mScale.x * 0.999, mScale.y * 0.999);
        mPosition.y += mSpeed / sqrt((mCharacter->getPosition().x - mPosition.x) * (mCharacter->getPosition().x -
                mPosition.x) + (mCharacter->getPosition().y - mPosition.y) * (mCharacter->getPosition().y -
                        mPosition.y)) * (mCharacter->getPosition().y - mPosition.y);
    }
    mSprite.setScale(mScale);
    mSprite.setPosition(mPosition);
}
