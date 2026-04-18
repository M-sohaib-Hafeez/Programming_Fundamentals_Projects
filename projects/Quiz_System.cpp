
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int score;


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
        // Read the four options into the array
        for (int i = 0; i < 4; ++i) {
            getline(file, quiz.options[i]);
        }

        // Read the correct answer (store as a single letter: A, B, C, or D)
        string correctAnswerStr;
        getline(file, correctAnswerStr);
        quiz.correctAnswer = toupper(correctAnswerStr[0]);  // Store only the letter A, B, C, or D

        // Display the question and options (with A, B, C, D)
        cout << quiz.question << endl;
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
                score+=1;
            } else {
                cout << "Incorrect. The correct answer is: " << quiz.correctAnswer << endl;
            }
        } else {
            cout << "Invalid input. Please choose a letter between A and D." << endl;
        }

      
        cout << "Press Enter to see the next question...";
        cin.ignore(); 
        cin.get(); 
    }

    file.close();
}
// Function to save the user's score to a file
void saveScore(const string &username, int score) {
    ofstream outputFile("scores.txt");
    if (!outputFile) {
        cerr << "Error: Could not open the file 'scores.txt' to save scores!" << endl;
        return;
    }

    outputFile << username << " scored " << score << " points." << endl;
    outputFile.close();
}

int main() {
    cout<<"Enter your name? ";
    string username;
    getline(cin,username);

    string quizBank = "questions.txt"; 
    displayQuiz(quizBank);
    saveScore (username, score );
    cout <<"Your score is " <<score;
return 0;
}