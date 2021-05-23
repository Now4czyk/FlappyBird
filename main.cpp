#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Bird.h"
#include "Functions.h"

int main()
{
    std::vector<std::unique_ptr<sf::Drawable>> shapes;

    //creating sky
    sf::Texture tex_sky;
    tex_sky.loadFromFile("sky.png");
    tex_sky.setRepeated(1);
    sf::Sprite sky;
    sky.setTexture(tex_sky);
    sky.setPosition(-2000, 0);
    sky.setTextureRect(sf::IntRect(0,0,30000,550)); //update to implement view
    shapes.emplace_back(&sky);

    //creating path
    sf::Texture tex_path;
    tex_path.loadFromFile("path.png");
    tex_path.setRepeated(1);
    sf::Sprite path;
    path.setTexture(tex_path);
    path.setPosition(-2000, 550);
    path.setTextureRect(sf::IntRect(0,0,30000,550)); //update to implement view
    shapes.emplace_back(&path);

    //creating spark
    sf::Texture tex_spark;
    tex_spark.loadFromFile("spark.png");
    sf::Sprite spark;
    spark.setTexture(tex_spark);
    spark.setTextureRect(sf::IntRect(0,0,1700,550));
    spark.setScale(2,2);

    //creating a bird
    Bird bird;
    sf::Texture tex_bird;
    tex_bird.loadFromFile("bird.png");
    bird.setTexture(tex_bird);
    bird.setPosition(0, 100);
    bird.setTextureRect(sf::IntRect(90,138,320,225));
    bird.setOrigin(bird.getGlobalBounds().width/2,bird.getGlobalBounds().height/2);
    bird.setScale(0.15,0.15);
    shapes.emplace_back(&bird);
    //2nd bird
    Bird bird2;
    bird2.setTexture(tex_bird);
    bird2.setPosition(0, 100);
    bird2.setTextureRect(sf::IntRect(90,138,320,225));
    bird2.setOrigin(bird2.getGlobalBounds().width/2,bird2.getGlobalBounds().height/2);
    bird2.setScale(0.15,0.15);
    shapes.emplace_back(&bird2);

    //creating components for pipes
    sf::Texture tex_pipe;
    tex_pipe.loadFromFile("pipeEdit.png");
    std::vector<sf::Sprite> pipeSpritevec;

    //sounds
    //wing
    sf::SoundBuffer buffer_wing;
    buffer_wing.loadFromFile("wing.wav");
    sf::Sound wing;
    wing.setBuffer(buffer_wing);
    //hit
    sf::SoundBuffer buffer_hit;
    buffer_hit.loadFromFile("hit.wav");
    sf::Sound hit;
    hit.setBuffer(buffer_hit);
    //bomb release
    sf::SoundBuffer buffer_bombrelease;
    buffer_bombrelease.loadFromFile("bombrelease.wav");
    sf::Sound bombrelease;
    bombrelease.setBuffer(buffer_bombrelease);
    //explosion
    sf::SoundBuffer buffer_explosion;
    buffer_explosion.loadFromFile("explosion.wav");
    sf::Sound explosion;
    explosion.setBuffer(buffer_explosion);
    //explosion
    sf::SoundBuffer buffer_point;
    buffer_point.loadFromFile("point.wav");
    sf::Sound point;
    point.setBuffer(buffer_point);

    //creating font and texts
    sf::Text text;
    sf::Text text_points;
    sf::Font font;
    font.loadFromFile("font.ttf");

    //creating a view
    sf::View view;
    view.setSize(sf::Vector2f(1400,600));

    //settings
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1700, 600), "Flappy_bird");
    Menu menu(window.getSize().x, window.getSize().y);
    bool is_jump = false, is_jump2,first = true, expl = true, text_activate = false, is_first = true;
    int counter = 0;
    double size_scale = 0.2;
    float jump_value = -0.25, gravitation_value = 0.0008, vel_rotate = 20;

    while (window.isOpen())
    {
        //measuring time
        sf::Time elapsed = clock.restart();
        //communication
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    is_jump = true;
                    wing.play();
                }
                if (event.key.code == sf::Keyboard::RShift)
                {
                    is_jump2 = true;
                    wing.play();
                }
                if(event.key.code == sf::Keyboard::Up)
                {
                    menu.MoveUp();
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown();
                }
                if(event.key.code == sf::Keyboard::Return)
                {
                    choosing_lvl_and_generating_pipes(menu, pipeSpritevec, tex_pipe, is_first);
                }
            }
        }

        //clearing a window
        window.clear(sf::Color::Black);

        //menu
        if(is_first)
        {
            menu.draw(window);
        }
        //game
        else
        {
            //moving bird
            bird.move(bird.velx(), bird.vely());
            bird2.move(bird2.velx(), bird2.vely());


            //no explosion
            if(bird.boom() == false && bird2.boom() == false)
            {
                view.setCenter(sf::Vector2f(bird.getGlobalBounds().left, window.getSize().y/2));
                bird.velocity_x(100  * elapsed.asSeconds());
                bird2.velocity_x(100  * elapsed.asSeconds());
                gravitation(bird, elapsed, gravitation_value);
                gravitation(bird2, elapsed, gravitation_value);

                if(is_jump)
                {
                    bird.velocity_y(jump_value);
                    is_jump = false;
                }
                if(is_jump2)
                {
                    bird2.velocity_y(jump_value);
                    is_jump2 = false;
                }

                //rotating a bird
                if(bird.vely() < 0)
                {
                    bird.setRotation(-7);
                }else if(bird.vely() > 0)
                {
                    bird.setRotation(7);
                }else{
                    bird.setRotation(0);
                }
                if(bird2.vely() < 0)
                {
                    bird2.setRotation(-7);
                }else if(bird2.vely() > 0)
                {
                    bird2.setRotation(7);
                }else{
                    bird2.setRotation(0);
                }

                //collisions && turning on point sound
                for(int i = 0; i < pipeSpritevec.size(); i++)
                {
                    collision_pipe(bird, pipeSpritevec[i]);
                    collision_pipe(bird2, pipeSpritevec[i]);
                    if(bird.getGlobalBounds().left > pipeSpritevec[i].getGlobalBounds().left && bird.getGlobalBounds().left < pipeSpritevec[i].getGlobalBounds().left + pipeSpritevec[i].getGlobalBounds().width)
                    {
                        point.play();
                    }
                }
                collision_wall(bird, window.getSize().y-50);
                collision_wall(bird2, window.getSize().y-50);
            }

            //explosion
            if(bird.boom() == true || bird2.boom() == true)
            {
                bird.velocity_y(0);
                bird2.velocity_y(0);
                bird.velocity_x(0);
                bird2.velocity_x(0);

                if(expl)
                {
                    if(first)
                    {
                        hit.play();
                        bombrelease.play();
                    }
                    first = false;
                    if(bird.boom() == true)
                    {
                        bird.rotate(vel_rotate*elapsed.asSeconds());
                        bird.setScale(size_scale, size_scale);
                    }
                    if(bird2.boom() == true)
                    {
                        bird2.rotate(vel_rotate*elapsed.asSeconds());
                        bird2.setScale(size_scale, size_scale);
                    }
                    vel_rotate+=0.3;
                    size_scale+=0.0001;
                }
                if(expl && bombrelease.getStatus() == !(sf::SoundSource::Playing))
                {
                    ending(shapes, spark, text_activate, expl, explosion, text, text_points, counter, bird, window, font);
                }
            }

            //drawing shapes
            for(auto &object : shapes)
            {
                window.draw(*object);
            }

            //drawing pipes
            for(auto &object : pipeSpritevec)
            {
                window.draw(object);
            }

            //drawing closing results
            if(text_activate)
            {
                window.draw(text);
                window.draw(text_points);
            }

            //setting a new view
            window.setView(view);
        }

        //displaying shapes
        window.display();
    }
    return 0;
}
