#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

//The class allows us to implement a menu at the beginning of the game.
//Here we can choose how difficult our game should be

class Menu {
private:
    int number_of_strings = 3;
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3];
    sf::Texture tex_backbround;
    sf::Sprite background;
public:
    Menu(const sf::RenderTarget &window)
    {
        tex_backbround.loadFromFile("background.png");
        tex_backbround.setRepeated(true);
        background.setTexture(tex_backbround);
        background.setPosition(0,0);
        background.setTextureRect(sf::IntRect(0,0,window.getSize().x, window.getSize().y));

        if(!font.loadFromFile("font.ttf"))
        {
            std::cout << "error" <<std::endl;
        }
        menu[0].setFont(font);
        menu[0].setColor(sf::Color::Red);
        menu[0].setString("EASY");
        menu[0].setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/(number_of_strings+1)*1));

        menu[1].setFont(font);
        menu[1].setColor(sf::Color::Black);
        menu[1].setString("MEDIUM");
        menu[1].setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/(number_of_strings+1)*2));

        menu[2].setFont(font);
        menu[2].setColor(sf::Color::Black);
        menu[2].setString("HARD");
        menu[2].setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/(number_of_strings+1)*3));

        selectedItemIndex = 0;
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(background);
        for(int i = 0; i < number_of_strings; i++)
        {
            window.draw(menu[i]);
        }
    }
    void MoveUp()
    {
        if(selectedItemIndex -1 >= 0)
        {
            menu[selectedItemIndex].setColor(sf::Color::Black);
            selectedItemIndex--;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }
    void MoveDown()
    {
        if(selectedItemIndex + 1 < number_of_strings)
        {
            menu[selectedItemIndex].setColor(sf::Color::Black);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }

    int getPressed()
    {
        return selectedItemIndex;
    }
};
