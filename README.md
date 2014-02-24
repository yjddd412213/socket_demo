socket_demo
===========

use socket to send and receive msg. only fit for windows


config
===========
A sample config.ini content is listed below.

[Function]
Receive=0
Send=1
Train=1
Rescue=0
[Server_Inner]
IP=192.168.1.212
Port=-1
[Server_Inter]
IP=192.168.1.130
Port=5544
[Database]
host=MIDCARDS_192.168.1.48
user=midcards
passwd=ht706
db=midcards
port=1521


[Function] is used to identify whether this app is used to send or to receive."Train" and "Rescue" are used to config which kind of data this app should send.

[Server_Inner] identifies a server that the app should connect by socked when it acts as a client role, 
while [Server_Inter] identifies another one.

[Database] specifies which database to use.