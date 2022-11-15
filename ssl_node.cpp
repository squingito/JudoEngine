//
// Created by squin on 10/28/2022.
//

#include "ssl_node.hpp"

void dstr_ssl_node(struct ssl_node* in) {
    if (in != nullptr) {
        SSL_free(in->ssl);
        SSL_CTX_free(in->ssl_ctx);
        delete in;
    }
};

void dstr_request_node(struct judo_request_node* in) {
    if (in != nullptr) {
        dstr_ssl_node(in->ssl_info);
    }
}

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

void dstr_judo_request_node(struct judo_request_node* in) {
    dstr_ssl_node(in->ssl_info);
    delete in;
}

void dstr_judo_general_request_node(struct judo_general_request_node* in) {
    dstr_ssl_node(in->ssl_info);
    delete in->msg;
    delete in;
}