#include <iostream>
#include "../include/Application.h"

using namespace std;

// Constructor implementation
Application::Application()
{

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
	cout << "Welcome to the Quiz System!" << endl;
	cout << "1. Manage Question Bank" << endl;
	cout << "2. Manage Quizzes" << endl;
	cout << "3. Take a Quiz" << endl;
	cout << "4. Save & Exit" << endl;
	cout << "Please enter your choice: ";
}

void Application::handleQuestionBankMenu()
{
	// Placeholder for question bank management logic
	cout << "Question Bank Management is not implemented yet." << endl;
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



