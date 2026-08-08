#pragma once
#include "Question.h"
#include <string>
#include <vector>

class MCQ : public Question {
private:
    std::vector<std::string> options;

public:
    MCQ(int id, const std::string& prompt, int points, const std::vector<std::string>& options, const std::string& correctOptionStr);
    ~MCQ() override = default;

    void display() const override;
    std::vector<std::string> getOptions() const;
    void setOptions(const std::vector<std::string>& newOptions) override;
};
