#include "CodingExam.h"
#include <iostream>

CodingExam::CodingExam() {
    if (!CodingFont.loadFromFile("Fonts/SourceSansPro-Bold.ttf")) {
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

    // Timer setup
    timerText.setFont(CodingFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);

    timerText.setPosition(1200, toolbarHeight);
}


void CodingExam::setupToolbar() {
    toolbarBackground.setSize(sf::Vector2f(1400, 50));
    toolbarBackground.setFillColor(sf::Color(1, 40, 95));

    titleText.setFont(CodingFont);
    titleText.setString("STUHELP");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color(231, 209, 152));
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(700, 15);

    CodingText.setFont(CodingFont);
    CodingText.setString("CODING EXAM");
    CodingText.setCharacterSize(30);
    CodingText.setFillColor(sf::Color::Black);
    CodingText.setPosition(610, 50);
}


void CodingExam::openWindow() {
    CodingWindow.create(sf::VideoMode(1400, 800), "STUHELP CODING EXAM ACTIVE");
    while (CodingWindow.isOpen()) {
        handleEvents();
        updateTimer();
        render();
    }
}

void CodingExam::handleEvents() {
    sf::Event event;
    while (CodingWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            CodingWindow.close();
    }
}

void CodingExam::updateTimer() {
    sf::Time elapsed = clock.getElapsedTime();
    sf::Time timeLeft = sf::seconds(1800) - elapsed; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CHANGE THE TEST TIMER FOR TESTING!

    if (timeLeft.asSeconds() <= 0) {
        if (!testCompleted) {
            timerText.setString("00:00 - Exam Failed");
            CodingText.setString("Coding Exam Failed");
            render();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            CodingWindow.close();
        }
    }
    else {
        int minutes = static_cast<int>(timeLeft.asSeconds()) / 60;
        int seconds = static_cast<int>(timeLeft.asSeconds()) % 60;
        timerText.setString("Time left: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    }
}

void CodingExam::render() {
    CodingWindow.clear(sf::Color(250, 250, 250));
    CodingWindow.draw(toolbarBackground);
    CodingWindow.draw(leftLogoSprite);
    CodingWindow.draw(rightLogoSprite);
    CodingWindow.draw(titleText);
    CodingWindow.draw(CodingText);
    CodingWindow.draw(timerText);
    CodingWindow.display();
}
