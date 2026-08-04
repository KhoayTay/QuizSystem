#include "../include/QuizEngine.h"

#include <iostream>

using namespace std;

QuizEngine::QuizEngine()
    : state_(AttemptState::NOT_STARTED),
      currentIndex_(0),
      score_(0) {
}

bool QuizEngine::start(const Quiz& quiz, const QuestionBank& questionBank) {
    reset();

    if (quiz.isEmpty()) {
        return false;
    }

    const vector<int>& questionIds = quiz.getQuestionIds();

    for (int questionId : questionIds) {
        Question* question = questionBank.findById(questionId);

        if (question == nullptr) {
            reset();
            return false;
        }

        questions_.push_back(question);
    }

    answers_.assign(questions_.size(), "");
    currentIndex_ = 0;
    score_ = 0;
    state_ = AttemptState::IN_PROGRESS;

    return true;
}

bool QuizEngine::next() {
    if (state_ != AttemptState::IN_PROGRESS || !hasCurrentQuestion()) {
        return false;
    }

    if (currentIndex_ + 1 >= questions_.size()) {
        return false;
    }

    ++currentIndex_;
    return true;
}

bool QuizEngine::previous() {
    if (state_ != AttemptState::IN_PROGRESS || !hasCurrentQuestion()) {
        return false;
    }

    if (currentIndex_ == 0) {
        return false;
    }

    --currentIndex_;
    return true;
}

bool QuizEngine::answerCurrent(const string& answer) {
    if (state_ != AttemptState::IN_PROGRESS || !hasCurrentQuestion()) {
        return false;
    }

    answers_[currentIndex_] = answer;
    return true;
}

bool QuizEngine::submit() {
    if (state_ != AttemptState::IN_PROGRESS) {
        return false;
    }

    score_ = 0;

    for (size_t index = 0; index < questions_.size(); ++index) {
        if (!answers_[index].empty()
            && questions_[index]->checkAnswer(answers_[index])) {
            score_ += questions_[index]->getPoints();
        }
    }

    state_ = AttemptState::SUBMITTED;
    return true;
}

void QuizEngine::displayCurrentQuestion() const {
    if (!hasCurrentQuestion()) {
        cout << "No current question.\n";
        return;
    }

    cout << "Question " << currentIndex_ + 1
         << "/" << questions_.size() << ":\n";
    questions_[currentIndex_]->display();
}

void QuizEngine::displayResult() const {
    if (state_ != AttemptState::SUBMITTED) {
        cout << "Quiz has not been submitted yet.\n";
        return;
    }

    cout << "Score: " << score_ << "\n";

    for (size_t index = 0; index < questions_.size(); ++index) {
        const bool isCorrect = !answers_[index].empty()
            && questions_[index]->checkAnswer(answers_[index]);

        cout << "Question ID " << questions_[index]->getId()
             << ": " << (isCorrect ? "Correct" : "Incorrect")
             << " | Your answer: ";

        if (answers_[index].empty()) {
            cout << "(empty)";
        } else {
            cout << answers_[index];
        }

        cout << "\n";
    }
}

AttemptState QuizEngine::getState() const {
    return state_;
}

int QuizEngine::getScore() const {
    return score_;
}

size_t QuizEngine::getCurrentIndex() const {
    return currentIndex_;
}

size_t QuizEngine::getQuestionCount() const {
    return questions_.size();
}

bool QuizEngine::hasCurrentQuestion() const {
    return !questions_.empty() && currentIndex_ < questions_.size();
}

void QuizEngine::reset() {
    state_ = AttemptState::NOT_STARTED;
    questions_.clear();
    answers_.clear();
    currentIndex_ = 0;
    score_ = 0;
}
