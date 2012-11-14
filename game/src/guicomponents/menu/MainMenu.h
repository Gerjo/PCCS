#ifndef MAINMENU_H_
#define MAINMENU_H_
#include <phantom.h>

class MainMenu : public phantom::Composite
{
public:
    MainMenu();
    ~MainMenu();
    
    void paint();
    void update(const phantom::Time& time);

private:
    bool _repaint;
};
#endif
