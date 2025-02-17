#ifndef SCOREVIEW_HPP
#define SCOREVIEW_HPP

#include <gui_generated/score_screen/ScoreViewBase.hpp>
#include <gui/score_screen/ScorePresenter.hpp>

class ScoreView : public ScoreViewBase
{
public:
    ScoreView();
    virtual ~ScoreView() {}
    virtual void setupScreen() override;
    virtual void tearDownScreen();

    void setFinalScore(int score); 
    virtual void nextClicked();
protected:

private:
    int score;
    Unicode::UnicodeChar textArea1Buffer[32];  
};
#endif // SCOREVIEW_HPP
