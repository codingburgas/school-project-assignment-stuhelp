#ifndef MATHEXAM_H
#define MATHEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class MathExam {
public:
    MathExam();
    void openWindow();

private:
    sf::RenderWindow mathWindow;
    sf::Font mathFont;
    sf::Text mathText, titleText, timerText;
    sf::Clock clock;
    sf::RectangleShape toolbarBackground;
    sf::Sprite leftLogoSprite, rightLogoSprite;
    sf::Texture leftLogoTexture, rightLogoTexture;

    bool testCompleted = false;

    void setupToolbar();
    void handleEvents();
    void render();
    void updateTimer();
    void closeWindow();
};

#endif // MATHEXAM_H
