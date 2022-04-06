

#ifndef GAMESTARS_ENEMY_H
#define GAMESTARS_ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Enemy {
public:
    Vector2f mPosition;
    Texture* mTexture = new Texture;
    Sprite mSprite;
    int mHealth = 3;

    bool isAlive(){
        if (mHealth > 0)
            return true;
        else
            return false;

    }
    void hit(){
        mHealth = mHealth - 1;
    }

    Vector2f getPosition(){
        return mPosition;
    }

    Vector2f getScale(){
        return mScale;
    }

    ~Enemy() {
        delete mTexture;
    }


protected:
    Vector2f mScale;
};


#endif //GAMESTARS_ENEMY_H
