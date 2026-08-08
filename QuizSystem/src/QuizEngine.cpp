#include "../include/QuizEngine.h"
#include "../include/DataFileManager.h"
#include "../include/QuizManager.h"

#include <iostream>
#include <cctype>
#include <limits>

using namespace std;

QuizEngine::QuizEngine()
    : state_(AttemptState::NOT_STARTED),
      currentIndex_(0),
      score_(0)
{
}

bool QuizEngine::start(const Quiz &quiz, const QuestionBank &questionBank)
{
    reset();

    if (quiz.isEmpty())
    {
        return false;
    }

    const vector<int> &questionIds = quiz.getQuestionIds();

    for (int questionId : questionIds)
    {
        Question *question = questionBank.findById(questionId);

        if (question == nullptr)
        {
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

bool QuizEngine::next()
{
    if (state_ != AttemptState::IN_PROGRESS || !hasCurrentQuestion())
    {
        return false;
    }

    if (currentIndex_ + 1 >= questions_.size())
    {
        return false;
    }

    ++currentIndex_;
    return true;
}

bool QuizEngine::previous()
{
    if (state_ != AttemptState::IN_PROGRESS || !hasCurrentQuestion())
    {
        return false;
    }

    if (currentIndex_ == 0)
    {
        return false;
    }

    --currentIndex_;
    return true;
}

bool QuizEngine::answerCurrent(const string &answer)
{
    if (state_ != AttemptState::IN_PROGRESS || !hasCurrentQuestion())
    {
        return false;
    }

    answers_[currentIndex_] = answer;
    return true;
}

bool QuizEngine::submit()
{
    if (state_ != AttemptState::IN_PROGRESS)
    {
        return false;
    }

    score_ = 0;

    for (size_t index = 0; index < questions_.size(); ++index)
    {
        if (!answers_[index].empty() &&
            isCorrectAnswer(answers_[index], questions_[index]->getAnswer()))
        {
            score_ += questions_[index]->getPoints();
        }
    }

    state_ = AttemptState::SUBMITTED;
    return true;
}

void QuizEngine::displayCurrentQuestion() const
{
    if (!hasCurrentQuestion())
    {
        cout << "No current question.\n";
        return;
    }

    cout << "Question " << currentIndex_ + 1
         << "/" << questions_.size() << ":\n";
    questions_[currentIndex_]->display();

    cout << "Current answer: ";
    if (answers_[currentIndex_].empty())
    {
        cout << "(empty)";
    }
    else
    {
        cout << answers_[currentIndex_];
    }
    cout << "\n";
}

void QuizEngine::displayResult() const
{
    if (state_ != AttemptState::SUBMITTED)
    {
        cout << "Quiz has not been submitted yet.\n";
        return;
    }

    cout << "Score: " << score_ << "\n";

    for (size_t index = 0; index < questions_.size(); ++index)
    {
        const bool isCorrect = !answers_[index].empty() &&
                               isCorrectAnswer(answers_[index], questions_[index]->getAnswer());

        cout << "Question ID " << questions_[index]->getId()
             << ": " << (isCorrect ? "Correct" : "Incorrect")
             << " | Your answer: ";

        if (answers_[index].empty())
        {
            cout << "(empty)";
        }
        else
        {
            cout << answers_[index];
        }

        cout << "\n";
    }
}

bool QuizEngine::pickAQuiz(const QuizManager &quizManager, const QuestionBank &questionBank)
{
    if (quizManager.isEmpty())
    {
        cout << "No quizzes available to take.\n";
        return false;
    }

    cout << "\nAvailable quizzes:\n";
    const vector<Quiz> &quizzes = quizManager.getQuizzes();
    for (const Quiz &quiz : quizzes)
    {
        cout << quiz.getId() << ". " << quiz.getTitle()
             << " (" << quiz.getQuestionCount() << " questions)\n";
    }

    cout << "Choose quiz ID: ";
    int selectedQuizId = 0;
    if (!(cin >> selectedQuizId))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid quiz ID.\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    const Quiz *selectedQuiz = quizManager.findQuizById(selectedQuizId);
    if (selectedQuiz == nullptr)
    {
        cout << "Quiz ID was not found.\n";
        return false;
    }

    if (selectedQuiz->isEmpty())
    {
        cout << "Cannot start an empty quiz.\n";
        return false;
    }

    if (!start(*selectedQuiz, questionBank))
    {
        cout << "Could not start quiz. Please check question IDs.\n";
        return false;
    }

    // --- Vòng lặp làm bài thi giữ y nguyên ---
    while (getState() == AttemptState::IN_PROGRESS)
    {
        cout << "\n";
        displayCurrentQuestion();

        cout << "Enter answer, N-next, P-previous, S-submit: ";
        string input;
        getline(cin, input);

        size_t first = input.find_first_not_of(" \t");
        size_t last = input.find_last_not_of(" \t");

        if (first == string::npos)
        {
            cout << "Please enter an answer or command.\n";
            continue;
        }

        input = input.substr(first, last - first + 1);
        char command = static_cast<char>(toupper(static_cast<unsigned char>(input[0])));

        if (command == 'N' && input.size() == 1)
        {
            if (!next())
            {
                cout << "Already at the last question.\n";
            }
        }
        else if (command == 'P' && input.size() == 1)
        {
            if (!previous())
            {
                cout << "Already at the first question.\n";
            }
        }
        else if (command == 'S' && input.size() == 1)
        {
            submit();
        }
        else
        {
            answerCurrent(input);
            if (getCurrentIndex() + 1 < getQuestionCount())
            {
                next();
            }
        }
    }

    if (getState() == AttemptState::IN_PROGRESS)
    {
        submit();
    }

    cout << "\nResult:\n";
    displayResult();

    return true;
}

AttemptState QuizEngine::getState() const
{
    return state_;
}

int QuizEngine::getScore() const
{
    return score_;
}

size_t QuizEngine::getCurrentIndex() const
{
    return currentIndex_;
}

size_t QuizEngine::getQuestionCount() const
{
    return questions_.size();
}

bool QuizEngine::hasCurrentQuestion() const
{
    return !questions_.empty() && currentIndex_ < questions_.size();
}

bool QuizEngine::isCorrectAnswer(const string &userAnswer, const string &correctAnswer) const
{
    string user = userAnswer;
    string correct = correctAnswer;

    size_t first = user.find_first_not_of(" \t");
    size_t last = user.find_last_not_of(" \t");
    if (first == string::npos)
    {
        return false;
    }
    user = user.substr(first, last - first + 1);

    first = correct.find_first_not_of(" \t");
    last = correct.find_last_not_of(" \t");
    if (first == string::npos)
    {
        return false;
    }
    correct = correct.substr(first, last - first + 1);

    for (char &c : user)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    for (char &c : correct)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    if (user == "t")
    {
        user = "true";
    }
    else if (user == "f")
    {
        user = "false";
    }

    if (correct == "t")
    {
        correct = "true";
    }
    else if (correct == "f")
    {
        correct = "false";
    }

    return user == correct;
}

void QuizEngine::reset()
{
    state_ = AttemptState::NOT_STARTED;
    questions_.clear();
    answers_.clear();
    currentIndex_ = 0;
    score_ = 0;
}
