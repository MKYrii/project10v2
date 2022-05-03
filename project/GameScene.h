#ifndef GAMESTARS_GAMESCENE_H
#define GAMESTARS_GAMESCENE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "WalkingEnemy.h"
#include "ShootingEnemy.h"
#include "Character.h"
#include <cmath>
#include "windows.h"
#include <string>
#include "Star.h"
#include "ExplosionImage.h"
#include "TargetEnemy.h"

using namespace sf;
using namespace std;

class GameScene: public Drawable {
public:
    GameScene(Vector2f windowSize, string fontLink, int walkingEnemyCount, int shootingEnemyCount, int targetEnemyCount, int wHealth = 3, int sHealth = 3, int tHealth = 3, int n = 1, int maxn = 1, int* score = nullptr){
        Character character(Vector2f(windowSize.x / 2.0 - 70, windowSize.y - 200));
        mCharacter = character;
        mWindowSize = windowSize;
        x = windowSize.x;
        y = (x * 920 * 0.15 * pow(0.995, windowSize.y / mCharacter.getSpeed())) / (920 * 0.15);
        level = n;
        maxLevel = maxn;
        countShootingEnemies = shootingEnemyCount;
        countWalkingEnemies = walkingEnemyCount;
        countTargetEnemies = targetEnemyCount;
        healthS = sHealth;
        healthW = wHealth;
        healthT = tHealth;
        if (maxn == 100000) {
            mCharacter.countRockets = 20;
            mCharacter.health = 10;
        }
        // расстановка противников и генерация звезд

        for (int i = 0; i < countShootingEnemies; i++) {
            int p = 50;
            ShootingEnemy* enemy = new ShootingEnemy(Vector2f((y + 2 * p * p / 1080) / shootingEnemyCount * i + (y + 2 * p * p / 1080) / shootingEnemyCount / 2 - 80 / 2 + (x - y) / 2 - p * p / 1080 , p), Clock(), sHealth);
            shootingEnemies.emplace_back(enemy);
        }
        for (int i = 0; i < countWalkingEnemies; i++) {
            int p = 250;
            WalkingEnemy* enemy = new WalkingEnemy(Vector2f((y + 2 * p * p / 1080) / walkingEnemyCount * i + (y + 2 * p * p / 1080) / walkingEnemyCount / 2 - 80 / 2 + (x - y) / 2 - p * p / 1080 , p), wHealth);
            walkingEnemies.emplace_back(enemy);
        }
        for (int i = 0; i < countTargetEnemies; i++) {
            int p = 150;
            TargetEnemy* enemy = new TargetEnemy(Vector2f((y + 2 * p * p / 1080) / targetEnemyCount * i + (y + 2 * p * p / 1080) / targetEnemyCount / 2 - 80 / 2 + (x - y) / 2 - p * p / 1080 , p), &mCharacter, tHealth);
            targetEnemies.emplace_back(enemy);
        }
        countEnemies = countWalkingEnemies + countShootingEnemies + countTargetEnemies;

        for (int i = 0; i < 50; ++i) {
            Star* star = new Star(Vector2f((double(rand()) / double(RAND_MAX)) * y + (x - y) / 2,
                                           double(rand()) / double(RAND_MAX) * windowSize.y), y);
            mStars.push_back(star);
        }

        leftSight->setRotation(90 + atan(((x - y) / 2) / windowSize.y) * 180 / 3.14159265);
        leftSight->setSize(Vector2f(sqrt(pow((x - y) / 2, 2) + pow(windowSize.y, 20)), 5));
        leftSight->setPosition((x - y) / 2, 0);
        leftSight->setFillColor(Color::White);
        rightSight->setRotation( 90 - atan(((x - y) / 2) / windowSize.y) * 180 / 3.14159265);
        rightSight->setSize(Vector2f(sqrt(pow((x - y) / 2, 2) + pow(windowSize.y, 20)), 5));
        rightSight->setPosition(y + (x - y) / 2, 0);
        rightSight->setFillColor(Color::White);

        endingRect.setSize(Vector2f(windowSize.x / 3, windowSize.y / 3));
        endingRect.setOrigin(windowSize.x / 6, windowSize.y / 6);
        endingRect.setPosition(windowSize.x / 2, windowSize.y / 2);
        endingRect.setFillColor(Color(0, 0, 89));
        endingRect.setOutlineColor(Color::Blue);
        endingRect.setOutlineThickness(5);

        font.loadFromFile(fontLink);
        endingTextLose = Text("Defeat", font, int(windowSize.y / 12));
        endingTextLose.setOrigin(windowSize.y / 12 / 2 * endingTextLose.getString().getSize() / 2, windowSize.y / 24 * 4 / 3);
        endingTextLose.setFillColor(Color::Red);
        endingTextLose.setPosition(windowSize.x / 2, windowSize.y / 2);
        endingTextWin = Text("Victory", font, int(windowSize.y / 12));
        endingTextWin.setOrigin(windowSize.y / 12 / 2 * endingTextLose.getString().getSize() / 2, windowSize.y / 24 * 4 / 3);
        endingTextWin.setFillColor(Color::Red);
        endingTextWin.setPosition(windowSize.x / 2, windowSize.y / 2);
        nextLevel = Text("level " + to_string(level + 1), font, int(windowSize.y / 12));
        nextLevel.setOrigin(windowSize.y / 12 / 2 * endingTextLose.getString().getSize() / 2, windowSize.y / 24 * 4 / 3);
        nextLevel.setFillColor(Color::Red);
        nextLevel.setPosition(windowSize.x / 2, windowSize.y / 2);
        mScore = score;


        pt.restart();
    }
    void processFrame();
    void addBullet(Bullet *bullet);
    void removeOutOfBoundsBullets();
    void removeOutOfBoundsStars();
    void bulletCollisions();
    bool isGameOver();
    void killEnemies();
    void enemyCollisions();
    void generateStar();
    void addRocket(Vector2i target);
    void destroyRockets();
    void explosionCollisions();
    bool isAlive();
    void restart();

private:
    void draw(RenderTarget &target, RenderStates states) const override;

    Character mCharacter;
    RectangleShape* leftSight = new RectangleShape;
    RectangleShape* rightSight = new RectangleShape;
    vector<ShootingEnemy*> shootingEnemies;
    vector<WalkingEnemy*> walkingEnemies;
    vector<TargetEnemy*> targetEnemies;
    vector<Bullet*> mBullets;
    vector<Star*> mStars;
    vector<ExplosionImage*> mRockets;
    Vector2f mWindowSize;
    double x, y;
    RectangleShape endingRect;
    Font font;
    Text endingTextLose;
    Text endingTextWin;
    Text nextLevel;
    int countEnemies, countWalkingEnemies, countShootingEnemies, countTargetEnemies, healthW, healthS, healthT;
    int level, maxLevel;
    int* mScore;
    Clock mTimer = Clock();
    bool p = false;
    Clock pt = Clock();
};


#endif //GAMESTARS_GAMESCENE_H
