CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

OBJS = main.o Ship.o ShipManager.o GameBoard.o BoardRenderer.o AbilityManager.o IAbility.o DoubleDamage.o Scanner.o RandomStrike.o AbilityException.o PlacementException.o OutOfBoundsAttackException.o

all: battleship

battleship: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o: main.cpp ShipManager.h GameBoard.h BoardRenderer.h AbilityManager.h \
         IAbility.h DoubleDamage.h Scanner.h RandomStrike.h AbilityException.h \
         PlacementException.h OutOfBoundsAttackException.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Ship.o: Ship.cpp Ship.h
	$(CXX) $(CXXFLAGS) -c Ship.cpp

ShipManager.o: ShipManager.cpp ShipManager.h Ship.h AbilityManager.h
	$(CXX) $(CXXFLAGS) -c ShipManager.cpp

GameBoard.o: GameBoard.cpp GameBoard.h Ship.h PlacementException.h OutOfBoundsAttackException.h
	$(CXX) $(CXXFLAGS) -c GameBoard.cpp

BoardRenderer.o: BoardRenderer.cpp BoardRenderer.h GameBoard.h
	$(CXX) $(CXXFLAGS) -c BoardRenderer.cpp

IAbility.o: IAbility.cpp IAbility.h
	$(CXX) $(CXXFLAGS) -c IAbility.cpp

DoubleDamage.o: DoubleDamage.cpp DoubleDamage.h IAbility.h
	$(CXX) $(CXXFLAGS) -c DoubleDamage.cpp

Scanner.o: Scanner.cpp Scanner.h IAbility.h
	$(CXX) $(CXXFLAGS) -c Scanner.cpp

RandomStrike.o: RandomStrike.cpp RandomStrike.h IAbility.h
	$(CXX) $(CXXFLAGS) -c RandomStrike.cpp

AbilityManager.o: AbilityManager.cpp AbilityManager.h IAbility.h DoubleDamage.h Scanner.h RandomStrike.h AbilityException.h
	$(CXX) $(CXXFLAGS) -c AbilityManager.cpp

AbilityException.o: AbilityException.cpp AbilityException.h
	$(CXX) $(CXXFLAGS) -c AbilityException.cpp

PlacementException.o: PlacementException.cpp PlacementException.h
	$(CXX) $(CXXFLAGS) -c PlacementException.cpp

OutOfBoundsAttackException.o: OutOfBoundsAttackException.cpp OutOfBoundsAttackException.h
	$(CXX) $(CXXFLAGS) -c OutOfBoundsAttackException.cpp

clean:
	rm -f *.o battleship