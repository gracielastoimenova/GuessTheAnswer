/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef WELCOMEVIEWBASE_HPP
#define WELCOMEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/welcome_screen/WelcomePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class WelcomeViewBase : public touchgfx::View<WelcomePresenter>
{
public:
    WelcomeViewBase();
    virtual ~WelcomeViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image1;
    touchgfx::TextArea title1;
    touchgfx::TextArea title2;
    touchgfx::TextArea title3;
    touchgfx::ButtonWithLabel buttonWithLabel1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<WelcomeViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // WELCOMEVIEWBASE_HPP
