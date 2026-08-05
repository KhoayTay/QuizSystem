#include "../include/TF.h"
#include <iostream>
#include <cctype> // Thư viện để dùng hàm toupper()

using namespace std;

TF::TF(int id, const string& prompt, int points, bool correctAnswer)
    : Question(id, prompt, points), correctAnswer(correctAnswer) {
}

void TF::display() const {
    cout << "Câu " << getId() << ": " << prompt << " (" << getPoints() << " diem)\n";
    cout << "[ Vui long chon True (T) hoac False (F) ]\n";
}

bool TF::checkAnswer(const string& answer) const {
    //không nhập gì sẽ tính là false
    if (answer.empty()) return false;

    // Lấy ký tự đầu tiên của câu trả lời và chuyển thành chữ in hoa
    char firstLetter = toupper(answer[0]);

    bool userAnswerBool;

    // So sanh T với F để xác định true false
    if (firstLetter == 'T' || firstLetter == '1') {
        userAnswerBool = true;
    }
    else if (firstLetter == 'F' || firstLetter == '0') {
        userAnswerBool = false;
    }
    else {//trường hợp sai cú pháp sẽ tự tính là false
        return false;
    }
    return userAnswerBool == correctAnswer;
}
