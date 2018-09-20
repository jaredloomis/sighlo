#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>
#include <optional>
#include <memory>
#include "identifier.h"

enum class EntityType {
    NIL, STRING, LIST, HASH
};

std::string entity_type_str(EntityType ty) {
    switch(ty) {
        case EntityType::NIL:    return "NIL";
        case EntityType::STRING: return "STR";
        case EntityType::LIST:   return "LST";
        case EntityType::HASH:   return "HSH";
    }
}

EntityType parse_entity_type(std::string str) {
    if(str == "STR") return EntityType::STRING;
    if(str == "LST") return EntityType::LIST;
    if(str == "HSH") return EntityType::HASH;
                     return EntityType::NIL;
}

class Entity {
  public:
    EntityType type;
    Identifier id;

    Entity()              :
        type(EntityType::NIL), id(Identifier::generate()) {}
    Entity(const EntityType ty) :
        type(ty),              id(Identifier::generate()) {}
    Entity(const EntityType ty, const Identifier ident) :
        type(ty),              id(ident) {}
    Entity(const Entity& cp) :
        type(cp.type), id(cp.id) {}

    virtual ~Entity() {}

    virtual std::ostream& write(std::ostream& os) const {
        os << "Can't output Entity";
        return os;
    }

    virtual std::istream& read(std::istream& is) {
        return is;
    }

    std::istream& read_header(std::istream& is) {
        char raw_ty[4];
        char* raw_id = (char*) malloc(Identifier::length + 1);
        is.get(raw_ty, 4);
        is.get(raw_id, Identifier::length);

        type = parse_entity_type(std::string(raw_ty));
        id   = Identifier(std::string(raw_id));
        return is;
    }

    std::ostream& write_header(std::ostream& os) const {
        os << entity_type_str(type) << id;
        return os;
    }
};

class StringEntity : public Entity {
  private:
    std::string data;

  public:
    StringEntity() : Entity(EntityType::STRING) {}

    StringEntity(std::string str)
        : Entity(EntityType::STRING), data(str) {}

    StringEntity(Identifier id)
        : Entity(EntityType::STRING, id) {}

    StringEntity(Identifier id, std::string str)
        : Entity(EntityType::STRING, id), data(str) {}

    StringEntity(const Entity& cp)
        : Entity(cp) {}

    StringEntity(const Entity& cp, std::string str)
        : Entity(cp), data(str) {}

    std::ostream& write(std::ostream& os) const {
        write_header(os);
        os << data;
        return os;
    }

    std::istream& read(std::istream& is) {
        read_header(is);
        read_data(is);
        return is;
    }

    std::istream& read_data(std::istream& is) {
        char str[1024];
        is.getline(str, 1024);
        data = std::string(str);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Entity& entity) {
        return entity.write(os);
    }

    friend std::istream& operator>>(std::istream& is, Entity* entity) {
        Entity tmp;
        tmp.read_header(is);
        if(tmp.type == EntityType::STRING) {
            entity = new StringEntity(tmp);
            ((StringEntity*) entity)->read_data(is);
        }
        return is;
    }
};

std::optional<Entity*> read_entity(std::istream& is) {
    char ty[4];
    char* id = (char*) malloc(Identifier::length + 1);
    is.get(ty, 4);
    is.get(id, Identifier::length);
    if(std::string(ty) == "STR") {
        StringEntity* ret = new StringEntity(Identifier(std::string(id)));
        ret->read_data(is);
        return ret;
    } else {
        return {};
    }
}

#endif // _ENTITY_H
