//
// Created by squin on 10/13/2022.
//

#include <cstring>
#include "JudoServer.hpp"

namespace judo {
    void JudoServer::init_() {
        m_ssl_nodes = new DualDynamicArray<struct pollfd, struct ssl_node*>(compare_pollfd);
        m_server_list_sock = -1;
        m_server_list_sock_node = new struct ssl_node;
        m_list_sock_addr = {0};
        m_server_cert_file = nullptr;
        m_server_private_key_file = nullptr;
        m_buffer_size = 1024;
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();
    }

    JudoServer::JudoServer() {
        init_();
    }

    JudoServer::~JudoServer() {
        for (int i = m_ssl_nodes->getSize() - 1; i >= 0 ; i--) {
            if (m_server_list_sock_node->fp != ((m_ssl_nodes->getFromFirstByIndex(i))->fd)) {
                dstr_ssl_node(*m_ssl_nodes->getFromSecondByIndex(i));
                struct pollfd test = *m_ssl_nodes->getFromFirstByIndex(i);
                m_ssl_nodes->remove(&test);
            }
        }
        if (m_server_list_sock_node != nullptr) {
            dstr_ssl_node(m_server_list_sock_node);
        }
        delete m_ssl_nodes;
        close(m_server_list_sock);
    }

    JudoServer::JudoServer(struct sockaddr_in* t_addr) {
        init_();
        m_list_sock_addr = *t_addr;
        judoMakeServerSock_();
    }

    JudoServer::JudoServer(struct sockaddr_in* t_addr, char* t_server_cert_file, char* t_server_private_key_file) {
        init_();
        m_list_sock_addr = *t_addr;
        int32_t ret_val = judoMakeServerSock_();
        if (ret_val == 0) {
            m_server_cert_file = t_server_cert_file;
            m_server_private_key_file = t_server_private_key_file;
            judoSetUpServerSockSSL(m_server_cert_file, m_server_private_key_file);
        }
    }

