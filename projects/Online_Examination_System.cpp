
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Structure to represent a question
struct Question {
    string question;
    string options[4];
    char correct_answer;
};

// Function to load questions from a file
vector<Question> loadQuestions(string filename) {
    vector<Question> questions;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    Question q;
    while (getline(infile, q.question)) {
        for (int i = 0; i < 4; i++) {
            getline(infile, q.options[i]);
        }
        infile >> q.correct_answer;
        infile.ignore(); // Ignore newline character
        questions.push_back(q);
    }

    infile.close();
    return questions;
}

// Function to display a question
void displayQuestion(const Question& q) {
    cout << q.question << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << q.options[i] << endl;
    }
}

// Function to evaluate the answer
bool evaluateAnswer(char user_answer, char correct_answer) {
    return user_answer == correct_answer;
}

// Function to calculate and display the score
void calculateScore(int correct_answers, int total_questions) {
    double score = (static_cast<double>(correct_answers) / total_questions) * 100;
    cout << "\nYour Score: " << score << "%" << endl;
}

// Function to save results to a file
void saveResults(string result_file, string name, double score) {
    ofstream outfile(result_file, ios::app); // Append to existing file
    if (!outfile.is_open()) {
        cerr << "Error: Unable to open file " << result_file << endl;
        exit(1);
    }

    outfile << name << " - Score: " << score << "%" << endl;
    outfile.close();
}

int main() {
    string question_file = "C:/Project save file/questions.txt.txt"; 
    string result_file = "C:/Project save file/result.txt.txt";
    vector<Question> questions = loadQuestions(question_file);

    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    int correct_answers = 0;
    for (const Question& q : questions) {
        displayQuestion(q);

        char user_answer;
        cout << "Enter your answer (A/B/C/D): ";
        cin >> user_answer;
        cin.ignore(); // Ignore newline character

        if (evaluateAnswer(user_answer, q.correct_answer)) {
            correct_answers++;
        }
    }

    calculateScore(correct_answers, questions.size());

    saveResults(result_file, name, (static_cast<double>(correct_answers) / questions.size()) * 100);

    return 0;
}
