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
    if (!Coding2Font.loadFromFile("Fonts/SourceSansPro-Light.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
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
    setupFooter();

    timerText.setFont(CodingFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1200, toolbarHeight);
}

void CodingExam::setupQuestionsAndAnswers() {
    questions = {
    "What is a correct syntax to output \"Hello World\" in C++?",
    "How do you insert COMMENTS in C++ code?",
    "Which data type is used to create a variable that should store text?",
    "Which operator can be used to compare two values?",
    "Which keyword is used to create a variable with a fixed address?",
    "What is the correct way to declare a namespace in C++?",
    "How do you create a function in C++?",
    "Which header file lets us work with input and output objects?",
    "What is the correct way to refer to a member of a namespace?",
    "Which keyword is used to return a value inside a function?",
    "What is the standard exception class in C++ from which all exceptions inherit?",
    "How can you dynamically allocate memory in C++?",
    "What is the scope resolution operator in C++?",
    "Which keyword is used to define a new type in C++?",
    "In C++, what is the difference between \"delete\" and \"delete[]\"?",
    "What is the purpose of the std::move function?",
    "Which C++ feature ensures that a class has only one instance and provides a global point of access to it?",
    "How do you declare a pure virtual function in C++?",
    "Which C++11 keyword is used to indicate that a function does not throw an exception?",
    "In Lua, how do you declare a variable that is globally accessible, outside any functions?"
    };

    answers = {
        {"cout << \"Hello World\";", "Console.WriteLine(\"Hello World\");", "print(\"Hello World\");", "echo \"Hello World\";"},
        {"// This is a comment", "/* This is a comment */", "# This is a comment", "All of the above"},
        {"std::string", "String", "Txt", "string"},
        {"=", "==", "<>", "><"},
        {"const", "fixed", "static", "pointer"},
        {"package NamespaceName;", "namespace NamespaceName {}", "def NamespaceName: {}", "namespace NamespaceName;"},
        {"function functionName() {}", "def functionName() {}", "FunctionName function = () {}", "void functionName() {}"},
        {"<iostream>", "<istream>", "<stream>", "<stdio.h>"},
        {"Namespace::member", "Namespace.member", "Namespace->member", "member::Namespace"},
        {"return", "get", "return()", "goto"},
        {"std::exception", "std::error", "std::throwable", "std::runtime_error"},
        {"malloc", "alloc", "new", "mem_alloc"},
        {"::", ":", ".", "->"},
        {"struct", "typedef", "template", "define"},
        {"\"delete\" deallocates a single object, \"delete[]\" deallocates an array.", "\"delete\" is outdated, use \"delete[]\" for all deletions.", "No difference, both are interchangeable.", "\"delete\" frees memory, \"delete[]\" calls destructors."},
        {"To make a copy of an object.", "To transfer ownership of resources from one object to another.", "To remove an object from memory.", "To move the position of an object in memory."},
        {"Singleton Pattern", "Global Object", "Static Class", "Monostate Pattern"},
        {"virtual void functionName() = 0;", "void functionName() pure;", "abstract void functionName();", "virtual void functionName() abstract;"},
        {"noexcept", "nothrow", "safecall", "throwless"},
        {"global varName", "var varName", "_G.varName", "varName"}
    };

    correctAnswers = {
        'A',
        'D',
        'A',
        'B',
        'C',
        'B',
        'D',
        'A',
        'A',
        'A',
        'A',
        'C',
        'A',
        'B',
        'A',
        'B',
        'A',
        'A',
        'A',
        'D'
    };



    questionText.setFont(CodingFont);
    questionText.setCharacterSize(40);
    questionText.setFillColor(sf::Color::Black);
    questionText.setString(questions[0]);
    sf::FloatRect questionBounds = questionText.getLocalBounds();
    questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
    questionText.setPosition(700, 150);

    answerTexts.resize(4);
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        answerTexts[i].setFont(Coding2Font);
        answerTexts[i].setCharacterSize(30);
        answerTexts[i].setFillColor(sf::Color::Black);
        answerTexts[i].setString(answers[0][i]);
        sf::FloatRect answerBounds = answerTexts[i].getLocalBounds();
        answerTexts[i].setOrigin(answerBounds.width / 2, answerBounds.height / 2);
        answerTexts[i].setPosition(700, 300 + i * 55);
    }
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
    CodingText.setPosition(600, 50);
}


void CodingExam::openWindow() {
    CodingWindow.create(sf::VideoMode(1400, 800), "STUHELP CODING EXAM ACTIVE");
    while (CodingWindow.isOpen()) {
        handleEvents();
        updateTimer();
        render();
    }
}

