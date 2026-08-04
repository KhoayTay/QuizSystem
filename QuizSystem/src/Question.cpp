#include "../include/Question.h"

using namespace std;
Question::Question(int id, const string& prompt, int points)
    : id(id), prompt(prompt), points(points) {
}

int Question::getId() const {
    return id;
}

int Question::getPoints() const {
    return points;
}
