//
// Created by marki on 2021-06-04.
//
#include "Shop.h"
#include "MainMenu.h"
#include "iostream"
int Shop_currency;

void Shop::Menu() {
    if(!font.loadFromFile("assets/fonts/slant_regular.ttf")){
        //give some error message
    }

    MainText[0].setFont(font);
    MainText[0].setFillColor(sf::Color(255, 204, 153));
    MainText[0].setString("Green Snake");
    MainText[0].setCharacterSize(35);
    MainText[0].setPosition(sf::Vector2f(75, 110));

    TextChild[0].setFont(font);
    TextChild[0].setFillColor(sf::Color(255, 204, 153));
    TextChild[0].setString("Cost: 25 apples");
    TextChild[0].setCharacterSize(20);
    TextChild[0].setPosition(sf::Vector2f(75, 150));

    MainText[1].setFont(font);
    MainText[1].setFillColor(sf::Color(255, 204, 153));
    MainText[1].setString("Red Snake");
    MainText[1].setCharacterSize(35);
    MainText[1].setPosition(sf::Vector2f(75, 230));

    TextChild[1].setFont(font);
    TextChild[1].setFillColor(sf::Color(255, 204, 153));
    TextChild[1].setString("Cost: 25 apples");
    TextChild[1].setCharacterSize(20);
    TextChild[1].setPosition(sf::Vector2f(75, 270));

    MainText[2].setFont(font);
    MainText[2].setFillColor(sf::Color(255, 204, 153));
    MainText[2].setString("Blue Snake");
    MainText[2].setCharacterSize(35);
    MainText[2].setPosition(sf::Vector2f(75, 350));

    TextChild[2].setFont(font);
    TextChild[2].setFillColor(sf::Color(255, 204, 153));
    TextChild[2].setString("Cost: 25 apples");
    TextChild[2].setCharacterSize(20);
    TextChild[2].setPosition(sf::Vector2f(75, 390));

    MainText[3].setFont(font);
    MainText[3].setFillColor(sf::Color(255, 204, 153));
    MainText[3].setString("Yellow Snake");
    MainText[3].setCharacterSize(35);
    MainText[3].setPosition(sf::Vector2f(75, 470));

    TextChild[3].setFont(font);
    TextChild[3].setFillColor(sf::Color(255, 204, 153));
    TextChild[3].setString("Cost: 50 apples");
    TextChild[3].setCharacterSize(20);
    TextChild[3].setPosition(sf::Vector2f(75, 510));

    ExtraText[0].setFont(font);
    ExtraText[0].setFillColor(sf::Color(255, 204, 153));
    ExtraText[0].setString("Press Q to quit to Main menu");
    ExtraText[0].setCharacterSize(30);
    ExtraText[0].setPosition(sf::Vector2f(420, 560));

    ExtraText[1].setFont(font);
    ExtraText[1].setFillColor(sf::Color(255, 204, 153));
    //ExtraText[1].setString("Apples: " + to_string(::Shop_currency));
    ExtraText[1].setCharacterSize(40);
    ExtraText[1].setPosition(sf::Vector2f(75, 25));

    AltText[0].setFont(font);
    AltText[0].setFillColor(sf::Color::Green);
    AltText[0].setString("Equip");
    AltText[0].setCharacterSize(20);
    AltText[0].setPosition(sf::Vector2f(75, 150));

    AltText[1].setFont(font);
    AltText[1].setFillColor(sf::Color::Red);
    AltText[1].setString("Equip");
    AltText[1].setCharacterSize(20);
    AltText[1].setPosition(sf::Vector2f(75, 270));

    AltText[2].setFont(font);
    AltText[2].setFillColor(sf::Color::Blue);
    AltText[2].setString("Equip");
    AltText[2].setCharacterSize(20);
    AltText[2].setPosition(sf::Vector2f(75, 390));

    AltText[3].setFont(font);
    AltText[3].setFillColor(sf::Color::Yellow);
    AltText[3].setString("Equip");
    AltText[3].setCharacterSize(20);
    AltText[3].setPosition(sf::Vector2f(75, 510));

    ShopSelect = 0;
    MainText[ShopSelect].setFillColor(sf::Color::White);

}

void Shop::moveUp(){
    if(ShopSelect == 0){
        MainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));

        //Change this if there are more menu options.
        ShopSelect = 3;

        MainText[ShopSelect].setFillColor(sf::Color::White);
    }
    else{
        MainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));
        ShopSelect--;
        MainText[ShopSelect].setFillColor(sf::Color::White);
    }
}

void Shop::moveDown(){
    if(ShopSelect == 3){
        MainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));

        //Change this if there are more menu options.
        ShopSelect = 0;

        MainText[ShopSelect].setFillColor(sf::Color::White);
    }
    else{
        MainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));
        ShopSelect++;
        MainText[ShopSelect].setFillColor(sf::Color::White);
    }
}

