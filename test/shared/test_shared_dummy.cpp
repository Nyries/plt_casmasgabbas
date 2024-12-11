
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
/*  {
    BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
  }

  {

    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}
// Card.cpp test
BOOST_AUTO_TEST_SUITE(TestCard)
BOOST_AUTO_TEST_CASE(TestGetType)
{
{
  Card card(CardType::WEAPON_CARD);
  BOOST_CHECK(card.getType() == CardType::WEAPON_CARD);
}
}
BOOST_AUTO_TEST_SUITE_END();


// Cell.cpp test
BOOST_AUTO_TEST_SUITE(TestCell)
BOOST_AUTO_TEST_CASE(TestGetX)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  BOOST_CHECK(cell.getX() == 1);  
}
}
BOOST_AUTO_TEST_CASE(TestGetY)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  BOOST_CHECK(cell.getY() == 2);  
}
}
BOOST_AUTO_TEST_CASE(TestGetOccupied)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  BOOST_CHECK(cell.getOccupied() == false);  
}
}
BOOST_AUTO_TEST_CASE(TestSetCell)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  cell.setCell(3, 4, LocationType::ROOM);
  BOOST_CHECK(cell.getX() == 3);
  BOOST_CHECK(cell.getY() == 4);
  BOOST_CHECK(cell.getType() == LocationType::ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestSetX)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  cell.setX(3);
  BOOST_CHECK(cell.getX() == 3);
}
}
BOOST_AUTO_TEST_CASE(TestSetY)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  cell.setY(4);
  BOOST_CHECK(cell.getY() == 4);
}
}
BOOST_AUTO_TEST_CASE(TestSetOccupied)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  cell.setOccupied(true);
  BOOST_CHECK(cell.getOccupied() == true);
}
}
BOOST_AUTO_TEST_SUITE_END();

// Door.cpp test
BOOST_AUTO_TEST_SUITE(TestDoor)
BOOST_AUTO_TEST_CASE(TestgetRoom)
{
{
  Door door(1, 1, new Room(RoomName::KITCHEN));
  BOOST_CHECK(door.getRoom()->getName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END();

// Location.cpp test
BOOST_AUTO_TEST_SUITE(TestLocation)
BOOST_AUTO_TEST_CASE(TestGetType)
{
{
  Location location(LocationType::INACCESSIBLE);
  BOOST_CHECK(location.getType() == LocationType::INACCESSIBLE);
}
}
BOOST_AUTO_TEST_CASE(TestGetTypeAsString)
{
{
  Location location(LocationType::INACCESSIBLE);
  BOOST_CHECK(location.getTypeAsString() == "INACCESSIBLE");
}
{
  Location location(LocationType::CORRIDOR);
  BOOST_CHECK(location.getTypeAsString() == "CORRIDOR");
}
{
  Location location(LocationType::DOOR);
  BOOST_CHECK(location.getTypeAsString() == "DOOR");
}
{
  Location location(LocationType::ROOM);
  BOOST_CHECK(location.getTypeAsString() == "ROOM");
}
}
BOOST_AUTO_TEST_CASE(TestSetType)
{
{
  Location location(LocationType::INACCESSIBLE);
  location.setType(LocationType::CORRIDOR);
  BOOST_CHECK(location.getType() == LocationType::CORRIDOR);
}
}
BOOST_AUTO_TEST_CASE(TestSetTypeAsString)
{
{
  Location location(LocationType::INACCESSIBLE);
  location.setTypeAsString("CORRIDOR");
  BOOST_CHECK(location.getType() == LocationType::CORRIDOR);
}
{
  Location location(LocationType::INACCESSIBLE);
  location.setTypeAsString("DOOR");
  BOOST_CHECK(location.getType() == LocationType::DOOR);
}
{
  Location location(LocationType::INACCESSIBLE);
  location.setTypeAsString("ROOM");
  BOOST_CHECK(location.getType() == LocationType::ROOM);
}
{
  Location location(LocationType::INACCESSIBLE);
  location.setTypeAsString("Mouais");
  BOOST_CHECK(location.getType() == LocationType::INACCESSIBLE);
}
}
BOOST_AUTO_TEST_SUITE_END();

// Map.cpp test
BOOST_AUTO_TEST_SUITE(TestMap)

BOOST_AUTO_TEST_CASE(TestGetDisplayMap)
{
{
  Map map("test/shared/test_map.json");
  std::vector<std::vector<std::string>> displayMap = map.getDisplayMap();
  BOOST_CHECK(displayMap[0][0] == "-");
  BOOST_CHECK(displayMap[0][1] == "|");
  BOOST_CHECK(displayMap[1][1] == "X");
  BOOST_CHECK(displayMap[2][2] == " ");
  BOOST_CHECK(displayMap[2][4] == "R");
}
}
BOOST_AUTO_TEST_CASE(TestGetMapGrid){
{
  Map map("test/shared/test_map.json");
  BOOST_CHECK(map.getMapGrid().at(0).at(0).getType() == LocationType::INACCESSIBLE);
  BOOST_CHECK(map.getMapGrid().at(1).at(2).getType() == LocationType::ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetRoomList){
{
  Map map("test/shared/test_map.json");
  BOOST_CHECK(map.getRoomList().at(0).getName() == RoomName::LIVING_ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetHeightAndWidth){
{
  Map map("test/shared/test_map.json");
  BOOST_CHECK(map.getHeight() == 2);
  BOOST_CHECK(map.getWidth() == 3);
}
}
BOOST_AUTO_TEST_CASE(TestGetNeighborsAsCell){
{
  // First case where coords for getNeighborsAsCell are out of bounds
  Map map("test/shared/test_map.json");
  std::vector<Cell*> neighbors;
  neighbors.emplace_back(new Cell(4,-1, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(4, 1, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(3,0, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(5, 0, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(4,0).at(0), new Cell(4,-1, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(4,0).at(1), new Cell(4, 1, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(4,0).at(2), new Cell(3,0, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(4,0).at(3), new Cell(5, 0, LocationType::INACCESSIBLE));

}/*
{
  // Second case where coords for getNeighborsAsCell where x=0
  Map map("test/shared/test_map.json");
  std::vector<Cell*> neighbors;
  neighbors.emplace_back(new Cell(0,-1, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(0, 1, LocationType::CORRIDOR));
  neighbors.emplace_back(new Cell(-1,0, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(1, 0, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(0,0), neighbors);
  delete &neighbors;
  delete &map;
}
{
  // Third case where coords for getNeighborsAsCell where y=0
  Map map("test/shared/test_map.json");
  std::vector<Cell*> neighbors;
  neighbors.emplace_back(new Cell(1,-1, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(1, 1, LocationType::CORRIDOR));
  neighbors.emplace_back(new Cell(0,0, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(2, 0, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(1,0), neighbors);
  delete &neighbors;
  delete &map;
}
{
  // Fourth case where coords for getNeighborsAsCell where x=width
  Map map("test/shared/test_map.json");
  std::vector<Cell*> neighbors;
  int width = map.getWidth()-1;
  neighbors.emplace_back(new Cell(width,-1, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(width, 1, LocationType::CORRIDOR));
  neighbors.emplace_back(new Cell(width-1,0, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(width+1, 0, LocationType::INACCESSIBLE));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(width,0), neighbors);
  delete &neighbors;
  delete &map;
}
{
  // Fifth case where coords for getNeighborsAsCell where y=height
  Map map("test/shared/test_map.json");
  std::vector<Cell*> neighbors;
  int height = map.getHeight()-1;
  neighbors.emplace_back(new Cell(0,height-1, LocationType::CORRIDOR));
  neighbors.emplace_back(new Cell(0,height+1, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(-1,height, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(1,height, LocationType::ROOM));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(0,height), neighbors);
  delete &neighbors;
  delete &map;
}
{
  // Sixth case, general case
  Map map("test/shared/test_map.json");
  std::vector<Cell*> neighbors;
  int height = map.getHeight()-1;
  neighbors.emplace_back(new Cell(0,1, LocationType::CORRIDOR));
  neighbors.emplace_back(new Cell(2,1, LocationType::CORRIDOR));
  neighbors.emplace_back(new Cell(1,0, LocationType::INACCESSIBLE));
  neighbors.emplace_back(new Cell(1,2, LocationType::ROOM));
  BOOST_CHECK_EQUAL(map.getNeighborsAsCell(1,1), neighbors);
  delete &neighbors;
  delete &map;
}*/
}
BOOST_AUTO_TEST_SUITE_END();
/* vim: set sw=2 sts=2 et : */