std::string wrapTextCoding(std::string text, sf::Font& font, unsigned characterSize, unsigned width) {
    sf::Text line(text, font, characterSize);
    if (line.getLocalBounds().width <= width)
        return text;

    std::string wrappedText;
    std::string::size_type lastSpace = 0;
    std::string::size_type nextSpace = text.find(' ', lastSpace + 1);
    while (nextSpace != std::string::npos) {
        line.setString(text.substr(0, nextSpace));
        if (line.getLocalBounds().width > width) {
            wrappedText += text.substr(0, lastSpace) + "\n";
            text = text.substr(lastSpace + 1);
            nextSpace = text.find(' ', 0);
        }
        lastSpace = nextSpace;
        nextSpace = text.find(' ', lastSpace + 1);
    }
    wrappedText += text;

    return wrappedText;
}


void CodingExam::updateQuestionAndAnswers() {
    if (testCompleted) {

        std::string resultMessage = "Test Result: " + std::to_string(scoreCoding) + "/" + std::to_string(questions.size());
        if (scoreCoding >= 15) {
            resultMessage += "\nPASSED";
        }
        else if (scoreCoding >= 10) {
            resultMessage += "\nGOOD ENOUGH";
        }
        else if (scoreCoding > 0) {
            resultMessage += "\nFAILED";
        }
        else {
            resultMessage += "\nBETTER DON'T GO TO THE EXAM";
        }

        questionText.setString(resultMessage);
        sf::FloatRect questionBounds = questionText.getLocalBounds();
        questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
        questionText.setPosition(700, 200);


        for (auto& text : answerTexts) {
            text.setString("");
        }
    }
    else {

        updateRegularQuestions();
    }
}


void CodingExam::updateRegularQuestions() {
    std::string wrappedQuestion = wrapTextCoding(questions[currentQuestionCoding], CodingFont, 40, 1300);
    questionText.setString(wrappedQuestion);
    sf::FloatRect questionBounds = questionText.getLocalBounds();
    questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
    questionText.setPosition(700, 150);

    const auto& currentAnswers = answers[currentQuestionCoding];
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        answerTexts[i].setString(currentAnswers[i]);
        sf::FloatRect answerBounds = answerTexts[i].getLocalBounds();
        answerTexts[i].setOrigin(answerBounds.width / 2, answerBounds.height / 2);
        answerTexts[i].setPosition(700, 250 + i * 50);
    }
}



void CodingExam::setupFooter() {
    footerText.setFont(CodingFont);
    footerText.setString("Copyright © 2024 by STUHELP. All rights reserved.");
    footerText.setCharacterSize(20);
    footerText.setFillColor(sf::Color::Black);

    sf::FloatRect footerBounds = footerText.getLocalBounds();
    footerText.setOrigin(footerBounds.width / 2, footerBounds.height / 2);
    footerText.setPosition(700, 770);
}


void CodingExam::handleEvents() {
    sf::Event event;
    while (CodingWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            CodingWindow.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = CodingWindow.mapPixelToCoords(sf::Mouse::getPosition(CodingWindow));
                if (finishButton.getGlobalBounds().contains(mousePos) && testCompleted) {
                    CodingWindow.close();
                    return;
                }
                handleAnswerSelection(mousePos);
            }
        }
    }
}

void CodingExam::handleAnswerSelection(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        if (answerTexts[i].getGlobalBounds().contains(mousePos)) {
            if (correctAnswers[currentQuestionCoding] == 'A' + i) {
                scoreCoding++;
            }
            currentQuestionCoding++;
            if (currentQuestionCoding >= questions.size()) {
                testCompleted = true;
                setupFinishButton();
            }
            updateQuestionAndAnswers();
            break;
        }
    }
}



void CodingExam::updateTimer() {
    sf::Time elapsed = clock.getElapsedTime();
    sf::Time timeLeft = sf::seconds(1800) - elapsed;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< HERE SET THE TIMER FOR TESTING!!

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

void CodingExam::setupFinishButton() {
    finishButton.setSize(sf::Vector2f(200, 50));
    finishButton.setPosition(600, 350);
    finishButton.setFillColor(sf::Color(1, 40, 95));

    finishButtonText.setFont(CodingFont);
    finishButtonText.setString("FINISH");
    finishButtonText.setCharacterSize(24);
    finishButtonText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = finishButtonText.getLocalBounds();
    finishButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    finishButtonText.setPosition(finishButton.getPosition() + sf::Vector2f(100, 15));
}


void CodingExam::render() {
    CodingWindow.clear(sf::Color(250, 250, 250));
    CodingWindow.draw(toolbarBackground);
    CodingWindow.draw(leftLogoSprite);
    CodingWindow.draw(rightLogoSprite);
    CodingWindow.draw(titleText);
    CodingWindow.draw(CodingText);
    CodingWindow.draw(timerText);
    CodingWindow.draw(questionText);
    CodingWindow.draw(footerText);

    if (!testCompleted) {
        for (auto& answer : answerTexts) {
            CodingWindow.draw(answer);
        }
    }

    if (testCompleted) {
        CodingWindow.draw(finishButton);
        CodingWindow.draw(finishButtonText);
    }
    CodingWindow.display();
}

