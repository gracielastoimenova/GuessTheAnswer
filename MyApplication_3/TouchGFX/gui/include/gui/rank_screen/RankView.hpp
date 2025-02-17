#ifndef RANKVIEW_HPP
#define RANKVIEW_HPP

#include <vector>
#include <string>

#include <gui_generated/rank_screen/RankViewBase.hpp>
#include <gui/rank_screen/RankPresenter.hpp>

#define BUFFER_SIZE_RANK 300

struct User {
    std::string name;
    int score;
};

class RankView : public RankViewBase
{
public:
    RankView();
    virtual ~RankView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void addNewScore(const std::string& newUser, int newScore);
    virtual void updateUI();
    virtual void setScoreFromPreviousView(int score);
    int scoreFromPreviousView;
protected:
    touchgfx::Unicode::UnicodeChar score1Buffer[BUFFER_SIZE_RANK];
    touchgfx::Unicode::UnicodeChar score2Buffer[BUFFER_SIZE_RANK];
    touchgfx::Unicode::UnicodeChar score3Buffer[BUFFER_SIZE_RANK];
    touchgfx::Unicode::UnicodeChar score4Buffer[BUFFER_SIZE_RANK];
    touchgfx::Unicode::UnicodeChar score5Buffer[BUFFER_SIZE_RANK];
    touchgfx::Unicode::UnicodeChar score6Buffer[BUFFER_SIZE_RANK];

    std::vector<User> rankings;
    void sortRankings();
};

#endif // RANKVIEW_HPP
