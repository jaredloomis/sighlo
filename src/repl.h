#ifndef _REPL_H
#define _REPL_H

#include <iostream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include "table.h"

class Repl {
  private:
    static std::vector<std::string> tokenize(std::string statement) {
        std::vector<std::string> ret;

        long last_space = -1;
        long len        = statement.length();
        for(long i = 0; i < len; ++i) {
            if(statement[i] == ' ') {
                if(last_space != i-1)
                    ret.push_back(statement.substr(last_space+1, i - (last_space == -1 ? 0 : last_space)));
                last_space = i;
            }
            if(i == len-1)
                ret.push_back(statement.substr(last_space+1, last_space+1-len));
        }
        return ret;
    }

  public:
    bool read_eval_print(const Table& table) {
        std::cout << "> ";
        char command_raw[256];
        std::cin.getline(command_raw, 256);
        auto command = std::string(command_raw);
        auto tokens = tokenize(command);

        if(tokens[0] == "get") {
            auto id = tokens[1];
            auto m_entity = table.get(id);
            if(m_entity.has_value()) {
                std::cout << *m_entity.value() << std::endl;
            } else {
                std::cout << "No entity found with id " + id << std::endl;
            }
        } else if(tokens[0] == "list") {
            auto entities = table.list();
            for(size_t i = 0; i < entities.size(); ++i) {
                auto entity = entities[i];
                std::cout << entity.first << ": " << *entity.second << std::endl;
            }
        } else if(tokens[0] == "quit") {
            return false;
        } else {
            std::cout << "Didn't recognize command " << tokens[0] << std::endl;
        }
        return true;
    }
};

#endif // _REPL_H
