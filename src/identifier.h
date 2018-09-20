#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include <string>

class Identifier {
  private:
    std::string str;

  public:
    Identifier(std::string id) {
        str = id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Identifier& id) {
        os << id.str;
        return os;
    }

    friend bool operator<(const Identifier& l, const Identifier& r) {
        return l.str < r.str;
    }

    const static size_t length = 9;

    static Identifier generate() {
        return Identifier(std::to_string(rand()));
    }
};

#endif // _IDENTIFIER_H
