#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "table.h"
#include "entity.h"
#include "repl.h"

int main() {
    // Create table
    Table table;
    std::ifstream ifile;
    ifile.open("./test.db");
    ifile >> table;
    ifile.close();

    // REPL
    Repl repl   = Repl();
    bool active = true;
    try {
    while(active) {
        active = repl.read_eval_print(table);
    }
    } catch(std::exception ex) {

    // Save db to file
    std::ofstream ofile;
    ofile.open("./test.db");
    ofile << table;
    }

    // Save db to file
    std::ofstream ofile;
    ofile.open("./test.db");
    ofile << table;
}

/*
int main2() {
    std::ifstream ifile;
    ifile.open("./test.db");
    Entity* fuck = read_entity(ifile).value();
    //ifile >> e;
    std::cout << *fuck << std::endl;
    return 0;
}

int main1(int argc, char** argv) {
    // Create table
    Table table;
    std::ifstream ifile;
    ifile.open("./test.db");
    ifile >> table;
    ifile.close();

    std::cout << "PARSED:\n" << table << "\n\n";

    std::ofstream ofile;
    ofile.open("./test.db");

    // Insert
    std::vector<Identifier> ids;
    for(size_t i = 0; i < 12; ++i) {
        StringEntity* entity = new StringEntity("User #" + std::to_string(i));
        auto id = table.insert(entity);
        ids.push_back(id);
        std::cout << "Inserted " << id << std::endl;
    }
    std::cout << std::endl;

    // Retrieve (get)
    Entity def = StringEntity("nothing");
    Entity* ret = table.get(ids[0]).value_or(&def);
    std::cout << "Get: " << *ret << std::endl << std::endl;

    // Search
    auto results = table.search([](Identifier id, Entity* entity) {  
        return entity->type == EntityType::STRING;  
    });
    std::cout << "Search results: " << std::endl;
    for(size_t i = 0; i < results.size(); ++i) {
        std::cout << *results[i].second << std::endl;
    }

    ofile << table;

    return 0;
}*/
