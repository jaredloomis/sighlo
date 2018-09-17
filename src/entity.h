#ifndef _ENTITY_H
#define _ENTITY_H

#include <iostream>

enum class EntityType {
    STRING, LIST, HASH
};

class Entity {
  public:
    EntityType type;

    Entity() {}
    Entity(EntityType ty) : type(ty) {}

    virtual ~Entity() {}

    virtual std::ostream& write(std::ostream& os) const {
        os << "Can't output Entity";
        return os;
    }
};

class StringEntity : public Entity {
  public:
    std::string data;

    StringEntity(std::string str)
        : Entity(EntityType::STRING), data(str) {
    }

    std::ostream& write(std::ostream& os) const {
        os << data;
        return os;
    }
};

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    return entity.write(os);
}

#endif // _ENTITY_H
