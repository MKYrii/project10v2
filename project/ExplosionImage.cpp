
#include "ExplosionImage.h"
#include <cmath>

void ExplosionImage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (radius + 20 < sqrt(pow(mRocket->getPosition().x - 5 - mTarget.x, 2) + pow(mRocket->getPosition().y - 5 - mTarget.y, 2)) ) {
        target.draw(*mRocket);
    }
    else {
        target.draw(mSprite);
    }


}

void ExplosionImage::update() {
    if (radius + 20 < sqrt(pow(mRocket->getPosition().x - 5 - mTarget.x, 2) + pow(mRocket->getPosition().y - 5 - mTarget.y, 2))) {
        mRocket->move(mRocketSpeed);
    }
    else {
        mTexture->loadFromImage(*mImage, IntRect(0 + number % 8 * 240, 0 + number / 8 * 240, +240u, +240u));
        number = number + 1;
        if (number == 1)
            sound.play();
    }

}

Vector2f ExplosionImage::getTarget() {
    return mTarget;
}
