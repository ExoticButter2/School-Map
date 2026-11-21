#include <StructureCreator.h>
#include <iostream>

Room CreateRoom(const Coordinates& coordinates, int height, int width, const std::string& name)
{
    Room room;

    room.coordinates = coordinates;
    room.height = height;
    room.width = width;
    room.roomName = name;

    return room;
}

Floor CreateFloor(const std::vector<Room> rooms)
{
    Floor floor;

    floor.rooms = rooms;
    std::cout << "Created floor" << std::endl;

    return floor;
}

Building CreateBuilding(const std::vector<Floor> floors)
{
    Building building;
    
    building.floors = floors;
    std::cout << "Created building" << std::endl;

    return building;
}