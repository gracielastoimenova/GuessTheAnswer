#include <gui/rank_screen/RankView.hpp>
#include <algorithm>

RankView::RankView()
{
    rankings = {
        {"Alice", 5},
        {"Bob", 7},
        {"Charlie", 6},
        {"David", 3},
        {"Eve", 8}
    };
}

void RankView::setupScreen()
{
    RankViewBase::setupScreen();

     if (scoreFromPreviousView >= 0) {
        addNewScore("New User", scoreFromPreviousView);
    }
}

void RankView::setScoreFromPreviousView(int score)
{
    scoreFromPreviousView = score;
}

void RankView::tearDownScreen()
{
    RankViewBase::tearDownScreen();
}


void RankView::addNewScore(const std::string& newUser, int newScore) {
    rankings.push_back({newUser, newScore});

    sortRankings();
    updateUI();
}

void RankView::sortRankings() {
    std::sort(rankings.begin(), rankings.end(), [](const User &a, const User &b) {
        return a.score > b.score;
    });

    if (rankings.size() > 6) {
        rankings.resize(6);
    }
}


void RankView::updateUI() {
    if (rankings.size() >= 6) {

        std::string scoreString1 = std::to_string(rankings[0].score);
        std::string combined1 = rankings[0].name + " - " + scoreString1;
        Unicode::fromUTF8((const uint8_t*)combined1.c_str(), score1Buffer, BUFFER_SIZE_RANK - 1);

        std::string scoreString2 = std::to_string(rankings[1].score);
        std::string combined2 = rankings[1].name + " - " + scoreString2;
        Unicode::fromUTF8((const uint8_t*)combined2.c_str(), score2Buffer, BUFFER_SIZE_RANK - 1);

        std::string scoreString3 = std::to_string(rankings[2].score);
        std::string combined3 = rankings[2].name + " - " + scoreString3;
        Unicode::fromUTF8((const uint8_t*)combined3.c_str(), score3Buffer, BUFFER_SIZE_RANK - 1);

        std::string scoreString4 = std::to_string(rankings[3].score);
        std::string combined4 = rankings[3].name + " - " + scoreString4;
        Unicode::fromUTF8((const uint8_t*)combined4.c_str(), score4Buffer, BUFFER_SIZE_RANK - 1);

        std::string scoreString5 = std::to_string(rankings[4].score);
        std::string combined5 = rankings[4].name + " - " + scoreString5;
        Unicode::fromUTF8((const uint8_t*)combined5.c_str(), score5Buffer, BUFFER_SIZE_RANK - 1);

        std::string scoreString6 = std::to_string(rankings[5].score);
        std::string combined6 = rankings[5].name + " - " + scoreString6;
        Unicode::fromUTF8((const uint8_t*)combined6.c_str(), score6Buffer, BUFFER_SIZE_RANK - 1);

        score1Buffer[BUFFER_SIZE_RANK - 1] = 0;
        score2Buffer[BUFFER_SIZE_RANK - 1] = 0;
        score3Buffer[BUFFER_SIZE_RANK - 1] = 0;
        score4Buffer[BUFFER_SIZE_RANK - 1] = 0;
        score5Buffer[BUFFER_SIZE_RANK - 1] = 0;
        score6Buffer[BUFFER_SIZE_RANK - 1] = 0;

        score1.setWildcard(score1Buffer);
        score2.setWildcard(score2Buffer);
        score3.setWildcard(score3Buffer);
        score4.setWildcard(score4Buffer);
        score5.setWildcard(score5Buffer);
        score6.setWildcard(score6Buffer);

        score1.invalidate();
        score2.invalidate();
        score3.invalidate();
        score4.invalidate();
        score5.invalidate();
        score6.invalidate();
    }
}
