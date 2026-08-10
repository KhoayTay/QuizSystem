#pragma once

#include "Question.h"
#include "QuestionBank.h"
#include "QuizManager.h"

#include <cstddef>
#include <string>
#include <vector>

enum class AttemptState
{
    NOT_STARTED,
    IN_PROGRESS,
    SUBMITTED
};

class QuizEngine
{
public:
    QuizEngine();

    bool start(const Quiz &quiz, const QuestionBank &questionBank);
    bool next();
    bool previous();
    bool answerCurrent(const std::string &answer);
    bool submit();

    void displayCurrentQuestion() const;
    void displayResult() const;
    bool pickAQuiz(const QuizManager &quizManager, const QuestionBank &questionBank);

    AttemptState getState() const;
    int getScore() const;
    std::size_t getCurrentIndex() const;
    std::size_t getQuestionCount() const;

private:
    bool hasCurrentQuestion() const;
    bool isCorrectAnswer(const std::string &userAnswer, const std::string &correctAnswer) const;
    void reset();

    AttemptState state_;
    std::vector<Question *> questions_;
    std::vector<std::string> answers_;
    std::size_t currentIndex_;
    int score_;
};
