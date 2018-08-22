
all:./bin/SuperChat ./bin/unit_test

COMMON_LIBS=-L${OSPL_HOME}/lib/ \
            -ldcpssacpp \
            -lddskernel \
            -lpthread

CXX_FLAGS= -std=c++11 -Wall -O0 -g -Iinclude/
LDFLAGS= -L/usr/local/lib -lfltk -lXext -lX11 -lm


FILES_GENERATED_FROM_THE_IDL_BY_IDLPP= ./bin/SuperChatDcps_impl.h ./bin/SuperChat.cpp \
                                     ./bin/SuperChatSplDcps.cpp ./bin/SuperChatDcps.cpp \
                                     ./bin/SuperChatDcps_impl.cpp ./bin/ccpp_SuperChat.h \
                                     ./bin/SuperChatDcps.h ./bin/SuperChat.h ./bin/SuperChatSplDcps.h

${FILES_GENERATED_FROM_THE_IDL_BY_IDLPP}:./idl/SuperChat.idl
	idlpp -I ${OSPL_HOME}/etc/idl -l cpp ./idl/SuperChat.idl -d ./bin

SRC_FILES= src/DDSEntityManager.cpp src/CheckStatus.cpp src/nicks.cpp ./src/SuperChat_Access.h

GUI_FILES= GUI/Controller.h GUI/Controller.cpp GUI/Create_User_Dialog.h GUI/Create_User_Dialog.cpp GUI/Message.h GUI/Message.cpp GUI/Log_In.h GUI/Log_In.cpp GUI/Sign_Up.h GUI/Sign_Up.cpp GUI/User.h GUI/User.cpp GUI/View_Chatroom_Window.h GUI/View_Chatroom_Window.cpp src/SuperChat_Access.h

bin/SuperChat: ${FILES_GENERATED_FROM_THE_IDL_BY_IDLPP} ./src/SuperChat.cpp ${SRC_FILES}
	g++ ${CXX_FLAGS} $(fltk-config) -o ./bin/SuperChat ./src/SuperChat.cpp $(LDFLAGS)\
               -I./src/ -I./include -I./bin -I./GUI \
               -I${OSPL_HOME}/include/dcps/C++/SACPP/ \
               ${SRC_FILES} \
               ${FILES_GENERATED_FROM_THE_IDL_BY_IDLPP} \
               ${COMMON_LIBS} \
	       ${GUI_FILES}
	

bin/unit_test: ./src/unit_test.cpp ./src/nicks.h ./src/nicks.cpp
	g++ ${CXX_FLAGS} \
               -I./src/ -o bin/unit_test ./src/unit_test.cpp ./src/nicks.cpp \
              -lboost_unit_test_framework

clean:
	-rm -f ./bin/SuperChat ${FILES_GENERATED_FROM_THE_IDL_BY_IDLPP} bin/unit_test
