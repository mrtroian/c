Echo server

Gets a message from a client, reverses it and sends back.

To compile use make.

Usage:
$ ./server 8800
Server started on 0.0.0.0:8800

If port is not specified, port 8800 will be used for connections.
To connect, use echo_client or telnet:
$ telnet 0 8800
Trying 0.0.0.0...
Connected to 0.
Escape character is '^]'.
Connection succeed.
hello
olleh

Example with echo_client:
$ ./client
Connecting to 127.0.0.1:8800
Hello
olleH

To connect to remote host, provide the client with an ip and port of the server like this:
$ ./client ADDR PORT
