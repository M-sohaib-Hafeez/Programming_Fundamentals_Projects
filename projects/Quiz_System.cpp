#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // ADDED: Required for toupper()

using namespace std;
int score = 0;  // FIXED: Initialize score to 0

struct Quiz {
    string question;
    string options[4];  // Array to hold the 4 options
    char correctAnswer; 
};

void displayQuiz(const string& quizBank) {
    ifstream file(quizBank);
    if (!file) {
        cout << "Error: Unable to open file " << quizBank << endl;
        return;
    }

    Quiz quiz;  // Declare a variable of type Quiz to store each question's data

    while (getline(file, quiz.question)) {
        // Check if the question line is empty
        if (quiz.question.empty()) {
            continue;  // Skip empty lines
        }

        // Read the four options into the array
        bool validOptions = true;
        for (int i = 0; i < 4; ++i) {
            if (!getline(file, quiz.options[i])) {
                validOptions = false;
                break;
            }
        }
        
        if (!validOptions) break;

        // Read the correct answer (store as a single letter: A, B, C, or D)
        string correctAnswerStr;
        if (!getline(file, correctAnswerStr)) break;
        
        quiz.correctAnswer = toupper(correctAnswerStr[0]);  // Store only the letter A, B, C, or D

        // Display the question and options (with A, B, C, D)
        cout << "\n" << quiz.question << endl;
        char optionLabel = 'A';
        for (int i = 0; i < 4; ++i) {
            cout << optionLabel << ". " << quiz.options[i] << endl;
            optionLabel++;
        }

        // Get answer from the user (A, B, C, or D)
        char userAnswer;
        cout << "Enter the letter of your answer (A, B, C, D): ";
        cin >> userAnswer;

        // Convert the answer to uppercase to handle lowercase input
        userAnswer = toupper(userAnswer);

        // Check if the answer is correct
        if (userAnswer >= 'A' && userAnswer <= 'D') {
            if (userAnswer == quiz.correctAnswer) {
                cout << "Correct!" << endl;
                score += 1;  // FIXED: Changed from score+=1 to score += 1 (same, but clearer)
            } else {
                cout << "Incorrect. The correct answer is: " << quiz.correctAnswer << endl;
            }
        } else {
            cout << "Invalid input. Please choose a letter between A and D." << endl;
        }

        // FIXED: Clear input buffer properly before asking for Enter key
        cin.ignore(1000, '\n');  // Clear up to 1000 characters or until newline
        cout << "Press Enter to see the next question...";
        cin.get(); 
    }

    file.close();
}

// Function to save the user's score to a file
void saveScore(const string &username, int score) {
    ofstream outputFile("scores.txt", ios::app);  // FIXED: Use append mode to save multiple scores
    if (!outputFile) {
        cerr << "Error: Could not open the file 'scores.txt' to save scores!" << endl;
        return;
    }

    outputFile << username << " scored " << score << " points." << endl;
    outputFile.close();
}

int main() {
    cout << "Enter your name: ";  // FIXED: Added space after colon for better formatting
    string username;
    getline(cin, username);

    string quizBank = "questions.txt"; 
    displayQuiz(quizBank);
    saveScore(username, score);
    cout << "\nYour final score is: " << score << " out of ?" << endl;  // FIXED: Better output
    
    return 0;
}
