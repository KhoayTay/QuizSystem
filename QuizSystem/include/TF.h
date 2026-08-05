#pragma once
#include "Question.h"
#include <string>

class TF : public Question {
private:
    bool correctAnswer;

public:
    TF(int id, const std::string& prompt, int points, const std::string& correctAnswerStr);
    ~TF() override = default;

    void display() const override;
    bool checkAnswer(const std::string& answer) const override;
};
