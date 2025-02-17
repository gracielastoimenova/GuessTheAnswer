#include <gui/embedded_screen/EmbeddedView.hpp>
#include <cstdlib>  
#include <ctime>

#include <vector>
#include <algorithm>
#include <gui/score_screen/ScoreView.hpp>

//include-ni ja Color.hpp od tvojta papka deka se naoga
#include "C:\Users\graci\Downloads\MyApplication_3\MyApplication_3\Middlewares\ST\touchgfx\framework\include\touchgfx\Color.hpp"

const char* EmbeddedView::questions[EMBEDDED_QUESTION_COUNT] = {
    "What is an embed sys?",
    "What is key in embed sys?",
    "Which lang for embed sys?",
    "What does RTOS stand for?",
    "What does microcontroller do?",
    "Which is an embed sys?",
    "What are interrupts for?",
    "What does ADC mean?",
    "Which is not an embed sys?",
    "What is a key adv of embed sys?",
    "What stores firmware?",
    "What do sensors do?",
    "What is a watchdog?",
    "Which comm protocol used?",
    "What does GPIO mean?"
};

const char* EmbeddedView::answers[EMBEDDED_QUESTION_COUNT][ANSWER_COUNT] = {
    {"Dedicated", "General", "Cloud", "PC"},
    {"Micro", "Hard", "RAM", "Mon"},
    {"C", "Java", "Python", "All"},
    {"Real-Time", "Rapid", "Remote", "None"},
    {"Control", "Manage", "Connect", "Run"},
    {"Washer", "Smartphone", "Desktop", "Server"},
    {"Handle", "Improve", "Save", "None"},
    {"ADC", "Auto", "Advanced", "None"},
    {"Fridge", "Watch", "Laptop", "Camera"},
    {"Cost", "Power", "Capacity", "None"},
    {"Flash", "Hard", "RAM", "ROM"},
    {"Collect", "Output", "Process", "Save"},
    {"Resets sys", "Measure", "Memory", "None"},
    {"UART", "USB", "HDMI", "All"},
    {"Input", "Output", "Position", "None"}
};




EmbeddedView::EmbeddedView()
    : currentQuestionIndex(0), score(0), counter(15), tickCounter(0), counting(true),
      showFeedback(false), feedbackCounter(0) {}

void EmbeddedView::setupScreen() {
    EmbeddedViewBase::setupScreen();
    srand(time(0));
    initializeGame();
    loadNextQuestion();
    updateScore();
    updateTimer();
}

void EmbeddedView::tearDownScreen() {
    EmbeddedViewBase::tearDownScreen();
    counting = false;
}

void EmbeddedView::initializeGame() {
    selectedQuestions.clear();
    std::vector<int> availableIndices(EMBEDDED_QUESTION_COUNT);
    for (int i = 0; i < EMBEDDED_QUESTION_COUNT; i++) availableIndices[i] = i;

    std::random_shuffle(availableIndices.begin(), availableIndices.end());

    for (int i = 0; i < 10; i++) {
        selectedQuestions.push_back(availableIndices[i]);
    }

    currentQuestionIndex = 0;
}

void EmbeddedView::loadNextQuestion() {
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

void EmbeddedView::submitClicked() {
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


void EmbeddedView::highlightAnswer(int answerIndex, bool isCorrect) {
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

void EmbeddedView::resetAnswerColors() {
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

void EmbeddedView::updateScore() {
    Unicode::snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", score);
    scoreTextArea.setWildcard(scoreBuffer);
    scoreTextArea.invalidate();
}

void EmbeddedView::updateTimer() {
    Unicode::snprintf(counterBuffer, sizeof(counterBuffer), "%d", counter);
    textArea2.setWildcard(counterBuffer);
    textArea2.invalidate();
}

void EmbeddedView::handleTickEvent() {
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



//void EmbeddedView::gameOver() {

    // Unicode::snprintf(textArea1Buffer, sizeof(textArea1Buffer), "Game Over! Score: %d", score);
    // textArea1.setWildcard(textArea1Buffer);
    // textArea1.invalidate();
    // counting = false;

     //if(questionsDisplayed >= 5){
        
    //}
//}

void EmbeddedView::answerSelected1() {
    selectedAnswerIndex = 0;
    updateRadioSelection();
}

void EmbeddedView::answerSelected2() {
    selectedAnswerIndex = 1;
    updateRadioSelection();
}

void EmbeddedView::answerSelected3() {
    selectedAnswerIndex = 2;
    updateRadioSelection();
}

void EmbeddedView::answerSelected4() {
    selectedAnswerIndex = 3;
    updateRadioSelection();
}

void EmbeddedView::updateRadioSelection() {
    radioButton1.setSelected(selectedAnswerIndex == 0);
    radioButton2.setSelected(selectedAnswerIndex == 1);
    radioButton3.setSelected(selectedAnswerIndex == 2);
    radioButton4.setSelected(selectedAnswerIndex == 3);

    radioButton1.invalidate();
    radioButton2.invalidate();
    radioButton3.invalidate();
    radioButton4.invalidate();
}

void EmbeddedView::nextClicked() {
    if (currentQuestionIndex >= 9) {
        ScoreView* scoreView = new ScoreView();
        scoreView->setFinalScore(score);
        application().switchScreen(scoreView);
        return;
    }

    currentQuestionIndex++;
    loadNextQuestion();
}
