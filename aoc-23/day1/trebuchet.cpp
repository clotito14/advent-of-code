// Advent of Code 2023 
// Chase August Lotito

// Day 1: Trebuchet

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

// Function declarations
int numFromLine(std::string);
int numFromString(std::string, int);

int main() {

    std::string line;
    std::string inputFileName = "./input.txt";

    int current = 0;
    int total = 0;

    // create input file stream object
    std::ifstream inputFile (inputFileName);

    if (inputFile.is_open()) {
        while(std::getline(inputFile, line))
        {
            // extract number from line
            current = numFromLine(line);
            // take current and add to total!
            total += current;
        }

        std::cout << "Total Sum = " << total << std::endl;

        // Close the input file
        inputFile.close();        
    }
    else {
        std::cout << "ERROR: Unable to open file " << inputFileName << std::endl; 
    }

    return 0;
}


// Function Definitions

int numFromLine(std::string s) {
    int num = 0;
    int string_length = s.length();

    std::vector<int> numExtracted;

    // iterate through the entire line
    for (int i = 0; i < string_length; i++) {
        // check if we find numeric digit 
        if (isdigit(s[i])) {
            int digit = s[i] - '0';
            numExtracted.push_back(digit); 
        }
        // if alpha, then find if it's a word number 
        else if (isalpha(s[i])) {
            int digit = 0;
            digit = numFromString(s, i);
            if (digit != 0) {
                numExtracted.push_back(digit);
            }
        } 
        else {
            continue;
        }
    } 

    int vector_length = numExtracted.size();
    int firstElement = numExtracted.front();
    int lastElement = numExtracted.back();

    num = firstElement * 10 + lastElement;    

    // ANTIQUATED: extracts base 10 int from vector of ints
    //int vector_length = numExtracted.size();
    //int base, exponent, scaledNum;
    //for (int i = vector_length; i > 0; i--) {
    //    exponent = vector_length - i;
    //    base = pow(10, exponent);
    //    scaledNum = numExtracted[i - 1] * base;
    //    num += scaledNum; 
    //}

    return num;
}

int numFromString(std::string str, int iterator) {
    int num = 0;
    std::string substr;

    // iterate over string
    for (int i = iterator; i < str.length(); i++) {
        // if we have a alphabetic character, add this to working substring
        char ch = str[i];
        if (isalpha(ch)) {
            substr += ch;
        }

        // check if we have found a number, if so, set num to mapped val
        if (substr == "one") {
            num = 1;
            break;
        }
        else if (substr == "two") {
            num = 2;
            break;
        }
        else if (substr == "three") {
            num = 3;
            break;
        }
        else if (substr == "four") {
            num = 4;
            break;
        }  
        else if (substr == "five") {
            num = 5;
            break;
        }
        else if (substr == "six") {
            num = 6;
            break;
        }
        else if (substr == "seven") {
            num = 7;
            break;
        }
        else if (substr == "eight") {
            num = 8;
            break;
        }
        else if (substr == "nine") {
            num = 9;
            break;
        }
        else
            continue;
    }

    return num;
}