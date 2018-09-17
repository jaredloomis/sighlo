#include <iostream>
#include <memory>
#include <vector>
#include "table.h"
#include "entity.h"

int main(int argc, char** argv) {
    // Create table
    Table table("./test.db");

    // Insert
    std::vector<Identifier> ids;
    for(size_t i = 0; i < 12; ++i) {
        StringEntity* entity = new StringEntity("MY STRING ENTITY " + std::to_string(i));
        auto id = table.insert(entity);
        ids.push_back(id);
        std::cout << "ID" << i << ": " << id << std::endl;
    }

    // Retrieve (get)
    Entity def = StringEntity("nothing");
    Entity* ret = table.get(ids[0]).value_or(&def);
    std::cout << "Get: " << *ret << std::endl;

    // Search
    auto results = table.search([](Identifier id, Entity* entity) {  
        return entity->type == EntityType::STRING;  
    });
    std::cout << "Search results: " << std::endl;
    for(size_t i = 0; i < results.size(); ++i) {
        std::cout << *results[i].second << std::endl;
    }

    return 0;
}
