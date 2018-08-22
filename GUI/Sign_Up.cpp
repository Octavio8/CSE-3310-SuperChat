#include "Sign_Up.h"

Sign_Up::Sign_Up()
{
}

void Sign_Up::set_user()
{
}

void Sign_Up::create_user(string name, int year, int choice)
{
  User new_user;
  new_user.set_user(name,year, allowed_captains[choice-1]);
  //user_to_file(new_user);
}

void Sign_Up::user_to_file(User u_save)
{
  user_file.open("File_User.txt");
  user_file << "UUID"  << " " << setw(25) << "Nick" << " " << setw(20) << "Year" << " " << setw(20) << "Captain" << endl;
  user_file << endl;

  user_file << u_save.get_UUID(u_save) << " " << setw(20) << u_save.get_nick(u_save) << " " << setw(20) << u_save.get_grad_year(u_save) << " " << setw(20) << u_save.get_captain(u_save) << endl;
}
