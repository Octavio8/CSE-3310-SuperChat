#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

using namespace std;


class Message
{
  public:
    Message();
    void set_msg(string, int, int);
    string get_msg(Message);
    int get_UUID(Message);
    string get_user(Message);
    bool get_prv(Message);
  private:
    string user;
    int UUID;
    string msg;
    bool prv_msg;
};


#endif
