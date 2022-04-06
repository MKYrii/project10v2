

#ifndef GAMESTARS_WALKINGENEMY_H
#define GAMESTARS_WALKINGENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Enemy.h"

using namespace sf;
using namespace std;

class WalkingEnemy: public Enemy, public Drawable {
public:
    WalkingEnemy(Vector2f position, int health = 3) {
        mTexture->loadFromFile("..\\dragonShip.png");
        mSprite.setTexture(*mTexture);
        mSprite.setScale(mScale);
        mPosition = position;
        mSprite.setPosition(mPosition.x, mPosition.y);
        mHealth = health;
        mScale = Vector2f(0.12, 0.12);
    }

    void move(Vector2f windowSize,double y);

private:
    void draw(RenderTarget &target, RenderStates states) const override;
    Vector2f mSpeed = Vector2f(-3, 10);
};


#endif //GAMESTARS_WALKINGENEMY_H
