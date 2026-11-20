#line 1 "C:\\Users\\maksi\\OneDrive\\Documents\\GitHub\\School-Map\\SchoolMap\\CoordinateData.cpp"
#include <CoordinateData.h>
#include <string.h>
#include <iostream>
#include <vector>

struct Coordinates_t
{
    int x;
    int y;
};

struct Room_t
{
    int width;
    int height;
    struct Coordinates* coordinates;
    std::string roomName;
};

struct Floor_t
{
    std::vector<Room_t> rooms;
};

struct Building_t
{
    std::vector<Floor_t> floors;
};