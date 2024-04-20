#ifndef ENGLISHEXAM_H
#define ENGLISHEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class EnglishExam {
public:
    EnglishExam();
    void openWindow();

private:
    sf::RenderWindow EnglishWindow;
    sf::Font EnglishFont;
    sf::Text EnglishText, titleText, timerText;
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

#endif
