This project make a server with both ssl (secure socket layer) and multi-client capability. Still is very much a work in progress. 

This is built for UNIX. It is still a work in progress

Some information on features as of now:
- Right now the server achieves both ssl connections and multi-client server capability with only one thread.
- You can configure your server to specify requirements of clients. For example, you can require no certificates (no encryption), server certificates only (encrypted connection and allows clients to verify identify the server), client certs only (encrypted connection and allows server to verify the identity of the client), or both server and client certs (encryped and allows both sides to verify the identity fo the other).
- All incoming messages will be processed and placed in a queue as they come in along with all an struct ssl_node*. This struct identify connections on the server and you can use them to respond to said message.  

Some future things that will probably get added:
- More logging capability, networking and crypto are messy, and it will make debugging easier.
- Some kind of thead-poll addon that will scale its self based on the number of messages to be processed (for example an exponential scale can be used in order to add a thread whenever the workload doubles, this can be capped at some point). It will also be able to take input functions from the user to allow the user to define their own server's protocol.



I am making this as I want to do some networking projects in the future like chat servers, storage/file transfer servers, and much more.

In order to use the project u will need to generate your own and sign your own certificate. If you see in the code, right now I
have my certificate file paths hard coded, just change them if you want to try to use it. 

When building make sure to link to the ssl library.



