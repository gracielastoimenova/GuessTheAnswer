#ifndef CATEGORIESVIEW_HPP
#define CATEGORIESVIEW_HPP

#include <gui_generated/categories_screen/CategoriesViewBase.hpp>
#include <gui/categories_screen/CategoriesPresenter.hpp>

class CategoriesView : public CategoriesViewBase
{
public:
    CategoriesView();
    virtual ~CategoriesView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CATEGORIESVIEW_HPP
