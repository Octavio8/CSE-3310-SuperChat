#include "Log_In.h"

///global fltk variables that will be used troughout the file
Fl_Window *log_screen;
Fl_Window *success_win;
Fl_Window *unsuc_win;
Fl_Text_Display *log_msg;
Fl_Input *name;
Fl_Output *cap_val;
Fl_Scrollbar *cap_scroll;
Fl_Button *log_in_enter;
Fl_Button *log_ok;

Fl_Button *change_nick;
Fl_Window *change_nick_win;
Fl_Input *change_nick_input;
Fl_Input *change_nick_input_1;
Fl_Button *enter_change_nick;

string nick_to_be_changed;
string da_new_nick;

string logged_in_user;
int user_capi;
string allowed_captain[4] = {"kirk", "picard", "pike", "other"};
vector<User> log_vec;

void to_da_file(vector<User> user_l)
{
  ofstream user_file;
  user_file.open("File_User.txt");
  user_file << "UUID"  << " " << setw(25) << "Nick" << " " << setw(20) << "Year" << " " << setw(20) << "Captain" << endl;
  user_file << endl;
  int use_s = user_l.size();

  cout << "print vector size" << use_s << endl;
  for(int i = 0; i < use_s; i++)
  {
    cout << "i = " << i << endl;
    User temp;
    //int UUID, year;
    //string name, captain;
    temp = user_l[i];
    //UUID = temp.get_UUID(temp)
    user_file << temp.get_UUID(temp) << " " << setw(20) << temp.get_nick(temp) << " " << setw(20) << temp.get_grad_year(temp) << " " << setw(20) << temp.get_captain(temp) << endl;
  }
    user_file.close();
}

void ok_change_name_CB(Fl_Widget *w, void *p)
{
  User temp;
  int flag = 1;

  string old_nick = change_nick_input->value();
  string new_nick = change_nick_input_1->value();
	
  cout << "new nick2 " << new_nick << endl;
  cout << "old nick2 " << old_nick << endl;
	
  int vec_s = log_vec.size();
	
  cout << "log vec size = " << vec_s << endl;
  //cout << temp.get_nick(temp).compare(nick) << endl;

  for(int i = 0; i < vec_s; i++)
  {
    temp = log_vec[i];	
    cout << "new nick " << new_nick << endl;
    cout << "old nick " << old_nick << endl;
    string nick_1 = temp.get_nick(temp);
    cout << "vec_nick " << nick_1 << endl;
    if(old_nick == nick_1)
    {
      flag = 0;
      log_vec[i].set_nick(new_nick);
      change_nick_win->hide();
      to_da_file(log_vec);
      break;
    }
  }
  if(flag == 1)
  {
    fl_message("The nickname does not exist");
  }
  for(int i = 0; i < vec_s; i++)
  {
    User temp = log_vec[i];
    cout << temp.get_UUID(temp) << endl;
    cout << temp.get_nick(temp) << endl;
    cout << temp.get_grad_year(temp) << endl;
    cout << temp.get_captain(temp) << endl;
  }
}

void change_nick_CB(Fl_Widget *w, void *p)
{
  log_screen->hide();
  cout << "rename nick" << endl;
  change_nick_win = new Fl_Window(300, 200, "Change Nickname");
  change_nick_win->position((Fl::w() - change_nick_win->w())/2, (Fl::h() - change_nick_win->h())/2);
  change_nick_win->color(FL_DARK_CYAN);

  change_nick_input = new Fl_Input(140, 30, 150, 30, "Old Nickname:");
  change_nick_input_1 = new Fl_Input(140, 70, 150, 30, "New Nickname:");

  enter_change_nick = new Fl_Button(130, 120, 140, 35, "Update Nickname");
  enter_change_nick->callback((Fl_Callback*)ok_change_name_CB, 0);
	
  change_nick_win->resizable(change_nick_win);
  change_nick_win->show();
	
}

///Window will appear if either log in was succesfull or failed
void success_CB(Fl_Widget *w, void *p)
{
  success_win->hide();
}

///This callback is called by the scrollbar
void log_scroll_CB(Fl_Widget *w, void *p)
{
  char s[20];
  sprintf(s, "%d", cap_scroll->value());
  cap_val->value(s);
  string u = s;
  user_capi = atoi(u.c_str());
}

