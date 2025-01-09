#include <stdio.h>
#include <cstdlib>   
#include <ctime>       
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <map>
using namespace std;

const int WRONG_LIMIT = 6;

class WordBank {
    private:
        string words[20];
    public:
        void getWords(int choice) {
            ifstream ifs;
            int index = 0;
            switch(choice) {
                case 1:
                    ifs.open("/Users/maliaedmonds/Desktop/HackerRank practice/CppHangman/words/easy.txt");
                    break;
                case 2:
                    ifs.open("/Users/maliaedmonds/Desktop/HackerRank practice/CppHangman/words/medium.txt");
                    break;
                case 3:
                    ifs.open("/Users/maliaedmonds/Desktop/HackerRank practice/CppHangman/words/hard.txt");
                    break;
            }
            while(getline(ifs, words[index])) {
                index++;
            }
        }
        void print() {
            for (string word : this->words) {
                cout << word << "\n";
            }
        }
        string getRandomWord() {
            srand(time(0));
            return words[rand() % 20];
        }
};

class Game {
    private:
        string word;
        map<char, bool> letters;
        vector<char> guesses;
        WordBank bank;
        int wrong = 0;

    public:
        Game(int choice) {
            setWord(choice);
        }
        void setWord(int choice) {
            bank.getWords(choice);
            this->word = bank.getRandomWord();
            // cout << "WORD: " << word;
            for (char c : this->word) {
                letters[c] = false;
            }
        }
        int makeGuess(char letter) {
            if (find(this->guesses.begin(), this->guesses.end(), letter) != this->guesses.end()) {
                cout << "\n" << letter << " was already guessed. Try again.\n";
                return -1;
            }
            else {
                guesses.push_back(letter);
                if (letters.find(letter) != letters.end()) {
                    cout << "\n" << "Correct!\n";
                    letters[letter] = true;
                    if (checkWin()) {
                        return 3;
                    }
                }
                else {
                    wrong++;
                    if (wrong >= WRONG_LIMIT) {
                        cout << "\n" << "Incorrect. The word was " << word << ".\n";
                        return 2;
                    }
                    cout << "\n" << "Incorrect. " << WRONG_LIMIT - wrong << " guesses left.\n";
                }
                return 1;
            }
        }
        void printWord() {
            for (char c : word) {
                if (letters[c] == true) {
                    cout << c << " ";
                }
                else {
                    cout << "_ ";
                }
            }
            cout << "\n";
        }
        bool checkWin() {
            for (const auto& pair : letters) {
                if (!pair.second) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    bool playing;
    char play;
    int difficulty;
    char guess;

    cout << "*****************************************************************\n";
    cout << "* Welcome to Hangman! Would you like to start a new game? (y/n) *\n";
    cout << "*****************************************************************\n";
    cin >> play;
    playing =  play == 'y' ? true : false; 

    while (playing) {
        cout << "\n";
        cout << "*****************************************************************\n";
        cout << "* Enter a number to select your difficulty:                     *\n";
        cout << "*     1. Easy                                                   *\n";
        cout << "*     2. Medium                                                 *\n";
        cout << "*     3. Hard                                                   *\n";
        cout << "*****************************************************************\n";
        cin >> difficulty;

        Game game(difficulty);

        while (true) {
            game.printWord();
            cout << "\n";
            cout << "*****************************************************************\n";
            cout << "* Enter a letter to guess                                       *\n";
            cout << "*****************************************************************\n";
            cin >> guess;

            if (!isalpha(guess)) {
                cout << "\n";
                cout << "*****************************************************************\n";
                cout << "* Invalid input. Please try again.                              *\n";
                cout << "*****************************************************************\n";
                continue;
            }
            else {
                int result = game.makeGuess(guess);
                if (result == -1) {
                    continue;
                }
                else if (result == 2 || result == 3) {
                    break;
                }
            }
        }

        cout << "\n";
        cout << "*****************************************************************\n";
        cout << "* Game over! Would you like to play again? (y/n)                *\n";
        cout << "*****************************************************************\n";
        cin >> play;
        playing =  play == 'y' ? true : false; 
    }

    return 0;
}