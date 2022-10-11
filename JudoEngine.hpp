#ifndef JUDOENGINE_H
#define JUDOENGINE_H

#ifndef SYS_SOCKET_H
#define SYS_SOCKET_H
#include <sys/socket.h>
#endif

#ifndef CSTUDIO_H
#define CSTUDIO_H
#include <cstudio>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef ARPA_INET_H
#define ARPA_INET_H
#include <arpa/inet.h>
#endif

#ifndef UNISTD.H
#define UNISTD.H
#include <unistd.h>
#endif

#ifndef OPENSSL_H
#define OPENSSL_H
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef POLL_H
#define POLL_H
#include <poll.h>
#endif

#include "DynamicArray.hpp"
#include "BinarySearchTree.hpp"
#include "JudoEngineStructs.hpp"

namespace judo_engine {

	class JudoEngine {
	public:
		JudoEngine(uint32_t, char*, char*);
		~JudoEngine();
		int32_t run();
	
	




	private:
		BinarySearchTree<struct ssl_node>* m_incoming_connections = nullptr;
		DynamicArray<struct pollfd>* m_pollfd_array = nullptr;
		int32_t m_server_list_sock = 0;
		struct sockaddr_in m_list_sock_addr;
		char* m_cert_file = nullptr;
		char* m_private_key_file = nullptr;
		bool m_active = false;

		int32_t accept_();
		int32_t mainLoop_();
	

	};




}

#endif
