/*
 * --------------------------------------------------------------------------------
 * File :         GenericHashTable.cpp
 * Project :      CPP
 * Author :       Saurish Phatak
 *
 *
 * Description : Generic Hash Table in C++
 * --------------------------------------------------------------------------------
 *
 * Revision History :
 * 2020-August-09	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

using namespace std;

// Represents an Entry
template<class K, class V>
struct Entry
{
    // Holds the value of the Entry
    V value;

    // Holds the key of the Entry
    K key;

    // Points to the Collision Entry
    Entry<K, V> *collisionEntry;

    // Constructor
    Entry(K k, V v)
    {
        key = k;
        value = v;

        collisionEntry = nullptr;
    }
};

// Represents the Hash Table
template<class K, class V>
class HashTable
{
    // Points to the "buckets"
    Entry<K, V> **table;

    // Holds the size of the Hash Table
    int size;

    // Returns the hash of the Key
    int getHash(K key)
    {
        size_t hash = std::hash<K>()(key);

        return hash % size;
    }

public:
    // Constructor
    HashTable(int initialSize = 11)
    {
        // Create an array of pointers ("buckets")
        table = new Entry<K, V> *[(size = initialSize)];

        for (int i = 0; i < size; i++)
            table[i] = nullptr;

    }
    // Adds a value to the Hash Table
    void put(K key, V value)
    {
        // If the table exists
        // Create a new Entry
        Entry<K, V> *newEntry = new Entry<K, V>(key, value);

        // Get the hash of the Key
        int hash = getHash(key);

        // If this is a collision
        if (table[hash])
        {
            // Add newEntry at the front of the
            // Collision List
            newEntry->collisionEntry = table[hash];
        }

        // Point table hash to the newEntry
        table[hash] = newEntry;
    }

    // Gets the value of a key from the Hash Table
    bool get(K key, V &value)
    {
        // If the table exists
        if (table)
        {
            // Get the hash of the key
            int hash = getHash(key);

            // Search for the value in the "bucket"
            for (auto current = table[hash]; current; current = current->collisionEntry)
            {
                // Key found
                if (key == current->key)
                {
                    value = current->value;
                    return true;
                }
            }
        }

        // No such key in the Table
        return false;
    }

    // Removes a key-value pair from the Table
    bool remove(K key)
    {
        // Get the hash of the key
        int hash = getHash(key);

        // If the table exists
        if (table)
        {
            // Search for the key-value pair
            for (auto current = table[hash], previous = current; current; current = current->collisionEntry)
            {
                // Key found
                if (key == current->key)
                {
                    // If this pair is at the front of the Collision List
                    if (table[hash] == current)
                    {
                        // Point table[hash] to current's next Entry
                        table[hash] = current->collisionEntry;
                    }

                    // This value is at the end of the Collision List
                    // or in the middle of the List
                    else
                    {
                        // Point table[hash] to current's next Entry
                        previous->collisionEntry = current->collisionEntry;
                    }

                    delete current;
                    return true;
                }

                // Assign previous to current
                previous = current;
            }
        }
        // No such key in the Table
        return false;
    }

    // Clears the entire Table
    int clear()
    {
        int counter = 0;

        // If the table exists
        if (table)
        {
            for (int i = 0; i < size; i++)
            {
                for (auto current = table[i]; current; current = table[i])
                {
                    // If there are no Entries in a "bucket"
                    if (!table[i])
                        continue;

                    // Point table[hash] to the next Entry in the "bucket"
                    table[i] = table[i]->collisionEntry;

                    delete current;
                    counter++;
                }
            }
        }
        return counter;
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
                    output += ("[" + current->key + " : " + current->value + "] ");

                    if (current->collisionEntry)
                        output += " => ";
                }

                cout << output << endl;
                output = "";
            }
        }
    }
};

int main()
{
    // Create new Hash Table
    HashTable<string, string> table;

    table.put("adam", "19");
    table.put("eve", "22");
    table.put("john", "4");
    table.put("doe", "87");

    table.printTable();

    string result;
    if (table.get("adam", result))
        cout << result << endl;


    table.remove("adam");
    cout << table.get("adam", result) << endl;

    cout << table.clear() << endl;

    return 0;
}