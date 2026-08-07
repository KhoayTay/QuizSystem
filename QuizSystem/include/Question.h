#pragma once
#include <string>

class Question {

protected:
    int id;
    std::string prompt;
    int points;
	std::string correctAnswer; // For TF and MCQ, store the correct answer as a string

public:
    Question(int id, const std::string& prompt, int points);
    virtual ~Question() = default;
    virtual void display() const = 0;

    //TF,MCQ answer
    virtual bool checkAnswer(const std::string& answer) const = 0;

    //Getter
    int getId() const;
    int getPoints() const;
    std::string getPrompt() const;
	virtual std::string getAnswer() const; // For TF and MCQ, return the correct answer as a string

    //Setter
    void setPrompt(const std::string& newPrompt);
    void setPoints(int newPoints);
};
