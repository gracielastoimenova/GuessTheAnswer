#ifndef EMBEDDEDPRESENTER_HPP
#define EMBEDDEDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class EmbeddedView;

class EmbeddedPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    EmbeddedPresenter(EmbeddedView& v);

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

    virtual ~EmbeddedPresenter() {}

private:
    EmbeddedPresenter();

    EmbeddedView& view;
};

#endif // EMBEDDEDPRESENTER_HPP
