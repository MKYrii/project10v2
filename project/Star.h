
#ifndef GAMESTARS_STAR_H
#define GAMESTARS_STAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Star: public Drawable {
public:
    Star(Vector2f position, double y) {
        mCircle->setPosition(position);
        mCircle->setFillColor(Color(207, 255, 240, 128));
        mCircle->setRadius(2);
        mSpeed.x = mSpeed.y * ((1980 - y) / 2) / sqrt(pow((1980 - y) / 2, 2) + 1080 * 1080) * -1 *
                (abs(position.x - 1980 / 2) * 2 / (y + 2 * (1980 - y) / 2 * position.y / 1080));
        if (position.x > 1980 / 2)
            mSpeed.x = mSpeed.x * -1;
    }
    void update();
    Vector2f getPosition();
    ~Star() override {
        delete mCircle;
    }
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    CircleShape* mCircle = new CircleShape;
    Vector2f mSpeed = Vector2f(0, 1);
};


#endif //GAMESTARS_STAR_H
