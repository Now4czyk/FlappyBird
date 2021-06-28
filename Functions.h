#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include "Bird.h"
#include "Menu.h"
#include "Skins.h"

//The function creates gravitation for the main object
void gravitation(Bird &bird, const float &gravitation_value)
{
    float velY = bird.vely();
    if(velY < 8)
    {
        velY += gravitation_value;
    }
    bird.velocity_y(velY);
}

//The function checks whether there is a collision
//between a bird and a pipe
void collision_pipe(Bird &bird, const sf::Sprite &pipe)
{
    if(pipe.getGlobalBounds().intersects(bird.getGlobalBounds()))
    {
        bird.velocity(0,0);
        bird.set_BOOM(true);
        bird.dock_points();
    }
}

//The function checks whether there is a collision
//between a bird and a wall(top and bottom)
void collision_wall(Bird &bird, const float &window)
{
    if(bird.getGlobalBounds().top <= 0 || bird.getGlobalBounds().top + bird.getGlobalBounds().height > window)
    {
        bird.velocity(0,0);
        bird.set_BOOM(true);
    }
}

//The function generates upper parts of pipes
void generate_pipeU(std::vector<sf::Sprite> &pipes, const sf::Texture &tex_pipe, const float &pipe_x, const float &pipe_y)
{
    sf::Sprite pipe;
    pipe.setTexture(tex_pipe);
    pipe.setPosition(pipe_x, 200+pipe_y);
    pipe.setTextureRect(sf::IntRect(0,0,344,4000));
    pipe.setScale(0.15,0.15);
    pipe.setRotation(180);
    pipes.emplace_back(pipe);
}

//The function generates lower parts of pipes
void generate_pipeD(std::vector<sf::Sprite> &pipes, const sf::Texture &tex_pipe, const float &pipe_x, const float &pipe_y, const float &lvl)
{
    sf::Sprite pipe4;
    pipe4.setTexture(tex_pipe);
    pipe4.setPosition(-51.6+pipe_x, 200+lvl+pipe_y);
    pipe4.setTextureRect(sf::IntRect(0,0,344,4000));
    pipe4.setScale(0.15,0.15);
    pipes.emplace_back(pipe4);
}

//The function gets information which level was chosen
//and depending on it creates smaller or bigger distance
//between an upper and a lower part of pipe
void choosing_lvl_and_generating_pipes(Menu &menu, std::vector<sf::Sprite> &pipeSpritevec, const sf::Texture &tex_pipe, bool &is_menu, const float &easy, const float &medium, const float &hard, const float &dist)
{
    float coord_x = dist, coord_y;
    switch (menu.getPressed()) {

    case 0:
        std::cout << "=================================================" << std::endl;
        std::cout << "SELECTED LEVEL: EASY" << std::endl;
        for(int i = 0; i < 50; i++)
        {
            do
            {
                coord_y = rand() % 300 - 150;
            }while(coord_y+easy+200>550 || coord_y+easy+200 < 0);
            generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
            generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y, easy);
            coord_x += dist;
        }
        is_menu = 0;
        break;
    case 1:
        std::cout << "=================================================" << std::endl;
        std::cout << "SELECTED LEVEL: MEDIUM" << std::endl;
        for(int i = 0; i < 50; i++)
        {
            do
            {
                coord_y = rand() % 300 - 150;
            }while(coord_y+easy+200>550 || coord_y+easy+200 < 0);
            generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
            generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y, medium);
            coord_x += dist;
        }
        is_menu = 0;
        break;
    case 2:
        std::cout << "=================================================" << std::endl;
        std::cout << "SELECTED LEVEL: HARD" << std::endl;
        for(int i = 0; i < 50; i++)
        {
            do
            {
                coord_y = rand() % 300 - 150;
            }while(coord_y+easy+200>550 || coord_y+easy+200 < 0);
            generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
            generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y, hard);
            coord_x += dist;
        }
        is_menu = 0;
        break;
    }
}

//The function gets information which color of bird was chosen
//and depending on it creates a bird in this color
void choosing_skin(Skins &skins,Bird &bird, Bird &bird2, const int &number, std::vector<std::unique_ptr<sf::Drawable>> &shapes, bool &is_skins, const sf::Texture &yellow_bird, const sf::Texture &blue_bird, const sf::Texture &red_bird)
{
    sf::Texture tex_bird;

    switch (skins.getPressed()) {
    case 1:
        std::cout << "=================================================" << std::endl;
        std::cout << "SELECTED COLOR: YELLOW" << std::endl;
        bird.setTexture(yellow_bird);
        is_skins = 0;
        if(number == 2)
        {
            bird2.setTexture(red_bird);
        }
        break;
    case 2:
        std::cout << "=================================================" << std::endl;
        std::cout << "SELECTED COLOR: BLUE" << std::endl;
        bird.setTexture(blue_bird);
        is_skins = 0;
        if(number == 2)
        {
            bird2.setTexture(red_bird);
        }
        break;
    case 3:
        std::cout << "=================================================" << std::endl;
        std::cout << "SELECTED COLOR: RED" << std::endl;
        bird.setTexture(red_bird);
        is_skins = 0;
        if(number == 2)
        {
            bird2.setTexture(yellow_bird);
        }
        break;
    }

    bird.setPosition(-250, 100);
    bird.setTextureRect(sf::IntRect(90,138,320,225));
    bird.setOrigin(bird.getGlobalBounds().width/2,bird.getGlobalBounds().height/2);
    bird.setScale(0.15,0.15);
    shapes.emplace_back(&bird);
    if(number == 2)
    {
        bird2.setPosition(-250, 100);
        bird2.setTextureRect(sf::IntRect(90,138,320,225));
        bird2.setOrigin(bird2.getGlobalBounds().width/2,bird2.getGlobalBounds().height/2);
        bird2.setScale(0.15,0.15);
        shapes.emplace_back(&bird2);
    }
}

