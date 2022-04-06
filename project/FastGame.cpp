
#include "FastGame.h"

FastGame::FastGame(RenderWindow *window, int* score) {
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

    GameScene gameScene1(Vector2f(window->getSize()), "..\\calibri.ttf", 2, 2, 0, 3, 2, 3, 1, 5, score);
    GameScene gameScene2(Vector2f(window->getSize()), "..\\calibri.ttf", 3, 3, 1, 4, 3, 3, 2, 5, score);
    GameScene gameScene3(Vector2f(window->getSize()), "..\\calibri.ttf", 5, 5, 2, 5, 4, 3, 3, 5, score);
    GameScene gameScene4(Vector2f(window->getSize()), "..\\calibri.ttf", 6, 6, 3, 7, 5, 4, 4, 5, score);
    GameScene gameScene5(Vector2f(window->getSize()), "..\\calibri.ttf", 8, 7, 4, 11, 10, 6, 5, 5, score);
    int n1 = 1, n2 = 1, n3 = 1, n4 = 1, n5 = 1;
    bool b = true;
    while (window->isOpen() and b) {
        Event event;
        while (window->pollEvent(event)){
            if (event.type == Event::Closed or gameScene5.isGameOver() or not gameScene1.isAlive() or not gameScene2.isAlive() or not gameScene3.isAlive() or not gameScene4.isAlive()) {
                Sleep(3000);
                b = false;
                window->clear(Color::Black);
                return;
            }
        }
        window->clear(Color::Black);

        if (n1 == 1) {
            n1 = 0;
            window->draw(gameScene1);
            window->draw(rect);
            window->draw(firstLevel);
            window->display();
            Sleep(3000);
            continue;
        }
        if (not gameScene1.isGameOver() or not gameScene1.isAlive()) {
            gameScene1.processFrame();
            window->draw(gameScene1);
        }
        else if (not gameScene2.isGameOver() or not gameScene2.isAlive() and gameScene1.isGameOver()) {
            if (n2 == 1) {
                n2 = 0;
                window->draw(gameScene1);
                Sleep(3000);
            }
            gameScene2.processFrame();
            window->draw(gameScene2);
        }
        else if (not gameScene3.isGameOver() or not gameScene3.isAlive() and gameScene2.isGameOver()) {
            if (n3 == 1) {
                n3 = 0;
                window->draw(gameScene2);
                Sleep(3000);
            }
            gameScene3.processFrame();
            window->draw(gameScene3);
        }
        else if (not gameScene4.isGameOver() or not gameScene4.isAlive() and gameScene3.isGameOver()) {
            if (n4 == 1) {
                n4 = 0;
                window->draw(gameScene3);
                Sleep(3000);
            }
            gameScene4.processFrame();
            window->draw(gameScene4);
        }
        else if (gameScene4.isGameOver() or not gameScene5.isAlive()) {
            if (n5 == 1) {
                n5 = 0;
                window->draw(gameScene4);
                Sleep(3000);
            }
            gameScene5.processFrame();
            window->draw(gameScene5);
        }
        window->display();
    }
}
