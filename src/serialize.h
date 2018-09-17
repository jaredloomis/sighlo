#ifndef _SERIALIZE_H
#define _SERIALIZE_H

#include <string>
#include <fstream>
#include <vector>
#include "entity.h"

class Serializer {
  public:
    std::ifstream file;

    Serializer(std::string path) {
        file.open(path);
    }

    std::vector<Entity*> search(bool (*pred)(Entity*)) {
    }
};

#endif // _SERIALIZE_H
