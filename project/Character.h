
#ifndef GAMESTARS_CHARACTER_H
#define GAMESTARS_CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

using namespace sf;
using namespace std;

class Character: public Drawable {
public:
    Character(Vector2f position = Vector2f(1, 1)) {
        mTexture->loadFromFile("..\\ship.png");
        mSprite.setTexture(*mTexture);
        mSprite.setScale(mScale.x, mScale.y);
        mPosition = position;
        mSprite.setPosition(mPosition.x, mPosition.y);
    }
    void move(int x, int y);
    int getSpeed() const;
    void setPosition(Vector2f position);
    Vector2f getPosition() const;
    Vector2f getScale() const;
    int health = 3;
    bool isAlive = true;
    Rect<float> getBounds();
    Clock mTimer;
    int countRockets = 5;
private:
    void draw(RenderTarget &target, RenderStates states) const override;
    Texture* mTexture = new Texture;
    Sprite mSprite;

    int mSpeed = 12;
    Vector2f mPosition;
    Vector2f mScale = Vector2f(0.12, 0.12);

};


#endif //GAMESTARS_CHARACTER_H
