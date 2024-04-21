#include "EnglishExam.h"
#include <iostream>

int currentQuestion = 0;
int score = 0;


EnglishExam::EnglishExam() {
    if (!EnglishFont.loadFromFile("Fonts/SourceSansPro-Bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    if (!leftLogoTexture.loadFromFile("Textures/Logo.png") || !rightLogoTexture.loadFromFile("Textures/EDULOGO.png")) {
        std::cerr << "Failed to load one or both logos" << std::endl;
        return;
    }

    float toolbarHeight = 50; 
    leftLogoSprite.setTexture(leftLogoTexture);
    float scaleLeft = toolbarHeight / leftLogoTexture.getSize().y;
    leftLogoSprite.setScale(scaleLeft, scaleLeft);
    leftLogoSprite.setPosition(10, (toolbarHeight - leftLogoTexture.getSize().y * scaleLeft) / 2);

    rightLogoSprite.setTexture(rightLogoTexture);
    float scaleRight = toolbarHeight / rightLogoTexture.getSize().y;
    rightLogoSprite.setScale(scaleRight, scaleRight);
    rightLogoSprite.setPosition(1340 - rightLogoTexture.getSize().x * scaleRight, (toolbarHeight - rightLogoTexture.getSize().y * scaleRight) / 2);

    setupToolbar();
    setupQuestionsAndAnswers();
    timerText.setFont(EnglishFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1200, toolbarHeight);
}

void EnglishExam::setupQuestionsAndAnswers() {
    questions = {
        //QUESTIONS
        "How do birds fly?", 
        "What is the boiling point of water?", 
        "What is Bulgaria?" 
    };
    answers = {
        //ANSWERS FOR THE QUESTION
        {"By flapping wings", "By magic", "By swimming", "By running"}, 
        {"100 degrees Celsius", "90 degrees Celsius", "120 degrees Celsius", "80 degrees Celsius"},
        {"IDK", "COUNTRY", "CAR", "CAT"}
    };
    correctAnswers = {
        //CORECT ANSWERS FOR THE QUESTIONS
        'A', 
        'A', 
        'B'  
    };

    questionText.setFont(EnglishFont);
    questionText.setCharacterSize(60);
    questionText.setFillColor(sf::Color::Black);
    questionText.setString(questions[0]);
    sf::FloatRect questionBounds = questionText.getLocalBounds();
    questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
    questionText.setPosition(700, 150);  

    answerTexts.resize(4); 
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        answerTexts[i].setFont(EnglishFont);
        answerTexts[i].setCharacterSize(30);
        answerTexts[i].setFillColor(sf::Color::Black);
        answerTexts[i].setString(answers[0][i]); 
        sf::FloatRect answerBounds = answerTexts[i].getLocalBounds();
        answerTexts[i].setOrigin(answerBounds.width / 2, answerBounds.height / 2);
        answerTexts[i].setPosition(700, 200 + i * 50); 
    }
}


void EnglishExam::setupToolbar() {
    toolbarBackground.setSize(sf::Vector2f(1400, 50));
    toolbarBackground.setFillColor(sf::Color(1, 40, 95));
    titleText.setFont(EnglishFont);
    titleText.setString("STUHELP");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color(231, 209, 152));
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(700, 15);

    EnglishText.setFont(EnglishFont);
    EnglishText.setString("ENGLISH EXAM");
    EnglishText.setCharacterSize(30);
    EnglishText.setFillColor(sf::Color::Black);
    EnglishText.setPosition(600, 50);
}


void EnglishExam::openWindow() {
    EnglishWindow.create(sf::VideoMode(1400, 800), "STUHELP ENGLISH EXAM ACTIVE");
    while (EnglishWindow.isOpen()) {
        handleEvents();
        updateTimer();
        render();
    }
}

void EnglishExam::updateQuestionAndAnswers() {
    if (testCompleted) {

        questionText.setString("Test Result: " + std::to_string(score) + "/" + std::to_string(questions.size()));

        for (auto& text : answerTexts) {
            text.setString(""); 
        }
    }
    else {

        questionText.setString(questions[currentQuestion]);
        const auto& currentAnswers = answers[currentQuestion];
        for (size_t i = 0; i < answerTexts.size(); ++i) {
            answerTexts[i].setString(currentAnswers[i]); 
        }
    }
}



void EnglishExam::handleEvents() {
    sf::Event event;
    while (EnglishWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            EnglishWindow.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2f mousePos = EnglishWindow.mapPixelToCoords(sf::Mouse::getPosition(EnglishWindow));


                for (size_t i = 0; i < answerTexts.size(); ++i) {
                    if (answerTexts[i].getGlobalBounds().contains(mousePos)) {
                        if (correctAnswers[currentQuestion] == 'A' + i) {
                            score++;  
                        }
                        currentQuestion++;  
                        if (currentQuestion >= questions.size()) {
                            testCompleted = true; 
                        }
                        updateQuestionAndAnswers(); 
                        break;
                    }
                }
            }
        }
    }
}



void EnglishExam::updateTimer() {
    sf::Time elapsed = clock.getElapsedTime();
    sf::Time timeLeft = sf::seconds(1800) - elapsed;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< HERE SET THE TIMER FOR TESTING!!

    if (timeLeft.asSeconds() <= 0) {
        if (!testCompleted) {
            timerText.setString("00:00 - Exam Failed");
            EnglishText.setString("English Exam Failed");
            render();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            EnglishWindow.close();
        }
    }
    else {
        int minutes = static_cast<int>(timeLeft.asSeconds()) / 60;
        int seconds = static_cast<int>(timeLeft.asSeconds()) % 60;
        timerText.setString("Time left: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    }
}

void EnglishExam::render() {
    EnglishWindow.clear(sf::Color(250, 250, 250)); 
    EnglishWindow.draw(toolbarBackground);
    EnglishWindow.draw(leftLogoSprite);
    EnglishWindow.draw(rightLogoSprite);
    EnglishWindow.draw(titleText);
    EnglishWindow.draw(EnglishText);
    EnglishWindow.draw(timerText);
    EnglishWindow.draw(questionText); 
    for (auto& answer : answerTexts) {
        EnglishWindow.draw(answer); 
    }
    EnglishWindow.display();
}