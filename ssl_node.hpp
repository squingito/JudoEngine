//
// Created by squin on 10/28/2022.
//

#ifndef JUDO_ENGINE_SSL_NODE_HPP
#define JUDO_ENGINE_SSL_NODE_HPP


#include <iostream>
#include <mutex>
#include <arpa/inet.h>
#include <poll.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "LoggyMcLogFace.hpp"


struct ssl_node {
    struct sockaddr_in con;
    struct std::mutex lock;
    struct ssl_st* ssl;
    struct ssl_ctx_st* ssl_ctx;
    struct bio_st* read_bio;
    struct bio_st* write_bio;
    int32_t fp;
    uint8_t mode;
    enum sockType {JUDO_LIST, JUDO_OUTGOING, JUDO_INCOMING} type;

};

enum request {
    ADD_CONNECT = 1,
    DISCONNECT = 2,
    DO_HANDSHAKE = 4
};

struct judo_request_node {
    struct ssl_node* ssl_info;
    struct pollfd poll;
    request req;
};

struct judo_general_request_node {
    struct ssl_node* ssl_info;
    struct pollfd poll;
    char* msg;
    int32_t size;
};

void dstr_judo_request_node(struct judo_request_node* in);

void dstr_judo_general_request_node(struct judo_general_request_node* in);

void dstr_ssl_node(struct ssl_node* in) ;

void dstr_request_node(struct judo_request_node* in);

int32_t compare_pollfd(struct pollfd* a, struct pollfd* b) ;

void dstr_pollfd(void* in);

void read_ip(std::ofstream* t_stream, void* data) ;


void read_port(std::ofstream* t_stream, void* data);


void read_char_buf(std::ofstream* t_stream, void* data);

#endif //SSL_SERVER_SSL_NODE_H


