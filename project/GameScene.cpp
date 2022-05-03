
#include "GameScene.h"

void GameScene::addBullet(Bullet *bullet)
{
    mBullets.push_back(bullet);
}

void GameScene::generateStar() {
    Star *star = new Star(Vector2f((double(rand()) / double(RAND_MAX)) * y + (x - y) / 2, 5), y);
    mStars.push_back(star);
}

void GameScene::addRocket(Vector2i target) {
    auto *rocket = new ExplosionImage(target, Vector2f(mCharacter.getPosition().x + 920 * mCharacter.getScale().x / 2, mCharacter.getPosition().y));
    mRockets.push_back(rocket);
}

void GameScene::removeOutOfBoundsBullets() {
    bool wasDeleted = true;
    while (wasDeleted) {
        wasDeleted = false;
        for (int i = 0; i < mBullets.size(); ++i) {
            Vector2f position = mBullets[i]->getPosition();
            if (position.x > mWindowSize.x or position.y > mWindowSize.y or position.x < 0 or position.y < 0) {
                delete mBullets[i];
                mBullets.erase(mBullets.begin() + i);
                wasDeleted = true;
                break;
            }
        }
    }
}

void GameScene::destroyRockets() {
    bool wasDeleted = true;
    while (wasDeleted) {
        wasDeleted = false;
        for (int i = 0; i < mRockets.size(); ++i) {
            if (mRockets[i]->number >= 48) {
                delete mRockets[i];
                mRockets.erase(mRockets.begin() + i);
                wasDeleted = true;
                break;
            }
        }
    }
}

void GameScene::removeOutOfBoundsStars() {
    bool wasDeleted = true;
    while (wasDeleted) {
        wasDeleted = false;
        for (int i = 0; i < mStars.size(); ++i) {
            Vector2f position = mStars[i]->getPosition();
            if (position.x > mWindowSize.x or position.y > mWindowSize.y or position.x < 0 or position.y < 0) {
                delete mStars[i];
                mStars.erase(mStars.begin() + i);
                wasDeleted = true;
                break;
            }
        }
    }
}


void GameScene::killEnemies() {
    bool wasKilled = true;
    while (wasKilled) {
        wasKilled = false;
        for (int i = 0; i < walkingEnemies.size(); ++i) {
            if (not walkingEnemies[i]->isAlive()) {
                delete walkingEnemies[i];
                countEnemies--;
                walkingEnemies.erase(walkingEnemies.begin() + i);
                wasKilled = true;
                *mScore += 80 + 10 * level;
                break;
            }
        }
    }
    wasKilled = true;
    while (wasKilled) {
        wasKilled = false;
        for (int i = 0; i < shootingEnemies.size(); ++i) {
            if (not shootingEnemies[i]->isAlive()) {
                delete shootingEnemies[i];
                shootingEnemies.erase(shootingEnemies.begin() + i);
                wasKilled = true;
                countEnemies--;
                *mScore += 90 + 10 * level;
                break;
            }
        }
    }
    wasKilled = true;
    while (wasKilled) {
        wasKilled = false;
        for (int i = 0; i < targetEnemies.size(); ++i) {
            if (not targetEnemies[i]->isAlive()) {
                delete targetEnemies[i];
                targetEnemies.erase(targetEnemies.begin() + i);
                wasKilled = true;
                countEnemies--;
                *mScore += 100 + 10 * level;
                break;
            }
        }
    }
}

void GameScene::bulletCollisions() {
    bool wasHited = true;
    while (wasHited) {
        wasHited = false;
        for (int i = 0; i < mBullets.size(); ++i) {
            Vector2f position = mBullets[i]->getPosition();
            if (mCharacter.getPosition().x < position.x and position.x < mCharacter.getPosition().x + mCharacter.getScale().x * 920 and
                mCharacter.getPosition().y < position.y and position.y < mCharacter.getPosition().y + mCharacter.getScale().y * 982) {
                delete mBullets[i];
                mCharacter.health--;
                if (mCharacter.health <= 0) {
                    mCharacter.isAlive = false;
                }
                mBullets.erase(mBullets.begin() + i);
                wasHited = true;
                break;
            }
            for (auto enemy: walkingEnemies) {
                if (enemy->getPosition().x < position.x and position.x < enemy->getPosition().x + enemy->getScale().x * 655 and
                    enemy->getPosition().y < position.y and position.y < enemy->getPosition().y + enemy->getScale().y * 655 and
                    mBullets[i]->getColor() == Color::Blue) {
                    delete mBullets[i];
                    enemy->hit();
                    mBullets.erase(mBullets.begin() + i);
                    wasHited = true;
                    break;
                }
            }
            for (auto enemy: shootingEnemies) {
                if (enemy->getPosition().x < position.x and position.x < enemy->getPosition().x + enemy->getScale().x * 1600 and
                    enemy->getPosition().y < position.y and position.y < enemy->getPosition().y + enemy->getScale().y * 1600) {
                    delete mBullets[i];
                    enemy->hit();
                    mBullets.erase(mBullets.begin() + i);
                    wasHited = true;
                    break;
                }
            }
            for (auto enemy: targetEnemies) {
                if (enemy->getPosition().x < position.x and position.x < enemy->getPosition().x + enemy->getScale().x * 500 and
                    enemy->getPosition().y < position.y and position.y < enemy->getPosition().y + enemy->getScale().y * 500 and mBullets[i]->getColor() == Color::Blue) {
                    delete mBullets[i];
                    enemy->hit();
                    mBullets.erase(mBullets.begin() + i);
                    wasHited = true;
                    break;
                }
            }
        }
    }
}

