#include "../include/QuestionBank.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <iomanip>
 
using namespace std;
 
namespace {
    string toLowerStr(const string& text) {
        string result = text;
        transform(result.begin(), result.end(), result.begin(),
                  [](unsigned char c) { return tolower(c); });
        return result;
    }
}
 
QuestionBank::QuestionBank() {
}
 
QuestionBank::~QuestionBank() {
    for (Question* q : questions) delete q;
    questions.clear();
}
 
// Kiem tra id da ton tai
bool QuestionBank::existsId(int id) const {
    return findIndexId(id) != -1;
}
 
// Tim vi tri cau hoi theo id
int QuestionBank::findIndexId(int id) const {
    for (size_t i = 0; i < questions.size(); ++i) {
        if (questions[i]->getId() == id) return static_cast<int>(i);
    }
    return -1;
}
 
// Them MCQ
bool QuestionBank::addMCQ(int id, const string& prompt, int points,
                           const vector<string>& options,
                           const string& correctOption, string& errorMsg) {
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
    if (options.size() != 4) {
        errorMsg = "MCQ phai co dung 4 lua chon.";
        return false;
    }
    for (const string& opt : options) {
        if (opt.empty()) {
            errorMsg = "Lua chon khong duoc rong.";
            return false;
        }
    }
    if (correctOption.empty()) {
        errorMsg = "correctOption khong duoc rong.";
        return false;
    }
    char c = static_cast<char>(toupper(static_cast<unsigned char>(correctOption[0])));
    if (c < 'A' || c > 'D') {
        errorMsg = "correctOption phai thuoc A-D.";
        return false;
    }
 
    questions.push_back(new MCQ(id, prompt, points, options, correctOption));
    return true;
}
 
