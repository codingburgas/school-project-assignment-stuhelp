#ifndef BULGARIANEXAM_H
#define BULGARIANEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class BulgarianExam {
public:
    BulgarianExam();
    void openWindow();

private:
    sf::RenderWindow BulgarianWindow;
    sf::Font BulgarianFont;
    sf::Text BulgarianText, titleText, timerText;
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
