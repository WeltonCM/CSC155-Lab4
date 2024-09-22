/*
Name: Lab4_Welton
Author: Christopher Welton
Description: This program plays the 'Game of Nim' with the computer and human player 
*/

#include <iostream>
#include <random>
#include <cstdio>
#include <cmath>

using namespace std;

int generateRandomNumber(int lowerBound, int upperBound) {
    random_device device;
    mt19937 generator(device());

    uniform_int_distribution<> intDist(lowerBound, upperBound);
    return intDist(generator);
}

bool generateRobotBoolean() {
    return generateRandomNumber(0,1) == 1;
}

bool isPowerOfTwo(int number) {
    double logValue = log2(number);
    return floor(logValue) == ceil(logValue);
}

int getSmartNumber(int numMarbles) {
    if(isPowerOfTwo(numMarbles + 1)){
        return generateRandomNumber(1, numMarbles/2);
    }
    switch(numMarbles){
        case 6:
            return 3;
        case 5:
            return generateRandomNumber(1, numMarbles/2);
        case 4:
            return generateRandomNumber(1, numMarbles/2);
        case 2: 
            return 1;
        default:
            int targetRemoval = 3;
            while(targetRemoval * 2 + 1 <= (numMarbles / 2)){
                targetRemoval = targetRemoval * 2 + 1;
            }
            return targetRemoval;
    }
   
}

bool playGame(bool isComputerFirst, bool isComputerSmart, int numberOfMarbles) {
    cout << "There are " << numberOfMarbles << " marbles on the table." << endl;
    printf("%s first!\n", (isComputerFirst) ? "The robot goes" : "You go");
    if(isComputerSmart) {
        cout << "Robot is smart!" << endl;
    }
    bool turn = isComputerFirst;
    int marblesLeft = numberOfMarbles;
    while(marblesLeft >= 1){
        int marblesTaken; 
        if(marblesLeft == 1) {
            printf("*********************%s!************************\n\n", (turn) ? "Robot Loses" : "Player Loses");
            break;
        }
        if(turn){
            marblesTaken = (isComputerSmart) ? getSmartNumber(marblesLeft) : generateRandomNumber(1, marblesLeft/2);
            printf("Robot wants %d %s \n", marblesTaken, (marblesTaken > 1) ? "marbles" : "marble");
        } else {
            bool validInput = false;
            cout << "Player make your move." << endl;
            while(!validInput){
                cout << "How many marbles do you want?" << endl;
                cin >> marblesTaken;
                if(marblesTaken <= (marblesLeft/2)){
                    printf("Player wants %d %s \n", marblesTaken, (marblesTaken > 1) ? "marbles" : "marble");
                    validInput = true;
                } else {
                    cout << "Invalid input, the number taken must be less than half of the pile left." << endl;
                }
            }
        }

        marblesLeft -= marblesTaken;
        printf("There %s %d %s left on the table\n", (marblesLeft > 1) ? "are" : "is" , marblesLeft, (marblesLeft > 1) ? "marbles" : "marble");
        turn = !turn;
    }
    return !turn;
}

int main(){

    cout << "Welcome to the Game of Nim!" << endl;
    cout << "This is a best of 3 tournament. First to 2 wins will be champion!!!" << endl;
    int playerWins = 0, robotWins = 0;
    while(playerWins < 2 && robotWins < 2){
        if(playerWins == 1 && robotWins == 0){
            cout << "Player needs one more win." << endl;
        } else if(robotWins == 1 && playerWins == 0){
            cout << "Robot needs one more win." << endl;
        } else if(robotWins == 1 && playerWins == 1){
            cout << "Tie breaker game!" << endl;
        }
        int numberOfMarbles = generateRandomNumber(10, 100);
        bool computerFirstTurn = generateRobotBoolean();
        bool computerIntelligence = generateRobotBoolean();

        bool winner = playGame(computerFirstTurn, computerIntelligence, numberOfMarbles);
        if(winner){
            robotWins ++;
        } else {
            playerWins ++;
        }
    }
    printf("%s wins the tournament!", (playerWins > robotWins) ? "Player" : "Robot");

    return 0;
}

