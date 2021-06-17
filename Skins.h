#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

//The class allows us to implement a skin menu at the beginning of the game.
//Here we can choose the color of your bird

class Skins {
private:
    int number_of_strings = 4;
    int selectedItemIndex;
    sf::Font font;
    sf::Text skins[4];
    sf::Texture tex_backbround;
    sf::Sprite background;
    sf::Texture tex_yellow_bird;
    sf::Sprite yellow_bird;
    sf::Texture tex_red_bird;
    sf::Sprite red_bird;
    sf::Texture tex_blue_bird;
    sf::Sprite blue_bird;

public:
    Skins(const sf::RenderTarget &window)
    {
        tex_backbround.loadFromFile("background.png");
        tex_backbround.setRepeated(true);
        background.setTexture(tex_backbround);
        background.setPosition(0,0);
        background.setTextureRect(sf::IntRect(0,0,window.getSize().x, window.getSize().y));

        tex_yellow_bird.loadFromFile("yellow_bird.png");
        yellow_bird.setTexture(tex_yellow_bird);
        yellow_bird.setTextureRect(sf::IntRect(90,138,320,225));
        yellow_bird.setScale(0.2,0.2);
        yellow_bird.setPosition(window.getSize().x/4-100, window.getSize().y/(number_of_strings+1)*2);

        tex_blue_bird.loadFromFile("blue_bird.png");
        blue_bird.setTexture(tex_blue_bird);
        blue_bird.setTextureRect(sf::IntRect(90,138,320,225));
        blue_bird.setScale(0.2,0.2);
        blue_bird.setPosition(window.getSize().x/4-100, window.getSize().y/(number_of_strings+1)*3);

        tex_red_bird.loadFromFile("red_bird.png");
        red_bird.setTexture(tex_red_bird);
        red_bird.setTextureRect(sf::IntRect(90,138,320,225));
        red_bird.setScale(0.2,0.2);
        red_bird.setPosition(window.getSize().x/4-100, window.getSize().y/(number_of_strings+1)*4);


        if(!font.loadFromFile("font.ttf"))
        {
            std::cout << "error" <<std::endl;
        }

        for(int i = 0; i < number_of_strings; i++)
        {
            skins[i].setFont(font);
        }
        skins[0].setColor(sf::Color::Black);
        skins[0].setString("CHOOSE COLOR FOR PLAYER 1:");
        skins[0].Bold;
        skins[0].setPosition(sf::Vector2f(window.getSize().x/4 - 100, window.getSize().y/(number_of_strings+1)*1));

        skins[1].setColor(sf::Color::Red);
        skins[1].setString("YELLOW");
        skins[1].setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/(number_of_strings+1)*2));

        skins[2].setColor(sf::Color::Black);
        skins[2].setString("BLUE");
        skins[2].setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/(number_of_strings+1)*3));

        skins[3].setColor(sf::Color::Black);
        skins[3].setString("RED");
        skins[3].setPosition(sf::Vector2f(window.getSize().x/4, window.getSize().y/(number_of_strings+1)*4));

        selectedItemIndex = 1;
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(background);
        window.draw(yellow_bird);
        window.draw(blue_bird);
        window.draw(red_bird);
        for(int i = 0; i < number_of_strings; i++)
        {
            window.draw(skins[i]);
        }
    }
    void MoveUp()
    {
        if(selectedItemIndex -1 >= 1)
        {
            skins[selectedItemIndex].setColor(sf::Color::Black);
            selectedItemIndex--;
            skins[selectedItemIndex].setColor(sf::Color::Red);
        }
    }
    void MoveDown()
    {
        if(selectedItemIndex + 1 < number_of_strings)
        {
            skins[selectedItemIndex].setColor(sf::Color::Black);
            selectedItemIndex++;
            skins[selectedItemIndex].setColor(sf::Color::Red);
        }
    }

    int getPressed()
    {
        return selectedItemIndex;
    }
};

