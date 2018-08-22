#ifndef VIEW_CHATROOM_WINDOW_H
#define VIEW_CHATROOM_WINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/fl_ask.H>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class View_Chatroom_Window
{
  public:
    View_Chatroom_Window(){ }
    void show_the_rooms(string);
    void update_the_vec(string);
    vector<string> pub_vec;
    //pub_vec.push_back("Public");
};


#endif
