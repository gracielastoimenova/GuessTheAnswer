#ifndef DATABASESPRESENTER_HPP
#define DATABASESPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DatabasesView;

class DatabasesPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DatabasesPresenter(DatabasesView& v);

    virtual void activate();

    virtual void deactivate();

    virtual ~DatabasesPresenter() {}

private:
    DatabasesPresenter();

    DatabasesView& view;
};

#endif // DATABASESPRESENTER_HPP
