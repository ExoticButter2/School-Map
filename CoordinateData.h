#ifndef COORDINATE_DATA
#define COORDINATE_DATA

#include <string>
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
    struct Coordinates coordinates;
    std::string roomName;
};

struct Floor
{
    std::vector<Room> rooms;
};

struct Building
{
    std::string name;
    std::vector<Floor> floors;
};

#endif