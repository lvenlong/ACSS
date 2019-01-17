#ifndef EXCEPTION_INTERNAL_H_
#define EXCEPTION_INTERNAL_H_

#include <exception>
#include <string>
#include <sstream>
#include <errno.h>


namespace LiLong {

enum {
    OPERSUCCESS = 0,
    BUFFERISNULL = -1,
    PEEREXCEPTION = -2,
    WRITEEXCEPTION = -3,
    READEXCEPTION = -4,
    CONNECTSERVERFAIL = -5,
};

class Exception {
    public:
    void set_errno(int32_t e) {
        errno = e;
    }

    int32_t get_errno() {
        return errno;
    }

    virtual ~Exception() {}

    const char* get_err_msg() {
        return "error";
    }
};

class ConfigurationException : public std::exception {
public:
    ConfigurationException(const std::string& msg) : _msg("ConfigurationException> " + msg) {
    }

    ~ConfigurationException() throw() {
    }

    virtual const char * what() const throw() {
        return _msg.c_str();
    }

private:
    std::string _msg;
};
}
#endif
