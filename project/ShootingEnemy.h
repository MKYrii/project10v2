#ifndef GAMESTARS_SHOOTINGENEMY_H
#define GAMESTARS_SHOOTINGENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

class ShootingEnemy: public Enemy, public Drawable {
public:
    ShootingEnemy(Vector2f position, Clock startTime, int health = 3) {
        mScale = Vector2f(0.05, 0.05);
        mTimer = startTime;
        mTexture->loadFromFile("..\\grayShip.png");
        mSprite.setTexture(*mTexture);
        mSprite.setScale(mScale);
        mPosition = position;
        mSprite.setPosition(mPosition.x, mPosition.y);
        mHealth = health;
    }
    void shoot(vector<Bullet*>* bullets, double y);
    void move(Vector2f windowSize, double y);

private:
    void draw(RenderTarget &target, RenderStates states) const override;
    Clock mTimer;
    Time nextShoot = seconds(float(rand()) / float(RAND_MAX) * 3);
    float mSpeed = 2.5;
};


#endif //GAMESTARS_SHOOTINGENEMY_H
