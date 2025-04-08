//Developer: Austin Siller / Carter Zimmy / Mashhood Syed
// Class: COP 2006-202501, Spring 2025
// Date: April 7, 2025
// Description: A fun unique hangman game
// Word Cited: geeksforgeeks and Youtube

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <cctype>
#include <set>
#include <limits>

// Maximum number of wrong guesses allowed
const int MAX_STAGE = 6;

// Global game statistics
int totalGamesPlayed = 0;
int totalWins = 0;
int totalLosses = 0;

// Function to display the game instructions
void displayInstructions()
{
    std::cout << "\n========================================\n";
    std::cout << "           Hangman Game Instructions\n";
    std::cout << "========================================\n";
    std::cout << "1. You will try to guess the hidden word one letter at a time.\n";
    std::cout << "2. For each incorrect guess, the hangman drawing advances.\n";
    std::cout << "3. The game ends when you guess the word or the hangman is fully drawn.\n";
    std::cout << "4. Input must be a single alphabet letter. Input is case insensitive.\n";
    std::cout << "5. After each game, you can choose to play again.\n";
    std::cout << "Good luck!\n";
    std::cout << "========================================\n\n";
}

// Function to select a random word from an expanded list
std::string selectRandomWord()
{
    std::vector<std::string> wordCollection =
        {
        "programming", "hangman", "challenge", "unique", "cplusplus",
        "exception", "debugging", "algorithm", "function", "variable",
        "computer", "science", "keyboard", "mouse", "monitor",
        "internet", "software", "hardware", "programmer", "compile",
        "syntax", "binary", "execute", "debug", "runtime",
        "development", "engineer", "system", "logic", "operator",
        "iteration", "compiler", "network", "database", "storage",
        "cloud", "virtualization", "cybersecurity", "optimization",
        "multithreading", "inheritance", "polymorphism", "encapsulation",
        "abstraction", "constructor", "destructor", "pointer", "reference",
        "framework", "library", "template", "exceptional", "interface"
    };
    if (wordCollection.empty())
        {
        throw std::runtime_error("Word collection is empty!");
    }
    int randomIndex = std::rand() % wordCollection.size();
    return wordCollection[randomIndex];
}

// Function to print the hangman ASCII art based on the current stage
void printHangmanStage(int currentStage)
{
    std::cout << "Hangman state:\n";
    switch (currentStage)
        {
        case 0:
            std::cout << "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n";
            break;
        case 1:
            std::cout << "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n";
            break;
        case 2:
            std::cout << "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n";
            break;
        case 3:
            std::cout << "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n";
            break;
        case 4:
            std::cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n";
            break;
        case 5:
            std::cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n";
            break;
        default:
            std::cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n";
            break;
    }
}

// Function to display the current state of the game
void displayGameState(const std::string &currentMaskedWord, const std::vector<char> &incorrectGuesses, int currentStage)
{
    std::cout << "\nCurrent word: " << currentMaskedWord << "\n";
    std::cout << "Wrong guesses: ";
    for (char wrongLetter : incorrectGuesses)
        {
        std::cout << wrongLetter << " ";
    }
    std::cout << "\n";
    printHangmanStage(currentStage);
}

// Function to update the masked word by revealing correctly guessed letters
void updateMaskedWord(std::string &currentMaskedWord, const std::string &secretWord, char userGuess)
{
    for (std::size_t indexCounter = 0; indexCounter < secretWord.size(); ++indexCounter)
        {
        if (secretWord[indexCounter] == userGuess)
            {
            currentMaskedWord[indexCounter] = userGuess;
        }
    }
}

// Function to check if a letter has already been guessed
bool alreadyGuessedLetter(const std::set<char> &guessedLetters, char userGuess)
{
    return guessedLetters.find(userGuess) != guessedLetters.end();
}

// Function to get a valid guess from the user
char getUserGuess(std::set<char> &guessedLetters)
{
    std::string userInput;
    while (true)
        {
        std::cout << "Enter your guess (a single letter): ";
        std::getline(std::cin, userInput);
        if (userInput.empty())
            {
            std::cout << "No input detected. Please try again.\n";
            continue;
        }
        char userGuess = std::tolower(userInput[0]);
        if (!std::isalpha(userGuess))
            {
            std::cout << "Invalid input. Only alphabet letters are allowed.\n";
            continue;
        }
        if (alreadyGuessedLetter(guessedLetters, userGuess))
            {
            std::cout << "You already guessed '" << userGuess << "'. Please try a different letter.\n";
            continue;
        }
        guessedLetters.insert(userGuess);
        return userGuess;
    }
}

// Function to ask the user if they want to play again
bool askReplayGame()
{
    std::string replayInput;
    while (true)
        {
        std::cout << "\nDo you want to play again? (yes/no): ";
        std::getline(std::cin, replayInput);
        if (replayInput.empty())
            {
            std::cout << "No input detected. Please answer with 'yes' or 'no'.\n";
            continue;
        }
        char firstCharacter = std::tolower(replayInput[0]);
        if (firstCharacter == 'y')
            {
            return true;
        } else if (firstCharacter == 'n')
            {
            return false;
        } else
            {
            std::cout << "Invalid response. Please enter 'yes' or 'no'.\n";
        }
    }
}

// Function to display game statistics after all games are played
void displayGameStatistics()
{
    std::cout << "\n========================================\n";
    std::cout << "            Game Statistics             \n";
    std::cout << "========================================\n";
    std::cout << "Total games played: " << totalGamesPlayed << "\n";
    std::cout << "Total wins: " << totalWins << "\n";
    std::cout << "Total losses: " << totalLosses << "\n";
    std::cout << "Thanks for playing Hangman!\n";
    std::cout << "========================================\n";
}

// Additional helper function to simulate a brief pause (for effect)
void pauseForEffect()
{
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Main function where the game loop resides
int main()
{
    try
        {
        std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator
        displayInstructions();

        bool playAgain = true;
        while (playAgain)
            {
            totalGamesPlayed++;
            std::string secretWord = selectRandomWord();
            std::string currentMaskedWord(secretWord.length(), '_');
            std::set<char> guessedLetters;
            std::vector<char> incorrectGuesses;
            int currentStage = 0;

            // Game loop: continue until the word is guessed or maximum wrong guesses reached
            while (currentStage < MAX_STAGE && currentMaskedWord != secretWord)
                {
                displayGameState(currentMaskedWord, incorrectGuesses, currentStage);
                char userGuess = getUserGuess(guessedLetters);
                if (secretWord.find(userGuess) != std::string::npos)
                    {
                    updateMaskedWord(currentMaskedWord, secretWord, userGuess);
                    std::cout << "Good guess! '" << userGuess << "' is in the word.\n";
                } else
                    {
                    std::cout << "Sorry, '" << userGuess << "' is not in the word.\n";
                    incorrectGuesses.push_back(userGuess);
                    currentStage++;
                }
            }

            // Final state display after game loop ends
            displayGameState(currentMaskedWord, incorrectGuesses, currentStage);
            if (currentMaskedWord == secretWord)
                {
                std::cout << "Congratulations! You guessed the word: " << secretWord << "\n";
                totalWins++;
            } else
                {
                std::cout << "Game Over! The correct word was: " << secretWord << "\n";
                totalLosses++;
            }

            pauseForEffect();
            playAgain = askReplayGame();
        }

        displayGameStatistics();
    }
    catch (const std::exception &exceptionDetail)
        {
        std::cerr << "Error encountered: " << exceptionDetail.what() << "\n";
        return 1;
    }
    return 0;
}