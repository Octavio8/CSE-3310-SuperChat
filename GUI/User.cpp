#include "User.h"

User::User()
{

}

void User::set_user(string name, int grad, string ent_capt)
{
  nick = name;
  year = grad;
  captain = ent_capt;
  srand(time(NULL));
  UUID = rand() % 100+1;

  //cout << nick << endl;
  //cout << year << endl;
  //cout << captain << endl;
  //cout << UUID << endl;
}


string User::get_nick(User da_user)
{
    return nick;
}

int User::get_grad_year(User da_user)
{
    return year;
}

string User::get_captain(User da_user)
{
    return captain;
}

int User::get_UUID(User da_user)
{
    return UUID;
}

vector <User> User::get_ban(User da_user)
{
    return ban_list;
}
void User::set_nick(string name)
{
  nick = name;
}
