#pragma once
#include "Question.h"
#include <string>

class TF : public Question {
public:
    TF(int id, const std::string& prompt, int points, const std::string& correctOptionStr);
    ~TF() override = default;

    void display() const override;
};
