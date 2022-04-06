
#ifndef GAMESTARS_EXPLOSIONIMAGE_H
#define GAMESTARS_EXPLOSIONIMAGE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

using namespace std;
using namespace sf;

class ExplosionImage: public Drawable {
public:
    ExplosionImage(Vector2i target, Vector2f position) {
        mRocketSpeed = Vector2f(double((target.x - position.x)) / 20.0, double((target.y - position.y)) / 20.0);
        mTarget = Vector2f(target.x - 60, target.y - 60);

        mImage->loadFromFile("..\\explosion-min1.png");
        mTexture->loadFromImage(*mImage, IntRect(0u, 0u, +240u, +240u));
        mSprite.setTexture(*mTexture);
        mSprite.setScale(0.5, 0.5);
        mSprite.setPosition(mTarget);

        mRocket->setRadius(5);
        mRocket->setFillColor(Color::Yellow);
        mRocket->setPosition(position.x - 5, position.y - 5);
        buffer.loadFromFile("..\\explosion.wav");
        sound.setBuffer(buffer);
        sound.setVolume(17);
    }

    void update();
    Vector2f getTarget();
    int number = 0;
    float radius = 70;
    ~ExplosionImage(){
        delete mTexture;
        delete mImage;
        delete mRocket;
    }
    SoundBuffer buffer;
    Sound sound;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    Image* mImage = new Image;
    Texture* mTexture = new Texture;
    Sprite mSprite;
    Vector2f mRocketSpeed;
    CircleShape* mRocket = new CircleShape;
    Vector2f mTarget;
};


#endif //GAMESTARS_EXPLOSIONIMAGE_H