void GameScene::explosionCollisions() {

    for (int i = 0; i < walkingEnemies.size(); ++i) {
        Vector2f position = Vector2f(walkingEnemies[i]->getPosition().x + 665 * walkingEnemies[i]->getScale().x / 2,
                                     walkingEnemies[i]->getPosition().y + 665 * walkingEnemies[i]->getScale().y / 2);
        for (auto explosion: mRockets) {
            if (explosion->number > 0 and explosion->radius + 665 * walkingEnemies[i]->getScale().x / 2 >= sqrt(pow((position.x - explosion->getTarget().x), 2) +
                                          pow((position.y - explosion->getTarget().y), 2))) {
                walkingEnemies[i]->mHealth = 0;
            }
        }
    }
    for (int i = 0; i < shootingEnemies.size(); ++i) {
        Vector2f position = Vector2f(shootingEnemies[i]->getPosition().x + shootingEnemies[i]->getScale().x * 1600 / 2,
                                     shootingEnemies[i]->getPosition().y + shootingEnemies[i]->getScale().y * 1600 / 2);
        for (auto explosion: mRockets) {
            if (explosion->number > 0 and explosion->radius + shootingEnemies[i]->getScale().y * 1600 / 2 >= sqrt(pow((position.x - explosion->getTarget().x), 2) +
                                          pow((position.y - explosion->getTarget().y), 2))) {
                shootingEnemies[i]->mHealth = 0;
            }
        }
    }
    for (int i = 0; i < targetEnemies.size(); ++i) {
        Vector2f position = Vector2f(targetEnemies[i]->getPosition().x + targetEnemies[i]->getScale().x * 500 / 2,
                                     targetEnemies[i]->getPosition().y + targetEnemies[i]->getScale().y * 500 / 2);
        for (auto explosion: mRockets) {
            if (explosion->number > 0 and explosion->radius + targetEnemies[i]->getScale().y * 500 / 2 >= sqrt(pow((position.x - explosion->getTarget().x), 2) +
                                                                                        pow((position.y - explosion->getTarget().y), 2))) {
                targetEnemies[i]->mHealth = 0;
            }
        }
    }

}

void GameScene::enemyCollisions() {
    for (auto enemy: walkingEnemies) {
        if (mCharacter.getBounds().contains(enemy->getPosition()) or mCharacter.getBounds().contains(
                Vector2f(enemy->getPosition().x + enemy->getScale().x * 655,
                         enemy->getPosition().y + enemy->getScale().y * 655)) or mCharacter.getBounds().contains(
                Vector2f(enemy->getPosition().x + enemy->getScale().x * 655, enemy->getPosition().y)) or
            mCharacter.getBounds().contains(
                    Vector2f(enemy->getPosition().x, enemy->getPosition().y + enemy->getScale().y * 655))) {
            mCharacter.isAlive = false;
        }
    }
    for (auto enemy: targetEnemies) {
        if (mCharacter.getBounds().contains(enemy->getPosition()) or mCharacter.getBounds().contains(
                Vector2f(enemy->getPosition().x + enemy->getScale().x * 500,
                         enemy->getPosition().y + enemy->getScale().y * 500)) or mCharacter.getBounds().contains(
                Vector2f(enemy->getPosition().x + enemy->getScale().x * 500, enemy->getPosition().y)) or
            mCharacter.getBounds().contains(
                    Vector2f(enemy->getPosition().x, enemy->getPosition().y + enemy->getScale().y * 500))) {
            mCharacter.isAlive = false;
        }
    }
}

