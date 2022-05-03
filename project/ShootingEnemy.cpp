
#include "ShootingEnemy.h"

void ShootingEnemy::draw(RenderTarget &target, RenderStates states) const {
    target.draw(mSprite);
}

void ShootingEnemy::move(Vector2f windowSize, double y) {
    mPosition = Vector2f(mPosition.x + mSpeed, mPosition.y);
    if (mPosition.x + mScale.x * 1600 > (windowSize.x - y) / 2 + y + (windowSize.x - y) / 2 * mPosition.y / windowSize.y or mPosition.x < (windowSize.x - y) / 2 - mPosition.y * mPosition.y / windowSize.y) {
        mSpeed = -mSpeed;
        mPosition = Vector2f(mPosition.x + mSpeed, mPosition.y);
        mPosition = Vector2f(mPosition.x + mSpeed, mPosition.y);
    }
    mSprite.setPosition(mPosition);
}

void ShootingEnemy::shoot(vector<Bullet*>* bullets, double y){
    Time t1 = mTimer.getElapsedTime();
    if (t1 > nextShoot) {
        Bullet *b = new Bullet(Vector2f(mPosition.x + mScale.x * 800, mPosition.y + mScale.x * 1620), Color::Red, y);
        bullets->push_back(b);
        nextShoot = seconds(float(rand()) / float(RAND_MAX) * 3);
        mTimer.restart();
    }
}
