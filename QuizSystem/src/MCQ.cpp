#include "../include/MCQ.h"
#include <iostream>
#include <cctype>//cho hàm toupper kiểu in hoa-thường

using namespace std;
MCQ::MCQ(int id, const string& prompt, int points, const vector<string>& options, const string& correctOptionStr)
    : Question(id, prompt, points), options(options) {
    if (!correctOptionStr.empty()) {
        correctOption = toupper(correctOptionStr[0]);
    }
    else {
        correctOption = 'A';
    }
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

bool MCQ::checkAnswer(const string& answer) const {

    if (answer.empty()) return false;

    if (toupper(answer[0]) == correctOption) {
        return true;
    }
    else {
        return false;
    }
}
