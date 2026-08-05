#pragma once

#include "Quiz.h"
#include "DataFileManager.h"

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

class QuizManager {
public:
    bool loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const; 
    bool create(int quizId, const std::string& title);
    bool rename(int quizId, const std::string& newTitle);
    bool remove(int quizId);
    void display(std::ostream& output) const;

    const Quiz* findQuizById(int quizId) const;

    bool addQuestion(int quizId, int questionId);
    bool removeQuestion(int quizId, int questionId);
    std::size_t removeQuestionFromAllQuizzes(int questionId);

    bool containsQuizId(int quizId) const;
    bool containsTitle(const std::string& title) const;
    bool isEmpty() const;

    std::size_t getQuizCount() const;

    const std::vector<Quiz>& getQuizzes() const;
    const std::string& getLastError() const;

private:
    Quiz* findQuizByIdMutable(int quizId);

    bool isTitleUsedByAnotherQuiz(
        const std::string& title,
        int excludedQuizId) const;

    bool fail(const std::string& message);
    void clearError();

    std::vector<Quiz> quizzes_;
    std::string lastError_;
};