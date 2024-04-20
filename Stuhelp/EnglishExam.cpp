#include "EnglishExam.h"
#include <iostream>

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

    timerText.setFont(EnglishFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1200, toolbarHeight);
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

void EnglishExam::handleEvents() {
    sf::Event event;
    while (EnglishWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            EnglishWindow.close();
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
    EnglishWindow.display();
}
