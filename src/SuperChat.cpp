#include <signal.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "DDSEntityManager.h"
#include "ccpp_SuperChat.h"

#include "nicks.h"
//*****************************start**************************
#include "SuperChat_Access.h"
thread one;
mutex controll;
Fl_Window *chat_window;
Fl_Multiline_Input *send_da_chat;
Fl_Text_Display *receive_da_chat;
Fl_Button *send_msg;
string message_going_out;
Fl_Text_Display* send_count;
Fl_Text_Display* received_count;
Fl_Text_Display* user_count;
Fl_Text_Buffer* send_count_buff = new Fl_Text_Buffer();
Fl_Text_Buffer* received_count_buff = new Fl_Text_Buffer();
Fl_Text_Buffer* user_count_buff = new Fl_Text_Buffer();
unsigned long chat_index_cmp;
string user_nick;

Fl_Text_Buffer *buff = new Fl_Text_Buffer();
static unsigned long received = 0;
static unsigned long sent = 0;
static string Message_Received;

// create the uuid for this user, this session
long long int myUUID;

//*****************************End****************************


// This code is derived from the PrismTech HelloWorld examples

// You can include this code freely in your project.  Or not.

// This example program will show how to publish and subscribe 
// to the data items used in SuperChat.  

// It can be modified easily to provide data for software testing and
// debugging.

const bool sendChatroom = true;
const bool sendMsg = true;
const bool sendUser = true;
const bool recvChatroom = true;
const bool recvUser = true;
const bool recvMsg = true;


using namespace DDS;
using namespace SuperChat;

// these classes abstract out the sending and recieving of topics
// perhaps with some cleverness, generics could be used to eliminate
// some of the code 

typedef std::vector<chatroom> chatroom_list_t;
typedef std::vector<message> message_list_t;
typedef std::vector<user> user_list_t;

struct Active_Users
{
  char nick[NICK_SIZE_MAX];
  //seconds variable to indicate activity time
  int seconds;
};

typedef std::vector<Active_Users> active_users_list;

active_users_list active_users;

