#include <iostream>
#include "../include/Application.h"
#include "../include/DataFileManager.h"

using namespace std;

// Constructor implementation
Application::Application()
{
	ParsedQuestion question;

	vector<string> warnings;
	int loadedQuestions = questionBank_.loadFromFile("data/questions.txt", warnings);
	int loadedQuizzes = quizManager_.loadFromFile("data/quizzes.txt");

	cout << "Loaded " << loadedQuestions << " questions from questions.txt." << endl;
	cout << "Loaded all quizzes from quizzes.txt." << endl;
	for (const string& warning : warnings) {
		cout << "Warning: " << warning << endl;
	}
}

void Application::run()
{
	bool running = true;

	while (running) {
		showMainMenu();
		int choice;
		
		if (!(cin >> choice)) {
			cin.clear(); // clear the error flag
			cin.ignore(1000, '\n'); // discard invalid input
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}

		switch (choice) {
		case 1:
			handleQuestionBankMenu();
			break;
		case 2:
			handleQuizMenu();
			break;
		case 3:
			handleTakeQuizMenu();
			break;
		case 4:
			saveAndExit();
			running = false;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

void Application::showMainMenu()
{
	cout << "==== Welcome to the Quiz System! ====" << endl;
	cout << "1. Manage Question Bank" << endl;
	cout << "2. Manage Quizzes" << endl;
	cout << "3. Take a Quiz" << endl;
	cout << "4. Save & Exit" << endl;
	cout << "Please enter your choice: ";
}

void Application::handleQuestionBankMenu()
{
	cout << "===== Question Bank Menu =====" << endl;
	cout << "1. Display all questions" << endl;
	cout << "2. Add a new question" << endl;
	cout << "3. Update an existing question" << endl;
	cout << "4. Remove a question" << endl;
	cout << "5. Search questions" << endl;
	cout << "0. Back to main menu" << endl;
	cout << "Please enter your choice: ";

	int choice;
	if (!(cin >> choice)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please enter a number." << endl;
		return;
	}

	switch (choice) {
	case 1:	// display all questions
		questionBank_.displayAll();
		break;
	case 2:	// add a new question
		cout << "===== Add a New Question =====" << endl;
		cout << "1. Add a new MCQ Question" << endl;
		cout << "2. Add a new True/False Question" << endl;
		cout << "0. Back to Menu" << endl;
		int subChoice;
		if (!(cin >> subChoice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			return;
		}
		switch (subChoice) {
		case 1:	// add a new MCQ question
		{
			int questionId, points;
			string prompt, correctOption;
			vector <string> options(4);
			string errorMsg;

			cout << "Enter question ID: "; cin >> questionId; cin.ignore();
			cout << "Enter prompt: "; getline(cin, prompt);
			cout << "Enter points: "; cin >> points; cin.ignore();

			cout << "Enter 4 options (A-D): " << endl;
			for (int i = 0; i < 4; ++i) {
				cout << "Option " << static_cast<char>('A' + i) << ": ";
				getline(cin, options[i]);
			}

			cout << "Enter corect option (A-D): "; getline(cin, correctOption);

			if (!questionBank_.addMCQ(questionId, prompt, points, options, correctOption, errorMsg)) {
				cout << "Failed to add MCQ question. Error: " << errorMsg << endl;
			}
			else {
				cout << "MCQ question added successfully." << endl;
			}
			break;
		}	// case 2.1 add a new MCQ question

		case 2:	// add a new True/False question
		{
			int id, point;
			string prompt, correctAnswer, errorMsg;

			cout << "Enter question ID: "; cin >> id; cin.ignore();
			cout << "Enter prompt: "; getline(cin, prompt);
			cout << "Enter points: "; cin >> point; cin.ignore();
			cout << "Enter correct answer (True/False): "; getline(cin, correctAnswer);

			if (!questionBank_.addTF(id, prompt, point, correctAnswer, errorMsg)) {
				cout << "Failed to add TF question. Error: " << errorMsg << endl;
			}
			else {
				cout << "TF question added successfully." << endl;
			}
			break;
		}	// case 2.2 add a new True/False question
			
		case 0:
			// quay lại menu chính
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}	// case 2 add a new question
		break;
	//	update a question
	case 3:
	{
		int updateId;
		cout << "Enter the Question ID to update: "; cin >> updateId; cin.ignore();

		cout << "===== Update Question =====" << endl;
		string newPrompt, newAnswer, errorMsg;
		int newPoints;

		cout << "Enter new prompt: "; getline(cin, newPrompt);
		cout << "Enter new points: "; cin >> newPoints; cin.ignore();

		Question* q = questionBank_.findById(updateId);
		if (!q) {
			cout << "Question with ID " << updateId << " not found." << endl;
			break;
		}

		vector<string> newOptions;

		if (dynamic_cast<MCQ*>(q)) {
			newOptions.resize(4);
			cout << "Enter 4 new options (A-D): " << endl;
			for (int i = 0; i < 4; ++i) {
				cout << "Option " << static_cast<char>('A' + i) << ": ";
				getline(cin, newOptions[i]);
			}
			cout << "Enter new correct option (A-D): ";
			getline(cin, newAnswer);
		}
		else {
			cout << "Enter new correct answer (True/False): "; getline(cin, newAnswer);
		}

		if (!questionBank_.updateQuestion(updateId, newPrompt, newPoints, newAnswer, newOptions, errorMsg)) {
			cout << "Failed to update question. Error: " << errorMsg << endl;
		}
		else {
			cout << "Question updated successfully." << endl;
		}
		break;
	}	//case 3 Question Menu

	case 4:	// remove a question
	{
		int removeId;
		cout << "Enter the Question ID to remove: "; cin >> removeId; cin.ignore();

		if (!questionBank_.removeQuestion(removeId)) {
			cout << "Question with ID " << removeId << " not found." << endl;
		}
		else {
			cout << "Question removed successfully." << endl;
			quizManager_.removeQuestionFromAllQuizzes(removeId);
		}
		break;
	}	// case 4 Question Menu

	case 5:
	{
		cout << "===== Search Questions =====" << endl;
		cout << "1. Search by ID" << endl;
		cout << "2. Search by prompt keyword" << endl;
		cout << "0. Back to Menu" << endl;

		int searchChoice;
		if (!(cin >> searchChoice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			return;
		}

		switch (searchChoice) {
		case 1:
		{
			int searchId;
			cout << "Enter the Question ID to search: "; cin >> searchId; cin.ignore();
			Question* q = questionBank_.findById(searchId);
			if (q) {
				q->display();
			}
			else {
				cout << "Question with ID " << searchId << " not found." << endl;
			}
			break;
		}

		case 2:
		{
			string keyword;
			cout << "Enter the keyword to search in prompts: "; cin.ignore(); getline(cin, keyword);
			vector<Question*> results = questionBank_.findByPromptContains(keyword);
			if (results.empty()) {
				cout << "No questions found containing the keyword \"" << keyword << "\"." << endl;
			}
			else {
				cout << "Found " << results.size() << " question(s):" << endl;
				for (Question* q : results) {
					q->display();
				}
			}
			break;
		}

		case 0: break;

		default: cout << "Invalid choice. Please try again." << endl;

		}	// switch searchChoice for search Question Menu

		break;
	}

	case 0:
		// quay lại Main Menu
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
	}
}

void Application::handleQuizMenu()
{
	cout << "===== Quiz Menu =====" << endl;
	cout << "1. Display all quizzes" << endl;
	cout << "2. Create a new quiz" << endl;
	cout << "3. Rename an existing quiz" << endl;
	cout << "4. Remove a quiz" << endl;
	cout << "5. Add a question to a quiz" << endl;
	cout << "6. Remove a question from a quiz" << endl;
	cout << "0. Back to main menu" << endl;
	cout << "Please enter your choice: ";

	int choice;
	if (!(cin >> choice)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please enter a number." << endl;
		return;
	}

	switch (choice) {
	case 1:
		quizManager_.display(cout);
		break;
	case 2:
	{
		int quizId;
		string title;
		cout << "Enter new quiz ID: "; cin >> quizId; cin.ignore();
		cout << "Enter new quiz title: "; getline(cin, title);
		
		if (!quizManager_.create(quizId, title)) {
			cout << "Failed to create quiz. Error: " << quizManager_.getLastError() << endl;
		}
		else {
			cout << "Quiz created successfully." << endl;
		}
		break;
	}
	case 3:
	{
		int quizId;
		string newTitle;
		cout << "Enter the quiz ID to rename: "; cin >> quizId; cin.ignore();
		cout << "Enter new title: "; getline(cin, newTitle);

		if (!quizManager_.rename(quizId, newTitle)) {
			cout << "Failed to rename quiz. Error: " << quizManager_.getLastError() << endl;
		}
		else {
			cout << "Quiz renamed successfully." << endl;
		}
		break;
	}
	case 4:
	{
		int quizId;
		cout << "Enter the quiz ID to remove: "; cin >> quizId; cin.ignore();
		
		if (!quizManager_.remove(quizId)) {
			cout << "Failed to remove quiz. Error: " << quizManager_.getLastError() << endl;
		}
		else {
			cout << "Quiz removed successfully." << endl;
		}
		break;
	}
	case 5:
	{
		int quizID, questionID;

		cout << "Enter the quiz ID to add a question to: "; cin >> quizID; cin.ignore();
		cout << "Enter the question ID to add: "; cin >> questionID; cin.ignore();

		if (!quizManager_.addQuestion(quizID, questionID)) {
			cout << "Failed to add question to quiz. Error: " << quizManager_.getLastError() << endl;
		}
		else {
			cout << "Question added to quiz successfully." << endl;
		}
		break;
	}
	case 6:
	{
		int quizID, questionID;
		cout << "Enter the quiz ID to remove a question from: "; cin >> quizID; cin.ignore();
		cout << "Enter the question ID to remove: "; cin >> questionID; cin.ignore();

		if (!quizManager_.removeQuestion(quizID, questionID)) {
			cout << "Failed to remove question from quiz. Error: " << quizManager_.getLastError() << endl;
		}
		else {
			cout << "Question removed from quiz successfully." << endl;
		}
		break;
	}
	case 0:
		// quay lại menu chính
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
	}
}

void Application::handleTakeQuizMenu()
{
	quizEngine_.pickAQuiz(quizManager_, questionBank_);

}

void Application::saveAndExit()
{
	questionBank_.saveToFile("data/questions.txt");
	quizManager_.saveToFile("data/quizzes.txt");
	cout << "Saving data and exiting the application." << endl;
}



