Echo client

Connects and sends message to the server.

Usage:
$ ./client 127.0.0.1 8800
Trying to connect: 127.0.0.1 8801
Connecting to 127.0.0.1:8801
Hello

Server side:
$ ncat -lkv 8801
Ncat: Version 7.60 ( https://nmap.org/ncat )
Ncat: Listening on :::8801
Ncat: Listening on 0.0.0.0:8801
Ncat: Connection from 127.0.0.1.
Ncat: Connection from 127.0.0.1:38216.

