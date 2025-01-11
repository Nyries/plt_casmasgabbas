
#include <boost/test/unit_test.hpp>

#include <state.h>
#include <iostream>

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
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
BOOST_AUTO_TEST_CASE(TestSet_GetOccupied)
{
{
  Cell cell(1, 2, LocationType::INACCESSIBLE);
  //cell.setOccupied(true);
  BOOST_CHECK(cell.getOccupied() == true);
}
}
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

BOOST_AUTO_TEST_SUITE_END();

// Door.cpp test
BOOST_AUTO_TEST_SUITE(TestDoor)
BOOST_AUTO_TEST_CASE(TestgetRoom)
{
{
  Door door(1, 1, new Room(RoomName::KITCHEN));
  BOOST_CHECK(door.getRoom()->getRoomName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END();

// Location.cpp test
BOOST_AUTO_TEST_SUITE(TestLocation)
BOOST_AUTO_TEST_CASE(TestSet_GetType)
{
{
  Location location(LocationType::INACCESSIBLE);
  BOOST_CHECK(location.getType() == LocationType::INACCESSIBLE);
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
BOOST_AUTO_TEST_SUITE_END();

// Map.cpp test
BOOST_AUTO_TEST_SUITE(TestMap)

BOOST_AUTO_TEST_CASE(TestGetCell)
{
{
  
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK(map.getCell(0, 0).getType() == LocationType::INACCESSIBLE);
  BOOST_CHECK(map.getCell(1, 2).getType() == LocationType::ROOM);
}
}
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
BOOST_AUTO_TEST_CASE(TestGetHeightAndWidth){
{
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK(map.getHeight() == 3);
  BOOST_CHECK(map.getWidth() == 3);
}
}
BOOST_AUTO_TEST_CASE(TestGetRoomList){
{
  Map map("../../../test/shared/test_map.json");
  BOOST_CHECK(map.getRoomList().at(2).getRoomName() == RoomName::LIVING_ROOM);
}
}
BOOST_AUTO_TEST_CASE(TestGetNeighborsAsLocationType){
  // This method uses getNeighborsAsCell, so we will test it in the same time
{
  // First case where coords for getNeighborsAsLocationType are out of bounds
  Map map("../../../test/shared/test_map.json");
  std::cout << map.getCell(0,0).getTypeAsString() << std::endl;
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(3,0).at(0), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(3,0).at(1), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(3,0).at(2), LocationType::INACCESSIBLE);
  BOOST_CHECK_EQUAL(map.getNeighborsAsLocationType(3,0).at(3), LocationType::INACCESSIBLE);
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

// PlayerState.cpp test
BOOST_AUTO_TEST_SUITE(TestPlayerState)
BOOST_AUTO_TEST_CASE(TestSet_GetCanWin)
{
{
  PlayerState playerState(Suspect::ROSE);
  playerState.setCanWin(false);
  BOOST_CHECK(playerState.getCanWin() == false);
}
}
BOOST_AUTO_TEST_CASE(TestSet_GetIdentity)
{
{
  PlayerState playerState(Suspect::ROSE);
  playerState.setIdentity(Suspect::VIOLET);
  BOOST_CHECK(playerState.getIdentity() == Suspect::VIOLET);
}
}
BOOST_AUTO_TEST_CASE(TestSet_GetLocation){
{
  Location location(LocationType::CORRIDOR);
  PlayerState playerState(Suspect::ROSE);
  playerState.setLocation(location);
  BOOST_CHECK(playerState.getLocation().getType() == LocationType::CORRIDOR);
}
}
BOOST_AUTO_TEST_CASE(TestSet_GetPreviousHypothesisRoom)
{
{
  PlayerState playerState(Suspect::ROSE);
  playerState.setPreviousHypothesisRoom(RoomName::KITCHEN);
  BOOST_CHECK(playerState.getPreviousHypothesisRoom() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(TestRoom);
BOOST_AUTO_TEST_CASE(TestSet_Add_GetDoorList)
{
{
  Room room(RoomName::KITCHEN);
  Door door(1, 1, new Room(RoomName::KITCHEN));
  room.addDoor(door);
  BOOST_CHECK(room.getDoorList().at(0)->getRoom()->getRoomName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_CASE(TestGetRoomName)
{
{
  Room room(RoomName::KITCHEN);
  BOOST_CHECK(room.getRoomName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_CASE(TestSet_GetSecretPassage)
{
{
  Room room(RoomName::KITCHEN);
  Room room2(RoomName::LIVING_ROOM);
  room.setSecretPassage(room2);
  BOOST_CHECK(room.getSecretPassage()->getRoomName() == RoomName::LIVING_ROOM);
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
BOOST_AUTO_TEST_CASE(TestConvertSuspectToStartingCell){
{
  State state("../configurations/map.json",3); 
  Cell cell = state.convertSuspectToStartingCell(ROSE);
  BOOST_CHECK(cell.getX() == 15);
  BOOST_CHECK(cell.getY() == 1);
}
{
  State state("../configurations/map.json",3);
  Cell cell = state.convertSuspectToStartingCell(PERVENCHE);
  BOOST_CHECK(cell.getX() == 17);
  BOOST_CHECK(cell.getY() == 25);
}
{
  State state("../configurations/map.json",3);
  Cell cell = state.convertSuspectToStartingCell(LEBLANC);
  BOOST_CHECK(cell.getX() == 9);
  BOOST_CHECK(cell.getY() == 25);
}
{
  State state("../configurations/map.json",3);
  Cell cell = state.convertSuspectToStartingCell(OLIVE);
  BOOST_CHECK(cell.getX() == 10);
  BOOST_CHECK(cell.getY() == 1);
}
{
  State state("../configurations/map.json",3);
  Cell cell = state.convertSuspectToStartingCell(MOUTARDE);
  BOOST_CHECK(cell.getX() == 1);
  BOOST_CHECK(cell.getY() == 8);
}
{
  State state("../configurations/map.json",3);
  Cell cell = state.convertSuspectToStartingCell(VIOLET);
  BOOST_CHECK(cell.getX() == 1);
  BOOST_CHECK(cell.getY() == 18);
}
}

BOOST_AUTO_TEST_CASE(TestSet_GetAccusationSuccess)
{
{
  State state("../configurations/map.json",3);
  state.setAccusationSuccess(true);
  BOOST_CHECK(state.getAccusationSuccess() == true);
}
{
  State state("../configurations/map.json",3);
  state.setAccusationSuccess(false);
  BOOST_CHECK(state.getAccusationSuccess() == false);
}
}

BOOST_AUTO_TEST_CASE(TestGetEnvelope)
{
{
  State state("../configurations/map.json",3);
  Card card(CardType::WEAPON_CARD);
  state.getEnvelope().push_back(card);
  BOOST_CHECK(state.getEnvelope().at(0).getType() == CardType::WEAPON_CARD);
}
}

BOOST_AUTO_TEST_SUITE_END();

// SuspectCard.cpp test
BOOST_AUTO_TEST_SUITE(TestSuspectCard)
BOOST_AUTO_TEST_CASE(TestGetSuspectName)
{
{
  SuspectCard suspectCard(Suspect::ROSE);
  BOOST_CHECK(suspectCard.getSuspectName() == Suspect::ROSE);
}
}
BOOST_AUTO_TEST_SUITE_END();

// WeaponCard.cpp test
BOOST_AUTO_TEST_SUITE(TestWeaponCard)

BOOST_AUTO_TEST_CASE(TestGetWeaponName)
{
{
  WeaponCard weaponCard(Weapon::CANDLESTICK);
  BOOST_CHECK(weaponCard.getWeaponName() == Weapon::CANDLESTICK);
}
}
BOOST_AUTO_TEST_SUITE_END();
