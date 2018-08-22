#include "Controller.h"

///Global fltk variables that will be used throughout the file
Fl_Window *win;
Fl_Button *rp_sign_up;
Fl_Button *close_main;
Fl_Button *log_in;
Fl_Button *info_super;
Fl_Button *save_user;
Fl_Button *da_rooms;
Fl_Box *welcome_box;

Create_User_Dialog sign_up_screen;
Log_In log_in_screen;
View_Chatroom_Window them_chatrooms;
string main_user;

///A list of users of type User
vector<User> list_da_users, from_other;

void to_file(vector<User> user_l)
{
  ofstream user_file;
  user_file.open("File_User.txt");
  user_file << "UUID"  << " " << setw(25) << "Nick" << " " << setw(20) << "Year" << " " << setw(20) << "Captain" << endl;
  user_file << endl;
  int use_s = user_l.size();
  //cout << "print vector size" << use_s << endl;

  for(int i = 0; i < use_s; i++)
  {
    //cout << "i = " << i << endl;
    User temp;

    //int UUID, year;
    //string name, captain;
    temp = user_l[i];
    //UUID = temp.get_UUID(temp)

    user_file << temp.get_UUID(temp) << " " << setw(20) << temp.get_nick(temp) << " " << setw(20) << temp.get_grad_year(temp) << " " << setw(20) << temp.get_captain(temp) << endl;
  }
  user_file.close();
}

void from_file()
{
  ifstream to_vec;
  to_vec.open("File_User.txt");

  int counter = 0;

  string name, captain, UUID_s, year_s;
  int UUID, year;

  //cout << "from file at opening" << endl;
	
  while(to_vec >> UUID_s >> name >> year_s >> captain)
  {
    if(counter > 0)
    {
      UUID = stoi(UUID_s);
      year = stoi(year_s);
      User temp(name, UUID, year, captain);
      list_da_users.push_back(temp);
    }
    counter++;
  }

  to_vec.close();
  int vec_siz = list_da_users.size();

  for(int i = 0; i < vec_siz; i++)
  {
    User temp = list_da_users[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
}

void handle_close()
{
  from_other = sign_up_screen.get_users();
  list_da_users.reserve(list_da_users.size() + from_other.size());
  //list_da_users.insert(list_da_users.end(), list_da_users.begin(), list_da_users.end());
  list_da_users.insert(list_da_users.end(), from_other.begin(), from_other.end());

  //cout << "handle close" << endl;
  int vec_siz = list_da_users.size();

  for(int i = 0; i < vec_siz; i++)
  {
    //cout << "i = " << i << endl;
    User temp = list_da_users[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
  to_file(list_da_users);
}

void info_super_CB(Fl_Widget *w, void *p)
{
  fl_message("SuperChat is a free messaging service\nThis service was provided by:\nNatnael\nAninda\nOctavio\nCarlos");
}

void interval_update()
{	
  from_other = sign_up_screen.get_users();
  int vec_siz = from_other.size();

  //cout << "interval update vector size: " << vec_siz << endl;
  //cout << "interval_update CB" << endl;

  for(int i = 0; i < vec_siz; i++)
  {
    User temp = from_other[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
  handle_close();
}

void sign_up_CB(Fl_Widget *w, void *p)
{
  sign_up_screen.sign_them_up(list_da_users);
  //cout << "sign up callback" << endl;
  sign_up_screen.run_print();

  from_other = sign_up_screen.get_users();
  //cout << "sign up CB" << endl;
  int vec_siz = from_other.size();

  for(int i = 0; i < vec_siz; i++)
  {
    User temp = from_other[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
  from_other = sign_up_screen.get_users();
  //interval_update();
}

void close_main_CB(Fl_Widget *w, void *p)
{
  from_other = sign_up_screen.get_users();
  int vec_siz = from_other.size();

  //cout << "close main CB vector size: " << vec_siz << endl;
  //cout << "close main CB" << endl;

  for(int i = 0; i < vec_siz; i++)
  {
    User temp = from_other[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
  //handle_close();
  //to_file(list_da_users);
  win->hide();
}

///This function will open the chatroom window if the user has logged in
void da_rooms_CB(Fl_Widget *w, void *p)
{
  //cout << "view rooms CB" << endl;
  main_user = log_in_screen.get_logged_in_user();
  if(!(main_user.empty()))
  {
    //cout << "The main user is: " << main_user << endl;
    them_chatrooms.show_the_rooms(main_user);
  }
  else
  {
    fl_message("Please log in to see chatrooms.");
  }
}

///Function will save the last user signed up to the FileUser.txt
void save_CB(Fl_Widget *w, void *p)
{
  from_other = sign_up_screen.get_users();
  int vec_siz = from_other.size();
  //cout << "save CB vector size: " << vec_siz << endl;
  //cout << "save CB" << endl;

  for(int i = 0; i < vec_siz; i++)
  {
    User temp = from_other[i];
    //cout << temp.get_UUID(temp) << endl;
    //cout << temp.get_nick(temp) << endl;
    //cout << temp.get_grad_year(temp) << endl;
    //cout << temp.get_captain(temp) << endl;
  }
  handle_close();
}

///This function will open the log in window
void log_in_CB(Fl_Widget *w, void *p)
{	
  log_in_screen.log_s();
  //cout << "log_in_CB" << endl;
}


Controller::Controller()
{
	
}

///This function displays the Welcome window with all the buttons that the user
///will need
int Controller::run_the_show()
{
  from_file();
    
  const int X = 900;
  const int Y = 500;

  ///functions that will create a window and center it on the screen
  win = new Fl_Window(X, Y, "SuperChat");
  win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);
  win->color(FL_DARK_CYAN);

  ///Title for the welcome window
  welcome_box = new Fl_Box(300, 40, 260, 100, "Welcome to SuperChat!!");
  welcome_box->labelsize(36);
  welcome_box->labelfont(FL_BOLD);
  win->resizable(welcome_box);

  ///Sign-Up Button
  rp_sign_up = new Fl_Button(310, 200, 140, 50, "Sign Up");
  rp_sign_up->callback((Fl_Callback *)sign_up_CB, 0);

  ///Log-In Button
  log_in = new Fl_Button(450, 200, 140, 50, "Log In");
  log_in->callback((Fl_Callback *)log_in_CB, 0);

  ///Save User Button
  save_user = new Fl_Button(310, 250, 140, 50, "Save User");
  save_user->callback((Fl_Callback *)save_CB, 0);

  ///Information Button
  info_super = new Fl_Button(310, 300, 140, 50, "Info");
  info_super->callback((Fl_Callback *)info_super_CB,0);

  ///View Rooms Button
  da_rooms = new Fl_Button(450, 250, 140, 50, "View Rooms");
  da_rooms->callback((Fl_Callback *)da_rooms_CB, 0);

  ///Exit Button
  close_main = new Fl_Button(450, 300, 140, 50, "Exit");
  close_main->callback((Fl_Callback *)close_main_CB,0);

  win->end();
  win->show();

  return Fl::run();
}
