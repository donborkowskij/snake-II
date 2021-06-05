//
// Created by marki on 2021-06-05.
//

#include "Achievements.h"
#include "iostream"

int Myapples;
int Myscore;
int TotalApples;
int ShopSelect = 0;

void Achievements::Menu() {
    if(!font.loadFromFile("assets/fonts/slant_regular.ttf")){
        //give some error message
    }

    AchiveText[0].setFont(font);
    AchiveText[0].setFillColor(sf::Color(96,96,96));
    AchiveText[0].setString("Apple I");
    AchiveText[0].setCharacterSize(35);
    AchiveText[0].setPosition(sf::Vector2f(75, 110));

    AchiveText[1].setFont(font);
    AchiveText[1].setFillColor(sf::Color(96,96,96));
    AchiveText[1].setString("Apple II");
    AchiveText[1].setCharacterSize(35);
    AchiveText[1].setPosition(sf::Vector2f(75, 220));

    AchiveText[2].setFont(font);
    AchiveText[2].setFillColor(sf::Color(96,96,96));
    AchiveText[2].setString("Apple III");
    AchiveText[2].setCharacterSize(35);
    AchiveText[2].setPosition(sf::Vector2f(75, 330));

    AchiveText[3].setFont(font);
    AchiveText[3].setFillColor(sf::Color(96,96,96));
    AchiveText[3].setString("Apple IV");
    AchiveText[3].setCharacterSize(35);
    AchiveText[3].setPosition(sf::Vector2f(75, 440));

    AchiveText[4].setFont(font);
    AchiveText[4].setFillColor(sf::Color(96,96,96));
    AchiveText[4].setString("Apple V");
    AchiveText[4].setCharacterSize(35);
    AchiveText[4].setPosition(sf::Vector2f(75, 110));

    AchiveText[5].setFont(font);
    AchiveText[5].setFillColor(sf::Color(96,96,96));
    AchiveText[5].setString("Apple VI");
    AchiveText[5].setCharacterSize(35);
    AchiveText[5].setPosition(sf::Vector2f(75, 220));

    AchiveText[6].setFont(font);
    AchiveText[6].setFillColor(sf::Color(96,96,96));
    AchiveText[6].setString("Apple VII");
    AchiveText[6].setCharacterSize(35);
    AchiveText[6].setPosition(sf::Vector2f(75, 330));


    AchiveText[7].setFont(font);
    AchiveText[7].setFillColor(sf::Color(96,96,96));
    AchiveText[7].setString("Score I");
    AchiveText[7].setCharacterSize(35);
    AchiveText[7].setPosition(sf::Vector2f(75, 440));

    AchiveText[8].setFont(font);
    AchiveText[8].setFillColor(sf::Color(96,96,96));
    AchiveText[8].setString("Score II");
    AchiveText[8].setCharacterSize(35);
    AchiveText[8].setPosition(sf::Vector2f(75, 110));

    AchiveText[9].setFont(font);
    AchiveText[9].setFillColor(sf::Color(96,96,96));
    AchiveText[9].setString("Score III");
    AchiveText[9].setCharacterSize(35);
    AchiveText[9].setPosition(sf::Vector2f(75, 220));

    AchiveText[10].setFont(font);
    AchiveText[10].setFillColor(sf::Color(96,96,96));
    AchiveText[10].setString("Score IV");
    AchiveText[10].setCharacterSize(35);
    AchiveText[10].setPosition(sf::Vector2f(75, 330));

    AchiveText[11].setFont(font);
    AchiveText[11].setFillColor(sf::Color(96,96,96));
    AchiveText[11].setString("Score V");
    AchiveText[11].setCharacterSize(35);
    AchiveText[11].setPosition(sf::Vector2f(75, 440));

    AchiveText[12].setFont(font);
    AchiveText[12].setFillColor(sf::Color(96,96,96));
    AchiveText[12].setString("Score VI");
    AchiveText[12].setCharacterSize(35);
    AchiveText[12].setPosition(sf::Vector2f(75, 110));

    AchiveText[13].setFont(font);
    AchiveText[13].setFillColor(sf::Color(96,96,96));
    AchiveText[13].setString("Score VII");
    AchiveText[13].setCharacterSize(35);
    AchiveText[13].setPosition(sf::Vector2f(75, 220));

    AchiveText[14].setFont(font);
    AchiveText[14].setFillColor(sf::Color(96,96,96));
    AchiveText[14].setString("Grand Secret I");
    AchiveText[14].setCharacterSize(35);
    AchiveText[14].setPosition(sf::Vector2f(75, 330));

    AchiveText[15].setFont(font);
    AchiveText[15].setFillColor(sf::Color(96,96,96));
    AchiveText[15].setString("Grand Secret II");
    AchiveText[15].setCharacterSize(35);
    AchiveText[15].setPosition(sf::Vector2f(75, 440));




    TextChild[0].setFont(font);
    TextChild[0].setFillColor(sf::Color(96,96,96));
    TextChild[0].setString("You ate 1 apple.");
    TextChild[0].setCharacterSize(20);
    TextChild[0].setPosition(sf::Vector2f(75, 160));

    TextChild[1].setFont(font);
    TextChild[1].setFillColor(sf::Color(96,96,96));
    TextChild[1].setString("You ate 10 apples.");
    TextChild[1].setCharacterSize(20);
    TextChild[1].setPosition(sf::Vector2f(75, 270));

    TextChild[2].setFont(font);
    TextChild[2].setFillColor(sf::Color(96,96,96));
    TextChild[2].setString("You ate 50 apples.");
    TextChild[2].setCharacterSize(20);
    TextChild[2].setPosition(sf::Vector2f(75, 380));

    TextChild[3].setFont(font);
    TextChild[3].setFillColor(sf::Color(96,96,96));
    TextChild[3].setString("You ate 100 apples.");
    TextChild[3].setCharacterSize(20);
    TextChild[3].setPosition(sf::Vector2f(75, 490));

    TextChild[4].setFont(font);
    TextChild[4].setFillColor(sf::Color(96,96,96));
    TextChild[4].setString("You ate 200 apple.");
    TextChild[4].setCharacterSize(20);
    TextChild[4].setPosition(sf::Vector2f(75, 160));

    TextChild[5].setFont(font);
    TextChild[5].setFillColor(sf::Color(96,96,96));
    TextChild[5].setString("You ate 500 apples.");
    TextChild[5].setCharacterSize(20);
    TextChild[5].setPosition(sf::Vector2f(75, 270));

    TextChild[6].setFont(font);
    TextChild[6].setFillColor(sf::Color(96,96,96));
    TextChild[6].setString("You ate 1000 apples.");
    TextChild[6].setCharacterSize(20);
    TextChild[6].setPosition(sf::Vector2f(75, 380));


    TextChild[7].setFont(font);
    TextChild[7].setFillColor(sf::Color(96,96,96));
    TextChild[7].setString("You got a score of 100 points.");
    TextChild[7].setCharacterSize(20);
    TextChild[7].setPosition(sf::Vector2f(75, 490));

    TextChild[8].setFont(font);
    TextChild[8].setFillColor(sf::Color(96,96,96));
    TextChild[8].setString("You got a score of 1000 points.");
    TextChild[8].setCharacterSize(20);
    TextChild[8].setPosition(sf::Vector2f(75, 160));

    TextChild[9].setFont(font);
    TextChild[9].setFillColor(sf::Color(96,96,96));
    TextChild[9].setString("You got a score of 5000 points.");
    TextChild[9].setCharacterSize(20);
    TextChild[9].setPosition(sf::Vector2f(75, 270));

    TextChild[10].setFont(font);
    TextChild[10].setFillColor(sf::Color(96,96,96));
    TextChild[10].setString("You got a score of 10000 points.");
    TextChild[10].setCharacterSize(20);
    TextChild[10].setPosition(sf::Vector2f(75, 380));

    TextChild[11].setFont(font);
    TextChild[11].setFillColor(sf::Color(96,96,96));
    TextChild[11].setString("You got a score of 50000 points.");
    TextChild[11].setCharacterSize(20);
    TextChild[11].setPosition(sf::Vector2f(75, 490));

    TextChild[12].setFont(font);
    TextChild[12].setFillColor(sf::Color(96,96,96));
    TextChild[12].setString("You got a score of 1000000 points.");
    TextChild[12].setCharacterSize(20);
    TextChild[12].setPosition(sf::Vector2f(75, 160));

    TextChild[13].setFont(font);
    TextChild[13].setFillColor(sf::Color(96,96,96));
    TextChild[13].setString("You got a score of 500000 points.");
    TextChild[13].setCharacterSize(20);
    TextChild[13].setPosition(sf::Vector2f(75, 270));

    TextChild[14].setFont(font);
    TextChild[14].setFillColor(sf::Color(96,96,96));
    TextChild[14].setString("A good n00b?");
    TextChild[14].setCharacterSize(20);
    TextChild[14].setPosition(sf::Vector2f(75, 380));

    TextChild[15].setFont(font);
    TextChild[15].setFillColor(sf::Color(96,96,96));
    TextChild[15].setString("2 funny numbers.");
    TextChild[15].setCharacterSize(20);
    TextChild[15].setPosition(sf::Vector2f(75, 490));


    ExtraText[0].setFont(font);
    ExtraText[0].setFillColor(sf::Color(255, 204, 153));
    ExtraText[0].setString("Press Q to quit to Main menu");
    ExtraText[0].setCharacterSize(30);
    ExtraText[0].setPosition(sf::Vector2f(420, 560));

    ExtraText[1].setFont(font);
    ExtraText[1].setFillColor(sf::Color(255, 204, 153));
    //ExtraText[1].setString("Most apples eaten: " + to_string(::Myapples));
    ExtraText[1].setCharacterSize(40);
    ExtraText[1].setPosition(sf::Vector2f(75, 5));

    ExtraText[2].setFont(font);
    ExtraText[2].setFillColor(sf::Color(255, 204, 153));
    //ExtraText[2].setString("Your highest score: " + to_string(::Myscore));
    ExtraText[2].setCharacterSize(40);
    ExtraText[2].setPosition(sf::Vector2f(75, 45));
}

