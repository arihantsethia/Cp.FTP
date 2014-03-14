Cp.FTP
=======

Prerequisites 
------------------------ 
Thing you need to run this software :

1) GNU Compiler Collection

2) Make Utility

3) Linux Machine

File Transfer Protocol (FTP)
------------------------ 
File Transfer Protocol (FTP) is a standard network protocol used to transfer files from one host to another host over a TCP-based network, such as the Internet.

FTP is built on a client-server architecture and uses separate control and data connections between the client and the server. FTP users may authenticate themselves using a clear-text sign-in protocol, normally in the form of a username and password, but can connect anonymously if the server is configured to allow it.

To transfer files with FTP, you use a program often called the *client*. An *FTP client* program initiates a connection to a remote computer running FTP server software. After the connection is established, the client can choose to send and/or receive copies of files, singly or in groups. To connect to an *FTP server*, a *client* requires a *username* and *password* as set by the administrator of the server. Many public FTP archives follow a special convention for that accepts a username of "anonymous". In any FTP interface, clients identify the FTP server either by its IP address (such as 192.168.0.1) or by its host name (such as ftp.example.com).

FTP supports two modes of data transfer: plain text (ASCII), and binary. You set the mode in the FTP client. A common error when using FTP is attempting to transfer a binary file (such as a program or music file) while in text mode, causing the transferred file to be unusable.

More specification about File Transfer Protocol in specified in [RFC 959](https://www.ietf.org/rfc/rfc959.txt)

About the software
----------------------

###Steps to run the program

1) Open the terminal and type :
```bash
    $ make
```
2) This will produce the executable **cpftp** after linking and compiling the source code in **src** folder. 

3) This executable can be used as both as a **ftp-server** as well as a **ftp-client**.

###Cp.FTP-Client

To use the executable as a **ftp-client**, in your terminal type :
```bash
    $ ./cpftp host port
```
After which you will be prompted to input *username* and *password* to connect to host server.

- **`get filename [dest]`**: Get specified file from server and save it at [dest] if specified, else save it at current location.

###Cp.FTP-Server

- To use the executable to host a **ftp-server**, in your terminal type :
```bash
    $ ./cpftp port
```
**Note : ** To use port below **1024** you need to provide *root* priviliges.
```bash 
    $ sudo ./cpftp 21
```
