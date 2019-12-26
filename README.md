# Pilgrims-and-Sheep
Pilgrims and Sheep word guessing game built with C++.

## How to play
Here's how one round of Pilgrims and Sheep works: The computer picks a mystery word of four to six letters and tells the player how many letters are in the word. The player tries to determine the mystery word by presenting the computer with a series of trial words. Each trial word is a four to six letter word. If the trial word is the mystery word, the player wins. Otherwise, the computer responds to the trial word with two numbers: the number of pilgrims and the number of sheep. Pilgrims and sheep are pairings between a letter in the trial word and the same letter in the mystery word:

A pilgrim is a pairing of a letter in the trial word and the same letter in the mystery word in the same position. For example, if the mystery word is TOIL and the trial word is FOIL, there's three pilgrims: The Os, Is, and Ls are in the same positions (2, 3, 4).

A sheep is a pairing between a letter in the trial word and the same letter in the mystery word, but not in the same position as in the trial word, provided that neither of the two letters are involved in a pilgrim or another sheep. For example, if the mystery and trial words are EGRET and AGATE, the Ts form a bee, since we can pair them up but they're not in the same position, since one is the fifth letter of EGRET and the other is the fourth letter of AGATE. The E in AGATE and, say, the first E in EGRET can be paired up to form another bee; the second E in EGRET would then not be part of a bee — we can't pair it up with the E in AGATE because that E is already paired up with the first E in EGRET. If instead we paired the E in AGATE with the second E in EGRET, then the first E in EGRET would have to remain unpaired. *(Note that EGRET and AGATE have one pilgrim: the G in the second position)*

If a letter at a particular position in a word could be considered part of a pilgrim or part of a sheep, it must be treated as part of a pilgrim. For example, if the mystery and trial words were EGRET and VIXEN, the E in VIXEN must be paired up with the second E in EGRET to form a pilgrim; that takes priority over pairing it with the first E in EGRET to form a sheep.

## How To Start
Make sure the .exe file has a "words.txt" file (examples included in this repo) **in the same directory**. Make sure words in the file are 4-6 characters in length. To start, run the .exe file.

Two example word lists are given. The one labeled "words.txt" creates a challenging game while "ExampleGame.txt" creates a small game that can serve as a tutorial.


## Design Description


### isValidTrial function:
This function checks if a given trial word is valid. It returns true if it is.

- If length of trial word is not within 4-6 letters, return false
- Loop through each char in trial word
   - If char isn’t a lowercase letter, return false

- Return true if passed above tests

### isInWordList function:
This function checks if a given trial word is in the word list (provided text file). It returns true if it is.

- Loop through word list
	- If trial word in word list, return true
- If no match, return false

### printStats function:
This function calculates the average score and prints the average, minimum, and maximum scores.

- Divide total score by number of rounds to get average
- Print avg, min, max


### isInArray function:
This function returns true if the target parameter is in the array parameter.

- Loop through given array
	- If target in array, return true
- Otherwise return false

### playOneRound function:
This function plays one round of the pilgrims/sheep game. It is called in the main function. It takes in the master word list, the number of words being used for the game, and the randomly generated word index to randomly select a word in the master word list.

- If nwords or wordnum are invalid, return -1

- Loop until player guesses the mystery word
	- Ask user for trial word
	- Check validity of trial word
  - Loop through trial word and increment pilgrims for each corresponding index match in  mystery word
		- Restrict repeat usage of pilgrim indexes
	- Loop through trial word
		- Loop through mystery word
			- If not a restricted index and there is a char match
				- Increment sheep and restrict repeat usage of sheep index
	- Print number of pilgrims and sheep
	- Increment score
- Return score

### Main routine:
The main routine sets up the game and calls the playOneRound function to deliver the entire game experience.

- Populate master word list using text file
- Ask for number of rounds from user
- Initialize score variables to track game statistics

- Loop for user-specified number of rounds
	- Randomly select mystery word from word list
  - Call playOneRound using randomly selected word and increment score variables based on its return value
	- Call printStats

#### Thank you
Thank you to Dr. Smallberg at UCLA for the starting help!
