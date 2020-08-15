/*
 * --------------------------------------------------------------------------------
 * File :         HashTable.cpp
 * Project :      CPP
 * Author :       Saurish Phatak
 *
 *
 * Description : Hash Table in C++
 * --------------------------------------------------------------------------------
 *
 * Revision History :
 * 2020-August-08	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;

// Represents a value in the Hash Table
struct Entry
{
    // Holds the key of the Entry
    int key;

    // Holds the value
    int value;

    // Points to the collision Entry
    Entry *collisionEntry;

    // Constructor
    Entry(int k, int v)
    {
        // Set the key and value
        key = k;
        value = v;

        // Set the collisionEntry to nullptr
        collisionEntry = nullptr;
    }
};

// Represents the Hash Table itself
class HashTable
{
    // Points to the "buckets"
    Entry **table;

    // Holds the size of the Table
    int size;

    // Returns the hash of a key
    int getHash(int key)
    {
        // Simple Hash Function
        return key % size;
    }

public:
    // Parameterised Constructor
    HashTable(int initialSize = 11)
    {
        // Allocate an array of pointers
        table = new Entry *[this->size = initialSize];

        // Set the array of pointers to nullptr
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    // Adds a value to the Table
    void put(int key, int value)
    {
        // Holds a new Entry
        Entry *newEntry;

        // Allocate a new Entry
        if (!(newEntry = new Entry(key, value)))
            return;

        // Get the hash of the key
        int hash = getHash(key);

        // If there are already Entries in that bucket
        if (table[hash])
        {
            // Add the newEntry at the head of the
            // Collision List
            newEntry->collisionEntry = table[hash];
        }

        table[hash] = newEntry;
    }

    // Returns the value of the a given key
    int get(int key)
    {
        // Get the hash of the key
        int hash = getHash(key);

        // If the bucket at that hash is not empty
        if (table[hash])
        {
            // Search for the given key
            for (Entry *current = table[hash]; current; current = current->collisionEntry)
            {
                // Key found
                if (current->key == key)
                    return current->value;
            }
        }

        // No such key in the Table
        return 0;
    }

    // Prints the entire Hash Table
    void printTable()
    {
        // If the table exists
        if (table)
        {
            string output = "\n";

            // Print the Entries is each "bucket"
            for (int i = 0; i < size; i++)
            {
                output += ("[" + to_string(i) + "] => ");

                for (auto current = table[i]; current; current = current->collisionEntry)
                {
                    output += ("[" + to_string(current->key) + " : " + to_string(current->value) + "] ");

                    if (current->collisionEntry)
                        output += " => ";
                }

                cout << output << endl;
                output = "";
            }
        }
    }

    // Removes a key-value pair from the Table
    bool remove(int key)
    {
        // Get the hash of the key
        int hash = getHash(key);

        // If the table is not empty
        if (table)
        {
            // Search for the Entry with the given key
            for (Entry *current = table[hash], *previous = current; current; current = current->collisionEntry)
            {
                // Value found
                if (key == current->key)
                {
                    // If this Entry is at the Head of the Collision List
                    if (table[hash] == current)
                    {
                        table[hash] = current->collisionEntry;
                        delete current;

                        return true;
                    }

                    // Else this Entry is in the Middle of the Collision List
                    // Or at the end of the List
                    else
                    {
                        previous->collisionEntry = current->collisionEntry;
                        delete current;

                        return true;
                    }
                }

                // Update previous pointer
                previous = current;
            }
        }
        // No such key in the Table
        return false;
    }

    // Clears the Table
    void clear()
    {
        int counter = 0;

        // If the table exists
        if (table)
        {
            // Clear each bucket
            for (int i = 0; i < size; i++)
            {
                for (Entry *current = table[i]; current; current = table[i])
                {
                    // If there are no Entries in a bucket
                    if (!table[i])
                        continue;

                    // Else point table[hash] to the next Entry after current
                    table[i] = current->collisionEntry;

                    delete current;
                    counter++;
                }
            }
        }

        cout << "Table cleared. Deleted " << counter << " Entries." << endl;
    }
};

int main()
{
    // Create a new Hash Table
    HashTable table;

    // Add some values to the table
    table.put(1, 19);
    table.put(12, 43);
    table.put(29, 89);
    table.put(54, 44);

    // Print the table
    table.printTable();

    table.clear();
    table.printTable();

    return 0;
}