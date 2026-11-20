#line 1 "C:\\Users\\maksi\\OneDrive\\Documents\\GitHub\\School-Map\\SchoolMap\\CoordinateData.cpp"
#include <CoordinateData.h>
#include <string.h>
#include <iostream>
#include <vector>

struct Coordinates
{
    int x;
    int y;
};

struct Room
{
    int width;
    int height;
    struct Coordinates* coordinates;
    std::string roomName;
};

struct Floor
{
    std::vector<Room> rooms;
};

struct Building
{
    std::vector<Floor> floors;
};