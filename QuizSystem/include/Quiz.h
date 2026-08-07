#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

class Quiz {
public:
    int getId() const;
    const std::string& getTitle() const;
    const std::vector<int>& getQuestionIds() const;
    std::size_t getQuestionCount() const;

    bool containsQuestion(int questionId) const;
    bool isEmpty() const;
    bool isValid() const;

    void display(std::ostream& output) const;

    static bool isValidId(int id);
    static bool isValidTitle(const std::string& title);
    static std::string normalizeTitle(const std::string& title);

private:
    friend class QuizManager;

    Quiz(int id, const std::string& title);

    bool setTitle(const std::string& title);
    bool addQuestion(int questionId);
    bool removeQuestion(int questionId);

    int id_;
    std::string title_;
    std::vector<int> questionIds_;
};
