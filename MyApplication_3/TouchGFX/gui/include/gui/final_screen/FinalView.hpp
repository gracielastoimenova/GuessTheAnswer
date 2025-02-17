#ifndef FINALVIEW_HPP
#define FINALVIEW_HPP

#include <gui_generated/final_screen/FinalViewBase.hpp>
#include <gui/final_screen/FinalPresenter.hpp>

class FinalView : public FinalViewBase
{
public:
    FinalView();
    virtual ~FinalView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // FINALVIEW_HPP
