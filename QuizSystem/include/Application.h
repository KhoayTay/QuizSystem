#ifndef APPLICATION_H
#define APPLICATION_H

#include "../include/QuestionBank.h"
#include "../include/QuizManager.h"
#include "../include/QuizEngine.h"


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
	QuizManager quizManager_;
	QuizEngine quizEngine_;
};

#endif