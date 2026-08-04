#pragma once
#include "Question.h"
#include <string>

class TF : public Question {
private:
    bool correctAnswer;//true,false

public:
    TF(int id, const std::string& prompt, int points, bool correctAnswer);
    void display() const override;
    bool checkAnswer(const std::string& answer) const override;
};
