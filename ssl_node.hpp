//
// Created by squin on 10/3/2022.
//

#ifndef SSL_SERVER_SSL_NODE_H
#define SSL_SERVER_SSL_NODE_H

#include <iostream>
#include <mutex>
#include <arpa/inet.h>


struct ssl_node {
    struct sockaddr_in con;
    struct std::mutex lock;
    struct ssl_st* ssl;
    struct ssl_ctx_st* ssl_ctx;
    struct bio_st* read_bio;
    struct bio_st* write_bio;
    int32_t fp;
    uint8_t mode;
	uint8_t buff_size;


};

struct request_node {
    struct sockaddr_in to_con;
	char* cert;
	char* pk;
    uint32_t fp;
    uint8_t req;
};

int8_t compare_req_node(void* a, void* b) {
	return -1;
}

void req_node_destructor(void* a) {
	delete ((struct request_node*) a);
}

int32_t compare_ssl_nodes(struct ssl_node* one, struct ssl_node* two) {
	std::cout << ((one)->fp) << " " << (two)->fp << "\n";
    return ((one)->fp) - (((two)->fp));
}

void print_ssl_node(struct ssl_node* in) {
    std::cout << in->fp << "\n";
}

void dstr_ssl_node(struct ssl_node* in) {
    if (in != nullptr) {

        SSL_free(in->ssl);
        SSL_CTX_free(in->ssl_ctx);


        delete in;
    }
};

int32_t compare_pollfd(struct pollfd* a, struct pollfd* b) {

    return a->fd - b->fd;
}

void dstr_pollfd(void* in) {
    struct pollfd* to_dstr = (struct pollfd*) in;
    delete to_dstr;
}

void read_ip(std::ofstream* t_stream, void* data) {
    struct sockaddr_in* thing = (struct sockaddr_in*) data;
    *t_stream << inet_ntoa(thing->sin_addr);
}

void read_port(std::ofstream* t_stream, void* data) {
    struct sockaddr_in* thing = (struct sockaddr_in*) data;
    *t_stream << thing->sin_port;
}

void read_char_buf(std::ofstream* t_stream, void* data) {
    char* out = (char*) data;
    *t_stream<< out;
}

#endif //SSL_SERVER_SSL_NODE_H
