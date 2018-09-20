# Architechture of Internals

## Table

Pure in-memory representation of an entire table. Consists of a collection of
Entities.

# Entity

A row in a table. An Entity consists of:
- An EntityType
- An identifier
- Data

# Repl

The repl is initialized by reading a table file into a table.

The core of the repl is a loop of the following steps:
- Get user input
- Parse / tokenize input
- Perform actions

At the end of the loop, the table is written back to the file.
