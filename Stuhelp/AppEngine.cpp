//APP ENGINE 
//It will and is used to render every element and control thr app!

#include <iostream>
#include "AppEngine.h"

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
//HANDLES EVENTS such as closing the window!
void AppEngine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
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
    toolbarBackground.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(toolbarHeight)));
    toolbarBackground.setFillColor(sf::Color(1, 40, 95)); 

    // LOGO IMAGE
    toolbarSprite.setPosition(10, 0);

    // LOADS FONT
    if (!font.loadFromFile("Fonts/SourceSansPro-Bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    // TITLE
    titleText.setFont(font);
    titleText.setString("STUHELP");
    titleText.setCharacterSize(toolbarHeight - 10); 
    titleText.setFillColor(sf::Color(231, 209, 152));
    sf::FloatRect titleTextRect = titleText.getLocalBounds();
    titleText.setOrigin(titleTextRect.left + titleTextRect.width / 2.0f, titleTextRect.top + titleTextRect.height / 2.0f);
    titleText.setPosition(window.getSize().x / 2.0f, toolbarHeight / 2.0f);

    

    if (!descriptionFont.loadFromFile("Fonts/SourceSansPro-SemiboldItalic.ttf")) {
        std::cerr << "Failed to load description font" << std::endl;
        return;
    }

    // Places the DEC in a Container! This way is easier to set it to center!
    descriptionContainer.setSize(sf::Vector2f(window.getSize().x / 2, 150));
    descriptionContainer.setFillColor(sf::Color(250, 250, 250));
    // Plcaes the DEC in the center
    descriptionContainer.setPosition((window.getSize().x - descriptionContainer.getSize().x) / 2, toolbarHeight + 20);

    // DEC TEXT
    descriptionText.setFont(descriptionFont);
    descriptionText.setString(L"We are StuHelp. Here you can prepare for mathematics and the Bulgarian language. After reading the tutorial, you will have the opportunity to make a short test. When you finish the test, you will see your score from him and you'll see if you're prepared enough to get an A in school");
    descriptionText.setCharacterSize(35);
    descriptionText.setFillColor(sf::Color::Black);

    // CALLS the WRAPP TEXT FUNCTION
    wrapText(descriptionText, descriptionContainer.getSize().x - 20, descriptionFont, 25);

    // Aligin the elements DEC and RightIMG
    sf::FloatRect descTextRect = descriptionText.getLocalBounds();
    descriptionText.setOrigin(descTextRect.width / 2.0f, 0);
    descriptionText.setPosition(descriptionContainer.getPosition().x + descriptionContainer.getSize().x / 2, descriptionContainer.getPosition().y + 10);
    rightSideSprite.setPosition(window.getSize().x - rightSideSprite.getGlobalBounds().width - 60, 0);
}
// Renders the elements...
void AppEngine::render() {
    window.clear(backgroundColor);
    window.draw(toolbarBackground);
    window.draw(toolbarSprite); 
    window.draw(rightSideSprite); 
    window.draw(titleText);
    window.draw(descriptionContainer); 
    window.draw(descriptionText);  
    //vvv Renders the whole window :P vvv
    window.display();
}


