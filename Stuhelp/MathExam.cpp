#include "MathExam.h"
#include <iostream>

MathExam::MathExam() {
    if (!mathFont.loadFromFile("Fonts/SourceSansPro-Bold.ttf")) {
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
    timerText.setFont(mathFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1200, toolbarHeight);
}


void MathExam::setupToolbar() {
    toolbarBackground.setSize(sf::Vector2f(1400, 50));
    toolbarBackground.setFillColor(sf::Color(1, 40, 95));
    titleText.setFont(mathFont);
    titleText.setString("STUHELP");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color(231, 209, 152));
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(705, 15);

    mathText.setFont(mathFont);
    mathText.setString("MATH EXAM");
    mathText.setCharacterSize(30);
    mathText.setFillColor(sf::Color::Black);
    mathText.setPosition(625, 50);
}


void MathExam::openWindow() {
    mathWindow.create(sf::VideoMode(1400, 800), "STUHELP MATH EXAM ACTIVE");
    while (mathWindow.isOpen()) {
        handleEvents();
        updateTimer();
        render();
    }
}

void MathExam::handleEvents() {
    sf::Event event;
    while (mathWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mathWindow.close();
    }
}

void MathExam::updateTimer() {
    sf::Time elapsed = clock.getElapsedTime();
    sf::Time timeLeft = sf::seconds(1800) - elapsed;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TIMER FOR TESTING HERE!!!

    if (timeLeft.asSeconds() <= 0) {
        if (!testCompleted) {
            timerText.setString("00:00 - Exam Failed");
            mathText.setString("Math Exam Failed");
            render();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            mathWindow.close();
        }
    }
    else {
        int minutes = static_cast<int>(timeLeft.asSeconds()) / 60;
        int seconds = static_cast<int>(timeLeft.asSeconds()) % 60;
        timerText.setString("Time left: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    }
}

void MathExam::render() {
    mathWindow.clear(sf::Color(250, 250, 250));
    mathWindow.draw(toolbarBackground);
    mathWindow.draw(leftLogoSprite);
    mathWindow.draw(rightLogoSprite);
    mathWindow.draw(titleText);
    mathWindow.draw(mathText);
    mathWindow.draw(timerText);
    mathWindow.display();
}
