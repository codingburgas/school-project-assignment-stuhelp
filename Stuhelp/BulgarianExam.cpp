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
    if (!Bulgarian2Font.loadFromFile("Fonts/SourceSansPro-Light.ttf")) {
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
    shuffleQuestions();

    timerText.setFont(BulgarianFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(1200, toolbarHeight);
}

void BulgarianExam::setupQuestionsAndAnswers() {
    questions = {
    "Koy avtor e napisal 'Pod Igoto'?",
    "Kakva e stolicata na Bulgaria?",
    "V koy vek e osnovana Bălgarskata dărzhava?",
    "Koy e avtorăt na 'Tătăt na Hitar Petăr'?",
    "Kak se kazva bulgarskiyat natsionalen folkloren instrument s dyrveni piskuli?",
    "Koy praznik se chestva na 3-ti mart?",
    "Kakvo predstavlya bălgarskata martenitsa?",
    "Koy e osnovatel na Bălgarskata ekzarkhiya?",
    "Kakvo e 'chitalishte' v konteksta na bulgarskata kultura?",
    "Koy bulgarski vladetel e poznat s pravoto na Kaloyan?",
    "Koe e izvestnoto bulgarsko vŭstanie sreshtu osmanskata vlast?",
    "Koy grad e domakin na godishniya Mezhdunaroden panair?",
    "Koy e nay-visokiya vrăh v Bulgaria?",
    "Kakvo ozanachava dumat 'leka nosht' na bulgarski?",
    "Koy bulgarski pisatel e izvesten s proizvedenieto 'Bai Ganyo'?",
    "Koy e părviyat bulgarski tsar sled osvobozhdenieto?",
    "Kak se kazva natsionalnata opera na Bulgaria?",
    "Kakvo oznachava 'merindje' na bulgarski?",
    "Kak se praznuva 'Gergyovden' v Bulgaria?",
    "Koy e nay-stariyat grad v Bulgaria?"
    };

    answers = {
        {"Ivan Vazov", "Hristo Botev", "Peyo Yavorov", "Aleko Konstantinov"},
        {"Sofiya", "Plovdiv", "Varna", "Burgas"},
        {"VII vek", "VIII vek", "IX vek", "X vek"},
        {"Elin Pelin", "Ivan Vazov", "Lyuben Karavelov", "Aleko Konstantinov"},
        {"Gaida", "Gadulka", "Tambura", "Kaval"},
        {"Den na osvobozhdenieto", "Den na narodnite buditeli", "Den na nezavisimostta", "Den na truda"},
        {"Braslet ot chererveni i beli nishki", "Traditsionno bulgarsko yastie", "Narodna pesen", "Tanets"},
        {"Ekzarh Antim I", "Ekzarh Iosif I", "Ekzarh Stefan I", "Patriarh Evtimiy"},
        {"Mesto za chetene", "Kulturno- prosveshtensko zavedenie", "Tip bar", "Starinni dom"},
        {"Asen", "Peter", "Kaloyan", "Ivan Asen II"},
        {"Aprilsko vŭstanie", "Ilindensko-Preobrazhensko vŭstanie", "Shipchensko vŭstanie", "Bratsigovsko vŭstanie"},
        {"Plovdiv", "Sofiya", "Varna", "Ruse"},
        {"Musala", "Vihren", "Pirin", "Rila"},
        {"Good night", "Sweet dreams", "Good evening", "Sleep well"},
        {"Aleko Konstantinov", "Ivan Vazov", "Peyo Yavorov", "Geo Milev"},
        {"Ferdinand I", "Simeon Veliki", "Boris I", "Aleksandăr I Battenberg"},
        {"Sofiska opera", "Narodna opera", "Dărzhavna opera", "Metropolitna opera"},
        {"Ukrasa", "Med", "Sladko", "Podarăk"},
        {"S pazaruvane", "S yadeneto na agneshko", "S pesni i tantsi", "S semeen obed"},
        {"Plovdiv", "Sofiya", "Nesebăr", "Veliko Tărnovo"}
    };

    correctAnswers = {
        'A',
        'A',
        'B',
        'A',
        'A',
        'A',
        'A',
        'B',
        'B',
        'C',
        'A',
        'A',
        'A',
        'B',
        'A',
        'D',
        'A',
        'C',
        'B',
        'C'
    };



    questionText.setFont(BulgarianFont);
    questionText.setCharacterSize(40);
    questionText.setFillColor(sf::Color::Black);
    questionText.setString(questions[0]);
    sf::FloatRect questionBounds = questionText.getLocalBounds();
    questionText.setOrigin(questionBounds.width / 2, questionBounds.height / 2);
    questionText.setPosition(700, 150);

    answerTexts.resize(4);
    for (size_t i = 0; i < answerTexts.size(); ++i) {
        answerTexts[i].setFont(Bulgarian2Font);
        answerTexts[i].setCharacterSize(30);
        answerTexts[i].setFillColor(sf::Color::Black);
        answerTexts[i].setString(answers[0][i]);
        sf::FloatRect answerBounds = answerTexts[i].getLocalBounds();
        answerTexts[i].setOrigin(answerBounds.width / 2, answerBounds.height / 2);
        answerTexts[i].setPosition(700, 300 + i * 55);
    }
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
    BulgarianText.setPosition(600, 50);
}


void BulgarianExam::openWindow() {
    BulgarianWindow.create(sf::VideoMode(1400, 800), "STUHELP BULGARIAN EXAM ACTIVE");
    while (BulgarianWindow.isOpen()) {
        handleEvents();
        updateTimer();
        render();
    }
}

std::string wrapTextBulgarian(std::string text, sf::Font& font, unsigned characterSize, unsigned width) {
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


void BulgarianExam::updateQuestionAndAnswers() {
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


void BulgarianExam::updateRegularQuestions() {
    std::string wrappedQuestion = wrapTextBulgarian(questions[currentQuestion], BulgarianFont, 40, 1300);
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



void BulgarianExam::setupFooter() {
    footerText.setFont(BulgarianFont);
    footerText.setString("Copyright © 2024 by STUHELP. All rights reserved.");
    footerText.setCharacterSize(20);
    footerText.setFillColor(sf::Color::Black);

    sf::FloatRect footerBounds = footerText.getLocalBounds();
    footerText.setOrigin(footerBounds.width / 2, footerBounds.height / 2);
    footerText.setPosition(700, 770);
}


void BulgarianExam::handleEvents() {
    sf::Event event;
    while (BulgarianWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            BulgarianWindow.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = BulgarianWindow.mapPixelToCoords(sf::Mouse::getPosition(BulgarianWindow));
                if (finishButton.getGlobalBounds().contains(mousePos) && testCompleted) {
                    BulgarianWindow.close();
                    return;
                }
                handleAnswerSelection(mousePos);
            }
        }
    }
}

void BulgarianExam::handleAnswerSelection(const sf::Vector2f& mousePos) {
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

//TIMER

void BulgarianExam::updateTimer() {
    sf::Time elapsed = clock.getElapsedTime();
    sf::Time timeLeft = sf::seconds(1800) - elapsed;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< HERE SET THE TIMER FOR TESTING!!

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

void BulgarianExam::setupFinishButton() {
    finishButton.setSize(sf::Vector2f(200, 50));
    finishButton.setPosition(600, 350);
    finishButton.setFillColor(sf::Color(1, 40, 95));

    finishButtonText.setFont(BulgarianFont);
    finishButtonText.setString("FINISH");
    finishButtonText.setCharacterSize(24);
    finishButtonText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = finishButtonText.getLocalBounds();
    finishButtonText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    finishButtonText.setPosition(finishButton.getPosition() + sf::Vector2f(100, 15));
}

void BulgarianExam::shuffleQuestions() {

    std::random_device rd;
    std::mt19937 g(rd());


    std::vector<int> indices(questions.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::shuffle(indices.begin(), indices.end(), g);

    std::vector<std::string> shuffledQuestions(questions.size());
    std::vector<std::vector<std::string>> shuffledAnswers(answers.size());
    std::vector<char> shuffledCorrectAnswers(correctAnswers.size());

    for (size_t i = 0; i < indices.size(); ++i) {
        shuffledQuestions[i] = questions[indices[i]];
        shuffledAnswers[i] = answers[indices[i]];
        shuffledCorrectAnswers[i] = correctAnswers[indices[i]];
    }

    questions = std::move(shuffledQuestions);
    answers = std::move(shuffledAnswers);
    correctAnswers = std::move(shuffledCorrectAnswers);
}

void BulgarianExam::render() {
    BulgarianWindow.clear(sf::Color(250, 250, 250));
    BulgarianWindow.draw(toolbarBackground);
    BulgarianWindow.draw(leftLogoSprite);
    BulgarianWindow.draw(rightLogoSprite);
    BulgarianWindow.draw(titleText);
    BulgarianWindow.draw(BulgarianText);
    BulgarianWindow.draw(timerText);
    BulgarianWindow.draw(questionText);
    BulgarianWindow.draw(footerText);

    if (!testCompleted) {
        for (auto& answer : answerTexts) {
            BulgarianWindow.draw(answer);
        }
    }

    if (testCompleted) {
        BulgarianWindow.draw(finishButton);
        BulgarianWindow.draw(finishButtonText);
    }
    BulgarianWindow.display();
}

