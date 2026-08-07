#include <iostream>
#include "../include/Application.h"

using namespace std;

// Constructor implementation
Application::Application()
{
	vector<string> warnings;
	int loadedQuestions = questionBank_.loadFromFile("data/questions.txt", warnings);

	cout << "Loaded " << loadedQuestions << " questions from questions.txt." << endl;
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
	case 0:
		// quay lại menu chính
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
	}
}

void Application::handleQuizMenu()
{
	// Placeholder for quiz management logic
	cout << "Quiz Management is not implemented yet." << endl;
}

void Application::handleTakeQuizMenu()
{
	// Placeholder for taking a quiz logic
	cout << "Taking a Quiz is not implemented yet." << endl;
}

void Application::saveAndExit()
{
	// Placeholder for save and exit logic
	cout << "Saving data and exiting the application." << endl;
}