///function will handle if the user sign up properly or not
void log_in_enter_CB()
{
  string nick, cap, nick_1, cap_1;
  cap = allowed_captain[user_capi-1];
  int flag = 0;
  User temp;
  nick = name->value();
  int vec_s = log_vec.size();
  //cout << "log vec size = " << vec_s << endl;
  //cout << temp.get_nick(temp).compare(nick) << endl;
  for(int i = 0; i < vec_s; i++)
  {
    temp = log_vec[i];
    nick_1 = temp.get_nick(temp);
    cap_1 = temp.get_captain(temp);
    //cout << "login i = " << i << endl;
    if((nick_1 == nick))
    {
      //cout << "1login i = " << i << endl;
      ///Window will appear if user logs in properly
      if(cap == cap_1)
      {
        //cout << "2login i = " << i << endl;
	flag = 1;
	success_win = new Fl_Window(320, 200, "Log-In Successful");
        success_win->position((Fl::w()-success_win->w())/2, (Fl::h()-success_win->h())/2);
	log_msg = new Fl_Text_Display(145,100,0,50, "Log-In Success!");
	log_ok = new Fl_Button(130, 125, 70, 35, "Ok");
	log_ok->callback((Fl_Callback*)success_CB,0);
	success_win->show();
	success_win->color(FL_DARK_CYAN);
	logged_in_user = nick_1;
	log_screen->hide();
	break;
      }		
    }	
  }
  ///Window will appears if the User failed to log in properly
  if(flag == 0)
  {
    success_win = new Fl_Window(320, 200, "Log-In Failure");
    success_win->position((Fl::w()-success_win->w())/2, (Fl::h()-success_win->h())/2);
    log_msg = new Fl_Text_Display(145,100,0,100, "Log In Failure!");
    log_ok = new Fl_Button(130, 125, 70, 35, "Ok");
    log_ok->callback((Fl_Callback*)success_CB,0);
    success_win->show();
    success_win->color(FL_DARK_CYAN);
  }
}

void from_da_file()
{
  ifstream to_vec;
  to_vec.open("File_User.txt");
	
  int counter = 0;
  string name, captain, UUID_s, year_s;
  int UUID, year;

  //cout << "from file at opening log_in" << endl;
	
  while(to_vec >> UUID_s >> name >> year_s >> captain)
  {
    if(counter > 0)
    {
      UUID = stoi(UUID_s);
      year = stoi(year_s);
      User temp(name, UUID, year, captain);
      log_vec.push_back(temp);
    }
    counter++;
  }
  to_vec.close();
  int vec_siz = log_vec.size();
  for(int i = 0; i < vec_siz; i++)
  {
    User temp = log_vec[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
}


void Log_In::log_s()
{
  from_da_file();

  ///Window Settings
  log_screen = new Fl_Window(500, 400, "Log In");
  log_screen->position((Fl::w() - log_screen->w())/2, (Fl::h() - log_screen->h())/2);
  log_screen->color(FL_DARK_CYAN);

  ///Display message as a box and not as a seperate window
  Fl_Box* box = new Fl_Box(120, 0, 260, 50, "Please Enter the following fields:");
  box->labelsize(15);
  log_screen->resizable(box);

  ///Nickname input field
  name = new Fl_Input(145, 50, 210, 25, "Nickname:");

  ///Scrollbar information
  cap_scroll = new Fl_Scrollbar(90, 115, 30, 75);
  cap_scroll->bounds(1,4);
  cap_scroll->step(1);
  cap_scroll->callback(log_scroll_CB, (void*)&cap_val);

  ///Captain input field (different from nickname)
  cap_val = new Fl_Output(145, 80, 210, 25, "Captain:");
  cap_val->textsize(24);

  ///Print captain options for the scrollbar
  Fl_Box* box_captains = new Fl_Box(140, 60, 260, 200, "Use scroll bar to make selection:\n(1)Kirk\n(2)Picard\n(3)Pike\n(4)Other");
  box_captains->labelsize(15);

  ///Enter Button
  log_in_enter = new Fl_Button(350, 270, 70, 35, "Enter");
  log_in_enter->callback((Fl_Callback*)log_in_enter_CB, 0);

  ///Button will allow the user to change their nickname whenever they want
  change_nick = new Fl_Button(200,270, 140, 35, "Change Nickname");
  change_nick->callback((Fl_Callback*)change_nick_CB, 0);

  log_screen->end();
  log_screen->set_non_modal();
  log_screen->show();
}

string Log_In::get_logged_in_user()
{
	return logged_in_user;
}
