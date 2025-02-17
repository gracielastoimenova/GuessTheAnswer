#include <gui/databases_screen/DatabasesView.hpp>
#include <cstdlib>  
#include <ctime>
#include <vector>
#include <algorithm>
#include <gui/score_screen/ScoreView.hpp>

#include "C:\Users\graci\Downloads\MyApplication_3\MyApplication_3\Middlewares\ST\touchgfx\framework\include\touchgfx\Color.hpp"

const char* DatabasesView::questions[DATABASES_QUESTION_COUNT] = {
    "What does SQL stand for?",
    "Which type of database is best for unstructured data?",
    "What is the primary key used for?",
    "Which of the following is a NoSQL database?",
    "What does ACID stand for?",
    "Which command removes all records from a table?",
    "What is the purpose of an index?",
    "Which is a popular RDBMS?",
    "What is normalization?",
    "Which clause filters query results?",
    "What is the purpose of GROUP BY?",
    "Which data model does MongoDB use?",
    "What does a foreign key do?",
    "Which command retrieves data?",
    "What is a stored procedure?"
};

const char* DatabasesView::answers[DATABASES_QUESTION_COUNT][ANSWER_COUNT] = {
    {"Structured", "Sequential", "Simple", "System"},
    {"NoSQL", "Relational", "Graph", "Object"},
    {"Identify", "Store keys", "Create index", "Delete"},
    {"MongoDB", "MySQL", "Cassandra", "SQLite"},
    {"Atomicity", "Consistency", "Isolation", "Durable"},
    {"TRUNCATE", "DELETE", "DROP", "CLEAR"},
    {"Speed up", "Remove dupes", "Create keys", "Encrypt"},
    {"MySQL", "SQLite", "PostgreSQL", "Oracle"},
    {"Reduce red.", "Cache data", "Encrypt", "Backup"},
    {"WHERE", "ORDER BY", "HAVING", "JOIN"},
    {"Group rows", "Filter dupes", "Sort results", "Join tables"},
    {"Document", "Relational", "Hierarchical", "Network"},
    {"Link tables", "Store keys", "Speed query", "Delete"},
    {"SELECT", "FETCH", "GET", "QUERY"},
    {"SQL script", "Temp table", "Auto-index", "BG query"}
};




DatabasesView::DatabasesView()
    : currentQuestionIndex(0), score(0), counter(15), tickCounter(0), counting(true),
      showFeedback(false), feedbackCounter(0) {}

void DatabasesView::setupScreen() {
    DatabasesViewBase::setupScreen();
    srand(time(0));
    initializeGame();
    loadNextQuestion();
    updateScore();
    updateTimer();
}

void DatabasesView::tearDownScreen() {
    DatabasesViewBase::tearDownScreen();
    counting = false;
}

void DatabasesView::initializeGame() {
    selectedQuestions.clear();
    std::vector<int> availableIndices(DATABASES_QUESTION_COUNT);
    for (int i = 0; i < DATABASES_QUESTION_COUNT; i++) availableIndices[i] = i;

    std::random_shuffle(availableIndices.begin(), availableIndices.end());

    for (int i = 0; i < 10; i++) {
        selectedQuestions.push_back(availableIndices[i]);
    }

    currentQuestionIndex = 0;
}

void DatabasesView::loadNextQuestion() {
    if (currentQuestionIndex >= 10) {
        ScoreView* scoreView = new ScoreView();
        scoreView->setFinalScore(score);
        application().switchScreen(scoreView); 
        return;
    }

    int questionIdx = selectedQuestions[currentQuestionIndex];

    Unicode::fromUTF8((const uint8_t*)questions[questionIdx], textArea1Buffer, sizeof(textArea1Buffer) - 1);
    textArea1Buffer[sizeof(textArea1Buffer) - 1] = 0;
    textArea1.setWildcard(textArea1Buffer);
    textArea1.invalidate();

    std::vector<int> answerOrder = {0, 1, 2, 3};
    std::random_shuffle(answerOrder.begin(), answerOrder.end());

    correctAnswerIndex = std::find(answerOrder.begin(), answerOrder.end(), 0) - answerOrder.begin();

    Unicode::fromUTF8((const uint8_t*)answers[questionIdx][answerOrder[0]], answer1Buffer, BUFFER_SIZE - 1);
    Unicode::fromUTF8((const uint8_t*)answers[questionIdx][answerOrder[1]], answer2Buffer, BUFFER_SIZE - 1);
    Unicode::fromUTF8((const uint8_t*)answers[questionIdx][answerOrder[2]], answer3Buffer, BUFFER_SIZE - 1);
    Unicode::fromUTF8((const uint8_t*)answers[questionIdx][answerOrder[3]], answer4Buffer, BUFFER_SIZE - 1);

    answer1.setWildcard(answer1Buffer);
    answer2.setWildcard(answer2Buffer);
    answer3.setWildcard(answer3Buffer);
    answer4.setWildcard(answer4Buffer);

    answer1.invalidate();
    answer2.invalidate();
    answer3.invalidate();
    answer4.invalidate();

    selectedAnswerIndex = -1;
    radioButton1.setSelected(false);
    radioButton2.setSelected(false);
    radioButton3.setSelected(false);
    radioButton4.setSelected(false);
    radioButton1.invalidate();
    radioButton2.invalidate();
    radioButton3.invalidate();
    radioButton4.invalidate();

    counter = 15;
    updateTimer();
    resetAnswerColors();
}

