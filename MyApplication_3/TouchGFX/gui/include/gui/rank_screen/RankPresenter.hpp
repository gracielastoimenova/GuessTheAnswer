#ifndef RANKPRESENTER_HPP
#define RANKPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RankView;

class RankPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    RankPresenter(RankView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~RankPresenter() {}

private:
    RankPresenter();

    RankView& view;
};

#endif // RANKPRESENTER_HPP
