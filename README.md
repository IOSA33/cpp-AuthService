# cpp-AuthService with Network
- PostgreSQL database
- Client-server communication via Winsock2 over TCP protocol.
- Communication with my other servers
- libSodium for hashing passwords
- Implemented Dockerfile
- Using gTests for unit testing

# Commands that you can Run:
- `REG [EMAIL] [PASSWORD]` - Registration in database and returns sessionId
- `LOG [EMAIL] [PASSWORD]` - Returns sessionId
- `GET [sessionID]` - Returns JSON data from sessionId
- `UPDATE [EMAIL] [OLD_PASS] [NEW_PASS]` - Updates password of the user 
- `DELETE [EMAIL] [PASSWORD]` - Deletes users account from database

# How to Start:
- For graceful shotdown the server write in running `./server.exe` following command `exit` .
- In the main folder run following commands with Cmake for the server:
```
mkdir build
cd build
cmake ..
ninja
```

- After that run following command: `./app.exe`