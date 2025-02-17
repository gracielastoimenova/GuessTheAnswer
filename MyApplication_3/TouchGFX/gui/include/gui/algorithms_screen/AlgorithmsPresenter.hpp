#ifndef ALGORITHMSPRESENTER_HPP
#define ALGORITHMSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AlgorithmsView;

class AlgorithmsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AlgorithmsPresenter(AlgorithmsView& v);

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

    virtual ~AlgorithmsPresenter() {}

private:
    AlgorithmsPresenter();

    AlgorithmsView& view;
};

#endif // ALGORITHMSPRESENTER_HPP
