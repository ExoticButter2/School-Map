#ifndef STRUCTURE_CREATOR
#define STRUCTURE_CREATOR

#include <CoordinateData.h>
#include <vector>
#include <string>

Room CreateRoom(const Coordinates& coordinates, int height, int width, const std::string& name);
Floor CreateFloor(const std::vector<Room> rooms);
Building CreateBuilding(std::vector<Floor> floors);

#endif