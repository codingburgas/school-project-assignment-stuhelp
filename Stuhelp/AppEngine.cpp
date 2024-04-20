//APP ENGINE 
//It will and is used to render every element and control thr app!

#include <iostream>
#include "AppEngine.h"
#include "MathExam.h"
#include "EnglishExam.h"
#include "BulgarianExam.h"
#include "CodingExam.h"

//THIS THING IS LIFE SAVE! Simply function to wrap the text ... :D
void wrapText(sf::Text& text, unsigned width, const sf::Font& font, unsigned characterSize) {
    std::wstring s = text.getString();
    size_t n = s.length();
    unsigned lineWidth = 0;
    unsigned lastSpace = 0;
    std::wstring result;

    for (size_t i = 0; i < n; i++) {
        wchar_t c = s[i];
        sf::Glyph glyph = font.getGlyph(c, characterSize, false);
        lineWidth += glyph.advance;

        if (c == L' ' || c == L'-' || c == L',') {
            lastSpace = i;
        }

        if (lineWidth > width && lastSpace != 0) {
            s[lastSpace] = L'\n';
            lineWidth = 0;
            i = lastSpace;
            lastSpace = 0;
        }
    }

    text.setString(s);
}


bool AppEngine::isWindowCreated() const {
    return window.isOpen();
}
//Scales the window + adds backround color!
AppEngine::AppEngine() : backgroundColor(sf::Color( 250,250,250)) {
    window.create(sf::VideoMode(1400, 800), "STUHELP");
    setupToolbar();
    loadTextures();
}
// Runs the THING
void AppEngine::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}



void AppEngine::openMathExamWindow() {
    MathExam mathExam;
    mathExam.openWindow();
}

void AppEngine::openEnglishExamWindow() {
    EnglishExam englishExam;
    englishExam.openWindow();
}
void AppEngine::openBulgarianExamWindow() {
    BulgarianExam bulgarianExam;
    bulgarianExam.openWindow();
}
void AppEngine::openCodingExamWindow() {
    CodingExam codingExam;
    codingExam.openWindow();
}


//HANDLES EVENTS such as closing the window!
void AppEngine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // Check for mouse button pressed event
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Convert the click coordinates to the view of the window
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (button1.getGlobalBounds().contains(mousePos)) {
                    openMathExamWindow();
                }
                if (button2.getGlobalBounds().contains(mousePos)) {
                    openEnglishExamWindow();  
                }
                if (button3.getGlobalBounds().contains(mousePos)) {
                    openBulgarianExamWindow();  
                }
                if (button4.getGlobalBounds().contains(mousePos)) {
                    openCodingExamWindow(); 
                }
            }
        }
    }
}


void AppEngine::loadTextures() {
    //LOAD
    if (!toolbarTexture.loadFromFile("Textures/Logo.png")) {
        std::cerr << "Failed to load toolbar texture" << std::endl;
        return;
    }
    // SCALE THE LOGO
    float toolbarScale = static_cast<float>(toolbarHeight) / toolbarTexture.getSize().y;
    toolbarSprite.setScale(toolbarScale, toolbarScale);
    toolbarSprite.setTexture(toolbarTexture);

    // LOAD
    if (!rightSideTexture.loadFromFile("Textures/EDULOGO.png")) {
        std::cerr << "Failed to load right side image texture" << std::endl;
        return;
    }
    // SCALING THE RIGHT IMG
    float rightSideScale = static_cast<float>(toolbarHeight) / rightSideTexture.getSize().y;
    rightSideSprite.setScale(rightSideScale, rightSideScale);
    rightSideSprite.setTexture(rightSideTexture);
}


