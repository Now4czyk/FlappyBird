#include <iostream>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bird : public sf::Sprite{
private:
    float vel_y_ = 0, vel_x_ = 0;
public:
    Bird(){}

    float velx()
    {
        return vel_x_;
    }

    float vely()
    {
        return vel_y_;
    }

    void velocity(float velx,  float vely)
    {
        vel_x_ = velx;
        vel_y_ = vely;
    }

    void velocity_y(float vely)
    {
        vel_y_ = vely;
    }

    void velocity_x(float velx)
    {
        vel_x_ = velx;
    }
};

void gravitation(Bird(&bird), sf::Time elapsed, float gravitation_value)
{
   // float acceleration = 0.5/elapsed.asMicroseconds();
    float velY = bird.vely();
//    std::cout<< gravitation_value <<std::endl;
    if(velY < 0.8)
    {
        velY += gravitation_value;
    }
    bird.velocity_y(velY);
}

void collision_pipe(Bird &bird, sf::Sprite pipe, bool &BOOM)
{
    if(pipe.getGlobalBounds().intersects(bird.getGlobalBounds()))
    {
        bird.velocity(0,0);
        BOOM = true;
    }
}

void collision_wall(Bird &bird, float window, bool &BOOM)
{
    if(bird.getGlobalBounds().top <= 0 || bird.getGlobalBounds().top + bird.getGlobalBounds().height > window)
    {
        bird.velocity(0,0);
        BOOM = true;
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

void generate_pipeD(std::vector<sf::Sprite> &pipes, sf::Texture &tex_pipe, float pipe_x, float pipe_y)
{
    sf::Sprite pipe4;
    pipe4.setTexture(tex_pipe);
    pipe4.setPosition(248.4+pipe_x, 350+pipe_y);
    pipe4.setTextureRect(sf::IntRect(0,0,344,4000));
    pipe4.setScale(0.15,0.15);
    pipes.emplace_back(pipe4);
}

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
//    sky.setTextureRect(sf::IntRect(0,0,1700,550));
    sky.setTextureRect(sf::IntRect(0,0,30000,550)); //update to implement view
    shapes.emplace_back(&sky);

    //creating path
    sf::Texture tex_path;
    tex_path.loadFromFile("path.png");
    tex_path.setRepeated(1);
    sf::Sprite path;
    path.setTexture(tex_path);
    path.setPosition(-2000, 550);
//    path.setTextureRect(sf::IntRect(0,0,1700,550));
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

    //creating pipes
    sf::Texture tex_pipe;
    tex_pipe.loadFromFile("pipeEdit.png");
    //rand from -150 to 150
    std::vector<sf::Sprite> pipeSpritevec;

    float coord_x = 0;

    for(int i = 0; i < 50; i++)
    {
//        int a  = rand();
//        int b = rand();
        float coord_y = rand() % 300 - 150;
        generate_pipeU(pipeSpritevec, tex_pipe, coord_x, coord_y);
        generate_pipeD(pipeSpritevec, tex_pipe, coord_x, coord_y);
        coord_x += 230;
    }

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

    //settings
    sf::Clock clock;
    bool is_jump = false;
    sf::RenderWindow window(sf::VideoMode(1700, 600), "Flappy_bird");
    bool BOOM = false;
    bool first = true;
    bool expl = true;
    bool is_point = true;
    float vel_rotate = 20;
    int counter = 0;
    double size_scale = 0.2;
    float jump_value = -0.25, gravitation_value = 0.0009;
    int level;

    //creating a view
    sf::View view;
    view.setSize(sf::Vector2f(1400,600));

    //choosing the level of difficulty
//    std::cout << "=================================================" << std::endl;
//    std::cout << "CHOOSE THE LEVEL OF DIFFICULTY(PRESS 1, 2 OR 3)" << std::endl;
//    std::cout << "=================================================" << std::endl;
//    std::cout << "1 - EASY" << std::endl;
//    std::cout << "2 - MEDIUM" << std::endl;
//    std::cout << "3 - HARD" << std::endl;
//    std::cout << "=================================================" << std::endl;
//    std::cin >> level;
//    std::cout << "=================================================" << std::endl;
//    std::cout << "CHOOSE THE LEVEL OF DIFFICULTY(PRESS 1, 2 OR 3)" << std::endl;

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
//                    std::cout << "Space released" << std::endl;
                    is_jump = true;
                    wing.play();
                }
            }
        }

        //clearing a window
        window.clear(sf::Color::Black);

        //moving guy
        bird.move(bird.velx(), bird.vely());

        if(BOOM == false)
        {
            view.setCenter(sf::Vector2f(bird.getGlobalBounds().left, window.getSize().y/2));
            bird.velocity_x(100  * elapsed.asSeconds());
            gravitation(bird, elapsed, gravitation_value);

            if(is_jump)
            {
                //previously bird.velocity_y(-0.2);
                bird.velocity_y(jump_value);
                is_jump = false;
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

            //collisions && turning on point sound
            for(int i = 0; i < pipeSpritevec.size(); i++)
            {
                collision_pipe(bird, pipeSpritevec[i], BOOM);
                if(bird.getGlobalBounds().left > pipeSpritevec[i].getGlobalBounds().left && bird.getGlobalBounds().left < pipeSpritevec[i].getGlobalBounds().left + pipeSpritevec[i].getGlobalBounds().width)
                {
                    point.play();
                }
            }
            collision_wall(bird, window.getSize().y-50, BOOM);
        }

        if(BOOM == true)
        {
            if(expl)
            {
                if(first)
                {
                    hit.play();
                    bombrelease.play();

                }
                first = false;
                bird.rotate(vel_rotate*elapsed.asSeconds());
                bird.setScale(size_scale, size_scale);
                vel_rotate+=0.3;
                size_scale+=0.0001;
//                std::cout<< "vel_rotate: " << vel_rotate << std::endl;
            }
            if(expl && bombrelease.getStatus() == !(sf::SoundSource::Playing))
            {
                explosion.play();
                expl = false;
                spark.setPosition(bird.getGlobalBounds().left-500, bird.getGlobalBounds().top-500);
                shapes.emplace_back(&spark);
                counter = ((int)bird.getGlobalBounds().left-100) / 200;
                std::cout << "=================================================" << std::endl;
                std::cout << "CONGRATULATIONS!" << std::endl;
                std::cout << "=================================================" << std::endl;
                std::cout << "Your score: " << counter << std::endl;
                std::cout << "=================================================" << std::endl;
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

        //setting a new view
        window.setView(view);

        //displaying shapes
        window.display();
    }
    return 0;
}

