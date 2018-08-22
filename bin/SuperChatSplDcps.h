#ifndef SUPERCHATSPLTYPES_H
#define SUPERCHATSPLTYPES_H

#include "ccpp_SuperChat.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __SuperChat_SuperChat__load (c_base base);

extern c_metaObject __SuperChat_message__load (c_base base);
extern const char * __SuperChat_message__keys (void);
extern const char * __SuperChat_message__name (void);
struct _SuperChat_message ;
extern  c_bool __SuperChat_message__copyIn(c_base base, struct SuperChat::message *from, struct _SuperChat_message *to);
extern  void __SuperChat_message__copyOut(void *_from, void *_to);
struct _SuperChat_message {
    c_char message[144];
    c_ulonglong uuid;
    c_ulonglong cksum;
    c_ulong chatroom_idx;
    c_ulong seqno;
    c_ulonglong private_msg_destination_uuid;
    c_bool private_msg;
};

extern c_metaObject __SuperChat_chatroom__load (c_base base);
extern const char * __SuperChat_chatroom__keys (void);
extern const char * __SuperChat_chatroom__name (void);
struct _SuperChat_chatroom ;
extern  c_bool __SuperChat_chatroom__copyIn(c_base base, struct SuperChat::chatroom *from, struct _SuperChat_chatroom *to);
extern  void __SuperChat_chatroom__copyOut(void *_from, void *_to);
struct _SuperChat_chatroom {
    c_ulong chatroom_idx;
    c_char chatroom_name[25];
};

extern c_metaObject __SuperChat_captain_name_enum__load (c_base base);
enum _SuperChat_captain_name_enum {
    _SuperChat_kirk,
    _SuperChat_pike,
    _SuperChat_picard,
    _SuperChat_other
};

extern c_metaObject __SuperChat_user__load (c_base base);
extern const char * __SuperChat_user__keys (void);
extern const char * __SuperChat_user__name (void);
struct _SuperChat_user ;
extern  c_bool __SuperChat_user__copyIn(c_base base, struct SuperChat::user *from, struct _SuperChat_user *to);
extern  void __SuperChat_user__copyOut(void *_from, void *_to);
struct _SuperChat_user {
    c_char nick[8];
    c_ulonglong uuid;
    c_ulong chatroom_idx;
    c_ulong graduation_date;
    enum _SuperChat_captain_name_enum captain;
};

#endif
