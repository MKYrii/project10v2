

#ifndef GAMESTARS_BULLET_H
#define GAMESTARS_BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Bullet: public Drawable {
public:
    Bullet(Vector2f position, Color color, double y) {
        mCircle->setPosition(position);
        mCircle->setFillColor(color);
        if (color == Color::Blue) {
            mCircle->setRadius(mRadiusBlue);
            mCircle->setOrigin(mRadiusBlue, mRadiusBlue);
        }
        else {
            mCircle->setRadius(mRadiusRed);
            mCircle->setOrigin(mRadiusRed, mRadiusRed);
        }
        mSpeed.x = mSpeed.y * ((1980 - y) / 2) / sqrt(pow((1980 - y) / 2, 2) + 1080 * 1080) * -1 * (abs(position.x - 1980 / 2) * 2 / (y + 2 * (1980 - y) / 2 * position.y / 1080));
        if (position.x > 1980 / 2)
            mSpeed.x = mSpeed.x * -1;
        buffer.loadFromFile("..\\blast.wav");
        sound.setBuffer(buffer);
        sound.setVolume(10);
        sound.play();
    }

    float mRadiusBlue = 3;
    float mRadiusRed = 5;
    Vector2f getPosition() const;
    void update();
    Color getColor();
    ~Bullet() override {
        delete mCircle;
    }
    SoundBuffer buffer;
    Sound sound;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    Vector2f mSpeed = Vector2f(0, -15);
    CircleShape* mCircle = new CircleShape;
};


#endif //GAMESTARS_BULLET_H
