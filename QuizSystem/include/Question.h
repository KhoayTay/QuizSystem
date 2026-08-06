#pragma once
#include <string>

class Question {

protected:
    int id;
    std::string prompt;
    int points;
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
};
