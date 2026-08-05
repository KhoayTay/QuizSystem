#include "QuizManager.h"

#include <algorithm>
#include <ostream>

bool QuizManager::create(int quizId, const std::string& title) {
    clearError();

    if (!Quiz::isValidId(quizId)) {
        return fail("Quiz ID must be a positive integer.");
    }

    if (!Quiz::isValidTitle(title)) {
        return fail(
            "Quiz title must not be empty or contain '|', ',' or ';'.");
    }

    if (containsQuizId(quizId)) {
        return fail("Quiz ID already exists.");
    }

    if (containsTitle(title)) {
        return fail("Quiz title already exists.");
    }

    quizzes_.push_back(Quiz(quizId, title));
    return true;
}

bool QuizManager::rename(int quizId, const std::string& newTitle) {
    clearError();

    Quiz* quiz = findQuizByIdMutable(quizId);

    if (quiz == 0) {
        return fail("Quiz ID was not found.");
    }

    if (!Quiz::isValidTitle(newTitle)) {
        return fail(
            "Quiz title must not be empty or contain '|', ',' or ';'.");
    }

    if (isTitleUsedByAnotherQuiz(newTitle, quizId)) {
        return fail("Quiz title already exists.");
    }

    if (!quiz->setTitle(newTitle)) {
        return fail("Quiz title is invalid.");
    }

    return true;
}

bool QuizManager::remove(int quizId) {
    clearError();

    std::vector<Quiz>::iterator position = std::find_if(
        quizzes_.begin(),
        quizzes_.end(),
        [quizId](const Quiz& quiz) {
            return quiz.getId() == quizId;
        });

    if (position == quizzes_.end()) {
        return fail("Quiz ID was not found.");
    }

    quizzes_.erase(position);
    return true;
}

void QuizManager::display(std::ostream& output) const {
    if (quizzes_.empty()) {
        output << "No quizzes available.\n";
        return;
    }

    for (std::size_t index = 0; index < quizzes_.size(); ++index) {
        quizzes_[index].display(output);
    }
}

Quiz* QuizManager::findQuizByIdMutable(int quizId) {
    std::vector<Quiz>::iterator position = std::find_if(
        quizzes_.begin(),
        quizzes_.end(),
        [quizId](const Quiz& quiz) {
            return quiz.getId() == quizId;
        });

    if (position == quizzes_.end()) {
        return 0;
    }

    return &(*position);
}

const Quiz* QuizManager::findQuizById(int quizId) const {
    std::vector<Quiz>::const_iterator position = std::find_if(
        quizzes_.begin(),
        quizzes_.end(),
        [quizId](const Quiz& quiz) {
            return quiz.getId() == quizId;
        });

    if (position == quizzes_.end()) {
        return 0;
    }

    return &(*position);
}

bool QuizManager::addQuestion(int quizId, int questionId) {
    clearError();

    Quiz* quiz = findQuizByIdMutable(quizId);

    if (quiz == 0) {
        return fail("Quiz ID was not found.");
    }

    if (questionId <= 0) {
        return fail("Question ID must be a positive integer.");
    }

    if (quiz->containsQuestion(questionId)) {
        return fail("Question ID already exists in this Quiz.");
    }

    if (!quiz->addQuestion(questionId)) {
        return fail("Question could not be added to the Quiz.");
    }

    return true;
}

bool QuizManager::removeQuestion(int quizId, int questionId) {
    clearError();

    Quiz* quiz = findQuizByIdMutable(quizId);

    if (quiz == 0) {
        return fail("Quiz ID was not found.");
    }

    if (!quiz->removeQuestion(questionId)) {
        return fail("Question ID was not found in this Quiz.");
    }

    return true;
}

std::size_t QuizManager::removeQuestionFromAllQuizzes(int questionId) {
    clearError();

    std::size_t affectedQuizCount = 0;

    for (std::vector<Quiz>::iterator quiz = quizzes_.begin();
         quiz != quizzes_.end();
         ++quiz) {
        if (quiz->removeQuestion(questionId)) {
            ++affectedQuizCount;
        }
    }

    return affectedQuizCount;
}

bool QuizManager::containsQuizId(int quizId) const {
    return findQuizById(quizId) != 0;
}

bool QuizManager::containsTitle(const std::string& title) const {
    return isTitleUsedByAnotherQuiz(title, 0);
}

bool QuizManager::isEmpty() const {
    return quizzes_.empty();
}

std::size_t QuizManager::getQuizCount() const {
    return quizzes_.size();
}

const std::vector<Quiz>& QuizManager::getQuizzes() const {
    return quizzes_;
}

const std::string& QuizManager::getLastError() const {
    return lastError_;
}

bool QuizManager::isTitleUsedByAnotherQuiz(
    const std::string& title,
    int excludedQuizId) const {

    if (!Quiz::isValidTitle(title)) {
        return false;
    }

    const std::string normalizedTitle = Quiz::normalizeTitle(title);

    return std::find_if(
        quizzes_.begin(),
        quizzes_.end(),
        [&normalizedTitle, excludedQuizId](const Quiz& quiz) {
            return quiz.getId() != excludedQuizId
                && quiz.getTitle() == normalizedTitle;
        }) != quizzes_.end();
}

bool QuizManager::fail(const std::string& message) {
    lastError_ = message;
    return false;
}

void QuizManager::clearError() {
    lastError_.clear();
}
bool QuizManager::loadFromFile(const std::string& filename) {
    clearError();

    std::vector<ParsedQuiz> parsedQuizzes =
        DataFileManager::loadQuizzes(filename);

    quizzes_.clear();

    for (const ParsedQuiz& parsedQuiz : parsedQuizzes) {
        if (!create(parsedQuiz.quizID, parsedQuiz.title)) {
            return false;
        }

        for (int questionId : parsedQuiz.questionIDs) {
            if (!addQuestion(parsedQuiz.quizID, questionId)) {
                return false;
            }
        }
    }

    return true;
}
void QuizManager::saveToFile(const std::string& filename) const {
    std::vector<ParsedQuiz> parsedQuizzes;

    for (const Quiz& quiz : quizzes_) {
        ParsedQuiz parsedQuiz{};

        parsedQuiz.quizID = quiz.getId();
        parsedQuiz.title = quiz.getTitle();
        parsedQuiz.questionIDs = quiz.getQuestionIds();

        parsedQuizzes.push_back(parsedQuiz);
    }

    DataFileManager::saveQuizzes(filename, parsedQuizzes);
}