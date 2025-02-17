#include <gui/score_screen/ScoreView.hpp>
#include <gui/rank_screen/RankView.hpp>

ScoreView::ScoreView() : score(0)
{

}

void ScoreView::setupScreen()
{
    ScoreViewBase::setupScreen();
    Unicode::snprintf(textArea1Buffer, sizeof(textArea1Buffer), "%d", score);
    textArea1.setWildcard(textArea1Buffer);
    textArea1.invalidate();
}

void ScoreView::tearDownScreen()
{
    ScoreViewBase::tearDownScreen();
}

void ScoreView::setFinalScore(int finalScore) {
    score = finalScore;
}

void ScoreView::nextClicked() {
    RankView* rankView = new RankView();
    rankView->setScoreFromPreviousView(score);
    application().switchScreen(rankView);

}