bool GameScene::isGameOver() {
    if (not mCharacter.isAlive or countEnemies == 0)
        return true;
    else
        return false;
}

// функция, выполняющая все подсчеты между кадрами, изменяющая объекты
void GameScene::processFrame() {
    if (not mCharacter.isAlive or countEnemies == 0 and level == maxLevel)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and pt.getElapsedTime().asSeconds() > 0.5) {
        if (not p)
            p = true;
        else
            p = false;
        pt.restart();
    }
    if (p)
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (mCharacter.getPosition().y + mCharacter.getSpeed() >= 150) {
            mCharacter.move(0, -mCharacter.getSpeed());
            if ((mCharacter.getPosition().x / (mWindowSize.y - mCharacter.getPosition().y) <
                 (x - y) / 2 / mWindowSize.y)
                or ((mWindowSize.x - mCharacter.getPosition().x - 920 * mCharacter.getScale().x) /
                    (mWindowSize.y - mCharacter.getPosition().y) < (x - y) / 2 / mWindowSize.y)) {
                mCharacter.move(0, mCharacter.getSpeed());
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (mCharacter.getPosition().y + mCharacter.getSpeed() + mCharacter.getScale().y * 982 <= mWindowSize.y)
            mCharacter.move(0, mCharacter.getSpeed());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mCharacter.move(-mCharacter.getSpeed(), 0);
        if (mCharacter.getPosition().x / (mWindowSize.y - mCharacter.getPosition().y) < (x - y) / 2 / mWindowSize.y) {
            mCharacter.move(mCharacter.getSpeed(), 0);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mCharacter.move(mCharacter.getSpeed(), 0);
        if ((mWindowSize.x - mCharacter.getPosition().x - 920 * mCharacter.getScale().x) /
            (mWindowSize.y - mCharacter.getPosition().y) < (x - y) / 2 / mWindowSize.y) {
            mCharacter.move(-mCharacter.getSpeed(), 0);
        }
    }
    for (Bullet *bullet: mBullets) {
        bullet->update();
    }
    for (Star *star: mStars) {
        star->update();
    }
    if (sf::Mouse::isButtonPressed(Mouse::Left)) {
        Time t = seconds(0.2);
        if (mCharacter.mTimer.getElapsedTime() > t) {
            addBullet(new Bullet(Vector2f(mCharacter.getPosition().x + 920 * mCharacter.getScale().x / 2,
                                          mCharacter.getPosition().y), Color::Blue, y));
            mCharacter.mTimer.restart();
        }
    }
    if (sf::Mouse::isButtonPressed(Mouse::Right)) {
        Time t = seconds(0.5);
        if (mCharacter.mTimer.getElapsedTime() > t and mCharacter.countRockets > 0) {
            addRocket(sf::Mouse::getPosition());
            mCharacter.mTimer.restart();
            mCharacter.countRockets = mCharacter.countRockets - 1;
        }
    }

    Time t = seconds(1);
    if (mTimer.getElapsedTime() > t) {
        generateStar();
        mTimer.restart();
    }

    for (auto enemy: shootingEnemies) {
        enemy->shoot(&mBullets, y);
        enemy->move(mWindowSize, y);
    }
    for (auto enemy: walkingEnemies) {
        enemy->move(mWindowSize, y);
    }
    for (auto enemy: targetEnemies) {
        enemy->move();
    }

    for (auto rocket: mRockets) {
        rocket->update();
    }

    destroyRockets();
    removeOutOfBoundsStars();
    removeOutOfBoundsBullets();
    bulletCollisions();
    explosionCollisions();
    killEnemies();
    enemyCollisions();
}

// отрисовка кадра
void GameScene::draw(RenderTarget &target, RenderStates states) const {
    for (Star *star: mStars)
        target.draw(*star);
    target.draw(*leftSight);
    target.draw(*rightSight);
    target.draw(mCharacter);

    Text characterStateHp;
    Text enemiesState;
    Text characterStateRocket;
    Text levelState;
    string s = to_string(mCharacter.health);
    characterStateHp = Text("Health: " + s, font, int(mWindowSize.y / 32));
    characterStateHp.setOrigin(mWindowSize.y / 32 / 2 * endingTextLose.getString().getSize() / 2,
                             mWindowSize.y / 64 * 4 / 3);
    characterStateHp.setFillColor(Color::White);
    characterStateHp.setPosition(mWindowSize.x - 230, 135);
    s = to_string(countEnemies);
    enemiesState = Text("Remaining enemies: " + s, font, int(mWindowSize.y / 32));
    enemiesState.setOrigin(mWindowSize.y / 32 / 2 * endingTextLose.getString().getSize() / 2,
                           mWindowSize.y / 64 * 4 / 3);
    enemiesState.setFillColor(Color::White);
    enemiesState.setPosition(mWindowSize.x - 270, 25);
    s = to_string(mCharacter.countRockets);
    characterStateRocket = Text("Remaining rockets: " + s, font, int(mWindowSize.y / 32));
    characterStateRocket.setOrigin(mWindowSize.y / 32 / 2 * endingTextLose.getString().getSize() / 2,
                           mWindowSize.y / 64 * 4 / 3);
    characterStateRocket.setFillColor(Color::White);
    characterStateRocket.setPosition(mWindowSize.x - 250, 80);
    s = to_string(level);
    levelState = Text("Level: " + s, font, int(mWindowSize.y / 32));
    levelState.setOrigin(mWindowSize.y / 32 / 2 * endingTextLose.getString().getSize() / 2,
                                   mWindowSize.y / 64 * 4 / 3);
    levelState.setFillColor(Color::White);
    levelState.setPosition(mWindowSize.x - 210, 190);
    target.draw(characterStateHp);
    target.draw(enemiesState);
    target.draw(characterStateRocket);
    target.draw(levelState);

    for (ShootingEnemy *enemy: shootingEnemies)
        target.draw(*enemy);
    for (WalkingEnemy *enemy: walkingEnemies)
        target.draw(*enemy);
    for (TargetEnemy *enemy: targetEnemies)
        target.draw(*enemy);
    for (Bullet *bullet: mBullets)
        target.draw(*bullet);
    for (ExplosionImage *rocket: mRockets)
        target.draw(*rocket);

    if (not mCharacter.isAlive) {
        target.draw(endingRect);
        target.draw(endingTextLose);
    } else if (countEnemies == 0 and level == maxLevel) {
        target.draw(endingRect);
        target.draw(endingTextWin);
    }
    else if (countEnemies == 0 and level != maxLevel) {
        target.draw(endingRect);
        target.draw(nextLevel);
    }
}

bool GameScene::isAlive() {
    return mCharacter.isAlive;
}

void GameScene::restart() {
    mCharacter.setPosition(Vector2f(mWindowSize.x / 2.0 - 70, mWindowSize.y - 200));
    level += 1;
    if (countWalkingEnemies < 8) {
        countShootingEnemies += 1;
        countWalkingEnemies += 1;
    }
    if (level >= 2 and countTargetEnemies < 5) {
        countTargetEnemies += 1;
        healthT += 1;
    }
    healthS += 1 + level % 2;
    healthW += 1 + level % 2;


    for (int i = 0; i < countShootingEnemies; i++) {
        int p = 50;
        ShootingEnemy* enemy = new ShootingEnemy(Vector2f((y + 2 * p * p / 1080) / countShootingEnemies * i + (y + 2 * p * p / 1080) / countShootingEnemies / 2 - 80 / 2 + (x - y) / 2 - p * p / 1080 , p), Clock(), healthS);
        shootingEnemies.emplace_back(enemy);
    }
    for (int i = 0; i < countWalkingEnemies; i++) {
        int p = 250;
        WalkingEnemy* enemy = new WalkingEnemy(Vector2f((y + 2 * p * p / 1080) / countWalkingEnemies * i + (y + 2 * p * p / 1080) / countWalkingEnemies / 2 - 80 / 2 + (x - y) / 2 - p * p / 1080 , p), healthW);
        walkingEnemies.emplace_back(enemy);
    }
    for (int i = 0; i < countTargetEnemies; i++) {
        int p = 150;
        TargetEnemy* enemy = new TargetEnemy(Vector2f((y + 2 * p * p / 1080) / countTargetEnemies * i + (y + 2 * p * p / 1080) / countTargetEnemies / 2 - 80 / 2 + (x - y) / 2 - p * p / 1080 , p), &mCharacter, healthT);
        targetEnemies.emplace_back(enemy);
    }
    bool wasDeleted = true;
    while (wasDeleted) {
        wasDeleted = false;
        for (int i = 0; i < mRockets.size(); ++i) {
            delete mRockets[i];
            mRockets.erase(mRockets.begin() + i);
            wasDeleted = true;
            break;
        }
    }
    wasDeleted = true;
    while (wasDeleted) {
        wasDeleted = false;
        for (int i = 0; i < mBullets.size(); ++i) {
            delete mBullets[i];
            mBullets.erase(mBullets.begin() + i);
            wasDeleted = true;
            break;
        }
    }
    countEnemies = countWalkingEnemies + countShootingEnemies + countTargetEnemies;
    nextLevel.setString("Level " + to_string(level + 1));
}
