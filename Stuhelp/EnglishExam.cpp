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
    if (!English2Font.loadFromFile("Fonts/SourceSansPro-Light.ttf")) {
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

    timerText.setFont(EnglishFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1200, toolbarHeight);
}

void EnglishExam::setupQuestionsAndAnswers() {
    questions = {
    "What do you call a person who travels to space?",
    "Which word correctly completes the sentence? 'I haven’t seen you ______ ages!'",
    "Choose the correct form of the verb: 'She ________ the piano since she was six.'",
    "What is the passive voice of 'John writes the emails'?",
    "Which word is NOT a preposition?",
    "Find the synonym of 'Enormous'.",
    "What does 'feasible' mean?",
    "Choose the word that is spelled correctly.",
    "Which sentence uses the correct order of adjectives?",
    "What is the antonym of 'ancient'?",
    "Identify the misuse of the modal verb: 'He can to drive us to the airport.'",
    "Choose the correct indirect speech form: 'She said, \"I am watching TV.\"'",
    "What does 'benevolent' mean?",
    "Which punctuation is used correctly?",
    "Select the phrase that best replaces the italicized word: 'She *gave* him a gift.'",
    "Which form of the verb fits here? 'If I had known, I _________ differently.'",
    "Choose the most appropriate transitional word: 'He was late; _______, he missed the bus.'",
    "Identify the correct use of the relative pronoun:",
    "Select the correct plural form of the noun 'goose'.",
    "Which sentence correctly uses the subjunctive mood?"
    };

    answers = {
        {"Astronomer", "Astrologist", "Astronaut", "Cosmonaut"},
        {"since", "for", "in", "during"},
        {"is playing", "plays", "played", "has been playing"},
        {"The emails are written by John", "The emails were written by John", "The emails write by John", "The emails have been written by John"},
        {"Under", "Before", "Near", "Since"},
        {"Tiny", "Huge", "Small", "Weak"},
        {"Practical", "Imaginable", "Successful", "Possible"},
        {"Receive", "Recieve", "Recievee", "Receeve"},
        {"A lovely large old rectangular French silver clock", "A French lovely large old rectangular silver clock", "Large lovely old French rectangular silver clock", "Old large lovely French silver rectangular clock"},
        {"Modern", "Contemporary", "Old-fashioned", "Futuristic"},
        {"He can to drive us to the airport.", "He could drive us to the airport.", "He can drive us to the airport.", "He will be able to drive us to the airport."},
        {"She said she is watching TV.", "She said she was watching TV.", "She said, 'I am watching TV.'", "She says she was watching TV."},
        {"Kind-hearted", "Malevolent", "Selfish", "Cruel"},
        {"She's going to the doctor's.", "She's going to the doctors.", "Shes going to the doctor's.", "Shes' going to the doctors."},
        {"Provided", "Contributed", "Presented", "Donated"},
        {"have acted", "had acted", "would act", "would have acted"},
        {"Furthermore", "Moreover", "However", "Therefore"},
        {"The man, that we met yesterday, is very nice.", "The man, who we met yesterday, is very nice.", "The man who we met yesterday, is very nice.", "The man, whom we met yesterday, is very nice."},
        {"Gooses", "Geese", "Goosies", "Goosen"},
        {"I suggest that he leaves now.", "I suggest that he leave now.", "I suggested that he should leave now.", "I suggest that he left now."}
    };

   correctAnswers = {
        'C',
        'C',
        'D',
        'A',
        'D',
        'B',
        'A',
        'A',
        'A',
        'A',
        'A',
        'B',
        'A',
        'A',
        'D',
        'D',
        'C',
        'B',
        'B',
        'B'
    };


    questionText.setFont(EnglishFont);
    questionText.setCharacterSize(40);
    questionText.setFillColor(sf::Color::Black);
    questionText.setString(questions[0]);
    sf::FloatRect questionBounds = questionText.getLocalBounds();
    questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
    questionText.setPosition(700, 150);  

    answerTexts.resize(4); 
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        answerTexts[i].setFont(English2Font);
        answerTexts[i].setCharacterSize(30);
        answerTexts[i].setFillColor(sf::Color::Black);
        answerTexts[i].setString(answers[0][i]); 
        sf::FloatRect answerBounds = answerTexts[i].getLocalBounds();
        answerTexts[i].setOrigin(answerBounds.width / 2, answerBounds.height / 2);
        answerTexts[i].setPosition(700, 300 + i * 55); 
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

std::string wrapTextEnglish(std::string text, sf::Font& font, unsigned characterSize, unsigned width) {
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


void EnglishExam::updateQuestionAndAnswers() {
    if (testCompleted) {
       
        std::string resultMessage = "Test Result: " + std::to_string(score) + "/" + std::to_string(questions.size());
        if (score >= 15) {
            resultMessage += "\nPASSED";
        }
        else if (score >= 10) {
            resultMessage += "\nGOOD ENOUGH";
        }
        else if (score > 0) {
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


void EnglishExam::updateRegularQuestions() {
    std::string wrappedQuestion = wrapTextEnglish(questions[currentQuestion], EnglishFont, 40, 1300);
    questionText.setString(wrappedQuestion);
    sf::FloatRect questionBounds = questionText.getLocalBounds();
    questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
    questionText.setPosition(700, 150);

    const auto& currentAnswers = answers[currentQuestion];
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        answerTexts[i].setString(currentAnswers[i]);
        sf::FloatRect answerBounds = answerTexts[i].getLocalBounds();
        answerTexts[i].setOrigin(answerBounds.width / 2, answerBounds.height / 2);
        answerTexts[i].setPosition(700, 250 + i * 50);
    }
}



void EnglishExam::setupFooter() {
    footerText.setFont(EnglishFont); 
    footerText.setString("Copyright © 2024 by STUHELP. All rights reserved.");
    footerText.setCharacterSize(20); 
    footerText.setFillColor(sf::Color::Black);

    sf::FloatRect footerBounds = footerText.getLocalBounds();
    footerText.setOrigin(footerBounds.width / 2, footerBounds.height / 2);
    footerText.setPosition(700, 770);
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
                if (finishButton.getGlobalBounds().contains(mousePos) && testCompleted) {
                    EnglishWindow.close();
                    return;
                }
                handleAnswerSelection(mousePos);
            }
        }
    }
}

void EnglishExam::handleAnswerSelection(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        if (answerTexts[i].getGlobalBounds().contains(mousePos)) {
            if (correctAnswers[currentQuestion] == 'A' + i) {
                score++;
            }
            currentQuestion++;
            if (currentQuestion >= questions.size()) {
                testCompleted = true;
                setupFinishButton();  
            }
            updateQuestionAndAnswers();
            break;
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

void EnglishExam::setupFinishButton() {
    finishButton.setSize(sf::Vector2f(200, 50));
    finishButton.setPosition(600, 350); 
    finishButton.setFillColor(sf::Color(1, 40, 95));

    finishButtonText.setFont(EnglishFont);
    finishButtonText.setString("FINISH");
    finishButtonText.setCharacterSize(24);
    finishButtonText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = finishButtonText.getLocalBounds();
    finishButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    finishButtonText.setPosition(finishButton.getPosition() + sf::Vector2f(100, 15));
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
    EnglishWindow.draw(footerText);

    if (!testCompleted) { 
        for (auto& answer : answerTexts) {
            EnglishWindow.draw(answer);
        }
    }

    if (testCompleted) {
        EnglishWindow.draw(finishButton);
        EnglishWindow.draw(finishButtonText);
    }
    EnglishWindow.display();
}

