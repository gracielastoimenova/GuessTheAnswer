#ifndef EMBEDDEDVIEW_HPP
#define EMBEDDEDVIEW_HPP

#include <gui_generated/embedded_screen/EmbeddedViewBase.hpp>
#include <gui/embedded_screen/EmbeddedPresenter.hpp>

#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/Types.hpp>

#include <vector>
#include <algorithm>

#define EMBEDDED_QUESTION_COUNT 15
#define ANSWER_COUNT 4    
#define BUFFER_SIZE 100  

class EmbeddedView : public EmbeddedViewBase
{
public:
    EmbeddedView();
    virtual ~EmbeddedView() {}
    virtual void setupScreen();
       virtual void tearDownScreen();
       virtual void initializeGame();
       virtual void loadNextQuestion();
       virtual void submitClicked();
       virtual void highlightAnswer(int answerIndex, bool isCorrect);
       virtual void resetAnswerColors();
       virtual void updateScore();
       virtual void updateTimer();
       virtual void handleTickEvent();
       virtual void answerSelected1();
       virtual void answerSelected2();
       virtual void answerSelected3();
       virtual void answerSelected4();
       virtual void updateRadioSelection();
       virtual void nextClicked();

   protected:
       int currentQuestionIndex;
       static const char* questions[EMBEDDED_QUESTION_COUNT];
       static const char* answers[EMBEDDED_QUESTION_COUNT][ANSWER_COUNT];

       std::vector<int> selectedQuestions;
       int correctAnswerIndex;

       touchgfx::Unicode::UnicodeChar textArea1Buffer[300];
       touchgfx::Unicode::UnicodeChar answer1Buffer[BUFFER_SIZE];
       touchgfx::Unicode::UnicodeChar answer2Buffer[BUFFER_SIZE];
       touchgfx::Unicode::UnicodeChar answer3Buffer[BUFFER_SIZE];
       touchgfx::Unicode::UnicodeChar answer4Buffer[BUFFER_SIZE];
       touchgfx::Unicode::UnicodeChar answerBuffers[BUFFER_SIZE];
       int score = 0;
       int counter;

       int tickCounter;
       bool counting;
       touchgfx::Unicode::UnicodeChar counterBuffer[10];

       int questionsDisplayed = 0;
       int selectedAnswerIndex;
       touchgfx::Unicode::UnicodeChar scoreBuffer[10];

       bool showFeedback;
       int feedbackCounter;
   };


#endif // EMBEDDEDVIEW_HPP
