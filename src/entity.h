#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>
#include <optional>
#include <memory>

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

class Entity {
  public:
    EntityType type;

    Entity()              : type(EntityType::NIL) {}
    Entity(EntityType ty) : type(ty) {}

    virtual ~Entity() {}

    virtual std::ostream& write(std::ostream& os) const {
        os << "Can't output Entity";
        return os;
    }

    virtual std::istream& read(std::istream& is) {
        return is;
    }
};

class StringEntity : public Entity {
  public:
    std::string data;

    StringEntity() : Entity(EntityType::STRING) {}

    StringEntity(std::string str)
        : Entity(EntityType::STRING), data(str) {}

    std::ostream& write(std::ostream& os) const {
        os << data;
        return os;
    }

    std::istream& read(std::istream& is) {
        char str[1024];
        is.getline(str, 1024);
        data = std::string(str);
        return is;
    }
};

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    os << entity_type_str(entity.type);
    return entity.write(os);
}

/*
 * This operator should only be used when
 */
std::istream& operator>>(std::istream& is, Entity& entity) {
    char ty[3];
    is.get(ty, 3);
    if(std::string(ty) == "STR") {
        StringEntity ret;
        ret.read(is);
        entity = ret;
    }
    return is;
}

std::optional<Entity*> read_entity(std::istream& is) {
    char ty[4];
    is.get(ty, 4);
    if(std::string(ty) == "STR") {
        StringEntity* ret = new StringEntity();
        ret->read(is);
        return ret;
    } else {
        return {};
    }
}

#endif // _ENTITY_H