void Achievements::Screen(sf::RenderWindow &window, int i){
    window.draw(AchiveText[i]);
    window.draw(AchiveText[i+1]);
    window.draw(AchiveText[i+2]);
    window.draw(AchiveText[i+3]);
    window.draw(TextChild[i]);
    window.draw(TextChild[i+1]);
    window.draw(TextChild[i+2]);
    window.draw(TextChild[i+3]);
    window.draw(ExtraText[0]);
    window.draw(ExtraText[1]);
    window.draw(ExtraText[2]);
}

void Achievements::Color(int i) {
    AchiveText[i].setFillColor(sf::Color(212,175,55));
    TextChild[i].setFillColor(sf::Color(212,175,55));
}

void Achievements::DataHandling(){
    //load previous data
    ifstream saveFileProfile ("assets/save/dataProfile.txt");

    if (saveFileProfile.is_open()){
        saveFileProfile>>::Myapples>>::Myscore>>::TotalApples;
        saveFileProfile.close();
    }
    ExtraText[1].setString("Most apples eaten: " + to_string(::TotalApples));
    ExtraText[2].setString("Your highest score: " + to_string(::Myscore));
    //Why did i create this?
}


void Achievements::Brain() {
    if(::TotalApples>=1){
        Color(0);
    }
    if(::TotalApples>=10){
        Color(1);
    }
    if(::TotalApples>=50){
        Color(2);
    }
    if(::TotalApples>=100){
        Color(3);
    }
    if(::TotalApples>=200){
        Color(4);
    }
    if(::TotalApples>=500){
        Color(5);
    }
    if(::TotalApples>=1000){
        Color(6);
    }
    if(::Myscore>=100){
        Color(7);
    }
    if(::Myscore>=1000){
        Color(8);
    }
    if(::Myscore>=5000){
        Color(9);
    }
    if(::Myscore>=10000){
        Color(10);
    }
    if(::Myscore>=50000){
        Color(11);
    }
    if(::Myscore>=100000){
        Color(12);
    }
    if(::Myscore>=500000){
        Color(13);
    }
    if(::TotalApples==1337){
        Color(14);
    }
    if(::TotalApples>=69 && ::Myscore>=420){
        Color(15);
    }
}


void Achievements::AchievementsRun() {
    Menu();
    DataHandling();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    sf::Texture background;
    background.loadFromFile("assets/texture/AchievementsMenu.png");
    sf::Sprite bg_image(background);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    if(::ShopSelect!=12){
                        ::ShopSelect+=4;
                    }
                }
                if (event.key.code == sf::Keyboard::Up) {
                    if(::ShopSelect!=0){
                        ::ShopSelect-=4;
                    }
                }
                if (event.key.code == Keyboard::Q){
                    window.close();
                    runMenu();
                }

                }

            }


        window.clear();
        window.draw(bg_image);
        Screen(window, ::ShopSelect);
        Brain();
        window.display();

        }




    }

void Achievements::runMenu(){
    MainMenu menu;
    menu.Menu();
}