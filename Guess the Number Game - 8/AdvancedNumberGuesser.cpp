#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

class AdvancedNumberGuesser {
private:
    int secretNumber;
    int previousGuess;
    int attempts;
    bool hintsEnabled;
    int score;
    int maxAttempts;
    vector<int> previousGuesses;

    int generateRandomNumber(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    void updateScore() {
        if (attempts % 2 == 0) {
            score -= 50;
        }
        else {
            score -= 30;
        }
    }

public:
    AdvancedNumberGuesser() {
        srand(time(0));
        secretNumber = generateRandomNumber(1, 100);
        previousGuess = 0;
        attempts = 0;
        hintsEnabled = true;
        score = 1000;
        maxAttempts = 10;

        cout << "Welcome to the Advanced Number Guesser!" << endl;
        cout << "Try to guess the secret number between 1 and 100." << endl;
        cout << "You can enter '0' to get a hint" << endl;
        cout << "You can also disable hints by entering '-1'." << endl;
        cout << "Your score changes dynamically with each attempt, and there are only " << maxAttempts << " allowed." << endl;
    }

    void provideHint() {
        if (!hintsEnabled) {
            cout << "Hints are currently disabled." << endl;
            return;
        }
        if (attempts == 0) {
            cout << "Need at least one guess prior to getting a hint." << endl;
            return;
        }
        int difference = abs(previousGuess - secretNumber);
        if (difference >= 20) {
            cout << "Hint: You are far from the secret number." << endl;
        }
        else if (difference >= 10) {
            cout << "Hint: You are getting closer to the secret number." << endl;
        }
        else {
            cout << "Hint: You are very close to the secret number." << endl;
        }
    }

    void displayPreviousGuesses() {
        if (!previousGuesses.empty()) {
            cout << "Previous guesses: ";
            for (int guess : previousGuesses) {
                cout << guess << " ";
            }
            cout << endl;
        }
    }

    void playGame() {
        int numPlayers;
        cout << "Enter the number of players: ";
        cin >> numPlayers;

        for (int currentPlayer = 1; currentPlayer <= numPlayers; currentPlayer++) {
            do {
                cout << "Player " << currentPlayer << " - Attempts left: " << maxAttempts - attempts << " | Score: " << score << endl;
                cout << "Enter your guess: ";

                int guess;

                try {
                    cin >> guess;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw runtime_error("Invalid input. Please enter a valid number.");
                    }

                    if ((guess < 1 || guess > 100) && (guess != 0 && guess != -1)) {
                        throw out_of_range("Invalid guess. Please enter a number between 1 and 100.");
                    }
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    continue;
                }

                system("cls");

                if (guess != 0 && guess != -1) {
                    attempts++;

                    previousGuesses.push_back(guess);

                    updateScore();
                }

                if (guess == secretNumber) {
                    cout << "Congratulations! Player " << currentPlayer << " guessed the correct number in " << attempts << " attempts." << endl;
                    cout << "Player " << currentPlayer << "'s final score is: " << score << endl;

                }
                else if (guess == 0) {
                    provideHint();
                }
                else if (guess == -1) {
                    hintsEnabled = false;
                    cout << "Hints are now disabled. Continue guessing." << endl;

                }
                else if (guess < 1 || guess > 100) {
                    cout << "Invalid guess. Please enter a number between 1 and 100." << endl;
                }
                else if (guess < secretNumber && attempts < maxAttempts) {
                    cout << "Too low. Try again!" << endl;
                }
                else if (guess > secretNumber && attempts < maxAttempts) {
                    cout << "Too high. Try again!" << endl;
                }
                if (guess != secretNumber) {
                    displayPreviousGuesses();
                }
                if (guess != 0 && guess != -1) {
                    previousGuess = guess;
                }
            } while (previousGuess != secretNumber && attempts < maxAttempts);

            if (previousGuess != secretNumber) {
                cout << "Player " << currentPlayer << " lost! The secret number was: " << secretNumber << endl;
                cout << "Player " << currentPlayer << "'s final score is: " << score << endl;
            }

            // Reset game state for the next player
            attempts = 0;
            previousGuesses.clear();
            hintsEnabled = true;

        }
    }
};

int main() {
    AdvancedNumberGuesser advancedGame;
    advancedGame.playGame();
    
    return 0;
}
