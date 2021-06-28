#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Bird.h"
#include "Functions.h"
#include "Skins.h"
#include "CalibrationFile.h"

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
    Bird bird2;
    sf::Texture yellow_bird;
    yellow_bird.loadFromFile("yellow_bird.png");
    sf::Texture blue_bird;
    blue_bird.loadFromFile("blue_bird.png");
    sf::Texture red_bird;
    red_bird.loadFromFile("red_bird.png");


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
    sf::Text text_points2;
    sf::Font font;
    font.loadFromFile("font.ttf");

    //creating a view
    sf::View view;
    view.setSize(sf::Vector2f(1400,600));

    //settings
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1700, 600), "Flappy_bird");
    Menu menu(window);
    Skins skins(window);   
    int number = 0;
    double size_scale = 0.2;
    float jump_value = -5.3, gravitation_value = 0.4, vel_rotate = 20, dist, easy, medium, hard;
    bool is_jump = false, is_jump2 = false, first = true, expl = true, text_activate = false, is_menu = true, is_skins = true;
    srand(time(NULL));

    //coins
    std::vector<sf::CircleShape> coins;
    calibration(easy, medium, hard, dist, number);
    generate_coins(dist, coins);

    window.setFramerateLimit(60);

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
                if (event.key.code == sf::Keyboard::LShift)
                {
                    is_jump2 = true;
                    wing.play();
                }
                if(is_skins && is_menu == false)
                {
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        skins.MoveUp();
                    }
                    if(event.key.code == sf::Keyboard::Down)
                    {
                        skins.MoveDown();
                    }
                    if(event.key.code == sf::Keyboard::Return)
                    {
                        choosing_skin(skins, bird, bird2, number, shapes, is_skins, yellow_bird, blue_bird, red_bird);
                    }
                }
                if(is_menu)
                {
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
                        choosing_lvl_and_generating_pipes(menu, pipeSpritevec, tex_pipe, is_menu, easy, medium, hard, dist);
                    }
                }
            }
        }

        //clearing a window
        window.clear(sf::Color::Black);

        //menu
        if(is_menu)
        {
            menu.draw(window);
        }
        //skins
        else if(is_skins && is_menu == false)
        {
            skins.draw(window);
        }
        //game
        else
        {
            //moving bird
            bird.move(bird.velx(), bird.vely());
            collision_coin(coins, bird, bird2);
            if(number == 2)
            {
                bird2.move(bird2.velx(), bird2.vely());
            }

            //no explosion
            if(bird.boom() == false && bird2.boom() == false)
            {
                //setting the center of camera
                view.setCenter(sf::Vector2f(bird.getGlobalBounds().left, window.getSize().y/2));
                //setting horizontal velocity of the bird
                bird.velocity_x(100  * elapsed.asSeconds());
                bird2.velocity_x(100  * elapsed.asSeconds());
                //turning on gravitation
                gravitation(bird, gravitation_value);
                gravitation(bird2, gravitation_value);

                //jump
                if(is_jump)
                {
                    bird.velocity_y(jump_value);
                    is_jump = false;
                }
                if(is_jump2 && number == 2)
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

                if(bird2.vely() < 0 && number == 2)
                {
                    bird2.setRotation(-7);
                }else if(bird2.vely() > 0)
                {
                    bird2.setRotation(7);
                }else{
                    bird2.setRotation(0);
                }

                //collisions && turning on point sound
                for(unsigned int i = 0; i < pipeSpritevec.size(); i++)
                {
                    collision_pipe(bird, pipeSpritevec[i]);
                    if(number == 2)
                    {
                        collision_pipe(bird2, pipeSpritevec[i]);
                    }
                    if(bird.getGlobalBounds().left > pipeSpritevec[i].getGlobalBounds().left && bird.getGlobalBounds().left < pipeSpritevec[i].getGlobalBounds().left + pipeSpritevec[i].getGlobalBounds().width)
                    {
                        point.play();
                    }
                }
                collision_wall(bird, window.getSize().y-50);
                if(number == 2)
                {
                    collision_wall(bird2, window.getSize().y-50);
                }
            }

            //explosion
            if(bird.boom() == true || bird2.boom() == true)
            {
                bird.velocity(0, 0);
                bird2.velocity(0, 0);
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
                    vel_rotate+=30;
                    size_scale+=0.001;
                }
                if(expl && bombrelease.getStatus() == !(sf::SoundSource::Playing))
                {
                    ending(number, shapes, spark, text_activate, expl, explosion, text, text_points, text_points2, bird, bird2, window, font, dist);
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

            //drawing coins
            for(auto &object : coins)
            {
                window.draw(object);
            }

            //drawing closing results
            if(text_activate)
            {
                window.draw(text);
                window.draw(text_points);
                if(number == 2)
                {
                    window.draw(text_points2);
                }
            }

            //setting a new view
            window.setView(view);
        }

        //displaying shapes
        window.display();
    }
    return 0;
}
