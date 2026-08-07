#pragma once
#include <string>
#include <vector>

class Question {

protected:
    int id;
    int points;
    std::string prompt;
    std::string correctAnswer;

public:
    Question(int id, const std::string& prompt, int points, const std::string& correctAnswer);
    virtual ~Question() = default;
    virtual void display() const = 0;
    //Getter
    int getId() const;
    int getPoints() const;

    std::string getPrompt() const;
    std::string getAnswer() const;

    //Setter
    void setPrompt(const std::string& newPrompt);
    void setPoints(int newPoints);
    void setAnswer(const std::string& newAnswer);//MCQ,TF
    virtual void setOptions(const std::vector<std::string>& newOptions) {//MCQ
};
