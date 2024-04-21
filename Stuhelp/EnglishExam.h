#ifndef ENGLISHEXAM_H
#define ENGLISHEXAM_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <random>

class EnglishExam {
public:
    EnglishExam();
    void openWindow();

private:
    sf::RenderWindow EnglishWindow;
    sf::Font EnglishFont;
    sf::Text EnglishText, titleText, timerText;
    sf::Clock clock;
    sf::RectangleShape toolbarBackground;
    sf::Sprite leftLogoSprite, rightLogoSprite;
    sf::Texture leftLogoTexture, rightLogoTexture;

    bool testCompleted = false;

    void setupToolbar();
    void handleEvents();
    void render();
    void updateTimer();
    void closeWindow();
};
int main()
{

std::vector<std::string> questions = {
"Choose the correct form of the verb to complete the sentence: \"She ____________ to the party last night.\" \n A) go\n B) goes\n C) went\n D) gone\n",
"Which sentence is grammatically correct?\n A) He is reading a book for two hours.\n B) He has been reading a book for two hours.\n C) He reads a book for two hours.\n D) He read a book for two hours.\n",
"Select the sentence with the correct word order:\n A) My sister usually drives car to work.\n B) My sister drives usually car to work.\nC) My sister usually drives to work car.\nD) My sister usually drives to work.",
"Identify the correct past participle form of the verb \"eat\".\n A) eat\nB) eated\nC) eaten\nD) ate",
"Choose the correct form of the comparative adjective: \"This book is __________ than that one.\" \nA) more interesting\n B) interestinger\nC) interesting\nD) most interesting",
"Which sentence is in the passive voice? \nA) The teacher explained the lesson.\nB) The lesson was explained by the teacher.\nC) The teacher was explaining the lesson.\nD) The lesson explained the teacher.",
"Select the correct form of the irregular verb \"begin\" in the past tense: \nA) begined\nB) beginned\nC) begun\nD) began",
"Choose the correct modal verb to complete the sentence: \"You __________ stop here.\" \nA) shouldn\nB) could\nC) might\nD) must",
"Identify the correct plural form of \"child\": \nA) childs\nB) childs'\nC) childes\nD) children",
"Select the correct form of the possessive pronoun: \"This is __________ book.\" \nA) my\nB) mines\nC) me\nD) I",
"Choose the correct preposition to complete the sentence: \"She is interested __________ learning Spanish.\" \nA) in\nB) at\nC) on\nD) by",
"Which sentence is grammatically correct? \nA) There is many books on the shelf.\nB) There are much books on the shelf.\nC) There are many books on the shelf.\nD) There is much books on the shelf.",
"Identify the correct sentence structure: \nA) The cat sleep under the table.\nB) The cat sleeps under the table.\nC) The cat sleeping under the table.\nD) Sleeps the cat under the table.",
"Choose the correct form of the verb to complete the sentence: \"I __________ to the gym three times a week.\" \nA) go\nB) goes\nC) went\nD) gone",
"Select the sentence with the correct word order:\nA) They often go to the movies.\nB) Often they go to the movies.\nC) They go often to the movies.\nD) They go to the movies often.",
"Identify the correct past tense form of the verb \"run\": \nA) run\nB) ran\nC) running\nD) runned",
"Choose the correct form of the verb to complete the sentence: \"She ____________ a lot of questions.\" \nA) ask\nB) asks\nC) asked\nD) asking",
"Select the sentence with the correct word order:\nA) At 7 o'clock, we breakfast have.\nB) We have breakfast at 7 o'clock.\nC) Have breakfast we at 7 o'clock.\nD) We at 7 o'clock breakfast have.",
"Choose the correct form of the adjective: \"She is the __________ girl in the class.\" \nA) tallest\nB) tall\nC) more tall\nD) most tall",
"Identify the correct sentence structure:\nA) The car red is.\nB) Red the car is.\nC) The red car is.\nD) Car red the is."
};

std::vector<std::string> answers = {
    "C",
    "B",
    "D",
    "C",
    "A",
    "B",
    "D",
    "D",
    "D",
    "A",
    "A",
    "C",
    "B",
    "A",
    "A",
    "B",
    "B",
    "B",
    "A",
    "C"
};

std::random_device rd;
std::mt19937 gen(rd());

const int numTabs = 10;

std::uniform_int_distribution<> dist(0, questions.size() - 1);

int score = 10;

sf::RenderWindow window(sf::VideoMode(800, 600), "Quiz");

sf::Font font;
if (!font.loadFromFile("arial.ttf"))
{
    std::cerr << "Failed to load font file." << std::endl;
    return 1;
}

sf::Text questionText("", font, 24);
sf::Text answerText("", font, 24);
questionText.setPosition(50.f, 50.f);
answerText.setPosition(50.f, 100.f);

for (int tab = 0; tab < numTabs; ++tab)
{
    int index = dist(gen);
    questionText.setString("Tab " + std::to_string(tab + 1) + ":\n" + questions[index]);

    answerText.setString("");

    window.clear(sf::Color::White);
    window.draw(questionText);
    window.display();

    std::string input;
    std::cin >> input;

    if (input != answers[index])
    {
        score -= 1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
            {
                window.close();
            }
        }
    }

    if (tab == numTabs - 1)
    {
        double percentage = static_cast<double>(score) / 10 * 100;

        std::string grade;
        if (percentage < 60)
        {
            grade = "poor";
        }
        else if (percentage < 70)
        {
            grade = "average";
        }
        else if (percentage < 80)
        {
            grade = "good";
        }
        else if (percentage < 90)
        {
            grade = "very good";
        }
        else
        {
            grade = "excellent";
        }

        std::cout << "Your final score is: " << percentage << "%" << std::endl;
        std::cout << "The grade is " << grade << std::endl;
    }
}
}
#endif
