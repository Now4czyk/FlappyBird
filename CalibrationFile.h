//The function allows you to calibrate some
//settings in a game, such as the distance
//between pipes in each level of difficulty,
//distance between pipes and number of players
void calibration(float &easy, float &medium, float &hard, float &dist, int &number)
{
    //changing easy, medium and hard, please
    //use values only between 0 and 500
    //otherwise game won't start
    easy = 500; //default 150
    medium = 135; //default 135
    hard = 120; //default 120
    dist = 230; //default 230
    number = 2; //1 or 2
}
