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

About the application
----------------------
Cp.FTP is a simple *ftp-client* and *ftp-server* written in C++. It is a terminal based application for UNIX systems. This application implements the File Transfer Protocol specified in [RFC 959](https://www.ietf.org/rfc/rfc959.txt).

###Steps to compile the source code

Open the terminal and type :
```bash
    $ make
```
This will produce the executable **cpftp** after linking and compiling the source code in **src** folder. This executable can be used as both as a **ftp-server** as well as a **ftp-client**.

###Cp.FTP-Client
----------------------
Cp.FTP can be used as client to connect to various ftp-servers. It implements various basic features such as user login, sending files, receiving files, creating directories,etc. 

- Cp.FTP-Clent allows supports various commands like :
    * **`get filename`**: This command downloads specified file from server and saves it at the current working location on client.
    * **`get filename destination`**: This command downloads specified file from server and saves it at specified destination on client.
    * **`put filename`**: This command uploads specified file from client and saves it at the current working location on server.
    * **`put filename destination`**: This command uploads specified file from client and saves it at specified destination on server.
    * **`pwd`**: This command shows the path of current working directory of server.eg: `pwd` returns `/home/`
    * **`cd directory`**: This command changes the current working directory to the specified directory on server. eg: `cd /` changes current working directory to `/` directory on server.
    * **`ls [options]`**:  This command retrieves current directory listing from the client. You can specify options for custom results., eg: `ls -a` returns directory listing including hidden files for the current working directory on server.
    * **`ls [options] directory_name`**: This command retrieves the directory listing of directory specified in directory name from the client. As in previous, you can specify options for custom results., eg: `ls -a xyz` returns directory listing including hidden files for `xyz` directory on server.
    * **`mkdir directory_structure`**: This command creates the required directory structure on the server. If in case the specified directory structure is partially complete, it completes the structure. eg: `mkdir /a/b/c` creates the following structure.
    <pre><code class='bash'>.
    ├── a
    <span class='p'>|</span>   ├── b
    <span class='p'> </span>   <span class='p'>|</span>   └── c
    </code></pre>
    * **`!pwd`**: This command shows the path of current working directory of client.eg: `pwd` returns `/home/`
    * **`!cd directory`**: This command changes the current working directory to the specified directory on client. eg: `cd /` changes current working directory to `/` directory on client.
    * **`!ls [options]`**: This command retrieves current directory listing from the client. You can specify options for custom results., eg: `ls -a` returns directory listing including hidden files for the current working directory on client.
    * **`!ls [options] directory_name`**: This command retrieves the directory listing of directory specified in directory name from the client. As in previous, you can specify options for custom results., eg: `ls -a xyz` returns directory listing including hidden files for `xyz` directory on client.
    * **`!mkdir directory_structure`**: This command creates the required directory structure on the client. If in case the specified directory structure is partially complete, it completes the structure. eg: `mkdir /a/b/c` creates the following structure.
    <pre><code class='bash'>.
    ├── a
    <span class='p'>|</span>   ├── b
    <span class='p'> </span>   <span class='p'>|</span>   └── c
    </code></pre>
- Cp.FTP-Client connects in **PASSIVE** mode while transferring data over data socket to server. 
- Cp.FTP-Client can download/upload a maximum of one file at a time from/to server.

#### How to run Cp.FTP-Client
Once you have compiled the source-code, you can use it as a *ftp-client*. To use the executable as a **ftp-client**, in your terminal type :
```bash
    $ ./cpftp host port
```
After which you will be prompted to input *username* and *password* to connect to the host server.

###Cp.FTP-Server
----------------------
Cp.FTP can be used as a ftp-server and various client can connect to it. 
 
- Cp.FTP-Server operates in **PASSIVE** mode while transferring data over data socket. 
    #####How does PASSIVE Mode work?
    * The client connects from a random port to port 21 on the server and issues the PASV command. The server replies, indicating which (random) port it has opened for data transfer.
    
    * The client connects from another random port to the random port specified in the server's response. Once connection is established, data transfers are made through these client and server ports.
    <p align="center">
        <img src="https://www.serverintellect.com/wp-content/uploads/kb-passiveftpdiagram.jpg"/>
    </p>
    * In an active mode configuration, the server will attempt to connect to a random client-side port. So chances are, that port wouldn't be one of those predefined ports. As a result, an attempt to connect to it will be blocked by the firewall and no connection will be established.     
    <p align="center">
        <img src="http://www.jscape.com/Portals/26878/images/passive_ftp_with_firewall-resized-600.png"/>    
    </p>
    A passive configuration will not have this problem since the client will be the one initiating the connection. Of course, it's possible for the server side to have a firewall too. However, since the server is expected to receive a greater number of connection requests compared to a client, then it would be but logical for the server admin to adapt to the situation and open up a selection of ports to satisfy passive mode configurations.
- Cp.FTP-Server supports multiple users and also password based authentication for its users. System administrator can create new users by adding them in the file **/src/data/login.info**. While adding a new user administrator must specify 3 fields. **username**, **password**, **user's root directory** separated by spaces. Once a new user has been added in the file that user can then connect and login to ftp-server by providing the password. 
- Cp.FTP-Server is a multi-threaded server and can handle multiple clients simultaneously but every client that is connect to it can download/upload a maximum of one file at a time.
- Cp.FTP-Server supports various FTP commands specified in [RFC 959](https://www.ietf.org/rfc/rfc959.txt) like :
    * **`USER <SP> <username> <CRLF>`**
    * **`PASS <SP> <password> <CRLF>`**
    * **`CWD  <SP> <pathname> <CRLF>`**
    * **`QUIT <CRLF>`**
    * **`PASV <CRLF>`**
    * **`TYPE <SP> <type-code> <CRLF>`**
    * **`RETR <SP> <pathname> <CRLF>`**
    * **`STOR <SP> <pathname> <CRLF>`**
    * **`MKD  <SP> <pathname> <CRLF>`**
    * **`PWD  <CRLF>`**
    * **`LIST [<SP> <pathname>] <CRLF>`**
    * **`SYST <CRLF>`**

#### How to run Cp.FTP-Server
Once you have compiled the source-code, you can use it as a *ftp-server*. To use the executable as a **ftp-server**, in your terminal type :
```bash
    $ ./cpftp port
```
**Note : ** To use port below **1024** you need to provide *root* privileges.
```bash 
    $ sudo ./cpftp 21
```
