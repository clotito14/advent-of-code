// Advent of Code 2023 
// Chase August Lotito

// Day 2: Cube Connundrum

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// Function Declarations
    // Important functions
void ParseLineToMap(std::string, std::map<int, std::vector<std::vector<int>>>&);
int SumOfGoodGames(std::map<int, std::vector<std::vector<int>>>);
int SumOfPowerOfMinSets(std::map<int, std::vector<std::vector<int>>>);

    // Boilerplate functions
int FindTotalRounds(std::string);

// CONSTANTS
const int RED_CUBES = 12;
const int GREEN_CUBES = 13;
const int BLUE_CUBES = 14;

// it all starts here...
int main() {

    // input file stream object
    std::string InputFileName = "./input.txt";       // Input File Path
    std::ifstream InputFileStream (InputFileName);   // Input File
    std::string line;                                // file line temp variable

    // we will use a map to contain the values
    // using the game as the key
    // the values will be arrays of arrays of each game
    std::map<int, std::vector<std::vector<int>>> gameMap;

    // IF FILE IS OPENED:
    //  -> Read every single f**king line baby
    if (InputFileStream.is_open()) {
        while (std::getline(InputFileStream, line))
        {
            // given each line, we then send the map off
            // to recieve the parsed line data.
            ParseLineToMap(line, gameMap);
        }
        
    } else {
        std::cout << "ERROR: Unable to open FILE: " << InputFileName << std::endl;
    }

    // PART ONE:
    // Now with map of game outcomes, let us figure out the sum of good games
    int goodGames = 0;
    goodGames = SumOfGoodGames(gameMap);

    std::cout << "Sum of Possible IDs = " << goodGames << std::endl;

    // PART TWO:
    int sumOfPowers = 0;
    sumOfPowers = SumOfPowerOfMinSets(gameMap);
    
    std::cout << "Sum of Powers of Sets = " << sumOfPowers << std::endl;

    // it all ends here...
    return 0;
}

// Function Definitions

// This function will parse the incoming lines from the game log,
// and parse the pertinent game information into a map
void ParseLineToMap(std::string line, std::map<int, std::vector<std::vector<int>>> &map)
{
    // make line a string stream object
    std::stringstream s(line);

    // Have the string to store individual words
    std::string word;
    std::string prevWord;

    // Figure out number of rounds
    int total_rounds = FindTotalRounds(line);

    // Temp variables for map
    int key = 0;
    std::vector<std::vector<int>> value(total_rounds, std::vector<int>(3,0));
    int round = 0;

    // read through each individual word in each line
    while(s >> word) { 
        // extract key...game number...
        if (prevWord == "Game") {
            key = std::stoi(word); // extract key
            round = 0;           // reset to new game, therefore round reset to 0
        }
        // start populating the array for the map!
        // if red balls
        else if (isdigit(prevWord[0]) && word[0] == 'r') {
            value[round][0] = std::stoi(prevWord);
            map[key] = value;
        }
        // if green balls
        else if (isdigit(prevWord[0]) && word[0] == 'g') {
            value[round][1] = std::stoi(prevWord);
            map[key] = value;
        }
        // if blue balls
        else if (isdigit(prevWord[0]) && word[0] == 'b') {
            value[round][2] = std::stoi(prevWord);
            map[key] = value;
        }
        
        // Round logic
        if (word.back() == ';') {
            round++;
        }

        prevWord = word;
    }
}

// This function will find the sum of all good/possible games
int SumOfGoodGames(std::map<int, std::vector<std::vector<int>>> map) 
{
    // dummy variable for sum
    int sum = 0;

    // iterate through map
    for (const auto &pair : map) {
        int key = pair.first;
        std::vector<std::vector<int>> game = pair.second;
        std::vector<int> possibleRounds;

        // Iterate through each game's rounds
        for (int i = 0; i < game.size(); i++) {
            // find impossible rounds,
            // if no impossible round is detected,
            // add that game ID to the running sum of possible games
            if (game[i][0] > RED_CUBES || game[i][1] > GREEN_CUBES || game[i][2] > BLUE_CUBES) {
                std::cout << "[IMPOSSIBLE] Round " << i << " in Game " << key << std::endl;
                possibleRounds.clear();
                break;
            } else {
                std::cout << "[POSSIBLE]   Round " << i << " in Game " << key << std::endl;
                possibleRounds.push_back(key);
            }

            // if all rounds are possible, add that game ID to running sum
            if (possibleRounds.size() == game.size()) {
                sum += possibleRounds[0];
            }
        }   
    }

    // return sum of good games
    return sum;
}

int SumOfPowerOfMinSets(std::map<int, std::vector<std::vector<int>>> map) {
    int sum = 0;
    
    // iterate through map
    for (const auto &pair : map) {
        int key = pair.first;
        std::vector<std::vector<int>> game = pair.second;
        std::vector<int> possibleRounds;

        // variables for max of each color cube
        int redMax, greenMax, blueMax, product = 0;
        // Iterate through each game's rounds
        // find max of each color cube per game
        for (int i = 0; i < game.size(); i++) {
            
            if (game[i][0] > redMax) {
                redMax = game[i][0];
            } else if (game[i][1] > greenMax) {
                greenMax = game[i][1];
            }  else if (game[i][2] > blueMax) {
                blueMax = game[i][2];
            } else {
                continue;
            }
            std::cout << "Maxes {R,G,B}: " << "{" << redMax << "," << greenMax << "," << blueMax << "}" << std::endl; 
        }
        
        // find product of each max
        // then add that new product to sum!
        product = redMax * greenMax * blueMax;
        sum += product;
    }
    
    return sum;
}

// This function finds the total rounds per game line
int FindTotalRounds(std::string line) {
    std::stringstream s(line);
    std::string word;

    // Figure out number of rounds
    int n = 1;
    while (s >> word) {
        if (word.back() == ';') {
           n++;
        }
    }

    return n;
}



