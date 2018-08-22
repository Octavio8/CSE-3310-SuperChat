#ifndef LOG_IN_H
#define LOG_IN_H

#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/fl_ask.H>

#include "User.h"

using namespace std;

class Log_In
{
  public:
    Log_In(){}

    void log_s();
    string get_logged_in_user();
    //void set_default_user();
    //User get_user();
  private:
    //User default_user;
    //ifstream from_file;
};

#endif
