#pragma once
#include <string>
#include <exception>

class DatabaseException : public std::exception{
    private:
        std::string msg_;
    
    public:
        DatabaseException (const std::string &msg): msg_ (msg){}
        const char *what (void) const noexcept override{
            return this->msg_.c_str ();
        }
};
