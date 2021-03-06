#ifndef SERVER_INFO_H
#define SERVER_INFO_H


#define SI_CLIENTS_LIMIT    3

#define SI_IPC_KEY_NUMBER   15

#define SI_REQ_REGISTER     1
#define SI_REQ_MIRROR       2
#define SI_REQ_CALC         3
#define SI_REQ_TIME         4
#define SI_REQ_STOP         5   // Sent by clients before their termination
#define SI_REQ_END          6   // Sent to request server termination
#define SI_ACCEPTED         7
#define SI_REJECTED         8


#define SI_SERVTERM         5

#define SI_MESSAGE_MAX_SIZE 256


#endif
