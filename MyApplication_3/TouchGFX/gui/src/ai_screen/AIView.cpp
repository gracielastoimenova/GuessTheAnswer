#include <gui/ai_screen/AIView.hpp>
#include <cstdlib>  
#include <ctime>
#include <vector>
#include <algorithm>
#include <gui/score_screen/ScoreView.hpp>

#include "C:\Users\graci\Downloads\MyApplication_3\MyApplication_3\Middlewares\ST\touchgfx\framework\include\touchgfx\Color.hpp"

const char* AIView::questions[AI_QUESTION_COUNT] = {
    "What is AI's main goal?",
    "Which algo for class tasks?",
    "What is overfitting?",
    "What type involves feedback?",
    "What does a neural net do?",
    "Which is unsupervised?",
    "What does NLP mean?",
    "Which framework is for deep learn?",
    "What is reinforcement learn?",
    "What is a decision tree?",
    "What is the Turing test for?",
    "Which is a type of AI?",
    "What is feature extract?",
    "What is transfer learn?",
    "What is backpropagation?"
};

const char* AIView::answers[AI_QUESTION_COUNT][ANSWER_COUNT] = {
    {"Simulate", "Enhance", "Store", "None"},
    {"K-means", "Tree", "SVM", "Random"},
    {"Poor on new", "Equal", "Not learn", "Simple"},
    {"Supervised", "Reinforced", "Unsupervised", "None"},
    {"Model patterns", "Store", "Run", "Manage"},
    {"K-means", "Regression", "SVM", "None"},
    {"NLP", "Neural", "Network", "None"},
    {"Tensor", "WordPress", "React", "Node"},
    {"Learn from env", "Supervised", "Unlearn", "Data"},
    {"Flowchart", "Database", "Type", "None"},
    {"Measure AI", "Test hardware", "Assess", "Classify"},
    {"Reactive", "Limited", "Theory", "All"},
    {"Select features", "Clean", "Visualize", "None"},
    {"Reuse model", "Build data", "Training", "None"},
    {"Adjust weights", "Collect", "Validate", "None"}
};




AIView::AIView()
    : currentQuestionIndex(0), score(0), counter(15), tickCounter(0), counting(true),
      showFeedback(false), feedbackCounter(0) {}

void AIView::setupScreen() {
    AIViewBase::setupScreen();
    srand(time(0));
    initializeGame();
    loadNextQuestion();
    updateScore();
    updateTimer();
}

void AIView::tearDownScreen() {
    AIViewBase::tearDownScreen();
    counting = false;
}

void AIView::initializeGame() {
    selectedQuestions.clear();
    std::vector<int> availableIndices(AI_QUESTION_COUNT);
    for (int i = 0; i < AI_QUESTION_COUNT; i++) availableIndices[i] = i;

    std::random_shuffle(availableIndices.begin(), availableIndices.end());

    for (int i = 0; i < 10; i++) {
        selectedQuestions.push_back(availableIndices[i]);
    }

    currentQuestionIndex = 0;
}

void AIView::loadNextQuestion() {
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

void AIView::submitClicked() {
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


void AIView::highlightAnswer(int answerIndex, bool isCorrect) {
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

void AIView::resetAnswerColors() {
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

void AIView::updateScore() {
    Unicode::snprintf(scoreBuffer, sizeof(scoreBuffer), "%d", score);
    scoreTextArea.setWildcard(scoreBuffer);
    scoreTextArea.invalidate();
}

void AIView::updateTimer() {
    Unicode::snprintf(counterBuffer, sizeof(counterBuffer), "%d", counter);
    textArea2.setWildcard(counterBuffer);
    textArea2.invalidate();
}

void AIView::handleTickEvent() {
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


void AIView::answerSelected1() {
    selectedAnswerIndex = 0;
    updateRadioSelection();
}

void AIView::answerSelected2() {
    selectedAnswerIndex = 1;
    updateRadioSelection();
}

void AIView::answerSelected3() {
    selectedAnswerIndex = 2;
    updateRadioSelection();
}

void AIView::answerSelected4() {
    selectedAnswerIndex = 3;
    updateRadioSelection();
}

void AIView::updateRadioSelection() {
    radioButton1.setSelected(selectedAnswerIndex == 0);
    radioButton2.setSelected(selectedAnswerIndex == 1);
    radioButton3.setSelected(selectedAnswerIndex == 2);
    radioButton4.setSelected(selectedAnswerIndex == 3);

    radioButton1.invalidate();
    radioButton2.invalidate();
    radioButton3.invalidate();
    radioButton4.invalidate();
}

void AIView::nextClicked() {
    if (currentQuestionIndex >= 9) {
        ScoreView* scoreView = new ScoreView();
        scoreView->setFinalScore(score);
        application().switchScreen(scoreView);
        return;
    }

    currentQuestionIndex++;
    loadNextQuestion();
}

