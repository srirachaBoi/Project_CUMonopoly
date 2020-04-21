#include <iostream>
#include <iomanip>
#include "Game.h"
using namespace std;


int main()
{
    cout << setw(50) << "Welcome to a Game of Monopoly!" <<endl;
    cout << setw(50) << "Theme: CU Boudler" << endl;
    cout << setw(50) << "Solgan: The only place in Boulder where you can get rich!" << endl;

    Game monopoly;
    bool successfulRead = monopoly.readPlayers();
    monopoly.readProperty();
    if(!successfulRead)
    {
        successfulRead = monopoly.readPlayers();
    }

    string playerQuit;
    bool display_status = true;
    int playerMenuOptions = 0;
    int quitcounter = 0;
    do
    {
        int currentTurn = monopoly.getCurrentTurn();
        int numPlayers = monopoly.getNumPlayers();
        int amountBankrupt = monopoly.getAmountofBankruptPlayers();
        if(amountBankrupt == numPlayers - 1)
        {
            quitcounter = 1;
        }
        else if(monopoly.getBankruptStatus(currentTurn) == false && monopoly.getNumPlayers() != 1)
        {
            if(monopoly.getInJail(currentTurn) == true && monopoly.getTurnsInJail() > 0)
            {
                cout << "You are in jail for " << monopoly.getTurnsInJail() << " turn." << endl;
                monopoly.setTurnsInJail(monopoly.getTurnsInJail() - 1);
            }
            else
            {
                monopoly.setInJail(false);
                if(display_status == true)
                {
                    cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
                    monopoly.roll();
                    monopoly.move(currentTurn);
                    monopoly.display_MapAndPlayer();
                    monopoly.checkOwnership(currentTurn);
                    display_status = false;
                }
                cout << endl;
                cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
                cout << "Menu" << endl;
                cout << "1. Morgage" << endl;
                cout << "2. List of Owned Properties" << endl;
                cout << "3. Balance" << endl;
                cout << "4. Get Property Info" << endl;
                cout << "5. Buy House" << endl;
                cout << "6. End Turn" << endl;
                cout << "7. Trade" << endl;
                cout << "8. QUIT GAME" << endl;
                cin >> playerMenuOptions;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\x1B[91m" << "You Entered a non-digit Input" << "\x1B[0m" << endl;
                }
                else
                {
                    switch(playerMenuOptions)
                    {
                        case 1:
                        {
                            int morgageProperty_uI;
                            monopoly.morgage();
                            break;
                        }
                        case 2:
                        {
                            monopoly.listOfOwnedProperties();
                            break;
                        }
                        case 3:
                        {
                            monopoly.playerProfile();
                            break;
                        }
                        case 4:
                        {
                            int propertyLocation;
                            cout << "Enter from 0-39: ";
                            cin >> propertyLocation;
                            monopoly.getPropertyInfo(propertyLocation);
                            break;
                        }
                        case 5: 
                        {
                            int location = monopoly.getPlayerLocation();
                            monopoly.buyHouse(location);
                            break;
                        }
                        case 6:
                        {
                            monopoly.endTurn();
                            display_status = true;
                            break;
                        }
                        case 7:
                        {
                            int tradeMenu;
                            cout << "-------------Trade Menu-------------" << endl;
                            cout << "1. Trade with Money" << endl;
                            cout << "2. Trade with Property" << endl;
                            cin >> tradeMenu;

                            if(tradeMenu == 1)
                            {
                                int wantedProperty;
                                int moneyDeal;
                                cout << "Which property do you want? (Enter from 0 - 39): ";
                                cin >> wantedProperty;
                                cout << "How much money do you want to trade? $";
                                cin >> moneyDeal;
                                monopoly.tradeWithMoney(wantedProperty, moneyDeal);
                            }
                            else if(tradeMenu == 2)
                            {
                                int IwantThis;
                                int IGiveYouThat;
                                cout << "Which property do you want? (Enter from 0 - 39): ";
                                cin >> IwantThis;
                                cout << "Which Property do you want to trade for " << IwantThis << "? ";
                                cin >> IGiveYouThat;
                                monopoly.tradeWithProperty(IwantThis, IGiveYouThat);
                            }
                            break;
                        }
                        case 8:
                        {
                            int repeater = 0;
                            while(repeater == 0)
                            {
                                cout << "Are you sure you want to quit?" << endl;
                                cout << "Enter QUIT or Enter CANCEL. Ensure the letters are completely capitalized." << endl;
                                string entry;
                                cin >> entry;
                                if(entry == "QUIT")
                                {
                                    quitcounter = 1;
                                    repeater = 1;
                                }
                                else if(entry == "CANCEL")
                                {
                                    cout << "The game goes on." << endl;
                                    repeater = 1;
                                }
                                else
                                {
                                    cout << "Invalid input." << endl;
                                }
                            }
                            break;
                        }
                        case 8:
                        {
                            int propertyLocation;
                            cout << "Enter property Location: ";
                            cin >> propertyLocation;
                            monopoly.buy(propertyLocation, 1);
                            break;
                        }
                        default:
                            cout << "You have entered an option that does not exits." << endl;
                            break;
                    }
                }
            }
        }
        else
        {
            monopoly.endTurn();
        }
    } while (quitcounter == 0);

    monopoly.endGame();
    return 0;
}

