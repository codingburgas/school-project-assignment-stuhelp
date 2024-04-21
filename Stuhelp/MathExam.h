#ifndef MATHEXAM_H
#define MATHEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <random>

class MathExam {
public:
    MathExam();
    void openWindow();

private:
    sf::RenderWindow MathWindow;
    sf::Font MathFont, Math2Font;
    sf::Text MathText, questionText, titleText, timerText;
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
    int currentQuestionMath = 0;
    int scoreMath = 0;

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
};

#endif
