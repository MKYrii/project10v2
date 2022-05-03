#include <SFML/Graphics.hpp>
#include <fstream>
#include "FastGame.h"
#include "EndlessGame.h"
#include <stdlib.h>

using namespace sf;
using namespace std;

int main(){
    RenderWindow window(VideoMode::getDesktopMode(), "GameStars", Style::Fullscreen);
    window.setFramerateLimit(60);

    RectangleShape ButtonGame1 = RectangleShape(Vector2f(window.getSize().x / 3.5, window.getSize().y / 8));
    ButtonGame1.setFillColor(Color(205, 205, 255));
    ButtonGame1.setOutlineThickness(8);
    ButtonGame1.setOutlineColor(Color(0, 0, 104));
    ButtonGame1.setOrigin(window.getSize().x / 7, window.getSize().y / 16);
    ButtonGame1.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 8 * 2));

    RectangleShape ButtonGame2 = ButtonGame1;
    ButtonGame2.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 8 * 4));

    RectangleShape ButtonScore = ButtonGame1;
    ButtonScore.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 8 * 6));

    RectangleShape showTable = RectangleShape(Vector2f(window.getSize().x / 3, window.getSize().y / 1.3));
    showTable.setFillColor(Color(205, 205, 255));
    showTable.setOutlineThickness(8);
    showTable.setOutlineColor(Color(0, 0, 104));
    showTable.setOrigin(showTable.getSize().x / 2, showTable.getSize().y / 2);
    showTable.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 5 * 2.3));

    RectangleShape enterTable = RectangleShape(Vector2f(window.getSize().x / 2.8, window.getSize().y / 4));
    enterTable.setFillColor(Color(205, 205, 255));
    enterTable.setOutlineThickness(8);
    enterTable.setOutlineColor(Color(0, 0, 104));
    enterTable.setOrigin(enterTable.getSize().x / 2, enterTable.getSize().y / 2);
    enterTable.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 5 * 2.2));

    RectangleShape ButtonEnter = RectangleShape(Vector2f(window.getSize().x / 6, window.getSize().y / 13));
    ButtonEnter.setFillColor(Color(0, 0, 49));
    ButtonEnter.setOrigin(ButtonEnter.getSize().x / 2, ButtonEnter.getSize().y);
    ButtonEnter.setPosition(enterTable.getPosition().x, enterTable.getPosition().y + enterTable.getSize().y / 2);

    RectangleShape exit = RectangleShape(Vector2f(70, 45));
    exit.setPosition(window.getSize().x - 70, 0);
    exit.setFillColor(Color::Red);

    RectangleShape exitFromTable = exit;
    exitFromTable.setPosition(Vector2f(showTable.getPosition().x + showTable.getSize().x / 2 - 70, showTable.getPosition().y - showTable.getSize().y / 2));

    RectangleShape cross11 = RectangleShape(Vector2f(40,3));
    cross11.setOrigin(20, 1.5);
    cross11.setRotation(45);
    cross11.setPosition(window.getSize().x - 35, 22.5);
    cross11.setFillColor(Color(80, 80, 80));
    RectangleShape cross12 = cross11;
    cross12.setRotation(315);
    RectangleShape cross21 = cross11;
    cross21.setPosition(Vector2f(showTable.getPosition().x + showTable.getSize().x / 2 - 35, showTable.getPosition().y - showTable.getSize().y / 2 + 22.5));
    RectangleShape cross22 = cross21;
    cross22.setRotation(315);

    Font font;
    Text textForTitleTop, textForStartGame1, textForStartGame2, textForShowScores, textForShowInputUsername, textForShowTopScores, textForEnterUsername, textForHelpEnter;
    font.loadFromFile("..\\calibri.ttf");
    textForStartGame1 = Text("start fast game", font, int(window.getSize().y / 16));
    textForStartGame1.setOrigin(window.getSize().y / 16 / 1.2 / 2 * textForStartGame1.getString().getSize() / 2, window.getSize().y / 36 * 4 / 3);
    textForStartGame1.setFillColor(Color::Black);
    textForStartGame1.setPosition(ButtonGame1.getPosition());
    textForStartGame2 = Text("start endless game", font, int(window.getSize().y / 16));
    textForStartGame2.setOrigin(window.getSize().y / 16 / 1.2 / 2 * textForStartGame2.getString().getSize() / 2, window.getSize().y / 36 * 4 / 3);
    textForStartGame2.setFillColor(Color::Black);
    textForStartGame2.setPosition(ButtonGame2.getPosition());
    textForShowScores = Text("show top scores", font, int(window.getSize().y / 16));
    textForShowScores.setOrigin(window.getSize().y / 18 / 2 * textForShowScores.getString().getSize() / 2, window.getSize().y / 36 * 4 / 3);
    textForShowScores.setFillColor(Color::Black);
    textForShowScores.setPosition(ButtonScore.getPosition());
    textForShowInputUsername = Text("", font, int(window.getSize().y / 20));
    textForShowInputUsername.setOrigin(window.getSize().y / 22 / 2 * textForShowInputUsername.getString().getSize() / 2, window.getSize().y / 44 * 4 / 3);
    textForShowInputUsername.setFillColor(Color::Black);
    textForShowInputUsername.setPosition(enterTable.getPosition().x - enterTable.getSize().x / 3, enterTable.getPosition().y);
    textForShowTopScores = Text("", font, int(window.getSize().y / ((showTable.getSize().y - 60) / 40)));
    textForShowTopScores.setOrigin(window.getSize().y / ((showTable.getSize().y - 60) / 40) / 1.1 / 2 * textForShowTopScores.getString().getSize() / 2, window.getSize().y / ((showTable.getSize().y - 60) / 40) / 2.2 * 4 / 3);
    textForShowTopScores.setPosition(showTable.getPosition().x, showTable.getPosition().y - showTable.getSize().y / 2 + 200);
    textForShowTopScores.setFillColor(Color::Black);
    textForEnterUsername = Text("Enter", font, int(window.getSize().y / (exitFromTable.getSize().y / 2)));
    textForEnterUsername.setOrigin(window.getSize().y / (exitFromTable.getSize().y / 2) / 1.1 / 2 * textForEnterUsername.getString().getSize() / 2, window.getSize().y / ((exitFromTable.getSize().y / 2) / 2.2 * 4 / 3));
    textForEnterUsername.setPosition(enterTable.getPosition().x, enterTable.getPosition().y + enterTable.getSize().y / 2);
    textForEnterUsername.setFillColor(Color::White);
    textForHelpEnter = Text("Enter Your nickname (in English)", font, int(window.getSize().y / (exitFromTable.getSize().y / 2)));
    textForHelpEnter.setOrigin(window.getSize().y / (exitFromTable.getSize().y / 2) / 2 * textForHelpEnter.getString().getSize() / 2 / 1.2, window.getSize().y / ((exitFromTable.getSize().y / 2) / 2 * 4 / 3));
    textForHelpEnter.setPosition(enterTable.getPosition().x, enterTable.getPosition().y - enterTable.getSize().y / 2 + 80);
    textForHelpEnter.setFillColor(Color::Black);
    textForTitleTop = Text("Top 10 scores", font, int(window.getSize().y / ((showTable.getSize().y - 60) / 40)));
    textForTitleTop.setOrigin(window.getSize().y / ((showTable.getSize().y - 60) / 40) / 1.1 / 2 * textForTitleTop.getString().getSize() / 2, window.getSize().y / ((showTable.getSize().y - 60) / 40) / 2.2 * 4 / 3);
    textForTitleTop.setPosition(showTable.getPosition().x, showTable.getPosition().y - showTable.getSize().y / 2 + 40);
    textForTitleTop.setFillColor(Color::Black);


    bool needShowScores = false, showEnterWindow = false;

    vector<char> username;
    int score = 0;
    Clock timer;

    while (window.isOpen()) {
        Event event;
        // цикл для обработки событий (нажатия на кнопки меню, запуск уровней)
        while (window.pollEvent(event)){
            if (event.type == Event::Closed) {
                window.close();

            }
            if (event.type == Event::MouseButtonReleased) {
                if (exit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    window.close();
                else if (showEnterWindow and ButtonEnter.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    showEnterWindow = false;
                    ifstream fin("scores.txt", ios_base::in);
                    char buff[1000];
                    fin.getline(buff, 1000);
                    vector<String> names;
                    vector<int> scores;
                    vector<String> newNames;
                    vector<int> newScores;
                    int pointer = 0;
                    string localName, localScore;
                    for (char s: buff) {
                        if (s != '(' and s != ')') {
                            if (pointer == 0) {
                                localName += s;
                            } else {
                                localScore += s;
                            }
                        } else if (s == '(') {
                            pointer = 1;
                            names.emplace_back(localName);
                            localName = "";
                        } else {
                            pointer = 0;
                            scores.emplace_back(atoi(localScore.c_str()));
                            localScore = "";
                        }
                    }
                    int i = 0;
                    bool flag = true;
                    while (i < scores.size()) {
                        if (score > scores[i] and flag) {
                            newScores.emplace_back(score);
                            string si = "";
                            for (char s:username) {
                                si += s;
                            }
                            newNames.emplace_back(si);
                            flag = false;
                        }
                        newScores.emplace_back(scores[i]);
                        newNames.emplace_back((names[i]));
                        if (scores.size() < 10 and i + 1 == scores.size() and flag) {
                            newScores.emplace_back(score);
                            string si = "";
                            for (char s:username) {
                                si += s;
                            }
                            newNames.emplace_back(si);
                            flag = false;
                        }
                        ++i;
                    }
                    string buff2;
                    ofstream fout("scores.txt", ios_base::out);
                    for (int j = 0; j < min(10, int(newScores.size())); ++j) {
                        buff2 = buff2 + newNames[j] + "(" + to_string(newScores[j]) + ")";
                    }
                    fout << buff2;
                    fin.close();
                    fout.close();
                    score = 0;
                    username.clear();
                }
                else if (exitFromTable.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    needShowScores = false;
                    textForShowTopScores.setString("");
                }
                else if (not needShowScores and not showEnterWindow and ButtonScore.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                    needShowScores = true;
                    ifstream fin("scores.txt", ios_base::in);
                    char buff[1000];
                    fin.getline(buff, 1000);
                    vector<String> names;
                    vector<int> scores;
                    int pointer = 0;
                    string localName, localScore;
                    for (char s: buff) {
                        if (s != '(' and s != ')') {
                            if (pointer == 0) {
                                localName += s;
                            } else {
                                localScore += s;
                            }
                        } else if (s == '(') {
                            pointer = 1;
                            names.emplace_back(localName);
                            localName = "";
                        } else {
                            pointer = 0;
                            scores.emplace_back(atoi(localScore.c_str()));
                            localScore = "";
                        }
                    }
                    int i = 0;
                    while (i < 10 and i < names.size()) {
                        textForShowTopScores.setString(textForShowTopScores.getString() + names[i] + "  -  " + to_string(scores[i]) + '\n');
                        ++i;
                    }
                    string(textForShowTopScores.getString()); // без этого не работало
                    fin.close();
                    textForShowTopScores.setOrigin(window.getSize().y / ((showTable.getSize().y - 60) / 40) / 1.1 / 2 * 20 / 2, window.getSize().y / ((showTable.getSize().y - 60) / 40) / 2.2 * 4 / 3);
                    textForShowTopScores.setPosition(showTable.getPosition().x, showTable.getPosition().y - showTable.getSize().y / 2 + 100);
                }
                else if (not needShowScores and ButtonGame1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {

                    FastGame game = FastGame(&window, &score);

                    showEnterWindow = true;
                    timer.restart();
                }
                else if (not needShowScores and ButtonGame2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {

                    EndlessGame game = EndlessGame(&window, &score);

                    showEnterWindow = true;
                    timer.restart();
                }
            }
            if (event.type == sf::Event::TextEntered and showEnterWindow and timer.getElapsedTime().asSeconds() > 1) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) and username.size() > 0) {
                    username.pop_back();
                }
                else if ((event.text.unicode >= 'a' and event.text.unicode <= 'z') or (event.text.unicode >= 'A' and event.text.unicode <= 'Z') or (event.text.unicode >= '0' and event.text.unicode <= '9') or (event.text.unicode == ' ') or (event.text.unicode == '-') or (event.text.unicode == '_') or (event.text.unicode == '!') or (event.text.unicode == '?')) {
                    username.emplace_back(event.text.unicode);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    showEnterWindow = false;
                    ifstream fin("scores.txt", ios_base::in);
                    char buff[1000];
                    fin.getline(buff, 1000);
                    vector<String> names;
                    vector<int> scores;
                    vector<String> newNames;
                    vector<int> newScores;
                    int pointer = 0;
                    string localName, localScore;
                    for (char s: buff) {
                        if (s != '(' and s != ')') {
                            if (pointer == 0) {
                                localName += s;
                            } else {
                                localScore += s;
                            }
                        } else if (s == '(') {
                            pointer = 1;
                            names.emplace_back(localName);
                            localName = "";
                        } else {
                            pointer = 0;
                            scores.emplace_back(atoi(localScore.c_str()));
                            localScore = "";
                        }
                    }
                    int i = 0;
                    bool flag = true;
                    while (i < scores.size()) {
                        if (score > scores[i] and flag) {
                            newScores.emplace_back(score);
                            string si = "";
                            for (char s:username) {
                                si += s;
                            }
                            newNames.emplace_back(si);
                            flag = false;
                        }
                        newScores.emplace_back(scores[i]);
                        newNames.emplace_back((names[i]));
                        if (scores.size() < 10 and i + 1 == scores.size() and flag) {
                            newScores.emplace_back(score);
                            string si = "";
                            for (char s:username) {
                                si += s;
                            }
                            newNames.emplace_back(si);
                            flag = false;
                        }
                        ++i;
                    }
                    string buff2;
                    ofstream fout("scores.txt", ios_base::out);
                    for (int j = 0; j < min(10, int(newScores.size())); ++j) {
                        buff2 = buff2 + newNames[j] + "(" + to_string(newScores[j]) + ")";
                    }
                    fout << buff2;
                    fin.close();
                    fout.close();
                    score = 0;
                    username.clear();
                }
                string si = "";
                for (char s:username) {
                    si += s;
                }
                textForShowInputUsername.setString(si);
            }
        }
        // отрисовка всех элементов меню
        window.clear(Color::Black);
        window.draw(exit);
        window.draw(cross11);
        window.draw(cross12);
        window.draw(ButtonGame1);
        window.draw(ButtonGame2);
        window.draw(ButtonScore);
        window.draw(textForStartGame1);
        window.draw(textForStartGame2);
        window.draw(textForShowScores);
        if (needShowScores) {
            window.draw(showTable);
            window.draw(exitFromTable);
            window.draw(cross21);
            window.draw(cross22);
            textForShowTopScores.setPosition(showTable.getPosition().x, showTable.getPosition().y - showTable.getSize().y / 2 + 150);
            window.draw(textForShowTopScores);
            window.draw(textForTitleTop);
        }
        if (showEnterWindow) {
            window.draw(enterTable);
            window.draw(ButtonEnter);
            window.draw(textForShowInputUsername);
            window.draw(textForEnterUsername);
            window.draw(textForHelpEnter);
        }
        window.display();
    }

}
