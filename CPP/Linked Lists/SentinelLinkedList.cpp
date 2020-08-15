/*
 * --------------------------------------------------------------------------------
 * File :         SentinelLinkedList.cpp
 * Project :      CPP
 * Author :       Saurish Phatak
 *
 *
 * Description : Sentinel Linked List in C++
 * --------------------------------------------------------------------------------
 *
 * Revision History :
 * 2020-August-01	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;

// Node represents a value in the List
struct Node
{
    // Points to the previous Node
    Node *previous;

    // Holds the Node's value
    int value;

    // Points to the next Node
    Node *next;

    // Constructor
    Node(int v)
    {
        previous = next = nullptr;
        (*this).value = v;
    }
};

// Represents the SentinelLinkedList
class SentinelLinkedList
{
    // Points to the Dummy Head
    Node *head;

    // Points to the Dummy Tail
    Node *tail;

public:
    // Constructor
    SentinelLinkedList()
    {
        // Create dummy Nodes
        head = tail = new Node(0);

        // Point head and tail to each other
        head->next = tail;
        (*tail).previous = head;
    }

    // Method to add a Node in the Linked List
    void pushBack(int value)
    {
        /**
         * This is where the Sentinel Linked List
         * really SHINES!
         * We don't have to check if this the First Node
         * that we're adding.
         *
         * We simply create a newNode and add it before the
         * tail.
         */

        // Holds the new Node
        Node *newNode;

        // If the allocation failed
        if (!(newNode = new Node(value)))
            return;

        /**
         * Add the newNode before the tail
         * Think of the List as a wall
         */
        // Make the newNode climb up the wall
        newNode->next = tail;
        newNode->previous = tail->previous;

        // Pull the newNode up the wall
        newNode->previous->next = newNode;
        tail->previous = newNode;

        // And that's it! That's how easy it is
        // to add a new Node to the Sentinel List
    }

    // Method to remove a Node from the List
    bool remove(int valueToRemove)
    {
        // Search for the value
        // Start from the head's next and not the head
        // as head itself points to a Dummy Node
        for (Node *current = head->next; current != tail; current = current->next)
        {
            // Value found
            if ((*current).value == valueToRemove)
            {
                // Disconnect the current Node from the List 
                current->previous->next = current->next;
                current->next->previous = current->previous;

                // Delete the current Node
                delete current;
                return true;
            }
        }

        // Value not in the List
        return false;
    }

    // Method to print the List in Forward direction
    void printForward()
    {
        // Start from head's next and go upto tail
        for (Node *current = head->next; current != tail; current = current->next)
        {
            // Print the current Node's value
            cout << current->value << " ";
        }

        cout << endl;
    }
};

int main()
{
    // Create a new Sentinel List
    SentinelLinkedList list;

    // Add some values to the list
    int value;
    while (cout << "Enter value (0 to stop) : ",
           cin >> value,
           value)
    {
        list.pushBack(value);
    }

    return 0;
}