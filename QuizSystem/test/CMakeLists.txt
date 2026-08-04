file(GLOB TEST_SOURCES "*.cpp")

add_executable(QuizSystemTests ${TEST_SOURCES})

target_link_libraries(QuizSystemTests QuizSystem)
