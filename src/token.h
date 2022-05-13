#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class token{
  private:
    std::string str_;
  public:
    token(std::string str);
    inline std::string str() const;
    virtual ~token() = default;
};

std::ostream& operator<<(std::ostream& os, const token& tk);


/* IMPLEMENTACAO */

std::string token::str() const { return str_; }


#endif