#ifndef _TABLE_H
#define _TABLE_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <string>
#include <optional>
#include <cstdlib>
#include "entity.h"

typedef std::string Identifier;

class Table {
  public:
    std::ofstream file;
    std::map<Identifier, Entity*> entries;
    std::vector<std::string> log;

    Table() {}

    Table(std::string path) {
    }

    ~Table() {
        file.close();
        for(std::map<Identifier, Entity*>::iterator it = entries.begin(); it != entries.end(); ++it)
            delete it->second;
    }

    Identifier insert(Entity* entity) {
        // Generate ID
        Identifier id = generateID();
        // Insert in-memory
        entries[id] = entity;
        // Insert into file
        file << *entity;
        return id;
    }

    std::vector<std::pair<Identifier, Entity*>> search(bool (*pred)(Identifier, Entity*)) const {
        std::vector<std::pair<Identifier, Entity*>> ret;
        auto all = list();
        for(size_t i = 0; i < all.size(); ++i) {
            auto entity = all[i];
            if(pred(entity.first, entity.second))
                ret.push_back(entity);
        }
        return ret;
    }

    std::optional<Entity*> get(Identifier id) const {
        auto cached = get_cache(id);
        if(cached.has_value())
            return cached;
        else
            return get_disk(id);
    }

    std::optional<Entity*> get_cache(Identifier id) const {
        try {
            return std::optional(entries.at(id));
        } catch(std::out_of_range ex) {
            return std::nullopt;
        }
    }

    std::optional<Entity*> get_disk(Identifier id) const {
        
        return std::nullopt;
    }

    std::vector<std::pair<Identifier, Entity*>> list() const {
        std::vector<std::pair<Identifier, Entity*>> ret;
        for(std::map<Identifier, Entity*>::const_iterator it = entries.cbegin(); it != entries.cend(); ++it)
            ret.push_back(std::make_pair(it->first, it->second));
        return ret;
    }

    Identifier generateID() const {
        return std::to_string(rand());
    }
};

std::ostream& operator<<(std::ostream& os, const Table& table) {
    auto entities = table.list();
    for(size_t i = 0; i < entities.size(); ++i) {
        os << *entities[i].second << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Table& table) {
    Entity* entity;
    do {
        entity = new Entity();
        is >> *entity;
        if(entity->type != EntityType::NIL) {
            table.insert(entity);
        } else {
            delete entity;
        }
    } while(entity->type != EntityType::NIL);

    return is;
}

#endif // _TABLE_H
