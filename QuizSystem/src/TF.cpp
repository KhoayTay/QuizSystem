#include "..include/TF.h"
#include <iostream>

using namespace std;
TF::TF(int id, const string& prompt, int points, bool correctAnswer)
    : Question(id, prompt, points), correctAnswer(correctAnswer) {
}

void TF::display() const {

}
bool TF::checkAnswer(const string& answer) const {

    return false;
}
