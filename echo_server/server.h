#ifndef _SERVER_H_
#define _SERVER_H_

char *msgrev(char *str);
int listener(int sockfd);
int serve(int port);

#endif