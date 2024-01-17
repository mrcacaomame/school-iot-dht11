#pragma once
#include <exception>
#include <string>

class RaspberryPiException : public std::exception {
    private:
        std::string msg_;
    
    public:
        RaspberryPiException (const std::string &msg) : msg_ (msg) {}
    
    public:
        const char *what() const noexcept override{
            return this->msg_.c_str ();
        }
    
};
