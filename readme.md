# UNIX BASED SYSTEM INTERFACE ADDRESS
## Description
Program to launch an local HTTP server for file sharing on an unix based system.  
## Dependencies
### Program
No external dependency.
### Build
 - gcc: for compilation
 - ar: from binutils for static lib creation
## Usage
```bash
make build/server  
./build/server [file]  
```
## Reference
 - (book)   Hands-on network programming with C - by Lewis Van Winkle
 - (manual) man socket(2): for socket file creation
 - (manual) man bind(2): for address assignation
 - (manual) man listen(2): to open server for connection request
 - (manual) man accept(2): to allow client connection
 - (manual) man write(2): for input/output
 - (manual) man open(2): for file opening/closing
 - (manual) man htons(3): for port translation between readable and machine
 - (manual) man inet_addr(3): for address translation between readable and machine
 - (documentation) [mdn](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers): for HTTP (as a protocol) reference
## See also
 - Previous week:  [network interface list](https://github.com/DinaTolotra/W1-network-interface-list)
