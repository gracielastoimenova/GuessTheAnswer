#include <gui/algorithms_screen/AlgorithmsView.hpp>
#include <cstdlib>  
#include <ctime>

#include <vector>
#include <algorithm>
#include <gui/score_screen/ScoreView.hpp>
#include "C:\Users\graci\Downloads\MyApplication_3\MyApplication_3\Middlewares\ST\touchgfx\framework\include\touchgfx\Color.hpp"
const char* AlgorithmsView::questions[ALGORITHMS_QUESTION_COUNT] = {
    "What is an algo?",
    "Which is a sort algo?",
    "What is big O?",
    "What is binary search?",
    "What uses LIFO?",
    "What is hashing?",
    "Which finds the shortest path?",
    "What is dynamic prog?",
    "What does a stack do?",
    "What is recursion?",
    "Which algo traverses a tree?",
    "What is a greedy algo?",
    "What does divide and conquer mean?",
    "Which is a graph algo?",
    "What is a queue?"
};

const char* AlgorithmsView::answers[ALGORITHMS_QUESTION_COUNT][ANSWER_COUNT] = {
    {"Procedure", "Language", "Structure", "None"},
    {"Bubble", "Merge", "Quick", "All"},
    {"Efficiency", "Time", "Space", "None"},
    {"Find item", "Sort", "Search", "None"},
    {"Last In", "First In", "Random", "None"},
    {"Identify", "Store", "Encrypt", "None"},
    {"Dijkstra", "Merge", "Bubble", "Quick"},
    {"Break down", "Sorting", "Searching", "None"},
    {"Store", "Output", "Process", "None"},
    {"Calls self", "Loop", "Structure", "None"},
    {"DFS", "Binary", "Linear", "None"},
    {"Best choice", "Optimal", "Brute-force", "None"},
    {"Divide", "Sort", "Search", "None"},
    {"DFS", "BFS", "Binary", "None"},
    {"FIFO", "LIFO", "Random", "None"}
};



AlgorithmsView::AlgorithmsView()
    : currentQuestionIndex(0), score(0), counter(15), tickCounter(0), counting(true),
      showFeedback(false), feedbackCounter(0) {}

void AlgorithmsView::setupScreen() {
    AlgorithmsViewBase::setupScreen();
    srand(time(0));
    initializeGame();
    loadNextQuestion();
    updateScore();
    updateTimer();
}

void AlgorithmsView::tearDownScreen() {
    AlgorithmsViewBase::tearDownScreen();
    counting = false;
}

void AlgorithmsView::initializeGame() {
    selectedQuestions.clear();
    std::vector<int> availableIndices(ALGORITHMS_QUESTION_COUNT);
    for (int i = 0; i < ALGORITHMS_QUESTION_COUNT; i++) availableIndices[i] = i;

    std::random_shuffle(availableIndices.begin(), availableIndices.end());

    for (int i = 0; i < 10; i++) {
        selectedQuestions.push_back(availableIndices[i]);
    }

    currentQuestionIndex = 0;
}

void AlgorithmsView::loadNextQuestion() {
    if (currentQuestionIndex >= 10) {
        // Unicode::snprintf(textArea1Buffer, sizeof(textArea1Buffer), "Game Over! Score: %d", score);
        // textArea1.setWildcard(textArea1Buffer);
        // textArea1.invalidate();
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

void AlgorithmsView::submitClicked() {
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


void AlgorithmsView::highlightAnswer(int answerIndex, bool isCorrect) {
    touchgfx::colortype color = isCorrect ? touchgfx::Color::getColorFromRGB(0, 255, 0) : touchgfx::Color::getColorFromRGB(255, 0, 0);

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

void AlgorithmsView::resetAnswerColors() {
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

void AlgorithmsView::updateScore() {
    Unicode::snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", score);
    scoreTextArea.setWildcard(scoreBuffer);
    scoreTextArea.invalidate();
}

void AlgorithmsView::updateTimer() {
    Unicode::snprintf(counterBuffer, sizeof(counterBuffer), "%d", counter);
    textArea2.setWildcard(counterBuffer);
    textArea2.invalidate();
}

void AlgorithmsView::handleTickEvent() {
    if (counting) {
        tickCounter++;
        if (tickCounter % 60 == 0) {
            if (counter == 0) {
                counting = false;

                // GAME OVER - Switch to Score Screen
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



//void EmbeddedView::gameOver() {

    // Unicode::snprintf(textArea1Buffer, sizeof(textArea1Buffer), "Game Over! Score: %d", score);
    // textArea1.setWildcard(textArea1Buffer);
    // textArea1.invalidate();
    // counting = false;

     //if(questionsDisplayed >= 5){
        
    //}
//}

void AlgorithmsView::answerSelected1() {
    selectedAnswerIndex = 0;
    updateRadioSelection();
}

void AlgorithmsView::answerSelected2() {
    selectedAnswerIndex = 1;
    updateRadioSelection();
}

void AlgorithmsView::answerSelected3() {
    selectedAnswerIndex = 2;
    updateRadioSelection();
}

void AlgorithmsView::answerSelected4() {
    selectedAnswerIndex = 3;
    updateRadioSelection();
}

void AlgorithmsView::updateRadioSelection() {
    radioButton1.setSelected(selectedAnswerIndex == 0);
    radioButton2.setSelected(selectedAnswerIndex == 1);
    radioButton3.setSelected(selectedAnswerIndex == 2);
    radioButton4.setSelected(selectedAnswerIndex == 3);

    radioButton1.invalidate();
    radioButton2.invalidate();
    radioButton3.invalidate();
    radioButton4.invalidate();
}

void AlgorithmsView::nextClicked() {
    if (currentQuestionIndex >= 9) {
        ScoreView* scoreView = new ScoreView();
        scoreView->setFinalScore(score);
        application().switchScreen(scoreView);
        return;
    }

    currentQuestionIndex++;
    loadNextQuestion();
}

