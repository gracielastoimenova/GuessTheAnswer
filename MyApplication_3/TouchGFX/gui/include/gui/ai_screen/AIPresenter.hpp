#ifndef AIPRESENTER_HPP
#define AIPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AIView;

class AIPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AIPresenter(AIView& v);

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

    virtual ~AIPresenter() {}

private:
    AIPresenter();

    AIView& view;
};

#endif // AIPRESENTER_HPP
