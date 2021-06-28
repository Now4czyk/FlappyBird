#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

//The function allows you to calibrate some
//settings in a game, such as the distance
//between pipes in each level of difficulty,
//distance between pipes and number of players
void calibration(float &easy, float &medium, float &hard, float &dist, int &number)
{
    //changing easy, medium and hard, please
    //use values only between 0 and 500
    //otherwise game won't start

    std::fstream file;
    std::regex re(R"(\d+)");
    std::regex reEASY(R"(EASY)");
    std::regex reMEDIUM(R"(MEDIUM)");
    std::regex reHARD(R"(HARD)");
    std::regex reDISTANCE(R"(DISTANCE)");
    std::regex reNUMBER(R"(NUMBER)");
    std::smatch sm;
    std::smatch sm1;
    std::string lvl;

    file.open("ConfigurationFile.txt");
    std::string line;
    std::getline(file, line);

    while(std::getline(file, line))
    {
        if(std::regex_search(line, sm, re))
        {
             if(std::regex_search(line, sm1, reEASY))
             {
                 easy = std::stoi(sm[0]);
             }
             if(std::regex_search(line, sm1, reMEDIUM))
             {
                 medium = std::stoi(sm[0]);
             }
             if(std::regex_search(line, sm1, reHARD))
             {
                 hard = std::stoi(sm[0]);
             }
             if(std::regex_search(line, sm1, reDISTANCE))
             {
                 dist = std::stoi(sm[0]);
             }
             if(std::regex_search(line, sm1, reNUMBER))
             {
                 number = std::stoi(sm[0]);
             }
        }
    }
    file.close();
}
