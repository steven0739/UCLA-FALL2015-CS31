//
//  main.cpp
//  rocks
//
//  Created by 杨博超 on 15/11/12.
//  Copyright © 2015年 杨博超. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "utilities.h"
using namespace std;

//Declare constant integers
const int MAXPROBELEN = 100;
const int MAXWORDS = 9000;

//Functions that will be use later
int loadWords(char words[][MAXWORDLEN+1], int MAXWORDS);
int manageOneRound(char words[][MAXWORDLEN+1], int nWords, int wordnum);
bool contains(const char words[][MAXWORDLEN+1], int nWords, const char str[]);
int countPebbles(const char s1[], const char s2[], bool*, bool*);
int countRocks(const char s1[], const char s2[], bool*, bool*);
int randInt(int min, int max);


int main()
{
    char wordList[MAXWORDS][MAXWORDLEN+1];
    
    //nWords is the actual number of words in the array
    //Call loadWords to fill the array
    int nWords = loadWords(wordList,MAXWORDS);
    
    //Bad argument: no words are loaded
    if (nWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    //Choose how many rounds to play
    cout << "How many rounds do you want to play? ";
    int nRounds;
    cin >> nRounds;
    cin.ignore(100000, '\n');
    //Bad argument: non-positive round number
    if (nRounds <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return -1;
    }
    
    //Declare the times of guesses in each round
    int totalProbes = 0;
    int minProbes = 0;
    int maxProbes = 0;
    
    //Play one round
    for (int round = 1; round <= nRounds; round++)
    {
        cout << endl << "Round " << round << endl;
        
        // Select random word as secret word
        int wordnum = randInt(0, nWords-1);
        //Get the length of the secret word
        cout << "The secret word is " << strlen(wordList[wordnum]) << " letters long." << endl;
        
        // Play a round with that word
        int nProbes = manageOneRound(wordList, nWords, wordnum);
        
        //When the function manageOneRound returns -1
        if (nProbes == -1)
        {
            cout << "That's totally wrong." << endl;
            break;
        }

        //Special case when only need one guess
        if (nProbes == 1)
        {
            cout << "You got it in 1 try." << endl;
        }
        else
            cout << "You got it in " << nProbes << " tries." << endl;
        
        // Update and print statistics
        totalProbes += nProbes;
        if (round == 1)
        {
            minProbes = nProbes;
            maxProbes = nProbes;
        }
        else if (nProbes < minProbes)
            minProbes = nProbes;
        else if (nProbes > maxProbes)
            maxProbes = nProbes;
        cout << "Average: " << static_cast<double>(totalProbes)/round
        << ", minimum: " << minProbes
        << ", maximum: " << maxProbes << endl;
    }
}

int manageOneRound(char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    //Set two boolean
    bool used1[MAXWORDLEN + 1];
    bool used2[MAXWORDLEN + 1];
    
    //Bad arguments: beyond the range
    if (wordnum < 0 || wordnum >= nWords)
    {
        return -1;
    }
    
    char probe[MAXPROBELEN+1];
    for (int probeNum = 1; ;)
    {
        // Get probe word
        cout << "Probe word: ";
        cin.getline(probe, MAXPROBELEN+1);
            
        // If it's the secret word, return
        if (strcmp(probe, words[wordnum]) == 0)
            return probeNum;
        
        //Set all to false
        for(int i = 0; i < MAXWORDLEN + 1; i++)
        {
            used1[i] = false;
            used2[i] = false;
        }
        
        //See if probe word has a valid number of lower case letters
        bool valid = true;
        for (int k = 0; probe[k] != '\0'; k++)
            if (!islower(probe[k]) || !isalpha(probe[k]) ||  strlen(probe) < MINWORDLEN  ||  strlen(probe) > MAXWORDLEN)
            {
                valid = false;
            }
        if (valid == false)
        {
            cout << "Your probe word must be a word of " << MINWORDLEN << " to " << MAXWORDLEN << " lower case letters." << endl;
        }
            
        //See if the probe word is in the word list
        else if (! contains(words, nWords, probe) )
            cout << "I don't know that word." << endl;
            
        //Report number of matching letters by calling two functions
        else
        {
            probeNum ++;
            cout << "Rocks: " << countRocks(probe, words[wordnum], used1, used2) << ", Pebbles: " << countPebbles(probe, words[wordnum],used1, used2) << endl;
        }
    }
}

//To see whether the probe words are in the wordlist given
//If not, return false
bool contains(const char words[][MAXWORDLEN+1], int nWords, const char str[])
{
    for (int k = 0; k < nWords; k++)
    {
        if (strcmp(words[k], str) == 0)
            return true;
    }
    return false;
}

//Count how many rocks pair between the secret word and the probe word
int countRocks(const char s1[], const char s2[], bool used1[], bool used2[])
{
    
    int nRocksMatches = 0;
    
    for (int k = 0; s1[k] != '\0' && s2[k] != '\0'; k++)
    {
        if (s1[k] == s2[k])
        {
            nRocksMatches++;
            //In case the letter be used twice, replace it by true
            used1[k] = true;
            used2[k] = true;
        }
    }
    return nRocksMatches;
}

//Count how many pebbles pair between the secret word and the probe word
int countPebbles(const char s1[], const char s2[], bool used1[], bool used2[])
{
    int nPebblesMatches = 0;
    
    for (int k1 = 0; s1[k1] != '\0'; k1++)
    {
        for (int k2 = 0; s2[k2] != '\0'; k2++)
        {
            //If the letter was already uses, skip it
            if (s1[k1] == s2[k2] && k1 != k2 && (!used1[k1]) && (!used2[k2]))
            {
                nPebblesMatches++;
                //In case the letter be used twice, replace it by true
                used1[k1] = true;
                used2[k2] = true;
                break;
            }
        }
    }
    return nPebblesMatches;
}

