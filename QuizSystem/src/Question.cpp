#include "../include/Question.h"

using namespace std;

Question::Question(int id, const string& prompt, int points, const string& correctAnswer)
    : id(id), prompt(prompt), points(points), correctAnswer(correctAnswer) {
}

int Question::getId() const {
    return id;
}

int Question::getPoints() const {
    return points;
}

string Question::getPrompt() const {
    return prompt;
}

void Question::setPrompt(const string& newPrompt) {
    prompt = newPrompt;
}

void Question::setPoints(int newPoints) {
    points = newPoints;
}
string Question::getAnswer() const {
    return correctAnswer;
}