//The function displays a closing animation
//and counts the number of points of each player
void ending(const int &number, std::vector<std::unique_ptr<sf::Drawable>> &shapes, sf::Sprite &spark, bool &text_activate, bool &expl, sf::Sound &explosion, sf::Text &text, sf::Text &text_points, sf::Text &text_points2, Bird &bird, Bird &bird2, const sf::RenderWindow &window, const sf::Font &font, const float &dist)
{
    text_activate = true;
    explosion.play();
    expl = false;
    spark.setPosition(bird.getGlobalBounds().left-500, bird.getGlobalBounds().top-500);
    shapes.emplace_back(&spark);
    int counter, counter2;
    counter = (bird.getGlobalBounds().left + bird.getGlobalBounds().width) / dist;
    counter2 = (bird2.getGlobalBounds().left + bird2.getGlobalBounds().width) / dist;

    text.setFont(font);
    text.setColor(sf::Color::Black);
    text.setScale(3.0, 3.0);
    text_points.setFont(font);
    text_points.setScale(2.0, 2.0);
    text_points.setColor(sf::Color::Black);
    text_points2.setFont(font);
    text_points2.setScale(2.0, 2.0);
    text_points2.setColor(sf::Color::Black);

    //setting texts
    if(number == 2)
    {
        if(bird.boom())
        {
            counter += bird.return_points();
            counter2 += bird2.return_points();
        }
        if(bird2.boom())
        {
            counter += bird.return_points();
            counter2 += bird2.return_points();
        }

        if(counter > counter2)
        {
            text.setString("PLAYER 1 WINS");
        }
        else if(counter < counter2)
        {
            text.setString("PLAYER 2 WINS");
        }
        else
        {
            if(bird.boom())
            {
                text.setString("PLAYER 2 WINS");
            }
            if(bird2.boom())
            {
                text.setString("PLAYER 1 WINS");
            }
        }

        text.setPosition(bird.getGlobalBounds().left - 200, (window.getSize().y)/2 - 100);

        std::string points1 = "SCORE PLAYER1: ";
        std::string points2 = std::to_string(counter);

        std::string points12 ="SCORE PLAYER2: ";
        std::string points22 = std::to_string(counter2);

        text_points.setString(points1 + points2);
        text_points.setPosition(bird.getGlobalBounds().left - 150 , (window.getSize().y)/2);

        text_points2.setString(points12 + points22);
        text_points2.setPosition(bird.getGlobalBounds().left - 150 , 3*(window.getSize().y)/4);
    }
    else
    {
        text.setString("GAME OVER");
        text.setPosition(bird.getGlobalBounds().left - 200, (window.getSize().y)/2 - 100);

        counter += bird.return_points();
        std::string points1 = "YOUR SCORE: ";
        std::string points2 = std::to_string(counter);

        text_points.setString(points1 + points2);
        text_points.setPosition(bird.getGlobalBounds().left - 150 , (window.getSize().y)/2);

        std::cout << "=================================================" << std::endl;
        std::cout << "CONGRATULATIONS!" << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "Your score: " << counter << std::endl;
        std::cout << "=================================================" << std::endl;
    }
}

//The function generates coins that add points
//to the player result
void generate_coins(const float &dist, std::vector<sf::CircleShape> &coins)
{
    int x_, y_;
    x_ = (float)dist*3.0/2.0;
    for(int i = 0; i < 50; i++)
    {
        y_ = rand() % 450 + 50;
        sf::CircleShape circle(10.0);
        circle.setFillColor(sf::Color::Yellow);
        circle.setPosition(x_, y_);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        coins.emplace_back(circle);
        x_ += dist;
    }
}

//The function checks whether there is a collision
//of a bird and a coin
void collision_coin(std::vector<sf::CircleShape> &coins, Bird &bird, Bird &bird2)
{
    for(int i = 0; i < coins.size(); i++)
    {
        if(coins[i].getGlobalBounds().intersects(bird.getGlobalBounds()))
        {
            coins.erase(coins.begin() + i);
            bird.add_points();
        }
        if(coins[i].getGlobalBounds().intersects(bird2.getGlobalBounds()))
        {
            coins.erase(coins.begin() + i);
            bird2.add_points();
        }
    }
}

