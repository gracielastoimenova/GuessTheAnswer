#ifndef FINALPRESENTER_HPP
#define FINALPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class FinalView;

class FinalPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    FinalPresenter(FinalView& v);

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

    virtual ~FinalPresenter() {}

private:
    FinalPresenter();

    FinalView& view;
};

#endif // FINALPRESENTER_HPP
