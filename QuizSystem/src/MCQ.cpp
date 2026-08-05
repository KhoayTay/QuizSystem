#include "../include/MCQ.h"
#include <iostream>

using namespace std;
MCQ::MCQ(int id, const string& prompt, int points, const string& options, char correctOption)
    : Question(id, prompt, points), options(options), correctOption(correctOption) {
}
void MCQ::display() const {
    cout << "Câu " << getId() << ": " << prompt << " (" << getPoints() << " diem)\n";
    cout << options << "\n";
}
bool MCQ::checkAnswer(const string& answer) const {
    //không nhập gì sẽ tính là false
    if (answer.empty()) return false;
    //So sánh Answer với char correctoption trả về gtri tương ứng
    if (toupper(answer[0]) == toupper(correctOption)) {
        return true;
    }
    else {
        return false;
    }
}
