#include "View_Chatroom_Window.h"
#include "SuperChat_Access.h"

Fl_Window* chatroom_win;
Fl_Menu_Bar* menubar;
Fl_Window* create_new_room;
Fl_Input* chatroom_name_inp;
Fl_Button* chat_name_butt;
Fl_Box *privacy_box;
Fl_Button *chatroomButton;
Fl_Button *add_room;
Fl_Browser *browser;
Fl_Input_Choice *chatroom_choice;

string prime_user;
int chat_index =0;
int num_of_chatrooms = 1;
vector<struct chatrooms_available> customed_rooms;
char chat_room_name[25] = "Public";
char const *chat_ind;
vector<string> name_of_rooms;

struct chatrooms_available
{
  Fl_Button *chat_name;
  Fl_Box *chat_index;
};

//Chatroom new_chat;

void chat_butt_CB(Fl_Widget *w, void *p)
{
  string temp;
  int siz = name_of_rooms.size();
  cout << " siz = " << siz << endl;
  temp = chatroom_choice->value();
  assert(chat_index < 11);
  if(temp == "Public")
  {
    cout <<"in public " << endl;
    chat_index = 0;
    SuperChat_Access obj;
    obj.Chat_Window(temp, chat_index, prime_user);
    //removed chat_index++
    //chat_index = chat_index + 1;
  }
  else
  {
    for(int i = 0; i < siz; i++)
    {
      if(temp == name_of_rooms[i])
      {
	cout << "in custom " << temp << endl;
	chat_index = i+1;
	SuperChat_Access obj;
	obj.Chat_Window(temp, chat_index, prime_user);
	break;
      }
    }
  }
  //cout << "chosen room is " << temp << endl;
  //cout << "chat index is " << chat_index << endl;
  //cout << "primary user is " << prime_user << endl;
  //new_chat.run_chatroom(temp);
}

void view_room_CB(Fl_Widget *w, void *p)
{
  Fl_Window *chatroom_win = new Fl_Double_Window(350, 150, "Chatrooms");
  chatroom_win->position((Fl::w() - chatroom_win->w())/2, (Fl::h() - chatroom_win->h())/2);
  chatroom_win->color(FL_DARK_CYAN);
  chatroom_choice = new Fl_Input_Choice(160, 30, 100, 30,"Choose a Chatroom: ");
  chatroom_choice->add("Public");
  int toto_size = customed_rooms.size();
  for(int i = 0; i <toto_size; i++)
  {
    cout << "size of customed_rooms " << customed_rooms.size() << endl;
    cout << "name of room " << name_of_rooms[i] << endl;
    strncpy(chat_room_name, name_of_rooms[i].c_str(), sizeof(name_of_rooms[i]));
    chatroom_choice->add(chat_room_name);
  }
  Fl_Button *create_chat_room = new Fl_Button(200, 100, 70, 35,"Open");
  create_chat_room->callback((Fl_Callback *)chat_butt_CB, 0);
  chatroom_win->show();
}

void enter_chat_name_CB(Fl_Widget *w, void *p)
{
  string chat_name;
  int siz = customed_rooms.size();
	
  chat_name = chatroom_name_inp->value();
  name_of_rooms.push_back(chat_name);
  strncpy(chat_room_name, chat_name.c_str(), sizeof(chat_name));
	
  string s = to_string(siz-1);
  chat_ind = s.c_str();	

  struct chatrooms_available temp;
  temp.chat_name = new Fl_Button(100, siz-1 * 50, 200, siz-1 * 50, chat_room_name);
  temp.chat_index = new Fl_Box(50, siz-1 * 50, 50, siz-1 * 50, chat_ind);
  customed_rooms.push_back(temp);
	
  //strncpy(chat_type, c_t.c_str(), sizeof(c_t));
  create_new_room->hide();
}

void NewCB(Fl_Widget* w, void* p)
{
  num_of_chatrooms++;
  if(num_of_chatrooms > 10)
  {
    //cout << "num of rooms " << num_of_chatrooms << endl;
    fl_message("Cannot have more than 10 chatrooms");
  }
  else
  {
    //cout << "num of rooms " << num_of_chatrooms << endl;
    create_new_room = new Fl_Window(300, 150, "New Room");
    create_new_room->color(FL_DARK_CYAN);
    create_new_room->position((Fl::w() - create_new_room->w())/2, (Fl::h() - create_new_room->h())/2);
    chatroom_name_inp = new Fl_Input(75, 30, 200, 30, "Name:");
    chat_name_butt = new Fl_Button(150, 75, 75, 30, "Create");
    chat_name_butt->callback((Fl_Callback *)enter_chat_name_CB, 0);
    create_new_room->show();
  }
}


void ExitCB(Fl_Widget* w, void* p)
{
  chatroom_win->hide();
}


Fl_Menu_Item menuitems[] = {
  {"&Chatroom", 0,0,0, FL_SUBMENU},
    {"Create Chatroom", 0, (Fl_Callback*)NewCB},
    //{"Delete Chatroom", 0, (Fl_Callback*)delete_chatroomCB},
    {0},
  //{"&Users", 0,0, 0, FL_SUBMENU},
    //{"List Users", 0, (Fl_Callback *)display_usersCB},
    //{0},
  //{"&Setting", 0,0,0, FL_SUBMENU},
  //  {"Change Nickname", 0, (Fl_Callback *)change_nicknameCB},
  //  {"Exit", 0, (Fl_Callback *)ExitCB},
  //  {0},
  {0}
};

void View_Chatroom_Window::update_the_vec(string da_name)
{

}

void View_Chatroom_Window::show_the_rooms(string name)
{
  //name_of_rooms.push_back("Public");
  prime_user = name;
  Fl_Window *chatroom_win = new Fl_Double_Window(300, 150, "Chatrooms");
  chatroom_win->position((Fl::w() - chatroom_win->w())/2, (Fl::h() - chatroom_win->h())/2);
  chatroom_win->color(FL_DARK_CYAN);
  chat_name_butt = new Fl_Button(50, 70, 200, 30, "View Chatrooms");
  chat_name_butt->callback((Fl_Callback *)view_room_CB);
	
  menubar = new Fl_Menu_Bar(0, 0, 500, 30);
  menubar->menu(menuitems);

  chatroom_win->resizable(chatroom_win);
  chatroom_win->show();
}
