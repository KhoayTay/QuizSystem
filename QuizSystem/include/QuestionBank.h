#ifndef QUESTION_BANK_H
#define QUESTION_BANK_H

#include "../include/Question.h"
#include "../include/MCQ.h"
#include "../include/TF.h"
#include <string>
#include <vector>

class QuestionBank {
private:
    std::vector<Question*> questions;

    static const int MAX_QUESTIONS = 100; 

    bool existsId(int id) const; // kiem tra id da ton tai chua
    int  indexId(int id) const; // tra ve vi tri cua cau hoi co id

public:
    QuestionBank();
    ~QuestionBank();

    // Khong cho copy de tranh 2 QuestionBank cung so huu (va cung delete)
    // chung 1 tap Question* -> double free.
    QuestionBank(const QuestionBank&) = delete;
    QuestionBank& operator=(const QuestionBank&) = delete;

    // ------------------------- ADD -------------------------
    bool addMCQ(int id, const std::string& prompt, int points,
                const std::string& optA, const std::string& optB,
                const std::string& optC, const std::string& optD,
                char correctOption, std::string& errorMsg);

    bool addTF(int id, const std::string& prompt, int points,
               bool correctAnswer, std::string& errorMsg);

    // ------------------------- SEARCH -------------------------
    Question* findById(int id) const;

    // ------------------------- UPDATE -------------------------
    bool updateQuestion(int id, const std::string& newPrompt, int newPoints,
                         std::string& errorMsg);

    // ------------------------- REMOVE -------------------------
    bool removeQuestion(int id);
 
};

#endif