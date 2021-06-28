#pragma once

#include <SFML/Graphics.hpp>

//The class creates a bird that is the mian object in our game
//Here we can change: vertical and horizontal velocity of the bird,
//set whether there is an explosion(game over) and read the information


class Bird : public sf::Sprite{
private:
    float vel_y_ = 0, vel_x_ = 0;
    bool BOOM_ = false;
    int points = 0;
public:
    Bird(){}

    void add_points()
    {
        points += 1;
    }

    void dock_points()
    {
        points -= 1;
    }

    void restart_points()
    {
        points = 0;
    }

    int return_points()
    {
        return points;
    }

    float velx()
    {
        return vel_x_;
    }

    float vely()
    {
        return vel_y_;
    }

    void velocity(const float &velx, const float &vely)
    {
        vel_x_ = velx;
        vel_y_ = vely;
    }

    void velocity_y(const float &vely)
    {
        vel_y_ = vely;
    }

    void velocity_x(const float &velx)
    {
        vel_x_ = velx;
    }
    void set_BOOM(const bool &yes_or_no)
    {
        BOOM_ = yes_or_no;
    }
    bool boom() const
    {
        return BOOM_;
    }
};