// Them TF
bool QuestionBank::addTF(int id, const string& prompt, int points,
                          const string& correctAnswer, string& errorMsg) {
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
 
// Tim theo ID
Question* QuestionBank::findById(int id) const {
    int idx = findIndexId(id);
    if (idx == -1) return nullptr;
    return questions[static_cast<size_t>(idx)];
}
 
// Tim theo mot phan prompt, khong phan biet hoa/thuong
vector<Question*> QuestionBank::findByPromptContains(const string& keyword) const {
    vector<Question*> result;
    string lowerKeyword = toLowerStr(keyword);
    for (Question* q : questions) {
        if (toLowerStr(q->getPrompt()).find(lowerKeyword) != string::npos) {
            result.push_back(q);
        }
    }
    return result;
}
 
// Cap nhat prompt/points 
bool QuestionBank::updateQuestion(int id, const string& newPrompt, int newPoints,
                                   string& errorMsg) {
    int idx = findIndexId(id);
    if (idx == -1) {
        errorMsg = "Khong tim thay cau hoi co ID " + to_string(id) + ".";
        return false;
    }
    if (newPrompt.empty()) {
        errorMsg = "Prompt khong duoc rong.";
        return false;
    }
    if (newPoints <= 0) {
        errorMsg = "Points phai lon hon 0.";
        return false;
    }
 
    Question* q = questions[static_cast<size_t>(idx)];
    q->setPrompt(newPrompt);
    q->setPoints(newPoints);
    return true;
}
 
// Xoa cau hoi theo ID
bool QuestionBank::removeQuestion(int id) {
    int idx = findIndexId(id);
    if (idx == -1) return false;
    delete questions[static_cast<size_t>(idx)];
    questions.erase(questions.begin() + idx);
    return true;
}
 
// Nap du lieu tu file, chuyen ParsedQuestion MCQ/TF that
int QuestionBank::loadFromFile(const string& filename, vector<string>& warnings) {
    vector<ParsedQuestion> parsedList = DataFileManager::loadQuestions(filename);
    int loadedCount = 0;
 
    for (const ParsedQuestion& pq : parsedList) {
        string errorMsg;
        bool added = false;
 
        if (pq.type == "MCQ") {
            if (pq.correctAnswers.empty()) {
                warnings.push_back("ID " + to_string(pq.id) +
                                    ": thieu correctOption, bo qua.");
                continue;
            }
            added = addMCQ(pq.id, pq.prompt, pq.points, pq.options,
                            pq.correctAnswers[0], errorMsg);
 
        } else if (pq.type == "TF") {
            if (pq.correctAnswers.empty()) {
                warnings.push_back("ID " + to_string(pq.id) +
                                    ": thieu correctAnswer, bo qua.");
                continue;
            }
            added = addTF(pq.id, pq.prompt, pq.points, pq.correctAnswers[0], errorMsg);
 
        } else {
            warnings.push_back("ID " + to_string(pq.id) +
                                ": loai cau hoi khong xac dinh ('" + pq.type + "'), bo qua.");
            continue;
        }
 
        if (!added) {
            warnings.push_back("ID " + to_string(pq.id) + ": " + errorMsg + " Bo qua.");
            continue;
        }
        ++loadedCount;
    }
 
    return loadedCount;
}

// Luu toan bo Question Bank ra file, convert Question* nguoc lai thanh ParsedQuestion
bool QuestionBank::saveToFile(const string& filename) const {
    vector<ParsedQuestion> data;

    for (Question* q : questions) {
        ParsedQuestion pq;
        pq.id = q->getId();
        pq.points = q->getPoints();
        pq.prompt = q->getPrompt();
        pq.correctAnswers = { q->getAnswer() }; // dung chung cho ca MCQ va TF

        // Can dynamic_cast de biet la MCQ hay TF.
        // Chi dung de xac dinh type/options khi LUU FILE - khong dung cho logic khac
        MCQ* mcq = dynamic_cast<MCQ*>(q);
        if (mcq != nullptr) {
            pq.type = "MCQ";
            pq.options = mcq->getOptions();
        } else {
            pq.type = "TF";
        }

        data.push_back(pq);
    }

    DataFileManager::saveQuestions(filename, data);
    return true;
}

// Them MCQ, neu thanh cong thi luu luon xuong file
bool QuestionBank::saveMCQ(int id, const string& prompt, int points,
                            const vector<string>& options,
                            const string& correctOption,
                            const string& filename, string& errorMsg) {
    bool added = addMCQ(id, prompt, points, options, correctOption, errorMsg);
    if (!added) {
        return false; // addMCQ da gan errorMsg, khong can lam gi them
    }
    return saveToFile(filename);
}

// Them TF, neu thanh cong thi luu luon xuong file
bool QuestionBank::saveTF(int id, const string& prompt, int points,
                           const string& correctAnswer,
                           const string& filename, string& errorMsg) {
    bool added = addTF(id, prompt, points, correctAnswer, errorMsg);
    if (!added) {
        return false;
    }
    return saveToFile(filename);
}

//in ra toan bo cac question
void QuestionBank::displayAll() const {
    if (questions.empty()) {
        cout << "Question Bank hiện đang trống." << endl;
        return;
    }

    cout << std::left
        << std::setw(6) << "ID"
        << std::setw(8) << "Points"
        << std::setw(10) << "Type"
        << std::setw(40) << "Prompt"
        << std::setw(15) << "Correct"
        << endl;
	cout << std::string(80, '-') << endl;

    for (const Question* q : questions) {
		//ep kieu cau hoi MCQ hoac TF
        const MCQ* mcq = dynamic_cast<const MCQ*>(q);
        const TF* tf = dynamic_cast<const TF*>(q);

        string type = mcq ? "MCQ" : "TF";
        string correct = q->getAnswer();

        cout << std::left
            << std::setw(6) << q->getId()
            << std::setw(8) << q->getPoints()
            << std::setw(10) << type
            << std::setw(40) << q->getPrompt()
            << std::setw(15) << correct
            << endl;

		// in them cac lua chon neu la MCQ
        if (mcq) {
            char optChar = 'A';
            for (const auto& opt : mcq->getOptions()) {
                cout << "   " << optChar++ << ". " << opt << setw(10);
            }
			cout << endl;
        }
    }
}
