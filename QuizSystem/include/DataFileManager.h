#ifndef DATAFILEMANAGER_H
#define DATAFILEMANAGER_H

#include <string>
#include <vector>

struct ParsedQuestion {
	std::string type;
	int id;
	int points;
	std::string prompt;
	std::vector<std::string> options;		//MCQ only
	std::string correctAnswer;
};

struct ParsedQuiz {
	int quizID;
	std::string title;
	std::vector<int> questionIDs;
};

class DataFileManager {
public:
	static std::vector<ParsedQuestion> loadQuestions(const std::string& filename);
	static std::vector<ParsedQuiz> loadQuizzes(const std::string& filename);

	static void saveQuestions(const std::string& filename, const std::vector<ParsedQuestion>& data);
	static void saveQuizzes(const std::string& filename, const std::vector<ParsedQuiz>& data);
};

#endif