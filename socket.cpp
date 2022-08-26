#include "Socket.hpp"
#include <cstdio>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#undef FEATURE_FILE_SAVE

// ============================= Base Socket ===========================================
BaseSocket::BaseSocket(int socketFd) : socketFd(socketFd)
{
    if (socketFd == invalidSocketFd) {
        ErrorLog::BaseSocketError("Constructor, Error on initializing socket file descriptor");
    }
}

BaseSocket::~BaseSocket()
{
    if (socketFd >= 0) {
        close();
    }
}

void BaseSocket::close()
{
    if (::close(socketFd) < 0) {
        ErrorLog::BaseSocketError("Error on closing socket file descriptor");
    }
    socketFd = -1;
}

// ============================= Data Socket ===========================================
std::string DataSocket::receiveMessage()
{
    char recvMsg[MAX_BUFF_SIZE];
    ::memset(recvMsg, 0, MAX_BUFF_SIZE);
    ssize_t n;

    n = ::read(getSocketFd(), recvMsg, MAX_BUFF_SIZE);
    if (n < 0)
        ErrorLog::DataSocketError("error occuring when receiving data");
    return std::string(recvMsg);
}

// use for reading large data from socket file descriptor
std::string DataSocket::receiveData()
{
    int rc = 0;
    ssize_t n;
    std::string msg;
    char buffer[MAX_BUFF_SIZE];
    memset(buffer, 0, MAX_BUFF_SIZE);

    int flags;
    flags = fcntl(getSocketFd(), F_GETFL, 0);
    if (-1 == flags) {
        ErrorLog::DataSocketError("fcntl");
        exit(EXIT_FAILURE); 
    }
    fcntl(getSocketFd(), F_SETFL, flags | O_NONBLOCK);

    struct timeval tv;
    fd_set readfds;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_ZERO(&readfds);
    FD_SET(getSocketFd(), &readfds);

    while(1) {
        rc = select(getSocketFd() + 1, &readfds, NULL, NULL, &tv);
        if(rc < 0) {
            ErrorLog::DataSocketError("error on selecting file descriptor");
            exit(EXIT_FAILURE);
        } else if (rc == 0) {
            return msg; // timeout
        } else {
            n = read(getSocketFd(), buffer, MAX_BUFF_SIZE -1);
            if (n == 0) {
        	return msg;
            } else if(n == -1) {
        	ErrorLog::DataSocketError("error on reading data");
        	return msg;
            } else {
        	msg.append(buffer);
        	memset(buffer, 0, MAX_BUFF_SIZE);
            }
        }
    }
}

void DataSocket::clearFd()
{
    receiveMessage();
}

void DataSocket::sendMessage(const std::string& msg)
{
    char const* buffer = msg.c_str();
    std::size_t size = msg.size();
    std::size_t dataWritten = 0;

    while (dataWritten < size) {
        ssize_t put = ::write(getSocketFd(), buffer + dataWritten, size - dataWritten);

        if (put == -1) {
            switch(errno) {
                case EPIPE:
            	    // fatal error
                    ErrorLog::DataSocketError("error occuring when sending data");
                case EAGAIN:
    	            // temporary error, retry writing data
            	    continue;
            }
        }
        dataWritten += put;
    }  
}

bool DataSocket::sendFile(const std::string& file)
{
    FILE* fin = std::fopen(file.c_str(), "r");
    if (!fin) {
        // todo
        return false;
    }

    ssize_t bytesRead = 0, r;
    char buffer[MAX_BUFF_SIZE];
    while ((r = read(fileno(fin), buffer, MAX_BUFF_SIZE)) > 0) {
        bytesRead += r;
        ssize_t bytesWritten = 0, w;
        while (r > 0 && (w = write(getSocketFd(), buffer + bytesWritten, r)) > 0) {
            bytesWritten +=  w;
            r -= w;
        }
        if (w < 0) {
            // todo handle error
        }
    }
    if (r < 0) {
        // todo handle error
    }

    fclose(fin);
    return true;
}

bool DataSocket::receiveFile(const std::string& file)
{
#ifdef FEATURE_FILE_SAVE
    FILE* fout = std::fopen(file.c_str(), "w");
    if (!fout) {
        std::cout << "ERROR OPEN FILE RECV";
        return false;
    }
#endif

    ssize_t bytesRead = 0, r;
    char buffer[MAX_BUFF_SIZE];
    while ((r= read(getSocketFd(), buffer, MAX_BUFF_SIZE)) > 0) {
        bytesRead += r;

#ifdef FEATURE_FILE_SAVE
        ssize_t bytesWritten = 0, w;
        while (r > 0 && (w = write(fileno(fout), buffer + bytesWritten, r)) > 0) {
            bytesWritten += w;
            r -= w;
        }
        if (w < 0) {
            // todo handle error
        }
#endif
    }
    if (r < 0) {
        // todo handle error
    }

#ifdef FEATURE_FILE_SAVE
    fclose(fout);
#endif
    return true;
}

// ============================= Connect Socket ===========================================
ConnectSocket::ConnectSocket(const std::string& host, unsigned int port, const std::string& localIp) : DataSocket(::socket(AF_INET, SOCK_STREAM, 0))
{
    _host = ::gethostbyname(host.c_str());
    if (_host == NULL) {
        errno = ECONNREFUSED;
        ErrorLog::ConnectSocketError("No such host");
        return;
    }

    ::memset((char*) &_host_addr, 0, sizeof(_host_addr));
    _host_addr.sin_family = AF_INET;
    ::memcpy((char*) &_host_addr.sin_addr.s_addr, (char*) _host->h_addr , _host->h_length);
    _host_addr.sin_port = htons(port);

    // TBD : bind local IP
    if (localIp.length() != 0) {
        // bind local IP
        struct sockaddr_in my_addr;

        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(0); // Allow system to select
        inet_aton(localIp.c_str(), &my_addr.sin_addr);
        int error = ::bind(getSocketFd(), (struct sockaddr *)&my_addr, sizeof(my_addr));
        if (error!=0) {
            close();
            ErrorLog::ConnectSocketError("Can't bind local IP");
            return;
        }
    }

    if (::connect(getSocketFd(), (sockaddr*) &_host_addr, sizeof(_host_addr)) != 0) {
        close();
        ErrorLog::ConnectSocketError("Can't connect to host");
        return;
    }

    socklen_t len = sizeof(_myAddr);
    if (::getsockname(getSocketFd(), (sockaddr*)&_myAddr, &len) < 0) {
        close();
        ErrorLog::ConnectSocketError("getsockname");
    }
}

// ============================= Log ===========================================
using namespace ErrorLog;

void ErrorLog::error(const std::string& msg)
{
    std::cout << msg << ": " << std::strerror(errno) << '\n';
    // exit(EXIT_FAILURE);
}

void ErrorLog::BaseSocketError(const std::string& msg)
{
    error("[BaseSocket] " + msg);
}

void ErrorLog::DataSocketError(const std::string& msg)
{
    error("[DataSocket] " + msg);
}

void ErrorLog::HostSocketError(const std::string& msg)
{
     error("[HostSocket] " + msg);
}

void ErrorLog::ConnectSocketError(const std::string& msg)
{
     error("[ConnectSocket] " + msg);
}
