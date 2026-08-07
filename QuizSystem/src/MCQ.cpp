#include "../include/MCQ.h"
#include <iostream>

using namespace std;
MCQ::MCQ(int id, const string& prompt, int points, const vector<string>& options, const string& correctAnswerStr)
    : Question(id, prompt, points, correctAnswerStr), options(options) {
}

void MCQ::display() const {
    cout << "Câu " << getId() << ": " << prompt << " (" << getPoints() << " diem)\n";
    char label = 'A';
    for (size_t i = 0; i < options.size(); i++) {
        cout << label << ". " << options[i] << "   ";
        label++;
    }
    cout << "\n";
}
//getter
vector<string> MCQ::getOptions() const {
    return options;
}