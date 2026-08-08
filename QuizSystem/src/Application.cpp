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
	cout << "Loaded " << loadedQuizzes << " quizzes from quizzes.txt." << endl;
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
	case 1:
		questionBank_.displayAll();
		break;
	case 2:
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
		case 1:
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
		}

		case 2:
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
		}
			
		case 0:
			// quay lại menu chính
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
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
	cout << "Saving data and exiting the application." << endl;
}



