
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
  Map map("../../../test/shared/test_map.json");
  std::vector<std::vector<std::string>> displayMap = map.getDisplayMap();

  BOOST_CHECK(displayMap[0][0] == "-");
  BOOST_CHECK(displayMap[1][2] == "|");
  BOOST_CHECK(displayMap[1][3] == "X");
  BOOST_CHECK(displayMap[3][1] == " ");
  BOOST_CHECK(displayMap[5][3] == "R");
  BOOST_CHECK(displayMap[5][1] == "D");
}
}
BOOST_AUTO_TEST_CASE(TestGetMapGrid){
{
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK(map.getMapGrid().at(0).at(0).getType() == LocationType::INACCESSIBLE);
  BOOST_CHECK(map.getMapGrid().at(1).at(2).getType() == LocationType::ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetRoomList){
{
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK(map.getRoomList().at(2).getName() == RoomName::LIVING_ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetHeightAndWidth){
{
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK(map.getHeight() == 3);
  BOOST_CHECK(map.getWidth() == 3);
}
}
BOOST_AUTO_TEST_CASE(TestGetNeighborsAsLocationType){
  // This method uses getNeighborsAsCell, so we will test it as well
{
  // First case where coords for getNeighborsAsLocationType are out of bounds
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(4,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(4,0).at(1), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(4,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(4,0).at(3), LocationType::INACCESSIBLE);
}
{
  // Second case in the top left corner
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(1), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(3), LocationType::INACCESSIBLE);
}
{
  // Third case in the top right corner
  Map map("../../../test/shared/test_map.json");
  int width = map.getWidth()-1;
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(1), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(3), LocationType::INACCESSIBLE);
}
{
  // Fourth case in the bottom right corner
  Map map("../../../test/shared/test_map.json");
  int width = map.getWidth()-1;
  int height = map.getHeight()-1;
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,height).at(0), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,height).at(1), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,height).at(2), LocationType::ROOM);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,height).at(3), LocationType::INACCESSIBLE);
}
{
  // Fifth case in the bottom left corner
  Map map("../../../test/shared/test_map.json");
  int height = map.getHeight()-1;
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(0), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(1), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(3), LocationType::ROOM);
}
{
  // Second case where coords for getNeighborsAsLocationType where x=0
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(1), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,0).at(3), LocationType::INACCESSIBLE);
}
{
  // Third case where coords for getNeighborsAsLocationType where y=0
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,0).at(1), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,0).at(3), LocationType::INACCESSIBLE);
}
{
  // Fourth case where coords for getNeighborsAsLocationType where x=width
  Map map("../../../test/shared/test_map.json");
  int width = map.getWidth()-1;
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(1), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(width,0).at(3), LocationType::INACCESSIBLE);
}
{
  // Fifth case where coords for getNeighborsAsLocationType where y=height
  Map map("../../../test/shared/test_map.json");
  int height = map.getHeight()-1;
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(0), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(1), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(0,height).at(3), LocationType::ROOM);
}
{
  // Sixth case, general case
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,1).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,1).at(1), LocationType::ROOM);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,1).at(2), LocationType::CORRIDOR);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(1,1).at(3), LocationType::CORRIDOR);
}
}
BOOST_AUTO_TEST_SUITE_END();

// PlayerInfo.cpp test
BOOST_AUTO_TEST_SUITE(TestPlayerInfo)

