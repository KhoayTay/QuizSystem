#include "..include/MCQ.h"
#include <iostream>

using namespace std;

MCQ::MCQ(int id, const string& prompt, int points,
    const string& optA, const string& optB,
    const string& optC, const string& optD,
    char correctOption)
    : Question(id, prompt, points), correctOption(correctOption) { // ABCD to MCQ.h
    
}
void MCQ::display() const {
  
}

bool MCQ::checkAnswer(const string& answer) const {
    return false; 
}
