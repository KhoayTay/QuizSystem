#pragma once
#include "Question.h"
#include <string>

class MCQ : public Question {
private:
    std::string options;//fix từ char thành 1 string chứa ABCD
    char correctOption;

public:
    MCQ(int id, const std::string& prompt, int points, const std::string& options, char correctOption);

    ~MCQ() override = default;

    void display() const override;
    bool checkAnswer(const std::string& answer) const override;
};
