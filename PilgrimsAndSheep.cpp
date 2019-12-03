#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAXWORDS = 10'000;

bool isValidTrial(char cstring[]);
bool isInWordList(char cstring[], const char words[][MAXWORDLEN + 1], int nWords);
void printStats(int totalScore, int minScore, int maxScore, int roundNum);
bool isInArray(int array[], int n, int target);
int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);


int main() {

	//Initialize wordlist
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	const char WORDFILENAME[] = "./words.txt";

	//fills the array with the four-to-six-letter words found in the file named as its third argument 
	//returns the number of words put into the array
	int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); 
	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game.";
		return 1;
	}
	
	//Game setup
	cout << "How many rounds do you want to play? ";
	int roundCount = 0;
	cin >> roundCount; //assume input is always integer
	cin.ignore(10000, '\n'); //This consumes the \n char
	if (roundCount < 0)
	{
		cout << "The number of rounds must be positive.";
		return 1;
	}

	//Initialize variables to track game statistics
	int totalScore = 0;
	int minScore = 1;
	int maxScore = 1;
	//MAIN GAME LOOP//
	//Plays one round for the number of rounds that user specified
	for (int i = 1; i <= roundCount; i++)
	{
		//generate random int within the bounds of the word list
		int randNum = randInt(0, nWords - 1);
		int mysteryWordLen = strlen(wordList[randNum]);

		//Display round count and mystery word length
		cout << "\nRound " << i << "\n";
		cout << "The mystery word is " << mysteryWordLen << " letters long.\n";
		//Play a round and store the score for that round
		int score = playOneRound(wordList, nWords, randNum);
		if (score == 1)
			cout << "You got it in 1 try.\n";
		else
			cout << "You got it in " << score << " tries.\n";
		//Change variables to track stats
		totalScore += score;
		if (i == 1)
			minScore = score;
		if (score < minScore)
			minScore = score;
		if (score > maxScore)
			maxScore = score;
		//i is the round number (used for average)
		printStats(totalScore, minScore, maxScore, i);
	}
	



}


bool isValidTrial(char cstring[])	
{
	
	int n = strlen(cstring);
	if (n < 4 || n > 6)
		return false;
	//loop through each char in cstring
	for (int i = 0; cstring[i] != '\0'; i++)
	{
		//if current char is not a lowercase letter, return false
		if (! (isalpha(cstring[i]) && islower(cstring[i])))
			return false;
	}
	//if trial word is valid
	return true;
}

bool isInWordList(char cstring[], const char words[][MAXWORDLEN + 1], int nWords)
{
	//loop through word list 
	for (int i = 0; i < nWords; i++)
	{
		if (strcmp(cstring, words[i]) == 0) //if cstring (user input) is equal to a cstring in wordList
		{
			return true;
		}
	}
	return false; //If no match found, return false
}

void printStats(int totalScore, int minScore, int maxScore, int roundNum)
{
	//Find average
	double average = double(totalScore) / double(roundNum);
	//Sets output fixed to 2 decimal points
	cout.setf(ios::fixed);
	cout.precision(2);
	//Prints average, minimum score and maximum score
	cout << "Average: " << average << ", ";
	cout << "minimum: " << minScore << ", ";
	cout << "maximum: " << maxScore << "\n";
}

bool isInArray(int array[], int n, int target)
{
	//loops through array n times and returns true if target is in array
	for (int i = 0; i < n; i++)
	{
		if (array[i] == target)
			return true;
	}
	return false;
}

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{

	//If invalid nWords or wordnum
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords)
		return -1;

	//score = tries, higher score is worse
	int score = 0; //unknown words and trial strings that don't consist of exactly 4 to 6 lower case letters don't count

	while (true)
	{
		cout << "Trial word: ";
		//User input for guess/trial word
		char tword[200]; 
		cin.getline(tword, 200); 

		//if input is equal to the target word add a try and end round
		if (strcmp(tword, words[wordnum]) == 0) 
		{
			score++;
			break;
		}
		if (!isValidTrial(tword))
		{
			cout << "Your trial word must be a word of 4 to 6 lower case letters.\n";
			continue;
		}
		if (!isInWordList(tword, words, nWords))
		{
			cout << "I don't know that word.\n";
			continue;
		}
		//Initializations to track pilgrim count, sheep count, and repeated indexes
		int pilgrims = 0;
		int sheep = 0;
		int trial_indexes[MAXWORDLEN + 1];
		int mystery_indexes[MAXWORDLEN + 1];
		//These counts are to track how many spots in the index arrays are populated with meaningful values
		int count = 0;
		int count2 = 0;
		//loops through trial word
		for (int i = 0; i < int(strlen(tword)); i++)
		{
			//Check if pilgrim, save all pilgrim instances
			if (tword[i] == char(words[wordnum][i]))
			{
				//Add index of pilgrim to indexes
				trial_indexes[count] = i;
				mystery_indexes[count] = i;
				//Increment pilgrims for the game
				pilgrims++;
				//increment counts to keep track of how many elements to loop in respective arrays
				count++;
				count2++;
			}
			

		}
		//loop again, if letter is in target word and index is not in indexes
		
		//For each letter in trial word, loop through all letters in mystery word
		for (int i = 0; i < int(strlen(tword)); i++)
		{
			for (int j = 0; j < int(strlen(words[wordnum])); j++)
			{
				//If the char is in both words and is not already a pilgrim/sheep
				if (tword[i] == char(words[wordnum][j]) && (!isInArray(trial_indexes, count, i)) && (!isInArray(mystery_indexes, count2, j)))
				{
					//Increment sheep
					sheep++;
					//Add sheep index of mystery word to appropriate array
					mystery_indexes[count2] = j;
					//Increment count to know how many array elements to loop through
					count2++;
					//break out of internal loop and go to the next letter in trial word
					break;
				}
			}

			
		}
		
		//Print number of pilgrims and sheep for player to see
		cout << "pilgrims: " << pilgrims << ", sheep: " << sheep << "\n";

		//Increment score after resolving pilgrims and sheep
		score++;
	}
	


	return score;
}

