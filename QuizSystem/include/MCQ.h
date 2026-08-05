#pragma once
#include "Question.h"
#include <string>
#include <vector>

class MCQ : public Question {
private:
    std::vector<std::string> options;
    char correctOption;

public:
    MCQ(int id, const std::string& prompt, int points, const std::vector<std::string>& options, const std::string& correctOption);
    ~MCQ() override = default;

    void display() const override;
    bool checkAnswer(const std::string& answer) const override;
};