void Shop::Draw(sf::RenderWindow &window) {
    int number;
    for(int c=0; c <=3; c++){
        window.draw(MainText[c]);
        number = ReturnBought (c);
        if(number == 0){
            window.draw(TextChild[c]);
        }
        else{
            window.draw(AltText[c]);
        }

    }

    /*
    for(const auto & i : MainText){
        window.draw(i);
    }
     */
}
void Shop::DrawExtra(sf::RenderWindow &window) {
    ExtraText[1].setString("Apples: " + to_string(::Shop_currency));
    window.draw(ExtraText[0]);
    window.draw(ExtraText[1]);
}

void Shop::SaveData() {
    //load previous data
    ifstream saveFileProfile ("assets/save/dataProfile.txt");
    int apples;
    int score;
    if (saveFileProfile.is_open()){
        saveFileProfile>>apples>>score;
        saveFileProfile.close();
    }

    //store new + old data
    ofstream saveProfile ("assets/save/dataProfile.txt", ofstream::trunc);
    if (saveProfile.is_open()){
        saveProfile<<::Shop_currency<<endl<<score;
        saveFileProfile.close();
    }


}

void Shop::LoadData() {
    ifstream saveFileProfile ("assets/save/dataProfile.txt");
    if (saveFileProfile.is_open()){
        int a;
        saveFileProfile>>a;
        saveFileProfile.close();
        ::Shop_currency = a;
    }
}

int Shop::ReturnBought(int number) {
    //load previous data
    int GreenSnake,RedSnake,BlueSnake,YellowSnake;
    ifstream saveFileProfile ("assets/save/Bought.txt");
    if (saveFileProfile.is_open()){
        saveFileProfile>>GreenSnake>>RedSnake>>BlueSnake>>YellowSnake;
        saveFileProfile.close();
    }
    if(number == 0){
        return GreenSnake;
    }
    if(number == 1){
        return RedSnake;
    }
    if(number == 2){
        return BlueSnake;
    }
    if(number == 3){
        return YellowSnake;
    }
}
void Shop::SaveBought(int a, int b, int c, int d) {
    int GreenSnake = 0;
    int RedSnake = 0;
    int BlueSnake = 0;
    int YellowSnake  = 0;

    //load previous data
    ifstream saveFileProfile ("assets/save/Bought.txt");
    if (saveFileProfile.is_open()){
        saveFileProfile>>GreenSnake>>RedSnake>>BlueSnake>>YellowSnake;
        saveFileProfile.close();
    }

    //store new + old data
    ofstream saveProfile ("assets/save/Bought.txt", ofstream::trunc);
    if (saveProfile.is_open()){
        if(GreenSnake>=a){
            saveProfile<<GreenSnake<<endl;
        }
        else{
            saveProfile<<a<<endl;
        }
        if(RedSnake>=b){
            saveProfile<<RedSnake<<endl;
        }
        else{
            saveProfile<<b<<endl;
        }
        if(a!=BlueSnake){
            saveProfile<<BlueSnake<<endl;
        }
        else{
            saveProfile<<c<<endl;
        }
        if(a!=YellowSnake){
            saveProfile<<YellowSnake<<endl;
        }
        else{
            saveProfile<<d<<endl;
        }
        saveProfile.close();
    }
}

void Shop::ShopRun() {
    Menu();
    LoadData();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    sf::Texture background;
    background.loadFromFile("assets/texture/ShopMenu.png");
    sf::Sprite bg_image(background);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    moveDown();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    moveUp();
                }
                if (event.key.code == Keyboard::Q){
                    window.close();
                    runMenu();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    switch (ShopSelect) {
                        case 0:
                            if(ReturnBought(0) == 1){
                                SnakeColorBuy(0);
                            }
                            else if(::Shop_currency>=25){
                                ::Shop_currency-=25;
                                //cout << ::Shop_currency;
                                SnakeColorBuy(0);
                                SaveBought(1,0,0,0);
                                SaveData();
                            }
                            break;
                        case 1:
                            if(ReturnBought(1) == 1){
                                SnakeColorBuy(1);
                            }
                            else if(::Shop_currency>=25){
                                ::Shop_currency-=25;
                                SnakeColorBuy(1);
                                SaveBought(0,1,0,0);
                                SaveData();


                            }
                            break;
                        case 2:
                            if(ReturnBought(2) == 1){
                                SnakeColorBuy(2);
                            }
                            else if(::Shop_currency>=25){
                                ::Shop_currency-=25;
                                SnakeColorBuy(2);
                                SaveBought(0,0,1,0);
                                SaveData();


                            }
                            break;
                        case 3:
                            if(ReturnBought(3) == 1){
                                SnakeColorBuy(3);
                            }
                            else if(::Shop_currency>=50){
                                ::Shop_currency-=50;
                                SnakeColorBuy(3);
                                SaveBought(0,0,0,1);
                                SaveData();

                            }
                            break;

                    }
                }

            }
        }

        window.clear();
        window.draw(bg_image);
        DrawExtra(window);
        Draw(window);
        window.display();

    }
}
void Shop::runMenu(){
    MainMenu menu;
    menu.Menu();
}
void Shop::SnakeColorBuy(int a){
    Snake::SnakeColor(a);

}
