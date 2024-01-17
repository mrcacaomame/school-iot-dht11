#pragma once
#include <exception>
#include <string>

class CheckOptionsException : public std::exception {
    private:
        std::string msg_;
    
    public:
        CheckOptionsException (const std::string &msg) : msg_ (msg) {}
    
    public:
        const char *what() const noexcept override{
            return this->msg_.c_str ();
        }
    
};
