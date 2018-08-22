#ifndef USER_H
#define USER_H

#include <vector>
#include <cstdlib>
#include <string.h>
#include <time.h>


#include "Message.h"

using namespace std;

class User
{
  public:
    User();
    User(string name_1, int id_1, int grad_1, string capitan_1)
    {
      nick = name_1;
      UUID = id_1;
      year = grad_1;
      captain = capitan_1;
    }
    void set_user(string, int, string);
    void create_msg();
    void send_message(Message);
    //void make_offline();
    void put_in_ban(User);
    void set_nick(string);
    string get_nick(User);
    int get_UUID(User);
    int get_grad_year(User);
    string get_captain(User);
    vector <User> get_ban(User);
  private:
    string nick;
    int UUID;
    int year;
    string captain;
    //bool online;
    vector <User> ban_list;
};

#endif