class chatroom_data
{
  private:
  DDSEntityManager em;
  chatroomDataWriter_var Writer;
  chatroomDataReader_var Reader;
  public:
  void send ( chatroom messageInstance )
  {
     ReturnCode_t status = Writer->write(messageInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( chatroom_list_t* chatroomList )
  {
     // if any data is available, it returns a list
     assert ( chatroomList );
     chatroomSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       chatroomList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  chatroom_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    chatroomTypeSupport_var T = new chatroomTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = chatroomDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = chatroomDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~chatroom_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};

class message_data
{
  private:
  DDSEntityManager em;
  messageDataWriter_var Writer;
  messageDataReader_var Reader;
  public:
  void send ( message messageInstance )
  {
     ReturnCode_t status = Writer->write(messageInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( message_list_t* messageList )
  {
     // if any data is available, it returns a list
     assert ( messageList );
     messageSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       messageList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  message_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    messageTypeSupport_var T = new messageTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = messageDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = messageDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~message_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};

class user_data
{
  private:
  DDSEntityManager em;
  userDataWriter_var Writer;
  userDataReader_var Reader;
  public:
  void send ( user userInstance )
  {
     ReturnCode_t status = Writer->write(userInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( user_list_t* userList )
  {
     // if any data is available, it returns a list
     assert ( userList );
     userSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       userList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  user_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    userTypeSupport_var T = new userTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = userDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = userDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~user_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};
//********************************start*******************************
chatroom_data chatRoom ( (char*) "chatroom" );
  user_data User ( (char*) "user" );
  message_data Message ( (char*) "msg" );
//********************************end*********************************
///////////////////////////////////////////////////////////////////////////////
bool exit_flag = false;

void ctrlc ( int )
{
   exit_flag = true;
}
///////////////////////////////////////////////////////////////////////////////

std::deque<std::string> messageQ;

void callback (void*)
{
  // when this routine is called, you can call any Fltk routines
  // safely
  // this routine is called all the time when the gui is not active.
  // it can 'eat the machine' if we are not careful; thus
  // the usleep below
  //
  if ( messageQ.size () > 0 )  
  {
     //std::cout << "pulling one out " << '\n';
     buff->text(messageQ.front().c_str());
     messageQ.pop_front (); // delete the one just processed

     chat_window->redraw ();
     receive_da_chat->wrap_mode(100, 100);
//buff->remove_selection();
     receive_da_chat->redraw ();
     Fl::flush ();

  }
  else
  {
     usleep (10000);  // 1/10 of a second
  }
}

void display_msg_send();

void send_message_function(Fl_Widget *w, void *p)
{
int count = 0;
    // message topic
	message_going_out = send_da_chat->value();
	char *fill =  new char[message_going_out.length() + 1];
	strcpy(fill, message_going_out.c_str());
	//buff = send_da_chat->value();
	//message_going_out = buff->text();
	send_da_chat->value("");
	send_da_chat->clear_output();
      message messageInstance;
      strncpy ( messageInstance.message, message_going_out.c_str(), sizeof ( messageInstance.message ) );
         messageInstance.uuid = myUUID;
         messageInstance.chatroom_idx = chat_index_cmp;
         messageInstance.cksum = 0;
         messageInstance.seqno = count;
         count++;
         Message.send ( messageInstance );
	sent++;
        string temp = to_string(sent);
        const char* count_msg = temp.c_str();
        send_count_buff->text(count_msg);
        //display_msg_send();
	delete[] fill; 
          
}

///Function will display the number of messages send by the user
void display_msg_send()
{
  send_count = new Fl_Text_Display(30, 30, 165, 30, "Messages Sent: ");
  send_count->buffer(send_count_buff);
}

///Function will display the number of messages received to the user
void display_msg_rcv()
{
  received_count = new Fl_Text_Display(205, 30, 165, 30, "Messages Recv: ");
  received_count->buffer(received_count_buff);
}

///Function will display the total number of users in the chatroom
void display_num_users()
{
  user_count = new Fl_Text_Display(390, 30, 80, 30, "Users: ");
  user_count->buffer(user_count_buff);
}


void display_all()
{
  display_msg_send();
  display_msg_rcv();
  display_num_users();
}


void SuperChat_Access::Chat_Window(string chat_win_name, int chat_index, string name)
{
  ///This functions reset all Text_Displays
  received = 0;
  sent = 0;
  send_count_buff->text("");
  received_count_buff->text("");
  Message_Received= "";
  buff->text("");

  ///This makes a window that will display messages going through the network
  chat_window = new Fl_Window(500, 785, chat_win_name.c_str());
  chat_window->position((Fl::w()-chat_window->w())/2, (Fl::h()-chat_window->h())/2);
  chat_window->set_modal();

  chat_index_cmp = chat_index;
  user_nick = name;

  chat_window->resizable(send_count);
  chat_window->resizable(received_count);
  chat_window->resizable(user_count);
  display_all();
  

  ///This function will display a window where all the messages send/received can be seen
  receive_da_chat = new Fl_Text_Display(30, 70, 440, chat_window->h()-140);
	
  ///Function will display a multiline input box that will accept user input that will displayed and send to other users
  send_da_chat = new Fl_Multiline_Input(30, chat_window->h()-60, 380, 60);
  chat_window->resizable(chat_window);

  ///Message button will callback a function that will display the message to the sceen
  send_msg = new Fl_Button(chat_window->w()-80,chat_window->h()-50, 70, 35, "Send");
  send_msg->callback((Fl_Callback *)send_message_function, 0);
  chat_window->show();
  buff->remove_selection();
  
  receive_da_chat->buffer(buff);
  chat_window->redraw ();///added this line

	
  Fl::add_idle(callback);
}

void SuperChat_Access::run_chatroom(string chat_win_name)
{
  Message_Received= "";
  buff->text("");
  received_count_buff->text("");
  send_count_buff->text("");
  //Chat_Window(chat_win_name, );
}

void receiving(void)//***********************first thread starts here
{
  bool users_exists = false;
  string name_of_user;
  // set up ctrl-c handler
  signal ( SIGINT, ctrlc );
  // instantiate classes
  //  the argument is the topic name, or the identifier the data
  //  is known by in the DDS middleware.  these must match for 
  //  everyone on the network. Translation: If you change the topic
  //  names, you can communicate with yourself but no one else.
  // set up some variables
  int seconds = 0;
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  std::cout << "My UUID is " << uuid << std::endl;
  // lets go old school, and copy it over
  memcpy ( &myUUID, &uuid, sizeof (myUUID) );
  // the main loop
  while (!exit_flag)
  {
    assert(sendUser == true);
    // user topic
    if (sendUser)
    {
      user messageInstance;
      messageInstance.uuid = myUUID;  
      messageInstance.captain = kirk;
      // note the same name with different uuid's is something
      // you have to deal with when printing who is online and 
      // where a message is from.

      if ( validate_nick ( user_nick ) )
      {
         strncpy ( messageInstance.nick, user_nick.c_str(), sizeof ( messageInstance.nick ) );
      }
      messageInstance.chatroom_idx = 1; 
      if (seconds%2 == 0) 
      {
         // 2.0 is less than 2.5, so this is still compliant
         User.send ( messageInstance );
      }
    }
    assert(recvChatroom == true);
    // handle any input coming in
    if (recvChatroom)
    {
      // note the scope of 'List'.
      // if nothing is recv'd, then the vector is empty
      chatroom_list_t  List;
      chatRoom.recv ( &List );
      for (unsigned int i=0; i<List.size ();i++)
      {
        //std::cout << "received new chatroom name " << List[i].chatroom_name <<
        //              " chatroom index " << List[i].chatroom_idx << std::endl;
      }
    }
    assert(recvUser == true);
    if (recvUser) 
    {

      user_list_t  List;
      User.recv ( &List );
      for (unsigned int i=0; i<List.size ();i++)
      {
	 std::string captain_is;
	 if ( List[i].captain == kirk )
		 captain_is = "james tiberious kirk";
	 else if ( List[i].captain == picard )
		 captain_is = "jon luc picard";
	 else if ( List[i].captain == pike )
		 captain_is = "pike";
	 else
		 captain_is = "other";


//         std::cout << "recieved user " << std::hex << List[i].uuid 
//                   << std::dec << "  " << List[i].nick 
//		   << "  enterprise captain " << captain_is
//                   << " chatroom index " << List[i].chatroom_idx << std::endl;
	name_of_user =  string(List[i].nick);
	for(unsigned int j = 0; j < active_users.size();j++)
	{
          if(strcmp(active_users[j].nick,List[i].nick)==0)
	  {
	    users_exists = true;
	  }
	  if(active_users[j].nick == List[i].nick)
	  {
	    //do nothing
            //cout << "Users in chatroom: " << active_users.size() << endl;
            int size = active_users.size();
            string temp = to_string(size);
            const char* user_count = temp.c_str();
            user_count_buff->text(user_count);
	  }
	  else
	  {
	    strncpy(active_users[j+1].nick,List[i].nick,8);
	    active_users[j+1].seconds=seconds; /// active_users is the vector that holds the users in the chatroom it has a variable for nick's and seconds
            //cout << "Users in chatroom: " << active_users.size() << endl;
            int size = active_users.size();
            string temp = to_string(size);
            const char* user_count = temp.c_str();
            user_count_buff->text(user_count);
            // display_num_users();
	  }
	}
        if(!users_exists)
	{
	  Active_Users temporary;
	  strncpy(temporary.nick,List[i].nick,8);
	  temporary.seconds = seconds;
	  active_users.push_back(temporary);
	  users_exists = false;
	}
      }
    //cout << "This is the size of the List vector: " << List.size() << endl;
    //cout <<"These are the active users: "<< active_users.size() << endl;
    }

    assert(recvMsg == true);
    if (recvMsg) 
    {
      message_list_t  List;
      Message.recv ( &List );
      for (unsigned int i=0; i<List.size ();i++)
      {
        if(List[i].chatroom_idx == chat_index_cmp)
        {
          std::cout << "recieved user " << List[i].message <<
                      " chatroom index " << List[i].chatroom_idx << 
                      " sequence # " << List[i].seqno << std::endl;
          Message_Received +=name_of_user+ ":" + string(List[i].message) + "\n";
          messageQ.push_back(Message_Received);
	  received++;
          string temp = to_string(received);
          const char* count_recv = temp.c_str();
          received_count_buff->text(count_recv);
          //cout << received << endl;
          //display_msg_rcv();
	}
      }
    } 
    seconds++;
    sleep (1);
  }
  std::cout << "normal exit" << '\n';
}

/*! This is the main function it initiates FTLK multithreading.
instances an object of the Controller class, and it starts the GUI. In
this function and additional thread to main is declared with a name of one, and 
a mutex is also declared with a name of controll */
int main(int argc, char **argv)
{
thread one(receiving);
Controller boss;
boss.run_the_show();
one.join();
free(buff);
return 0;
}

