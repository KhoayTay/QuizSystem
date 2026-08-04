#include <iostream>
#include "../include/DataFileManager.h"
#include <sstream>
#include <fstream>

using namespace std;

ParsedQuestion parseQuestion(const string& line)
{
	ParsedQuestion question{};
	stringstream ss(line);
	string token;
	vector<string> parts;

	while (getline(ss, token, '|'))
	{
		parts.push_back(token);
	}

	if (parts.size() < 5)
	{
		cerr << "Error: Invalid question format at line: " << line << endl;
		return question; // Return an empty question on error
	}

	question.type = parts[0];
	//xử lý trường hợp string không thể chuyển sang int
	try {
		question.id = std::stoi(parts[1]);
		question.points = std::stoi(parts[2]);
	}
	catch (const std::exception& e) {
		cerr << "Error: Invalid number format at line: " << line << endl;
		return ParsedQuestion{};
	}
	question.prompt = parts[3];

	if (question.type == "MCQ") {
		stringstream optStream(parts[4]);
		string option;

		while (getline(optStream, token, ';'))
		{
			question.options.push_back(token);
		}

		question.correctAnswer = parts[5];
	}
	else if (question.type == "TF")
	{
		question.correctAnswer = parts[4];
	}

	return question;
}

ParsedQuiz parseQuiz(const string& line)
{
	ParsedQuiz quiz{};
	stringstream ss(line);
	string token;
	vector<string> parts;

	while (getline(ss, token, '|'))
	{
		parts.push_back(token);
	}

	if (parts.size() < 3)
	{
		cerr << "Error: Invalid quiz format at line: " << line << endl;
		return quiz; // Return an empty quiz on error
	}

	try {
		quiz.quizID = std::stoi(parts[0]);
	}
	catch (const std::exception& e) {
		cerr << "Error: Invalid quiz ID format at line: " << line << endl;
		return ParsedQuiz{};
	}
	quiz.title = parts[1];

	stringstream qidStream(parts[2]);
	while (getline(qidStream, token, ';'))
	{
		try {
			quiz.questionIDs.push_back(std::stoi(token));
		}
		catch (const std::exception& e) {
			cerr << "Error: Invalid question ID format at line: " << line << endl;
		}
	}

	return quiz;
}

// load toàn bộ file questions.txt
vector<ParsedQuestion> DataFileManager::loadQuestions(const std::string& filename)
{
	vector<ParsedQuestion> result;
	ifstream file(filename);

	if (!file)
	{
		cerr << "Error: Could not open file " << filename << endl;
		return result;
	}

	string line;

	while (getline(file, line))
	{
		ParsedQuestion question = parseQuestion(line);
		if (question.id != 0) result.push_back(question);
	}
	file.close();
	return result;
}

// load toàn bộ file quizzes.txt
vector<ParsedQuiz> DataFileManager::loadQuizzes(const std::string& filename)
{
	vector<ParsedQuiz> result;
	ifstream file(filename);

	if (!file)
	{
		cerr << "Error: Could not open file " << filename << endl;
		return result;
	}

	string line;

	while (getline(file, line))
	{
		ParsedQuiz quiz = parseQuiz(line);
		if (quiz.quizID != 0) result.push_back(quiz);
	}

	file.close();
	return result;
}

//lưu dữ liệu questions vào file questions.txt
void DataFileManager::saveQuestions(const std::string& filename, const std::vector<ParsedQuestion>& data)
{
	ofstream file(filename);

	if (!file)
	{
		cerr << "Error: Could not write file " << filename << endl;
		return;
	}

	for (const auto& question : data)
	{
		if (question.type == "MCQ")
		{
			file << "MCQ|" << question.id << "|" << question.points << "|" << question.prompt << "|";
			for (size_t i = 0; i < question.options.size(); i++)
			{
				file << question.options[i];
				if (i < question.options.size() - 1) file << ";";
			}
			file << "|" << question.correctAnswer << endl;
		}
		else if (question.type == "TF")
		{
			file << "TF|" << question.id << "|" << question.points << "|" << question.prompt << "|" << question.correctAnswer << endl;
		}
	}

	file.close();
}

void DataFileManager::saveQuizzes(const std::string& filename, const std::vector<ParsedQuiz>& data)
{
	ofstream file(filename);

	if (!file)
	{
		cerr << "Error: Could not write file " << filename << endl;
		return;
	}

	for (const auto& quiz : data)
	{
		file << quiz.quizID << "|" << quiz.title << "|";
		for (size_t i = 0; i < quiz.questionIDs.size(); i++)
		{
			file << quiz.questionIDs[i];
			if (i < quiz.questionIDs.size() - 1) file << ";";
		}

		file << endl;
	}

	file.close();
}