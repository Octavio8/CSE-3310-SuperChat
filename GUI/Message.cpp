#include "Message.h"

Message::Message()
{

}

void Message::set_msg(string nick, int id, int prv)
{
  cout << "Enter Message: ";
  cin.ignore();
  getline(cin, msg);
  cout << endl;

  while(msg.length() > 144)
  {
    cout << "ERROR! Message cannot be more than 144 characters" << endl;
    cout << endl;
    cout << "Enter Message: ";
    getline(cin, msg);
  }
  UUID = id;
  user = nick;
  //have to add the private message bool
}

string Message::get_msg(Message)
{
  return msg;
}

int Message::get_UUID(Message)
{
  return UUID;
}

string Message::get_user(Message)
{
  return user;
}
