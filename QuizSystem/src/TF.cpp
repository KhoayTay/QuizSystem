#include "../include/TF.h"
#include <iostream>
#include <cctype>

using namespace std;
TF::TF(int id, const string& prompt, int points, const string& correctAnswerStr)
    : Question(id, prompt, points) {

    // Ép kiểu từ string sang bool an toàn
    if (!correctAnswerStr.empty() && (toupper(correctAnswerStr[0]) == 'T' || correctAnswerStr == "1")) {
        correctAnswer = true;
    }
    else {
        correctAnswer = false;
    }
}
void TF::display() const {
    cout << "Câu " << getId() << ": " << prompt << " (" << getPoints() << " diem)\n";
    cout << "[ Vui long chon True (T) hoac False (F) ]\n";
}

bool TF::checkAnswer(const string& answer) const {
    // Không nhập gì sẽ tính là false
    if (answer.empty()) {
        return false;
    }

    // Lấy ký tự đầu tiên của câu trả lời và chuyển thành chữ in hoa
    char firstLetter = toupper(answer[0]);
    bool userAnswerBool;
    // So sanh T với F để xác định true false
    if (firstLetter == 'T' || firstLetter == '1') {
        userAnswerBool = true;
    }
    else {
        userAnswerBool = false;
    }
    if (userAnswerBool == correctAnswer) {
        return true;
    }
    else {
        return false;
    }
}
