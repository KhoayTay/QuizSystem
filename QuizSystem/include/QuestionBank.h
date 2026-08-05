#ifndef QUESTION_BANK_H
#define QUESTION_BANK_H

#include "../include/DataFileManager.h"
#include "../include/Question.h"
#include "../include/MCQ.h"
#include "../include/TF.h"
#include <string>
#include <vector>

class QuestionBank {
private:
    std::vector<Question*> questions;
    static const int MAX_QUESTIONS = 100;

    bool existsId(int id) const; // Kiem tra ID da ton tai chua
    int  indexId(int id) const;  // Tim vi tri cua cau hoi theo ID

public:
    QuestionBank();
    ~QuestionBank();

    QuestionBank(const QuestionBank&) = delete;
    QuestionBank& operator=(const QuestionBank&) = delete;

    // Them cau hoi MCQ 
    bool addMCQ(int id, const std::string& prompt, int points,
                const std::vector<std::string>& options,
                const std::string& correctOption, std::string& errorMsg);

    // Them cau hoi TF
    bool addTF(int id, const std::string& prompt, int points,
               bool correctAnswer, std::string& errorMsg);

    // Tim theo ID
    Question* findById(int id) const;

    // Tim theo mot phan prompt, khong phan biet hoa/thuong
    std::vector<Question*> findByPromptContains(const std::string& keyword) const;

    // Cap nhat prompt/points cua cau hoi da ton tai
    bool updateQuestion(int id, const std::string& newPrompt, int newPoints,
                         std::string& errorMsg);

    // Xoa cau hoi theo ID
    bool removeQuestion(int id);

    // Nap du lieu tu file questions.txt qua DataFileManager
    int loadFromFile(const std::string& filename, std::vector<std::string>& warnings);
};

#endif