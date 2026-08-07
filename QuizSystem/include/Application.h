#ifndef APPLICATION_H
#define APPLICATION_H

#include "../include/QuestionBank.h"

class Application {
public:
	Application();
	void run();
private:
	void showMainMenu();
	void handleQuestionBankMenu();
	void handleQuizMenu();
	void handleTakeQuizMenu();
	void saveAndExit();

	QuestionBank questionBank_;
};

#endif