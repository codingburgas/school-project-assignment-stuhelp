// AppEngine.h
//Declares the variables for the APP engine you know...
#ifndef APPENGINE_H
#define APPENGINE_H

#include <SFML/Graphics.hpp>

class AppEngine {
public:
    AppEngine();
    void run();
    bool isWindowCreated() const;

private:
    //MAIN WINDOW
    sf::RenderWindow window;
    //SPRITE (FOR THOSE WHO ASK SIMPLY IT"S AN ELEMENT AS A SHAPE!)
    sf::Sprite toolbarSprite;
    sf::Sprite rightSideSprite;
    //TEXTURES
    sf::Texture toolbarTexture;
    sf::Texture rightSideTexture;
    //FONTS
    sf::Font font;
    sf::Font descriptionFont;
    //SHAPES
    sf::RectangleShape descriptionContainer; 
    sf::RectangleShape toolbarBackground;
    //TEXT
    sf::Text titleText;
    sf::Text descriptionText;
    //SCALE FOR TOOLBAR
    const unsigned int toolbarHeight = 50;  
    sf::Color backgroundColor;
    // ... existing members ...
    sf::RectangleShape button1, button2 , button3 , button4; // Two buttons
    sf::Text button1Text, button2Text, button3Text, button4Text; // Text for each button
    sf::Text footerText; // Footer text


    //Events and functions
    void handleEvents();   
    void render();        
    void loadTextures();  
    void setupToolbar(); 
    void openMathExamWindow();
    void openEnglishExamWindow();
    void openBulgarianExamWindow();
    void openCodingExamWindow();
};

#endif