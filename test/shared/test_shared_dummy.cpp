
#include <boost/test/unit_test.hpp>

#include <state.h>
#include <engine.h>
#include <iostream>
#include <set>


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
BOOST_AUTO_TEST_SUITE_END()

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

BOOST_AUTO_TEST_SUITE_END()

// Door.cpp test
BOOST_AUTO_TEST_SUITE(TestDoor)
BOOST_AUTO_TEST_CASE(TestgetRoom)
{
{
  Door door(1, 1, new Room(RoomName::KITCHEN));
  BOOST_CHECK(door.getRoom()->getRoomName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END()

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
BOOST_AUTO_TEST_SUITE_END()

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
BOOST_AUTO_TEST_SUITE_END()

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
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestRoom)
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
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestRoomCard)
BOOST_AUTO_TEST_CASE(TestGetRoomName)
{
{
  RoomCard roomCard(RoomName::KITCHEN);
  BOOST_CHECK(roomCard.getRoomName() == RoomName::KITCHEN);
}
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestState)
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

//BOOST_AUTO_TEST_CASE(TestGetEnvelope)
//{
//{
//  State state("../configurations/map.json",3);
//  Card card(CardType::WEAPON_CARD);
//  state.getEnvelope().push_back(card);
//  BOOST_CHECK(state.getEnvelope().at(0).getType() == CardType::WEAPON_CARD);
//}
//}

BOOST_AUTO_TEST_SUITE_END()

// SuspectCard.cpp test
BOOST_AUTO_TEST_SUITE(TestSuspectCard)
BOOST_AUTO_TEST_CASE(TestGetSuspectName)
{
{
  SuspectCard suspectCard(Suspect::ROSE);
  BOOST_CHECK(suspectCard.getSuspectName() == Suspect::ROSE);
}
}
BOOST_AUTO_TEST_SUITE_END()

// WeaponCard.cpp test
BOOST_AUTO_TEST_SUITE(TestWeaponCard)

BOOST_AUTO_TEST_CASE(TestGetWeaponName)
{
{
  WeaponCard weaponCard(Weapon::CANDLESTICK);
  BOOST_CHECK(weaponCard.getWeaponName() == Weapon::CANDLESTICK);
}
}
BOOST_AUTO_TEST_SUITE_END()


// Engine command tests :
// ----------------------

// AccusationCommand.cpp test
BOOST_AUTO_TEST_SUITE(TestAccusationCommand)

    BOOST_AUTO_TEST_CASE(TestCorrectAccusation)
    {
        state::PlayerState player(ROSE);
        state::TripleClue correctAccusation{ROSE, CANDLESTICK, STUDY};
        state::TripleClue envelope{ROSE, CANDLESTICK, STUDY};
        State state("../configurations/map.json",3);
        engine::Engine engine(state);
        engine.getEnvelope() = envelope;

        engine::AccusationCommand command(engine, player, correctAccusation);
        command.execute();

        BOOST_CHECK(player.getCanWin() == true);
        BOOST_CHECK(engine.getState().getAccusationSuccess() == true);
    }

    BOOST_AUTO_TEST_CASE(TestIncorrectAccusation)
    {
        state::PlayerState player(ROSE);
        state::TripleClue incorrectAccusation{ROSE, CANDLESTICK, STUDY};
        state::TripleClue envelope{PERVENCHE, CANDLESTICK, STUDY};
        State state("../configurations/map.json",3);
        engine::Engine engine(state);
        engine.getEnvelope() = envelope;

        engine::AccusationCommand command(engine, player, incorrectAccusation);
        command.execute();

        BOOST_CHECK(player.getCanWin() == false);
        BOOST_CHECK(engine.getState().getAccusationSuccess() == false);
    }

BOOST_AUTO_TEST_SUITE_END()

// SecretPassageCommand.cpp test
BOOST_AUTO_TEST_SUITE(TestSecretPassageCommand)

    BOOST_AUTO_TEST_CASE(TestValidSecretPassage)
    {
        state::Room garage(GARAGE);
        state::Room kitchen(KITCHEN);
        garage.setSecretPassage(kitchen);

        state::PlayerState player(ROSE);
        player.setLocation(garage);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::SecretPassageCommand command(engine, player);
        command.execute();
        state::Room newPlayerRoom = dynamic_cast<Room&>(player.getLocation());

        BOOST_CHECK(newPlayerRoom.getRoomName() == kitchen.getRoomName());

    }

    BOOST_AUTO_TEST_CASE(TestInvalidStartingPosition)
    {
        state::Cell cell(8, 8, CORRIDOR);
        state::PlayerState player(ROSE);
        player.setLocation(cell);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::SecretPassageCommand command(engine, player);
        BOOST_CHECK_THROW(command.execute(), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(TestRoomWithoutSecretPassage)
    {
        state::Room garage(GARAGE);
        state::Room kitchen(KITCHEN);

        state::PlayerState player(ROSE);
        player.setLocation(garage);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::SecretPassageCommand command(engine, player);

        BOOST_CHECK_THROW(command.execute(), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()


// HypothesisCommand.cpp test
BOOST_AUTO_TEST_SUITE(TestHypothesisCommand)

    BOOST_AUTO_TEST_CASE(TestValidHypothesis)
    {
        state::Room study(STUDY);
        state::PlayerState player(ROSE);
        player.setLocation(study);

        state::PlayerState suspectPlayer(PERVENCHE);
        state::TripleClue hypothesis{PERVENCHE, CANDLESTICK, STUDY};

        State state("../configurations/map.json",3);
        engine::Engine engine(state);
        engine.setCurrentPlayer(player);

        engine::HypothesisCommand command(engine, player, hypothesis);
        command.execute();
        state::Room newPlayerRoom = dynamic_cast<Room&>(player.getLocation());

        BOOST_CHECK(newPlayerRoom.getRoomName() == study.getRoomName()); // Suspect téléporté
        BOOST_CHECK(player.getPreviousHypothesisRoom() == STUDY);   // Hypothesis room saved
    }

    BOOST_AUTO_TEST_CASE(TestInvalidRoomHypothesis)
    {
        state::Room study(STUDY);
        state::PlayerState player(ROSE);
        player.setLocation(study);

        state::TripleClue hypothesis{PERVENCHE, CANDLESTICK, HALL};

        State state("../configurations/map.json",3);
        engine::Engine engine(state);
        engine.setCurrentPlayer(player);

        engine::HypothesisCommand command(engine, player, hypothesis);
        command.execute();

        BOOST_CHECK(player.getPreviousHypothesisRoom() == NO_ROOM); // Hypothesis room not saved
    }

BOOST_AUTO_TEST_SUITE_END()


// MoveCommand.cpp test
BOOST_AUTO_TEST_SUITE(TestMoveCommand)

    BOOST_AUTO_TEST_CASE(TestMoveWithinCorridor)
    {
        state::Cell cell1(8, 8, state::CORRIDOR);
        state::Cell cell2(8, 9, state::CORRIDOR);

        state::PlayerState player(ROSE);
        player.setLocation(cell1);

        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::MoveCommand command(engine, player, cell2);
        command.execute();

        BOOST_CHECK(dynamic_cast<Cell&>(player.getLocation()).getX() == 8);
        BOOST_CHECK(dynamic_cast<Cell&>(player.getLocation()).getY() == 9);
    }

    BOOST_AUTO_TEST_CASE(TestMoveFromDoorToRoom)
    {
        state::Room living_room(LIVING_ROOM);
        state::Door door(5, 8, &living_room);
        living_room.addDoor(door);

        state::PlayerState player(ROSE);
        player.setLocation(door);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::MoveCommand command(engine, player, living_room);
        command.execute();
        state::Room newPlayerRoom = dynamic_cast<Room&>(player.getLocation());

        BOOST_CHECK(newPlayerRoom.getRoomName() == living_room.getRoomName());
    }

    BOOST_AUTO_TEST_CASE(TestMoveFromRoomToDoor)
    {
        state::Room living_room(LIVING_ROOM);
        state::Door door(5, 8, &living_room);
        living_room.addDoor(door);

        state::PlayerState player(ROSE);
        player.setLocation(living_room);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::MoveCommand command(engine, player, door);
        command.execute();

        BOOST_CHECK(dynamic_cast<Cell&>(player.getLocation()).getX() == 1);
        BOOST_CHECK(dynamic_cast<Cell&>(player.getLocation()).getY() == 1);
    }

    BOOST_AUTO_TEST_CASE(TestInvalidMove)
    {
        state::Cell cell1(8, 8, state::CORRIDOR);
        state::Cell cell2(8, 10, state::CORRIDOR);

        state::PlayerState player(ROSE);
        player.setLocation(cell1);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::MoveCommand command(engine, player, cell2);
        BOOST_CHECK_THROW(command.execute(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestMoveToOccupiedCell)
    {
        state::Cell cell1(8, 8, state::CORRIDOR);
        state::Cell cell2(8, 9, state::CORRIDOR);

        state::PlayerState player1(ROSE);
        player1.setLocation(cell1);
        state::PlayerState player2(PERVENCHE);
        player2.setLocation(cell2);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::MoveCommand command(engine, player1, cell2);
        BOOST_CHECK_THROW(command.execute(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestInvalidStartingLocationType)
    {
        state::Cell inaccessible(0, 0, INACCESSIBLE);
        state::PlayerState player(ROSE);
        player.setLocation(inaccessible);
        State state("../configurations/map.json",3);
        engine::Engine engine(state);

        engine::MoveCommand command(engine, player, inaccessible);

        BOOST_CHECK_THROW(command.execute(), std::invalid_argument);
    }

BOOST_AUTO_TEST_SUITE_END()

// Engine.cpp tests
// ----------------

BOOST_AUTO_TEST_SUITE(TestEngine)
    BOOST_AUTO_TEST_CASE(TestDealCards)
    {
        State state("../configurations/map.json",3);
        engine::Engine engine(state);
        engine.dealCards();

        TripleClue env = engine.getEnvelope();
        BOOST_TEST((std::is_same<decltype(env.suspect), Suspect>::value));
        BOOST_TEST((std::is_same<decltype(env.weapon), Weapon>::value));
        BOOST_TEST((std::is_same<decltype(env.room), RoomName>::value));

        std::vector<PlayerState> players = state.getPlayerStateVec();
        int minCards = 20;
        int maxCards = 0;
        for (PlayerState player : players) {
            int number_of_cards = player.getSuspectCards().size() + player.getWeaponCards().size() + player.getRoomCards().size();
            minCards = std::min(minCards, number_of_cards);
            maxCards = std::max(maxCards, number_of_cards);
        }
        BOOST_CHECK_LE(maxCards - minCards, 1); // At most one card difference between players
    }

    BOOST_AUTO_TEST_CASE(TestDistributionCharacters){
        State state("../configurations/map.json",6);
        engine::Engine engine(state);
        engine.distributionCharacters();

        std::vector<PlayerState> players = state.getPlayerStateVec();
        std::set<state::Suspect> assignedSuspects;
        for (const auto& player : players) {
            auto suspect = player.getIdentity();
            BOOST_CHECK(assignedSuspects.find(suspect) == assignedSuspects.end()); // No doubles
            assignedSuspects.insert(suspect);
        }
    }

    BOOST_AUTO_TEST_CASE(TestDice) {
        State state("../configurations/map.json", 3);
        engine::Engine engine(state);

        auto diceRoll = engine::Engine::dice();
        BOOST_CHECK_EQUAL(diceRoll.size(), 2);
        BOOST_CHECK(diceRoll[0] >= 1 && diceRoll[0] <= 6);
        BOOST_CHECK(diceRoll[1] >= 1 && diceRoll[1] <= 6);
    }

    BOOST_AUTO_TEST_CASE(GetPossessedCardsTest) {
        State state("../configurations/map.json", 3);
        engine::Engine engine(state);
        state::PlayerState player(ROSE);

        state::SuspectCard violetCard(state::VIOLET);
        state::SuspectCard roseCard(state::ROSE);
        state::WeaponCard wrenchCard(state::WRENCH);
        state::WeaponCard pistolCard(state::PISTOL);
        state::RoomCard kitchenCard(state::KITCHEN);
        state::RoomCard studyCard(state::STUDY);
        player.addSuspectCard(violetCard);
        player.addSuspectCard(roseCard);
        player.addWeaponCard(wrenchCard);
        player.addWeaponCard(pistolCard);
        player.addRoomCard(kitchenCard);
        player.addRoomCard(studyCard);

        state::TripleClue inputClues{};
        inputClues.suspect = ROSE;
        inputClues.weapon = PISTOL;
        inputClues.room = STUDY;  // All 3 cards possessed by the player

        auto possessedCards = engine.getPossessedCards(inputClues, player);

        BOOST_CHECK_EQUAL(possessedCards.size(), 3);
        BOOST_CHECK_EQUAL(possessedCards[0], &roseCard);
        BOOST_CHECK_EQUAL(possessedCards[1], &pistolCard);
        BOOST_CHECK_EQUAL(possessedCards[2], &studyCard);
    }

    BOOST_AUTO_TEST_CASE(ShowCardTest) {
        State state("../configurations/map.json", 3);
        engine::Engine engine(state);

        state::SuspectCard violetCard(state::VIOLET);
        state::SuspectCard roseCard(state::ROSE);
        state::WeaponCard wrenchCard(state::WRENCH);
        state::WeaponCard pistolCard(state::PISTOL);
        state::RoomCard kitchenCard(state::KITCHEN);
        state::RoomCard studyCard(state::STUDY);

        std::vector<state::Card> cards = {violetCard, roseCard, wrenchCard, pistolCard, kitchenCard, studyCard};

        state::Card card = engine.showCard(cards, 1);
        BOOST_CHECK_EQUAL(&card, &roseCard);
        BOOST_CHECK_THROW(engine.showCard(cards, 10), std::out_of_range);
    }

    BOOST_AUTO_TEST_CASE(GetPossibleMovesTest) {
        State state("../configurations/map.json", 3);
        engine::Engine engine(state);
        state::PlayerState player(ROSE);

        // Case 1 : A player in the middle of a corridor
        state::Cell cell1(8, 8, CORRIDOR);  // A corridor with 4 corridor neighbors
        player.setLocation(cell1);  // Le joueur est dans ce corridor
        std::vector<engine::Move> possibleMoves = engine.getPossibleMoves(player);
        BOOST_CHECK_EQUAL(possibleMoves.size(), 4);  // MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT

        // Cas 2 : A player on a door
        state::Room hall(HALL);
        state::Door door(8, 8, &hall);
        player.setLocation(door);

        std::vector<engine::Move> possibleMovesWithRoom = engine.getPossibleMoves(player);
        BOOST_CHECK(std::find(possibleMovesWithRoom.begin(), possibleMovesWithRoom.end(), engine::ENTER_ROOM) != possibleMovesWithRoom.end());

        // Case 3 : A player leaving a room
        state::Room kitchen(KITCHEN);
        player.setLocation(kitchen);

        std::vector<engine::Move> possibleMovesRoom = engine.getPossibleMoves(player);
        BOOST_CHECK(std::find(possibleMovesRoom.begin(), possibleMovesRoom.end(), engine::EXIT_ROOM) != possibleMovesRoom.end());

        // Case 4 : Invalid player location
        state::Location invalidLocation(INACCESSIBLE);
        player.setLocation(invalidLocation);

        BOOST_CHECK_THROW(engine.getPossibleMoves(player), std::runtime_error);
    }

BOOST_AUTO_TEST_SUITE_END()
