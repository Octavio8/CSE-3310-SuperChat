#ifndef CREATE_USER_DIALOG
#define CREATE_USER_DIALOG

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <iostream>
#include <string>
#include <string.h>

#include "Sign_Up.h"
#include "User.h"

using namespace std;

class Create_User_Dialog
{
  public:
    void sign_them_up(vector<User>);
    vector<User> get_users();
    void run_print();

  private:
    Fl_Return_Button *rp_create;
    Fl_Button *rp_cancel;
};
#endif
