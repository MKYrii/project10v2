
#include "EndlessGame.h"

EndlessGame::EndlessGame(RenderWindow *window, int *score) {
    RectangleShape rect;
    Font font;
    Text firstLevel;
    rect.setSize(Vector2f(window->getSize().x / 3, window->getSize().y / 3));
    rect.setOrigin(window->getSize().x / 6, window->getSize().y / 6);
    rect.setPosition(window->getSize().x / 2, window->getSize().y / 2);
    rect.setFillColor(Color(0, 0, 89));
    rect.setOutlineColor(Color::Blue);
    rect.setOutlineThickness(5);
    font.loadFromFile("..\\calibri.ttf");
    firstLevel = Text("level 1", font, int(window->getSize().y / 12));
    firstLevel.setOrigin(window->getSize().y / 12 / 2 * firstLevel.getString().getSize() / 2, window->getSize().y / 24 * 4 / 3);
    firstLevel.setFillColor(Color::Red);
    firstLevel.setPosition(window->getSize().x / 2, window->getSize().y / 2);
    bool b = true;
    int n = 1, p = 1;
    GameScene gameScene(Vector2f(window->getSize()), "..\\calibri.ttf", 2, 2, 0, 3, 2, 2, 1, 100000, score);

    while(window->isOpen() and b) {
        Event event;
        while(window->pollEvent(event)) {
            if (event.type == Event::Closed or not gameScene.isAlive() or (gameScene.isGameOver() and n == 100000)) {
                Sleep(3000);
                b = false;
                window->clear(Color::Black);
                return;
            }
        }
        window->clear(Color::Black);

        if (p == 1) {
            p = 0;
            window->draw(gameScene);
            window->draw(rect);
            window->draw(firstLevel);
            window->display();
            Sleep(3000);
            continue;
        }

        if (gameScene.isGameOver() and gameScene.isAlive()) {
            n += 1;
            Sleep(2000);
            gameScene.restart();
            window->draw(gameScene);
            window->display();
            Sleep(1000);
            continue;
        }
        gameScene.processFrame();
        window->draw(gameScene);
        window->display();
    }

}