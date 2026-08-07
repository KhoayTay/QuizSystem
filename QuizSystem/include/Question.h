#pragma once
#include <string>

class Question {

protected:
    int id;
    std::string prompt;
    int points;

public:
    Question(int id, const std::string& prompt, int points);
    virtual ~Question() = default;
    virtual void display() const = 0;

    //TF,MCQ answer
    virtual bool checkAnswer(const std::string& answer) const = 0;

    //QuizEngine
    int getId() const;
    int getPoints() const;
    //Getter
    std::string getPrompt() const;

    //Setter
    void setPrompt(const std::string& newPrompt);
    void setPoints(int newPoints);
};
