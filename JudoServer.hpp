//
// Created by squin on 10/13/2022.
//

#ifndef JUDO_ENGINE_JUDOSERVER_HPP
#define JUDO_ENGINE_JUDOSERVER_HPP

#include <sys/socket.h>
#include <cstdio>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>
#include <poll.h>

#include "DualDynamicArray.cpp"

#include "ssl_node.hpp"

#define JUDO_BUFFER_SIZE 12;

#define JUDO_SUCCESS 0
#define JUDO_FAILURE -1

#define JUDO_MODE_SERVER_SOCK 0x0001
#define JUDO_MODE_SSL_ENABLED 0x0002
#define JUDO_MODE_SERVER_CERTS_REQ 0x0004
#define JUDO_MODE_CLIENT_CERTS_REQ 0x0008

#define JUDO_READ_CERT_FILE_FAILURE -10
#define JUDO_READ_KEY_FILE_FAILURE -11;

#define JUDO_NO_SERVER_SOCK_ADDR -20
#define JUDO_CONNECTION_FAILURE -21
#define JUDO_SSL_HANDSHAKE_FAILURE -22
#define JUDO_REMOTE_HOST_SERVER_CERTS_REQUIRED -23
#define JUDO_REMOTE_HOST_CLIENT_CERTS_REQUIRED -24
#define JUDO_INPUT_CERT_FILES_MISSING -25
#define JUDO_REMOTE_HOST_NO_SERVER_CERTS -26
#define JUDO_REMOTE_HOST_NO_CLIENT_CERTS -27
#define JUDO_REMOTE_HOST_DISCONNECT -28

#define JUDO_CON_SERVER_CERTS 0x01
#define JUDO_CON_CLIENT_CERTS 0x02

namespace judo {
    class JudoServer {
    public:
        JudoServer(); //makes default server with no open sockets
        JudoServer(struct sockaddr_in*); //makes default server with an accepting socket
        JudoServer(struct sockaddr_in*, char*, char*); //makes a default ssl accepting socket
        ~JudoServer(); //destorys JudoServer


        //NonActiveMethods
        int32_t judoMakeServerSock_(); //sets up Judos Accepting socket
        int32_t judoFillServerSSLFields_(struct ssl_node*);

        void init_();
        int32_t judoInitServerSockSSL_(char*, char*);


        int32_t run();

        int32_t judoSetUpServerSockSSL(char*, char*);


        int32_t judoSend_(struct ssl_node*, char*, int32_t);
        int32_t judoSocketConnect_(struct sockaddr_in*, int32_t*);
        int32_t judoConnect_(struct sockaddr_in*, char*, char*, int8_t);
        void disconnect_(struct ssl_node*, struct pollfd*);

        int32_t judoFillClientSSLFields_(struct ssl_node*, char*, char*);
        int32_t judoFillGeneralSSLFields_(struct ssl_node*, char*, char*, const SSL_METHOD*);

        int32_t judoAccept_();
        int32_t judoHandshake_(struct ssl_node*, char*);
        int32_t judoServerRequireCerts();
        int32_t judoClientRequireCerts();
    private:
        DualDynamicArray<struct pollfd, struct ssl_node*>* m_ssl_nodes = nullptr;
        //stores information on all sockets

        int32_t m_server_list_sock = 0;
        struct ssl_node* m_server_list_sock_node = nullptr;
        struct sockaddr_in m_list_sock_addr;
        //These hold the listing socket, the ssl_node for it, and its address;

        char* m_server_cert_file = nullptr;
        char* m_server_private_key_file = nullptr;
        //holds accepting sock cert and key files

        bool m_active = false;
        //boolean that designates running of main loop

        int16_t m_mode = 0;
        int32_t m_buffer_size = 1024;


    };
}





#endif //JUDO_ENGINE_JUDOSERVER_HPP
