#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include "Bird.h"
#include "Menu.h"

void gravitation(Bird(&bird), sf::Time elapsed, float gravitation_value)
{
   // float acceleration = 0.5/elapsed.asMicroseconds();
    float velY = bird.vely();
    if(velY < 0.8)
    {
        velY += gravitation_value;
    }
    bird.velocity_y(velY);
}

void collision_pipe(Bird &bird, sf::Sprite pipe)
{
    if(pipe.getGlobalBounds().intersects(bird.getGlobalBounds()))
    {
        bird.velocity(0,0);
        bird.set_BOOM(true);
    }
}

void collision_wall(Bird &bird, float window)
{
    if(bird.getGlobalBounds().top <= 0 || bird.getGlobalBounds().top + bird.getGlobalBounds().height > window)
    {
        bird.velocity(0,0);
        bird.set_BOOM(true);
    }
}

void generate_pipeU(std::vector<sf::Sprite> &pipes, sf::Texture &tex_pipe, float pipe_x, float pipe_y)
{
    sf::Sprite pipe;
    pipe.setTexture(tex_pipe);
    pipe.setPosition(300+pipe_x, 200+pipe_y);
    pipe.setTextureRect(sf::IntRect(0,0,344,4000));
    pipe.setScale(0.15,0.15);
    pipe.setRotation(180);
    pipes.emplace_back(pipe);
}

void generate_pipeD(std::vector<sf::Sprite> &pipes, sf::Texture &tex_pipe, float pipe_x, float pipe_y, float lvl)
{
    sf::Sprite pipe4;
    pipe4.setTexture(tex_pipe);
    pipe4.setPosition(248.4+pipe_x, 200+lvl+pipe_y);
    pipe4.setTextureRect(sf::IntRect(0,0,344,4000));
    pipe4.setScale(0.15,0.15);
    pipes.emplace_back(pipe4);
}

void choosing_lvl_and_generating_pipes(Menu &menu, std::vector<sf::Sprite> &pipeSpritevec, sf::Texture &tex_pipe, bool &is_first)
{
    float coord_x = 0;
    switch (menu.getPressed()) {

    case 0:
        std::cout << "=================================================" << std::endl;
        std::cout << "CHOOSEN LEVEL: EASY" << std::endl;
        for(int i = 0; i < 50; i++)
        {
            float coord_y = rand() % 300 - 150;
            generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
            generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y, 150);
            coord_x += 230;
        }
        is_first = 0;
        break;
    case 1:
        std::cout << "=================================================" << std::endl;
        std::cout << "CHOOSEN LEVEL: MEDIUM" << std::endl;
        for(int i = 0; i < 50; i++)
        {
            float coord_y = rand() % 300 - 150;
            generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
            generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y, 135);
            coord_x += 230;
        }
        is_first = 0;
        break;
    case 2:
        std::cout << "=================================================" << std::endl;
        std::cout << "CHOOSEN LEVEL: HARD" << std::endl;
        for(int i = 0; i < 50; i++)
        {
            float coord_y = rand() % 300 - 150;
            generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
            generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y, 120);
            coord_x += 230;
        }
        is_first = 0;
        break;
    }
}

void ending(std::vector<std::unique_ptr<sf::Drawable>> &shapes, sf::Sprite &spark, bool &text_activate, bool &expl, sf::Sound &explosion, sf::Text &text, sf::Text &text_points, int &counter, Bird &bird, sf::RenderWindow &window, sf::Font &font)
{
    text_activate = true;
    explosion.play();
    expl = false;
    spark.setPosition(bird.getGlobalBounds().left-500, bird.getGlobalBounds().top-500);
    shapes.emplace_back(&spark);
    counter = ((int)bird.getGlobalBounds().left-100) / 200;

    //setting texts
    text.setString("GAME OVER");
    text.setFont(font);
    text.setPosition(bird.getGlobalBounds().left - 200, (window.getSize().y)/2 - 100);
    text.setScale(3.0, 3.0);
    text.setColor(sf::Color::Black);
    text.Bold;

    std::string points1 = "YOUR SCORE: ";
    std::string points2 = std::to_string(counter);
    text_points.setFont(font);
    text_points.setString(points1 + points2);
    text_points.setPosition(bird.getGlobalBounds().left - 150 , (window.getSize().y)/2);
    text_points.setScale(2.0, 2.0);
    text_points.setColor(sf::Color::Black);
    text_points.Bold;

    std::cout << "=================================================" << std::endl;
    std::cout << "CONGRATULATIONS!" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "Your score: " << counter << std::endl;
    std::cout << "=================================================" << std::endl;
}

