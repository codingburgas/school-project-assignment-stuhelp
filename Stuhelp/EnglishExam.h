#ifndef ENGLISHEXAM_H
#define ENGLISHEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <random>

class EnglishExam {
public:
    EnglishExam();
    void openWindow();

private:
    sf::RenderWindow EnglishWindow;
    sf::Font EnglishFont;
    sf::Text EnglishText ,questionText, titleText, timerText;
    std::vector<sf::Text> answerTexts; 
    std::vector<std::string> questions;
    std::vector<std::vector<std::string>> answers;  
    std::vector<char> correctAnswers;
    sf::Clock clock;
    sf::RectangleShape toolbarBackground;
    sf::Sprite leftLogoSprite, rightLogoSprite;
    sf::Texture leftLogoTexture, rightLogoTexture;

    bool testCompleted = false;
    int currentQuestion = 0;  
    int score = 0; 

    void setupToolbar();
    void handleEvents();
    void setupQuestionsAndAnswers();
    void updateQuestionAndAnswers(); 
    void render();
    void updateTimer();

};

#endif
