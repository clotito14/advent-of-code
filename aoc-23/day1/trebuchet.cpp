// Advent of Code 2023 
// Chase August Lotito

// Day 1: Trebuchet

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

// Function declarations
int numFromLine(std::string s);

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

    for (int i = 0; i < string_length; i++) {
        if (isdigit(s[i])) {
            int digit = s[i] - '0';
            numExtracted.push_back(digit); 
        } else {
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