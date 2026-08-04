#include "../include/QuestionBank.h"
#include <cctype>
#include <iostream>

using namespace std;

QuestionBank::QuestionBank() {
}

QuestionBank::~QuestionBank() {
    for (Question* q : questions) {
        delete q;
    }
    questions.clear();
}

bool QuestionBank::existsId(int id) const {
    return indexId(id) != -1;
}
 
int QuestionBank::indexId(int id) const {
    for (size_t i = 0; i < questions.size(); ++i) {
        if (questions[i]->getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// ============================================================================
//  ADD
// ============================================================================
bool QuestionBank::addMCQ(int id, const string& prompt, int points,
                           const string& optA, const string& optB,
                           const string& optC, const string& optD,
                           char correctOption, string& errorMsg) {
    if (static_cast<int>(questions.size()) >= MAX_QUESTIONS) {
        errorMsg = "Da dat gioi han " + to_string(MAX_QUESTIONS) + " cau hoi.";
        return false;
    }
    if (id <= 0) {
        errorMsg = "ID phai la so nguyen duong.";
        return false;
    }
    if (existsId(id)) {
        errorMsg = "ID " + to_string(id) + " da ton tai trong Question Bank.";
        return false;
    }
    if (prompt.empty()) {
        errorMsg = "Prompt khong duoc rong.";
        return false;
    }
    if (points <= 0) {
        errorMsg = "Points phai lon hon 0.";
        return false;
    }
    if (optA.empty() || optB.empty() || optC.empty() || optD.empty()) {
        errorMsg = "Ca 4 lua chon (A-D) khong duoc rong.";
        return false;
    }
    char normalized = static_cast<char>(toupper(static_cast<unsigned char>(correctOption)));
    if (normalized != 'A' && normalized != 'B' && normalized != 'C' && normalized != 'D') {
        errorMsg = "correctOption phai thuoc A-D.";
        return false;
    }
    
    questions.push_back(new MCQ(id, prompt, points, optA, optB, optC, optD, normalized));
    return true;
}
 
bool QuestionBank::addTF(int id, const string& prompt, int points,
                          bool correctAnswer, string& errorMsg) {
    if (static_cast<int>(questions.size()) >= MAX_QUESTIONS) {
        errorMsg = "Da dat gioi han " + to_string(MAX_QUESTIONS) + " cau hoi.";
        return false;
    }
    if (id <= 0) {
        errorMsg = "ID phai la so nguyen duong.";
        return false;
    }
    if (existsId(id)) {
        errorMsg = "ID " + to_string(id) + " da ton tai trong Question Bank.";
        return false;
    }
    if (prompt.empty()) {
        errorMsg = "Prompt khong duoc rong.";
        return false;
    }
    if (points <= 0) {
        errorMsg = "Points phai lon hon 0.";
        return false;
    }
 
    questions.push_back(new TF(id, prompt, points, correctAnswer));
    return true;
}

// ============================================================================
//  SEARCH
// ============================================================================
Question* QuestionBank::findById(int id) const {
    int idx = indexId(id);
    if (idx == -1) return nullptr;
    return questions[static_cast<size_t>(idx)];
}

// ============================================================================
//  UPDATE
// ============================================================================
bool QuestionBank::updateQuestion(int id, const string& newPrompt, int newPoints,
                                   string& errorMsg) {
}

// ============================================================================
//  REMOVE
// ============================================================================
bool QuestionBank::removeQuestion(int id) {
    int idx = indexId(id);
    if (idx == -1) {
        return false;
    }
    delete questions[static_cast<size_t>(idx)];
    questions.erase(questions.begin() + idx);
    return true;
}
