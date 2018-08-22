#ifndef SUPERCHAT_ACCESS_H
#define SUPERCHAT_ACCESS_H
#include <FL/Fl.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>

#include "Controller.h"
#include "Message.h"
#include "User.h"

class SuperChat_Access
{
  public:
    void Chat_Window(string chat_win_name, int chat_index, string name);
    void run_chatroom(string chat_win_name);
    void disp_msg(vector <Message>);
    void put_msg_in_vec(Message);
    void disp_chat_user(vector <User>);
  private:
    vector <Message> the_msg;
    vector <User> the_users;
    string room_name;
    int room_index;
    Fl_Button* button;

};


#endif
