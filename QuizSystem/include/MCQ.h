#pragma once
#include "../include/Question.h"
#include <string>
class MCQ : public Question {
private:
    std::string options[4]; //ABCD
    char correctOption;
public:
    MCQ(int id, const std::string& prompt, int points,
        const std::string& optA, const std::string& optB,
        const std::string& optC, const std::string& optD,
        char correctOption);

    void display() const override;
    bool checkAnswer(const std::string& answer) const override;
};