void DatabasesView::submitClicked() {
    if (selectedAnswerIndex == -1) return;
    if (selectedAnswerIndex == correctAnswerIndex) {
        score++;
        updateScore();
        highlightAnswer(selectedAnswerIndex, true);
    } else {
        highlightAnswer(selectedAnswerIndex, false);
        highlightAnswer(correctAnswerIndex, true);
    }
    counting = false;
    showFeedback = true;
    feedbackCounter = 50;
}


void DatabasesView::highlightAnswer(int answerIndex, bool isCorrect) {
    touchgfx::colortype color = isCorrect ?
    		touchgfx::Color::getColorFromRGB(0, 255, 0)
			: touchgfx::Color::getColorFromRGB(255, 0, 0);
    switch (answerIndex) {
        case 0: answer1.setColor(color); break;
        case 1: answer2.setColor(color); break;
        case 2: answer3.setColor(color); break;
        case 3: answer4.setColor(color); break;
    }
    answer1.invalidate();
    answer2.invalidate();
    answer3.invalidate();
    answer4.invalidate();
}

void DatabasesView::resetAnswerColors() {
    touchgfx::colortype whiteColor = touchgfx::Color::getColorFromRGB(255, 255, 255);
    answer1.setColor(whiteColor);
    answer2.setColor(whiteColor);
    answer3.setColor(whiteColor);
    answer4.setColor(whiteColor);

    answer1.invalidate();
    answer2.invalidate();
    answer3.invalidate();
    answer4.invalidate();
}

void DatabasesView::updateScore() {
    Unicode::snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", score);
    scoreTextArea.setWildcard(scoreBuffer);
    scoreTextArea.invalidate();
}

void DatabasesView::updateTimer() {
    Unicode::snprintf(counterBuffer, sizeof(counterBuffer), "%d", counter);
    textArea2.setWildcard(counterBuffer);
    textArea2.invalidate();
}

void DatabasesView::handleTickEvent() {
    if (counting) {
        tickCounter++;
        if (tickCounter % 60 == 0) {
            if (counter == 0) {
                counting = false;

                ScoreView* scoreView = new ScoreView();
                scoreView->setFinalScore(score);
                application().switchScreen(scoreView);

                return;
            }
            counter--;
            updateTimer();
        }
    }

    if (showFeedback) {
        if (feedbackCounter > 0) {
            feedbackCounter--;
            if (feedbackCounter == 0) {
                showFeedback = false;
                currentQuestionIndex++;
                loadNextQuestion();
                counting = true;
            }
        }
    }
}


void DatabasesView::answerSelected1() {
    selectedAnswerIndex = 0;
    updateRadioSelection();
}

void DatabasesView::answerSelected2() {
    selectedAnswerIndex = 1;
    updateRadioSelection();
}

void DatabasesView::answerSelected3() {
    selectedAnswerIndex = 2;
    updateRadioSelection();
}

void DatabasesView::answerSelected4() {
    selectedAnswerIndex = 3;
    updateRadioSelection();
}

void DatabasesView::updateRadioSelection() {
    radioButton1.setSelected(selectedAnswerIndex == 0);
    radioButton2.setSelected(selectedAnswerIndex == 1);
    radioButton3.setSelected(selectedAnswerIndex == 2);
    radioButton4.setSelected(selectedAnswerIndex == 3);

    radioButton1.invalidate();
    radioButton2.invalidate();
    radioButton3.invalidate();
    radioButton4.invalidate();
}

void DatabasesView::nextClicked() {
    if (currentQuestionIndex >= 9) {
        ScoreView* scoreView = new ScoreView();
        scoreView->setFinalScore(score);
        application().switchScreen(scoreView);
        return;
    }

    currentQuestionIndex++;
    loadNextQuestion();
}

