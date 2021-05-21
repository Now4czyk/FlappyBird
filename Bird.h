#pragma once

#include <SFML/Graphics.hpp>

class Bird : public sf::Sprite{
private:
    float vel_y_ = 0, vel_x_ = 0;
    bool BOOM_ = false;
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
    void set_BOOM(bool yes_or_no)
    {
        BOOM_ = yes_or_no;
    }
    bool boom()
    {
        return BOOM_;
    }
};
