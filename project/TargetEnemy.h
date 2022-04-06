
#ifndef GAMESTARS_TARGETENEMY_H
#define GAMESTARS_TARGETENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Character.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

class TargetEnemy: public Enemy, public Drawable {
public:
    TargetEnemy(Vector2f position, Character* character, int health = 3) {
        mCharacter = character;
        mScale = Vector2f(0.16, 0.16);
        mTexture->loadFromFile("..\\orangeShip.png");
        mSprite.setTexture(*mTexture);
        mSprite.setScale(mScale);
        mPosition = position;
        mSprite.setPosition(mPosition.x, mPosition.y);
        mHealth = health;
    }
    void move();

private:
    void draw(RenderTarget &target, RenderStates states) const override;
    float mSpeed = 3;
    Character* mCharacter;
};


#endif //GAMESTARS_TARGETENEMY_H
