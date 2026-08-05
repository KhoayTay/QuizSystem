#include "../include/Quiz.h"

#include <algorithm>
#include <cctype>
#include <ostream>

Quiz::Quiz(int id, const std::string& title)
    : id_(id), title_(normalizeTitle(title)) {
}

int Quiz::getId() const {
    return id_;
}

const std::string& Quiz::getTitle() const {
    return title_;
}

const std::vector<int>& Quiz::getQuestionIds() const {
    return questionIds_;
}

std::size_t Quiz::getQuestionCount() const {
    return questionIds_.size();
}

bool Quiz::setTitle(const std::string& title) {
    if (!isValidTitle(title)) {
        return false;
    }

    title_ = normalizeTitle(title);
    return true;
}

bool Quiz::addQuestion(int questionId) {
    if (questionId <= 0 || containsQuestion(questionId)) {
        return false;
    }

    questionIds_.push_back(questionId);
    return true;
}

bool Quiz::removeQuestion(int questionId) {
    std::vector<int>::iterator position = std::find(
        questionIds_.begin(), questionIds_.end(), questionId);

    if (position == questionIds_.end()) {
        return false;
    }

    questionIds_.erase(position);
    return true;
}

bool Quiz::containsQuestion(int questionId) const {
    return std::find(questionIds_.begin(), questionIds_.end(), questionId)
        != questionIds_.end();
}

bool Quiz::isEmpty() const {
    return questionIds_.empty();
}

bool Quiz::isValid() const {
    return isValidId(id_) && isValidTitle(title_);
}

void Quiz::display(std::ostream& output) const {
    output << id_ << '|'
           << title_ << '|';

    for (std::size_t index = 0; index < questionIds_.size(); ++index) {
        if (index > 0) {
            output << ',';
        }

        output << questionIds_[index];
    }

    output << '\n';
}

bool Quiz::isValidId(int id) {
    return id > 0;
}

bool Quiz::isValidTitle(const std::string& title) {
    const std::string normalized = normalizeTitle(title);
    return !normalized.empty()
        && normalized.find_first_of("|,;") == std::string::npos;
}

// xóa khoảng trắng đầu và cuối của title
std::string Quiz::normalizeTitle(const std::string& title) {
    std::string::const_iterator first = std::find_if(
        title.begin(), title.end(),
        [](unsigned char character) { return !std::isspace(character); });

    if (first == title.end()) {
        return "";
    }

    std::string::const_reverse_iterator last = std::find_if(
        title.rbegin(), title.rend(),
        [](unsigned char character) { return !std::isspace(character); });

    return std::string(first, last.base());
}
