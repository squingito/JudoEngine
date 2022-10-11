namespace judo_engine {

	void JudoEngine::init(int16_t t_mode) {
		//need constructors
		SSL_load_error_strings();
		OpenSSL_Add_ssl_algorithms();

		m_incoming_connections = new BinarySearchTree<struct ssl_node>();
		m_pollfd_array = new DynamicArray<struct pollfd>();
		m_mode = t_mode;
	}

	JudoEngine::JudoEngine(int16_t t_mode) {
		this->init(t_mode);
	}

	JudoEngine::JudoEngine(int16_t t_mode, struct sockaddr_in* t_addr) {
		this->init(t_mode);
		this->judoMakeServerSock(t_addr);
	}

	JudoEngine::JudoEngine(int16_t t_mode, struct sockaddr_in* t_addr, char* t_cert, char* t_private_key) {
		this->init(t_mode);
		this->judoMakeServerSock(t_addr);
		this->judoStartServerSockSSL();
	}

	void JudoEngine::judoMakeServerSock(struct sockaddr_in* t_addr) {
		if (t_addr != nullptr) {
			m_server_list_sock = socket(AF_INET, SOCK_STREAM, 0);
			int mode = 1;
			setsockopt(m_server_list_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &mode, sizeof(mode));
			bind(m_server_list, (struct sockaddr*) &t_addr, sizeof(t_addr));
			m_list_sock_addr = *t_addr;
			m_mode &= JUDO_SEVER_SOCK_ENABLE;
		}
	}

	int32_t JudoEngine::judoFillSSLFields(struct ssl_node* t_to_fill) {

		const SSL_METHOD* method = TLS_server_method();
		struct ssl_st* ssl_ctx = SSL_CTX_new(method);
		const clong flags = SSL_EXT_TLS1_3_ONLY;
		SSL_CTX_set_options

	


	int32_t JudoEngine::run() {
		if (m_mode != 0) {
			m_active = true;
		} else {
			return JUDO_MODE_NOT_SET;

		return this->mainLoop_();
	}


