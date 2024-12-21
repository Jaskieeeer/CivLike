#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <sstream>
#include "../include/Grid.h"
#include "../include/TurnManager.h"
#include "../include/Player.h"
#include "../include/Civilization.h"
#include "../include/RomanCiv.h"
#include "../include/Settler.h"
#include "../include/globals.h"
#include "../include/Warrior.h"


void writeMatchResult(const std::string& result) {
    std::ofstream file("./match_history.txt", std::ios::app); 
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << "match_history.txt" << std::endl;
        return;
    }

    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    file << result << " on " << buf << std::endl;

    file.close();
}

void displayMatchHistory() {
    std::ifstream file("./match_history.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << "match_history.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}
std::vector<std::pair<int, int>> generateSpawnPoints(int numPlayers, int gridWidth, int gridHeight) 
    {
        std::vector<std::pair<int, int>> spawnPoints;
        int sectionWidth = gridWidth / numPlayers;
        int sectionHeight = gridHeight / numPlayers;

        for (int i = 0; i < numPlayers; ++i) {
            int spawn_x = (std::rand() % sectionWidth) + (i * sectionWidth);
            int spawn_y = (std::rand() % sectionHeight) + (i * sectionHeight);
            spawnPoints.push_back(std::make_pair(spawn_x, spawn_y));
        }

        return spawnPoints;
    }


int main() {
    std::srand(std::time(0)); 
    std::string input;
    std::cout << "play(p) show match history(h) exit(e)\n";
    std::cin >> input;
    if (input == "e") {
        return 0;
    }
    else if (input == "h") {
        std::cout << "Match history:\n";
        displayMatchHistory();
        std::cout << "play(p) exit(e)\n";
        std::cin >> input;
        if (input == "e") {
            return 0;
        }
    }
    if (input != "p") {
        std::cout << "Invalid input\n";
        return 0;
    }
    
    Player player1("Jaskier", new RomanCiv());
    Player player2("Mhynio", new RomanCiv());
    TurnManager turnManager(&player1, &player2);
    std::vector<std::pair<int, int>> spawnPoints = generateSpawnPoints(2, globalGrid.getWidth(), globalGrid.getHeight());
    player1.addUnit(new Settler (spawnPoints[0].first, spawnPoints[0].second,&player1));
    player2.addUnit(new Settler (spawnPoints[1].first, spawnPoints[1].second,&player2)); 
    turnManager.nextTurn();
    bool isGameOver = false;
    std::string message = "";
    while (!isGameOver) {
        if (!turnManager.getCurrentPlayer().hasSettlersOrTowns()) {
            isGameOver = true;
            std::string result = "Player " + turnManager.getOpponentPlayer().getName()+ " wins!";
            std::cout << result << std::endl;
            writeMatchResult(result);
            break;
        }
        bool isTurnSkipped = false;
        while(!isTurnSkipped){
            for (int i = 0; i < 100; ++i) std::cout << "\n";  // "wyczyszczenie konsoli"
            std::cout<<"info: \n"<<message<<std::endl;
            message = "";
            turnManager.displayStatus();
            std::cout << "Player " << turnManager.getCurrentPlayer().getPlayerID() << " is taking action...\n";

            std::cout << "-Skip a turn(s)\n-give up(ff)\n-Chose a tile(c)\n";
            std::string input;
            std::cin >> input;
    
            if (input == "s") 
            {
                turnManager.skipTurn();
                isTurnSkipped = true;
                continue;
            } 
            else if (input == "ff") 
            {
                isGameOver = true;
                std::string result = "Player " + turnManager.getOpponentPlayer().getName() + " wins!";
                std::cout << result << std::endl;
                writeMatchResult(result);
                break;
            } 
            else if (input == "c") 
            {
                int x,y;
                int _ = 0;
                while (true) {
                    if (_!=0)
                    {
                        std::cout << "Enter tiles coordinates (x y) (or 's' to skip): ";
                    }
                    std::getline(std::cin, input); 

                    if (input == "s")
                    {
                        isTurnSkipped = true;
                        break;
                    }
                    std::istringstream iss(input);
                    if (iss >> x >> y) { 
                        break; 
                    } else if( _!=0) {
                        std::cout <<"Invalid input. Please enter two integers or 's' to stop.\n";
                    }
                    if (_ == 0){
                        _++;
                    }
                }
                if (isTurnSkipped) {
                    continue;
                }
                if (x < 0 || x >= globalGrid.getWidth() || y < 0 || y >= globalGrid.getHeight()) {
                    message += "Invalid coordinates\n";
                    continue;
                }
                if(!globalGrid.isVisible(x, y, turnManager.getCurrentPlayer().getPositions())){
                    message += "Tile is not visible\n";
                    continue;
                }
                Cell::Type type = globalGrid.getCellType(x, y);
                if (type == Cell::Type::TOWN){
                    if (globalGrid.getOwner(x, y) == turnManager.getCurrentPlayer().getPlayerID()) {
                        std::cout << "You have selected:\n";
                        turnManager.getCurrentPlayer().getTown(globalGrid.getUnitId(x, y))->displayTownStatus();
                        Town *town = turnManager.getCurrentPlayer().getTown(globalGrid.getUnitId(x, y));
                        town->getActions();
                        std::string action;
                        std::cin >> action;
                        if (action == "s")
                        {
                            turnManager.skipTurn();
                            isTurnSkipped = true;
                            continue;
                        }
                        if (action == "p")
                        {
                            continue;
                        }
                        std::string addMessage = turnManager.performAction(action, town);
                        if (addMessage == "skip"){
                            turnManager.skipTurn();
                            isTurnSkipped = true;
                            continue;
                        }
                        message +=  addMessage;

                        
                    } else {
                        message += "this is enemy Town:";
                        continue;
                    } 
                } 
                else if (std::find(unitTypes.begin(), unitTypes.end(), type) != unitTypes.end()) 
                {
                    if (globalGrid.getOwner(x, y) == turnManager.getCurrentPlayer().getPlayerID()) {
                        std::cout << "You have selected:\n";
                        turnManager.getCurrentPlayer().getUnit(globalGrid.getUnitId(x, y))->displayStatus();
                        Unit *unit = turnManager.getCurrentPlayer().getUnit(globalGrid.getUnitId(x, y));
                        unit->displayActions();
                        std::string action;
                        std::cin >> action;
                        if (action == "s")
                        {
                            turnManager.skipTurn();
                            isTurnSkipped = true;
                            continue;
                        }
                        if (action == "p")
                        {
                            continue;
                        }
                        std::string addMessage = turnManager.performAction(action, unit);
                        if (addMessage == "skip"){
                            turnManager.skipTurn();
                            isTurnSkipped = true;
                            continue;
                        }
                        message +=  addMessage;

                    } else {
                        message += "this is enemy unit:";
                        continue;
                    } 
                } 
                else if (type == Cell::Type::EMPTY) 
                {
                    message += "this is empty tile:";
                    continue;
                } 
                
                
            } 
            
            
        }

        turnManager.nextPlayer();
    }
    
    return 0;
}

