#include <iostream>

//The function allows you to calibrate some
//settings in a game, such as the distance
//between pipes in each level of difficulty
void calibration(float &easy, float &medium, float &hard, float &dist)
{
    //use values only between 0 and 500
    //otherwise game will crash
    easy = 150; //default 150
    medium = 135; //default 135
    hard = 120; //default 120
    dist = 230; //default 230
}
