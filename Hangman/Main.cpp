#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <map>


std::string emptyWord(size_t wordCount);
void clearScreen();
void hangman();

int main()
{
	// game variables init
	std::ifstream wordlist;
	size_t winning = 0;
	int losing = 0;
	int numberOfWords = 0;
	bool isPlaying = true;
	bool choiceCorrect = false;
	char choice = ' ';
	std::string line;
	std::vector<std::string> listOfWords;
	std::map<char, bool> usedLetters;

	wordlist.open("wordlist.txt");

	while (std::getline(wordlist, line))
	{
		numberOfWords++;
		listOfWords.push_back(line);
	}

	wordlist.close();

	if (numberOfWords == 0)
	{
		std::cout << "Empty wordlist!" << std::endl;
		return -1;
	}

	// generate random number for random word 
	srand((unsigned)time(NULL));
	int randomWordInt = rand() % numberOfWords;
	std::string answer = listOfWords.at(randomWordInt);
	size_t wordLength = answer.length();
	std::string blankWord = emptyWord(wordLength);

	// game loop
	while (isPlaying)
	{
		clearScreen();
		switch (losing)
		{
		case 0:
			std::cout << "|----" << std::endl;
			break;
		case 1:
			std::cout << "|----" << std::endl;
			std::cout << "  O " << std::endl;
			break;
		case 2:
			std::cout << "|----" << std::endl;
			std::cout << "  O " << std::endl;
			std::cout << "  | " << std::endl;
			break;
		case 3:
			std::cout << "|----" << std::endl;
			std::cout << "  O " << std::endl;
			std::cout << " /| " << std::endl;
			break;
		case 4:
			std::cout << "|----" << std::endl;
			std::cout << "  O " << std::endl;
			std::cout << " /|\\ " << std::endl;
			break;
		case 5:
			std::cout << "|----" << std::endl;
			std::cout << "  O " << std::endl;
			std::cout << " /|\\ " << std::endl;
			std::cout << " /   " << std::endl;
			break;
		}
		std::cout << std::endl << blankWord << std::endl;
		std::cout << "Guess the word!" << std::endl;
		std::cin >> choice;

		if (usedLetters[choice])
		{
			std::cout << "Letter used in previous guess." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}
		else
		{
			usedLetters[choice] = true;
		}

		for (size_t i = 0; i < answer.length(); i++)
		{
			if (answer[i] == choice)
			{
				blankWord[i] = choice;
				winning++;
				choiceCorrect = true;
			}
		}

		if (!choiceCorrect)
		{
			losing++;
		}

		if (winning == answer.length())
		{
			clearScreen();
			std::cout << "The answer is " << answer << std::endl;
			std::cout << "You win!" << std::endl;
			isPlaying = false;
		}

		if (losing == 6)
		{
			hangman();
			std::cout << "Sorry, you lose..." << std::endl;
			std::cout << "The answer was " << answer << std::endl;
			isPlaying = false;
		}
		choiceCorrect = false;
	} 
}

/***********************************************
* Generate "-" for each letter in the word the * 
* player is guessing                           *
* I.E. "python" is "------"                    *
***********************************************/
std::string emptyWord(size_t wordCount)
{
	std::string blankWord = "";
	for (size_t i = 0; i < wordCount; i++)
	{
		blankWord.append("-");
	}
	return blankWord;
}

/***********************************************
*         Clear the player screen              *
***********************************************/
void clearScreen()
{
	std::cout << "\033c";
}

/***********************************************
* End game screen when the player loses        *
***********************************************/
void hangman()
{
	clearScreen();
	std::cout << "|----" << std::endl;
	std::cout << "  O " << std::endl;
	std::cout << " /|\\ " << std::endl;
	std::cout << " / \\  " << std::endl;
}