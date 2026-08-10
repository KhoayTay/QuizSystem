#include "../include/TF.h"
#include <iostream>

using namespace std;
TF::TF(int id, const string& prompt, int points, const string& correctAnswerStr)
    : Question(id, prompt, points, correctAnswerStr) {}

void TF::display() const {
    cout << "Cau " << getId() << ": " << prompt << " (" << getPoints() << " diem)\n";
    cout << "[ Vui long chon True (T) hoac False (F) ]\n";
}
