#include "BulgarianExam.h"
#include <iostream>

BulgarianExam::BulgarianExam() {
    if (!BulgarianFont.loadFromFile("Fonts/SourceSansPro-Bold.ttf")) {
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
    timerText.setFont(BulgarianFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);

    timerText.setPosition(1200, toolbarHeight);
}


void BulgarianExam::setupToolbar() {
    toolbarBackground.setSize(sf::Vector2f(1400, 50));
    toolbarBackground.setFillColor(sf::Color(1, 40, 95));

    titleText.setFont(BulgarianFont);
    titleText.setString("STUHELP");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color(231, 209, 152));
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(700, 15);

    BulgarianText.setFont(BulgarianFont);
    BulgarianText.setString("BULGARIAN EXAM");
    BulgarianText.setCharacterSize(30);
    BulgarianText.setFillColor(sf::Color::Black);
    BulgarianText.setPosition(580, 50);
}


void BulgarianExam::openWindow() {
    BulgarianWindow.create(sf::VideoMode(1400, 800), "STUHELP BULGARIAN EXAM ACTIVE");
    while (BulgarianWindow.isOpen()) {
        handleEvents();
        updateTimer();
        render();
    }
}

void BulgarianExam::handleEvents() {
    sf::Event event;
    while (BulgarianWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            BulgarianWindow.close();
    }
}

void BulgarianExam::updateTimer() {
    sf::Time elapsed = clock.getElapsedTime();
    sf::Time timeLeft = sf::seconds(1800) - elapsed; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< CHANGE THE TEST TIMER FOR TESTING!

    if (timeLeft.asSeconds() <= 0) {
        if (!testCompleted) {
            timerText.setString("00:00 - Exam Failed");
            BulgarianText.setString("Bulgarian Exam Failed");
            render();  
            std::this_thread::sleep_for(std::chrono::seconds(3)); 
            BulgarianWindow.close();
        }
    }
    else {
        int minutes = static_cast<int>(timeLeft.asSeconds()) / 60;
        int seconds = static_cast<int>(timeLeft.asSeconds()) % 60;
        timerText.setString("Time left: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    }
}

void BulgarianExam::render() {
    BulgarianWindow.clear(sf::Color(250, 250, 250));
    BulgarianWindow.draw(toolbarBackground);
    BulgarianWindow.draw(leftLogoSprite);
    BulgarianWindow.draw(rightLogoSprite);
    BulgarianWindow.draw(titleText);
    BulgarianWindow.draw(BulgarianText);
    BulgarianWindow.draw(timerText);
    BulgarianWindow.display();
}