BOOST_AUTO_TEST_CASE(TestSet_GetLocation){
{
  Location location(LocationType::CORRIDOR);
  PlayerInfo playerInfo("John", Suspect::ROSE);
  playerInfo.setLocation(location);
  BOOST_CHECK(playerInfo.getLocation().getType() == LocationType::CORRIDOR);
}
}
BOOST_AUTO_TEST_CASE(TestGiveCard){
{
  Card card(CardType::WEAPON_CARD);
  PlayerInfo playerInfo("John", Suspect::ROSE);
  playerInfo.giveCard(card);
  BOOST_CHECK(playerInfo.getCards().at(0).getType() == CardType::WEAPON_CARD);
}
}
BOOST_AUTO_TEST_CASE(TestGetName)
{
{
  PlayerInfo playerInfo("John", Suspect::ROSE);
  BOOST_CHECK(playerInfo.getName() == "John");
}
}
BOOST_AUTO_TEST_CASE(TestGetPlayerIdentity)
{
{
  PlayerInfo playerInfo("John", Suspect::ROSE);
  playerInfo.setIdentity(Suspect::VIOLET);
  BOOST_CHECK(playerInfo.getIdentity() == Suspect::VIOLET);
}
}
BOOST_AUTO_TEST_CASE(TestGetCanWin)
{
{
  PlayerInfo playerInfo("John", Suspect::ROSE);
  playerInfo.setCanWin(false);
  BOOST_CHECK(playerInfo.getCanWin() == false);
}
}
BOOST_AUTO_TEST_CASE(TestGetPreviousHypothesisRoom)
{
{
  PlayerInfo playerInfo("John", Suspect::ROSE);
  playerInfo.setPreviousHypothesisRoom(RoomName::KITCHEN);
  BOOST_CHECK(playerInfo.getPreviousHypothesisRoom() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(TestRoom);

BOOST_AUTO_TEST_CASE(TestSet_GetName)
{
{
  Room room(RoomName::KITCHEN);
  room.setName(RoomName::LIVING_ROOM);
  BOOST_CHECK(room.getName() == RoomName::LIVING_ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetNameAsString)
{
{
  Room room(RoomName::KITCHEN);
  BOOST_CHECK(room.getNameAsString() == "KITCHEN");
}
{
  Room room(RoomName::LIVING_ROOM);
  BOOST_CHECK(room.getNameAsString() == "LIVING_ROOM");
}
{
  Room room(RoomName::DINING_ROOM);
  BOOST_CHECK(room.getNameAsString() == "DINING_ROOM");
}
{
  Room room(RoomName::GARAGE);
  BOOST_CHECK(room.getNameAsString() == "GARAGE");
}
{
  Room room(RoomName::GAME_ROOM);
  BOOST_CHECK(room.getNameAsString() == "GAME_ROOM");
}
{
  Room room(RoomName::BEDROOM);
  BOOST_CHECK(room.getNameAsString() == "BEDROOM");
}
}
BOOST_AUTO_TEST_CASE(TestSet_Add_GetDoorList)
{
{
  Room room(RoomName::KITCHEN);
  Door door(1, 1, new Room(RoomName::KITCHEN));
  room.addDoor(door);
  BOOST_CHECK(room.getDoorList().at(0)->getRoom()->getName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_CASE(TestSet_GetSecretPassage)
{
{
  Room room(RoomName::KITCHEN);
  Room room2(RoomName::LIVING_ROOM);
  room.setSecretPassage(room2);
  BOOST_CHECK(room.getSecretPassage()->getName() == RoomName::LIVING_ROOM);
}
}
BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(TestRoomCard);

BOOST_AUTO_TEST_CASE(TestGetRoomName)
{
{
  RoomCard roomCard(RoomName::KITCHEN);
  BOOST_CHECK(roomCard.getRoomName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(TestState);

BOOST_AUTO_TEST_CASE(TestGetPlayerList)
{
{
  State state("../../../test/shared/test_state.json");
  PlayerInfo playerInfo("John", Suspect::ROSE);
  state.addPlayer(playerInfo);
  BOOST_CHECK(state.getPlayerList()->getList().at(0).getName() == "John");
}
}
BOOST_AUTO_TEST_CASE(TestGetMap)
{
{
  State state("../../../test/shared/test_state.json");
  BOOST_CHECK(state.getMap()->getRoomList().at(2).getName() == RoomName::LIVING_ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetEnvelope)
{
{
  State state("../../../test/shared/test_state.json");
  Card card(CardType::WEAPON_CARD);
  state.getEnvelope().push_back(card);
  BOOST_CHECK(state.getEnvelope().at(0).getType() == CardType::WEAPON_CARD);
}
}
BOOST_AUTO_TEST_CASE(TestSetCircularPlayerList)
{
{
  State state("../../../test/shared/test_state.json");
  std::vector<std::tuple<std::string, int, int>> players;
  players.push_back(std::make_tuple("John", 0, Suspect::ROSE));
  state.setCircularPlayerList(players);
  BOOST_CHECK(state.getPlayerList()->getList().at(0).getName() == "John");
}
}
BOOST_AUTO_TEST_CASE(TestAddPlayer)
{
{
  State state("../../../test/shared/test_state.json");
  PlayerInfo playerInfo("John", Suspect::ROSE);
  state.addPlayer(playerInfo);
  BOOST_CHECK(state.getPlayerList()->getList().at(0).getName() == "John");
}
}
BOOST_AUTO_TEST_SUITE_END();
/* vim: set sw=2 sts=2 et : */
