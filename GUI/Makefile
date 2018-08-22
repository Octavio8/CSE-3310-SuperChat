COMPILER = g++ -Wall -std=c++11

LIBRARIES = -L/usr/local/lib -lfltk -lXext -lX11 -lm

all:gui

gui:
	$(COMPILER) $(fltk-config --cxxflags) main.cpp Controller.h Controller.cpp Create_User_Dialog.h Create_User_Dialog.cpp Chatroom.h Chatroom.cpp Message.h Message.cpp Log_In.h Log_In.cpp Sign_Up.h Sign_Up.cpp User.h User.cpp View_Chatroom_Window.h View_Chatroom_Window.cpp $(LIBRARIES)

clean:

	-rm -f *a.out *.gch
