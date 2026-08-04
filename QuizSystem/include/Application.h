#ifndef APPLICATION_H
#define APPLICATION_H

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

};

#endif