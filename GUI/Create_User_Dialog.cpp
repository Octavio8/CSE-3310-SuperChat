#include "Create_User_Dialog.h"

///Global fltk variables that will be used throughout the file
Fl_Window *dialog;
Fl_Window *err_dialog;
Fl_Input *rp_nickname;
Fl_Input *rp_year;
Fl_Scrollbar *captain_scroll;
Fl_Output *captain_value;
Fl_Text_Display *error;
Fl_Button *error_okay;

int user_cap;
string allowed_captains[4] = {"kirk", "picard", "pike", "other"};
vector<User> create_dial_user;
vector<User> check_vec;

void error_okay_button_CB()
{
  err_dialog->hide();
}

void cancel_buttonCB(Fl_Widget* w, void* p)
{
  dialog->hide();
}

void cap_scroll_CB(Fl_Widget *w, void *p)
{
  char s[20];
  sprintf(s, "%d", captain_scroll->value());
  captain_value->value(s);
  string u = s;
  user_cap = atoi(u.c_str());
}

void print_from_vector()
{
  cout << "print from vec" << endl;
  int vec_siz = create_dial_user.size();

  for(int i = 0; i < vec_siz; i++)
  {
    User temp = create_dial_user[i];
    cout << temp.get_UUID(temp) << endl;
    cout << temp.get_nick(temp) << endl;
    cout << temp.get_grad_year(temp) << endl;
    cout << temp.get_captain(temp) << endl;
  }
}

void create_userCB(Fl_Widget* w, void* p)
{
  string nick, year;
  int year_num;
  int flag=0;
  int create = 1;

  nick = rp_nickname->value();
  year = rp_year->value();

   int siz = check_vec.size();
	
   for(int i = 0; i < siz; i++)
   {
     User temp = check_vec[i];
		
		cout << temp.get_UUID(temp) << endl;
		cout << temp.get_nick(temp) << endl;
		cout << temp.get_grad_year(temp) << endl;
		cout << temp.get_captain(temp) << endl;

		if(temp.get_nick(temp) == nick)
		{
			create = 0;
			fl_message("The nick already exists");
		}
	}

  if(year.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*.?;:,+'/}{]" "[><~` ") != string::npos)
  {
    err_dialog = new Fl_Window(320, 200, "ERROR!");
    error = new Fl_Text_Display(150,100, 0, 0, "Year must be an int!");
    error_okay = new Fl_Button(175, 150, 30, 25, "Okay");
    error_okay->callback((Fl_Callback*)error_okay_button_CB, 0);
    err_dialog->show();
    err_dialog->color(FL_RED);
    flag = 1;
    create = 0;	
  }

  else
  {
    year_num = atoi(year.c_str());
  }	

  if(nick.length() > 8)
  {
    err_dialog = new Fl_Window(320, 200, "ERROR!");
    error = new Fl_Text_Display(150,100, 0, 0, "Nick cannot have more than 8 characters!");
    error_okay = new Fl_Button(175, 150, 30, 25, "Okay");
    error_okay->callback((Fl_Callback*)error_okay_button_CB, 0);
    err_dialog->show();
    err_dialog->color(FL_RED);
    create = 0;
	
  }

  else if(nick.find_first_of("1234567890!@#$%^&*.?;:,+'/}{]" "[><~` ") != string::npos)
  {
    cout << "ERROR! Only Upper & Lower case letters allowed and '-' or '_'" << endl;
    err_dialog = new Fl_Window(320, 200, "ERROR!");
    error = new Fl_Text_Display(150,100, 0, 0, "Nick can only have upper, lower, '-', '_'");
    error_okay = new Fl_Button(175, 150, 30, 25, "Okay");
    error_okay->callback((Fl_Callback*)error_okay_button_CB, 0);
    err_dialog->show();
    err_dialog->color(FL_RED);
    create = 0;
  }

  else if (!(year_num >= 2017 && year_num <= 2040) && !flag)
  {
    cout << "ERROR! Year of graduation must be between 2017 and 2040" << endl;
    err_dialog = new Fl_Window(320, 200, "ERROR!");
    error = new Fl_Text_Display(150,100, 0, 0, "Graduation year must be between 2017 and 2040");
    error_okay = new Fl_Button(175, 150, 30, 25, "Okay");
    error_okay->callback((Fl_Callback*)error_okay_button_CB, 0);
    err_dialog->show();
    err_dialog->color(FL_RED);
    create = 0;	        
  }

  if(create == 1)
  {
    srand(time(NULL));
    int UUID = rand();// % 100+1;
    User init_user(nick, UUID, year_num, allowed_captains[user_cap-1]);
    create_dial_user.push_back(init_user);
    print_from_vector();
    dialog->hide();
  }
}

vector <User> Create_User_Dialog::get_users()
{
	return create_dial_user;
}


void Create_User_Dialog::run_print()
{
	print_from_vector();
}

///This function displays the GUI for the Sign-Up window
void Create_User_Dialog::sign_them_up(vector<User> da_users)
{
  check_vec = da_users;

  //create_dial_user = da_users;
  dialog = new Fl_Window(500, 350, "New User");
  dialog->position((Fl::w() - dialog->w())/2, (Fl::h() - dialog->h())/2);
  dialog->color(FL_DARK_CYAN);

  //Create box for message
  Fl_Box* box = new Fl_Box(150, 10, 200, 30, "Please Enter the following fields:");
  box->labelsize(15);
  dialog->resizable(box);

  //Nickname Input field
  rp_nickname = new Fl_Input(150, 40, 210, 25, "Nickname:");
  rp_nickname->align(FL_ALIGN_LEFT);

  //Graduation Input field
  rp_year = new Fl_Input(150, 70, 210, 25, "Graduation Year:");
  rp_year->align(FL_ALIGN_LEFT);

  //Scroll bar data for captains
  captain_scroll = new Fl_Scrollbar(100, 150, 30, 75);
  //captain_scroll->slider_size(1);
  captain_scroll->bounds(1,4);
  captain_scroll->step(1);
  captain_scroll->callback(cap_scroll_CB, (void*)&captain_value);

  //Box that displays captains
  Fl_Box* captains = new Fl_Box(230, 100, 50, 150, "Use scroll bar to make selection:\n(1) Kirk\n(2) Picard\n(3) Pike\n(4) Other");
  captains->labelsize(15);

  //Captain data input (different from nickname)
  captain_value = new Fl_Output(150, 100, 210, 25, "Captain Value");
  captain_value->textsize(24);

  //Create button for new user      
  rp_create = new Fl_Return_Button(240, 270, 100, 25, "Create");
  rp_create->callback((Fl_Callback *)create_userCB, 0);

  //Cancel button for new user
  rp_cancel = new Fl_Button(350, 270, 100, 25, "Cancel");
  rp_cancel->callback((Fl_Callback *)cancel_buttonCB, 0);
      
  dialog->end();
  dialog->set_non_modal();
  dialog->show();
}
