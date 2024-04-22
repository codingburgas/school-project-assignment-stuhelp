#ifndef BULGARIANEXAM_H
#define BULGARIANEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>

class BulgarianExam {
public:
    BulgarianExam();
    void openWindow();

private:
    sf::RenderWindow BulgarianWindow;
    sf::Font BulgarianFont, Bulgarian2Font;
    sf::Text BulgarianText, questionText, titleText, timerText;
    std::vector<sf::Text> answerTexts;
    std::vector<std::string> questions;
    std::vector<std::vector<std::string>> answers;
    std::vector<char> correctAnswers;
    sf::Clock clock;
    sf::RectangleShape toolbarBackground;
    sf::Sprite leftLogoSprite, rightLogoSprite;
    sf::Texture leftLogoTexture, rightLogoTexture;
    sf::Text footerText;
    sf::RectangleShape finishButton;
    sf::Text finishButtonText;

    bool testCompleted = false;
    int currentQuestion = 0;
    int score = 0;

    void setupToolbar();
    void handleEvents();
    void handleAnswerSelection(const sf::Vector2f& mousePos);
    void setupQuestionsAndAnswers();
    void updateQuestionAndAnswers();
    void render();
    void updateTimer();
    void setupFooter();
    void updateRegularQuestions();
    void setupFinishButton();
    void shuffleQuestions();

};

#endif
