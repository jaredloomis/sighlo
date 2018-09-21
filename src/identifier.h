#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include <string>
#include <algorithm>
#include <random>

class Identifier {
  private:
    std::string str;

    static std::string random_string(size_t length) {
        auto randchar = []() -> char {
            const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = sizeof(charset) - 1;


            std::default_random_engine rng(std::random_device{}());
            std::uniform_int_distribution<> dist(0, sizeof(charset)-1);
            return charset[dist(rng) % max_index];
        };
        std::string str(length, 0);
        std::generate_n(str.begin(), length, randchar);
        return str;
    }

  public:
    const static size_t length = 9;

    Identifier() {}

    Identifier(std::string id) {
        str = id;
    }

    static Identifier generate() {
        std::string str = random_string(Identifier::length);
        return Identifier(str);
    }

    friend std::ostream& operator<<(std::ostream& os, const Identifier& id) {
        os << id.str;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Identifier& id) {
        char raw_str[Identifier::length + 1];
        is.get(raw_str, Identifier::length);
        id.str = std::string(raw_str);
        return is;
    }

    friend bool operator<(const Identifier& l, const Identifier& r) {
        return l.str < r.str;
    }
};

#endif // _IDENTIFIER_H