    int32_t JudoServer::judoMakeServerSock_() {
        struct sockaddr_in test = {0};
        if (test.sin_addr.s_addr == m_list_sock_addr.sin_addr.s_addr && test.sin_port == m_list_sock_addr.sin_port) {
            return JUDO_NO_SERVER_SOCK_ADDR;
        }
        m_server_list_sock = socket(AF_INET, SOCK_STREAM, 0);
        int mode = 1;
        setsockopt(m_server_list_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &mode, sizeof(mode));
        bind(m_server_list_sock, (struct sockaddr*) &m_list_sock_addr, sizeof(m_list_sock_addr));
        listen(m_server_list_sock, 5);
        mode |= JUDO_MODE_SERVER_SOCK;
        struct pollfd new_pollfd = {m_server_list_sock, POLLIN, 0};
        m_ssl_nodes->add(&new_pollfd, &m_server_list_sock_node);
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoSetUpServerSockSSL(char* t_cert, char* t_private_key) {
        m_server_cert_file = t_cert;
        m_server_private_key_file = t_private_key;
        int32_t return_val = judoFillServerSSLFields_(m_server_list_sock_node);
        if (return_val != JUDO_SUCCESS) return return_val;
        m_mode |= JUDO_MODE_SSL_ENABLED;
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoServerRequireCerts() {
        if (m_mode & JUDO_MODE_SSL_ENABLED && !m_active) {
            m_mode |= JUDO_MODE_SERVER_CERTS_REQ;
            return 0;
        }
        return -1;
    }

    int32_t JudoServer::judoClientRequireCerts() {
        if (m_mode & JUDO_MODE_SSL_ENABLED && !m_active) {
            m_mode |= JUDO_MODE_CLIENT_CERTS_REQ;
            return 0;
        }
        return -1;
    }

    int32_t JudoServer::judoFillClientSSLFields_(struct ssl_node* t_node, char* t_cert, char* t_key) {
        const SSL_METHOD* method = TLS_client_method();
        int32_t return_val = judoFillGeneralSSLFields_(t_node, t_cert, t_key, method);
        SSL_set_connect_state(t_node->ssl);

        if (return_val != JUDO_SUCCESS) return return_val;
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoFillServerSSLFields_(struct ssl_node* t_node) {
        const SSL_METHOD* method = TLS_server_method();
        int32_t return_val = judoFillGeneralSSLFields_(t_node, m_server_cert_file, m_server_private_key_file, method);
        if (return_val != JUDO_SUCCESS) return return_val;
        SSL_set_accept_state(t_node->ssl);
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoFillGeneralSSLFields_(struct ssl_node *t_ssl_node, char* t_cert, char* t_key, const SSL_METHOD *t_method) {
        t_ssl_node->ssl_ctx = SSL_CTX_new(t_method);

        SSL_CTX_set_ecdh_auto(t_ssl_node->ssl_ctx, 1);
        int32_t ret = SSL_CTX_use_certificate_file(t_ssl_node->ssl_ctx, t_cert, SSL_FILETYPE_PEM);
        if (ret <= 0) {
            ERR_print_errors_fp(stderr);
            return JUDO_READ_CERT_FILE_FAILURE;
        }
        ret = SSL_CTX_use_PrivateKey_file(t_ssl_node->ssl_ctx, t_key, SSL_FILETYPE_PEM);
        if (ret <= 0) {
            ERR_print_errors_fp(stderr);
            return JUDO_READ_KEY_FILE_FAILURE;
        }
        const long flags = SSL_EXT_TLS1_3_ONLY;
        SSL_CTX_set_options(t_ssl_node->ssl_ctx, flags);
        t_ssl_node->ssl = SSL_new(t_ssl_node->ssl_ctx);
        t_ssl_node->read_bio = BIO_new(BIO_s_mem());
        t_ssl_node->write_bio = BIO_new(BIO_s_mem());
        SSL_set_bio(t_ssl_node->ssl, t_ssl_node->read_bio, t_ssl_node->write_bio);
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoAccept_() {
        struct ssl_node* new_node = new struct ssl_node;
        new_node->mode = 0;
        if (m_mode & JUDO_MODE_SSL_ENABLED) {
            this->judoFillServerSSLFields_(new_node);
        }
        if (m_mode & JUDO_MODE_SERVER_CERTS_REQ) {
            new_node->mode |= JUDO_CON_SERVER_CERTS;
        }
        if (m_mode & JUDO_MODE_CLIENT_CERTS_REQ) {
            //new_node->mode |= JUDO_CON_CLIENT_CERTS;
        }
        struct sockaddr_in client_addr = {0};
        char* buffer = new char[m_buffer_size];
        int32_t client_addr_size = sizeof(client_addr);
        new_node->fp = accept(m_server_list_sock, (struct sockaddr*) &client_addr, (socklen_t*) &client_addr_size);
        buffer[0] = 0x01;

        write(new_node->fp, buffer, 1);
        int32_t resp = read(new_node->fp, buffer, 1);
        if ((resp > 0) && (buffer[0] == 0x01) ) {
            if (m_mode & JUDO_MODE_SSL_ENABLED) this->judoHandshake_(new_node, buffer);
        } else {
            close(new_node->fp);
            dstr_ssl_node(new_node);
            return -1;
        }
        struct pollfd new_pollfd = {new_node->fp, POLLIN, 0};
        m_ssl_nodes->add(&new_pollfd, &new_node);
        delete[] buffer;
    }

    int32_t JudoServer::judoSocketConnect_(struct sockaddr_in* t_addr, int32_t* t_fp_out) {
        *t_fp_out = socket(AF_INET, SOCK_STREAM, 0);
        int32_t return_val = connect(*t_fp_out, (struct sockaddr*) t_addr, sizeof(*t_addr));
        if (return_val < 0) {
            perror("Unable to Connect");
            close(*t_fp_out);
            *t_fp_out = -1;
            return JUDO_CONNECTION_FAILURE;
        }
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoConnect_(struct sockaddr_in* t_addr, char* t_cert, char* t_key, int8_t t_mode) {
        if ((t_mode & JUDO_CON_CLIENT_CERTS) && ((t_cert == nullptr) || (t_key == nullptr))) {
            return JUDO_INPUT_CERT_FILES_MISSING;
        }
        struct ssl_node* new_node = new struct ssl_node;
        new_node->mode = t_mode;
        if (t_mode & (JUDO_CON_CLIENT_CERTS | JUDO_CON_SERVER_CERTS)) {
            this->judoFillClientSSLFields_(new_node, t_cert, t_key);
        }
        int32_t return_val = judoSocketConnect_(t_addr, &(new_node->fp));
        if (return_val != JUDO_SUCCESS) {
            dstr_ssl_node(new_node);
            return return_val;
        }
        char* buffer = new char[m_buffer_size];
        int32_t bytes_read = read(new_node->fp, buffer, 1);
        if (bytes_read > 0) {
            if ((buffer[0] & 0x01) != (t_mode & 0x01)) {
                int32_t output;
                if (buffer[0] & JUDO_CON_SERVER_CERTS) {
                    output = JUDO_REMOTE_HOST_SERVER_CERTS_REQUIRED;
                } else {
                    output = JUDO_REMOTE_HOST_NO_SERVER_CERTS;
                }
                buffer[0] = 0xFF;
                write(new_node->fp, buffer, 1);
                close(new_node->fp);
                delete[] buffer;
                dstr_ssl_node(new_node);
                return output;
            } else if ((buffer[0] & 0x02) != (t_mode & 0x02)) {
                int32_t output;
                if (buffer[0] & JUDO_CON_CLIENT_CERTS) {
                    output = JUDO_REMOTE_HOST_CLIENT_CERTS_REQUIRED;
                } else {
                    output = JUDO_REMOTE_HOST_NO_CLIENT_CERTS;
                }
                buffer[0] = 0xFF;
                write(new_node->fp, buffer, 1);
                close(new_node->fp);
                delete[] buffer;
                dstr_ssl_node(new_node);
                return output;
            } else {
                write(new_node->fp, buffer, 1);
            }
        } else {
            delete[] buffer;
            dstr_ssl_node(new_node);
            close(new_node->fp);
            return JUDO_REMOTE_HOST_DISCONNECT;
        }
        if (new_node->mode & 0x03) {
            this->judoHandshake_(new_node, buffer);
        }
        struct pollfd new_pollfd = {new_node->fp, POLLIN, 0};
        m_ssl_nodes->add(&new_pollfd, &new_node);
        buffer[0] = 'J';
        buffer[1] = 'e';
        buffer[2] = 'J';
        buffer[3] = 'e';
        buffer[4] = 'J';
        buffer[5] = 'e';
        buffer[6] = '\0';



        this->judoSend_(new_node, buffer, m_buffer_size);
        delete[] buffer;
        close(new_node->fp);
        return JUDO_SUCCESS;
    }

    int32_t JudoServer::judoSend_(struct ssl_node* t_node, char* t_buffer, int32_t t_size) {
        int32_t str_len  = strlen(t_buffer) + 1;

        int32_t bytes_to_write = str_len;
        if (t_node->mode & (JUDO_CON_CLIENT_CERTS | JUDO_CON_SERVER_CERTS)) {
            SSL_write(t_node->ssl, t_buffer, str_len);
            bytes_to_write = BIO_read(t_node->write_bio, t_buffer, t_size);

        }
        write(t_node->fp, t_buffer, bytes_to_write);
        return 0;

    }

    int32_t JudoServer::judoHandshake_(struct ssl_node* t_node, char* buffer) {
        while (!SSL_is_init_finished(t_node->ssl)) {
            SSL_do_handshake(t_node->ssl);
            int32_t bytes_to_write = BIO_read(t_node->write_bio, buffer, m_buffer_size);
            if (bytes_to_write > 0) {
                write(t_node->fp, buffer, bytes_to_write);
            } else {
                int32_t bytes_to_read = read(t_node->fp, buffer, m_buffer_size);
                if (bytes_to_read > 0) {
                    BIO_write(t_node->read_bio, buffer, bytes_to_read);
                }
            }
        }
        std::cout <<"JUDO: Handshake with Client " << t_node->fp << " Successful\n"<< std::flush;
        return 1;
    }

    int32_t JudoServer::run() {
        std::cout << "JUDO: RUNNING\n" << std::flush;
        m_active = true;
        char* buffer = new char[m_buffer_size];
        int a = 0;
        while(a != 10) {
            struct pollfd* poll_array = m_ssl_nodes->getFirstArray();
            struct ssl_node** node_array = m_ssl_nodes->getSecondArray();

            int32_t array_size = m_ssl_nodes->getSize();


            int32_t sockets_to_handel = poll(poll_array, array_size, 100);
            int32_t index = 0;
            while (sockets_to_handel != 0) {
                struct pollfd current_poll = poll_array[index];
                struct ssl_node* current_node = node_array[index];
                if (current_poll.revents & POLLIN) {
                    if (current_poll.fd == m_server_list_sock) {
                        std::cout << "JUDO: Accepting Client\n" << std::flush;
                        judoAccept_();
                        a++;
                    } else {
                        int32_t bytes_read = read(current_poll.fd, buffer, m_buffer_size);
                        if (bytes_read <= 0) {

                            std::cout << "JUDO: Disconnecting Client " << current_node->fp << "\n" << std::flush;
                            close(current_node->fp);
                            dstr_ssl_node(current_node);
                            m_ssl_nodes->remove(&current_poll);
                            index -= 1;
                        } else {

                            BIO_write(current_node->read_bio, buffer, bytes_read);
                            SSL_read(current_node->ssl, buffer, m_buffer_size);

                            std::cout << "JUDO: Client "<< current_node->fp << ": " << buffer << "\n" << std::flush;
                        }
                        a++;
                    }
                    sockets_to_handel -= 1;
                    poll_array[index].revents = 0;
                }

                index++;

            }
        }
        delete[] buffer;
        return 0;
    }
}
// server test mode (accept clients)
/*
int main() {
    char cert[] = "/home/squin/programming/cert.pem";
    char key[] = "/home/squin/programming/key.pem";
    struct sockaddr_in addr = {0};
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;
    judo::JudoServer* a = new judo::JudoServer(&addr, cert, key);
    a->run();
    delete a;
}
 */


// client test mode (connect to remote host)

int main() {
    char cert[] = "/home/squin/programming/cert.pem";
    char key[] = "/home/squin/programming/key.pem";
    struct sockaddr_in addr = {0};
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;
    judo::JudoServer* a = new judo::JudoServer();
    a->judoConnect_(&addr, cert, key, 0x01);
    delete a;
}

