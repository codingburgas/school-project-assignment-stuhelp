#ifndef CODINGEXAM_H
#define CODINGNEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class CodingExam {
public:
    CodingExam();
    void openWindow();

private:
    sf::RenderWindow CodingWindow;
    sf::Font CodingFont;
    sf::Text CodingText, titleText, timerText;
    sf::Clock clock;
    sf::RectangleShape toolbarBackground;
    sf::Sprite leftLogoSprite, rightLogoSprite;
    sf::Texture leftLogoTexture, rightLogoTexture;
    sf::Text footerText;

    bool testCompleted = false;

    void setupToolbar();
    void handleEvents();
    void render();
    void updateTimer();
    void closeWindow();
};

#endif