void AppEngine::setupToolbar() {
    // Set the toolbar background size and color
    toolbarBackground.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(toolbarHeight)));
    toolbarBackground.setFillColor(sf::Color(1, 40, 95));  // Dark blue color for the toolbar

    // Position the logo image on the left side of the toolbar
    toolbarSprite.setPosition(10, 0);  // Slightly offset from the edge

    // Load and set the font for the title text
    if (!font.loadFromFile("Fonts/SourceSansPro-Bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    // Set up the title text properties
    titleText.setFont(font);
    titleText.setString("STUHELP");
    titleText.setCharacterSize(toolbarHeight - 10);  // Ensure the text fits within the toolbar
    titleText.setFillColor(sf::Color(231, 209, 152));  // Light gold color for visibility
    sf::FloatRect titleTextRect = titleText.getLocalBounds();
    titleText.setOrigin(titleTextRect.width / 2.0f, titleTextRect.height / 2.0f);
    titleText.setPosition(window.getSize().x / 2.0f, toolbarHeight / 4.0f);  // Center horizontally in the toolbar

    // Load the description font, if different
    if (!descriptionFont.loadFromFile("Fonts/SourceSansPro-SemiboldItalic.ttf")) {
        std::cerr << "Failed to load description font" << std::endl;
        return;
    }

    // Set up the description container below the toolbar
    descriptionContainer.setSize(sf::Vector2f(window.getSize().x / 2, 150));  // Example size
    descriptionContainer.setFillColor(sf::Color(250, 250, 250));  // Light background for the text
    descriptionContainer.setPosition((window.getSize().x - descriptionContainer.getSize().x) / 2, toolbarHeight + 20);  // Center horizontally and position just below the toolbar

    // Set up the description text
    descriptionText.setFont(descriptionFont);
    descriptionText.setString(L"We are StuHelp. Here you can prepare for MATH , ENGLISH , BULGARIAN and CODING exams. After a short revision on your own you are able to test your skills! Start up one of our short tests and test yuor self! Remember to complete it under 30 minutes!");
    descriptionText.setCharacterSize(35);
    descriptionText.setFillColor(sf::Color::Black);
    wrapText(descriptionText, descriptionContainer.getSize().x - 20, descriptionFont, 25);  // Apply text wrapping

    // Align the description text within its container
    sf::FloatRect descTextRect = descriptionText.getLocalBounds();
    descriptionText.setOrigin(descTextRect.width / 2.0f, 0);
    descriptionText.setPosition(descriptionContainer.getPosition().x + descriptionContainer.getSize().x / 2, descriptionContainer.getPosition().y + 10);

    // Position the right side logo image
    rightSideSprite.setPosition(window.getSize().x - rightSideSprite.getGlobalBounds().width - 60, 0);

    // Configure and position buttons centrally between the description and the footer
    float buttonYPosition = descriptionContainer.getPosition().y + descriptionContainer.getSize().y + 20;
    float totalButtonWidth = 2 * 200 + 20;  // Total width of two buttons plus padding
    float startButtonX = (window.getSize().x - totalButtonWidth) / 2;

    button1.setSize(sf::Vector2f(200, 50));
    button1.setFillColor(sf::Color(231, 209, 152));
    button1.setPosition(startButtonX-250, buttonYPosition + 200);

    button2.setSize(sf::Vector2f(200, 50));
    button2.setFillColor(sf::Color(231, 209, 152));
    button2.setPosition(startButtonX  -10, buttonYPosition+200);  // 20 pixels apart from button1

    button3.setSize(sf::Vector2f(200, 50));
    button3.setFillColor(sf::Color(231, 209, 152));
    button3.setPosition(startButtonX + 220 + 10, buttonYPosition + 200);  // 20 pixels apart from button1

    button4.setSize(sf::Vector2f(200, 50));
    button4.setFillColor(sf::Color(231, 209, 152));
    button4.setPosition(startButtonX + 470 , buttonYPosition + 200);  // 20 pixels apart from button1

    button1Text.setFont(font);
    button1Text.setString("MATH EXAM");
    button1Text.setCharacterSize(20);
    button1Text.setFillColor(sf::Color::Black);
    sf::FloatRect button1TextRect = button1Text.getLocalBounds();
    button1Text.setOrigin(button1TextRect.width / 2, button1TextRect.height / 2);
    button1Text.setPosition(button1.getPosition().x + 100, button1.getPosition().y + 15);  // Center in button1

    button2Text.setFont(font);
    button2Text.setString("ENGLISH EXAM");
    button2Text.setCharacterSize(20);
    button2Text.setFillColor(sf::Color::Black);
    sf::FloatRect button2TextRect = button2Text.getLocalBounds();
    button2Text.setOrigin(button2TextRect.width / 2, button2TextRect.height / 2);
    button2Text.setPosition(button2.getPosition().x + 100, button2.getPosition().y + 15);  // Center in button2

    button3Text.setFont(font);
    button3Text.setString("BULGARIAN EXAM");
    button3Text.setCharacterSize(20);
    button3Text.setFillColor(sf::Color::Black);
    sf::FloatRect button3TextRect = button3Text.getLocalBounds();
    button3Text.setOrigin(button3TextRect.width / 2, button3TextRect.height / 2);
    button3Text.setPosition(button3.getPosition().x + 100, button3.getPosition().y + 15);  // Center in button2

    button4Text.setFont(font);
    button4Text.setString("CODING EXAM");
    button4Text.setCharacterSize(20);
    button4Text.setFillColor(sf::Color::Black);
    sf::FloatRect button4TextRect = button4Text.getLocalBounds();
    button4Text.setOrigin(button4TextRect.width / 2, button4TextRect.height / 2);
    button4Text.setPosition(button4.getPosition().x + 100, button4.getPosition().y + 15);  // Center in button2

    // Set up the footer text at the bottom of the window
    footerText.setFont(font);
    footerText.setString("Copyright © 2024 All Rights Reserved");
    footerText.setCharacterSize(20);
    footerText.setFillColor(sf::Color::Black);
    sf::FloatRect footerTextRect = footerText.getLocalBounds();
    footerText.setOrigin(footerTextRect.width / 2, footerTextRect.height / 2);
    footerText.setPosition(window.getSize().x / 2, window.getSize().y - 30);
}
// Renders the elements...
void AppEngine::render() {
    window.clear(backgroundColor); // Clear the window
    window.draw(toolbarBackground); // Draw the toolbar background
    window.draw(toolbarSprite);     // Draw the toolbar sprite
    window.draw(rightSideSprite);   // Draw the right side image
    window.draw(titleText);         // Draw the title text
    window.draw(descriptionContainer); // Draw the description container
    window.draw(descriptionText);   // Draw the description text

    // Draw buttons
    window.draw(button1);
    window.draw(button1Text);
    window.draw(button2);
    window.draw(button2Text);
    window.draw(button3);
    window.draw(button3Text);
    window.draw(button4);
    window.draw(button4Text);

    // Draw footer text
    window.draw(footerText);

    window.display(); // Display everything we've drawn
}


