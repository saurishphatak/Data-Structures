/*
 * --------------------------------------------------------------------------------
 * File :         GenericSentinelLinkedList.cpp
 * Project :      CPP
 * Author :       Saurish Phatak 
 * 
 * 
 * Description : Generic Sentinel Linked List
 * --------------------------------------------------------------------------------
 * 
 * Revision History : 
 * 2020-August-12	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

using namespace std;

// Node represents a value in the List
template <class V>
struct Node
{
    // Points to the previous Node
    Node<V> *previous;

    // Holds the Node's value
    V value;

    // Points to the next Node
    Node<V> *next;

    // Constructor
    Node(V v)
    {
        previous = next = nullptr;
        (*this).value = v;
    }
};

// Represents the SentinelLinkedList
template <class V>
class SentinelLinkedList
{
    // Points to the Dummy Head
    Node<V> *head;

    // Points to the Dummy Tail
    Node<V> *tail;

public:
    // Constructor
    SentinelLinkedList()
    {
        // Create dummy Nodes
        // of default value of a type
        // (invokes the Default Constructor of a type
        // SWEET C++
        head = new Node<V>(V());
        tail = new Node<V>(V());

        // Point head and tail to each other
        head->next = tail;
        tail->previous = head;
    }

    // Method to add a Node in the Linked List
    void pushBack(V value)
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
        Node<V> *newNode;

        // If the allocation failed
        if (!(newNode = new Node<V>(value)))
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
    bool remove(V valueToRemove)
    {
        // Search for the value
        // Start from the head's next and not the head
        // as head itself points to a Dummy Node
        for (Node<V> *current = head->next; current != tail; current = current->next)
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
        for (Node<V> *current = head->next; current != tail; current = current->next)
        {
            // Print the current Node's value
            cout << current->value;

            if (current->next != tail)
                cout << " <=> ";
        }

        cout << endl;
    }

    // Method to clear the entire List
    int clear()
    {
        int counter = 0;

        // If the List exists
        if (head->next != tail)
        {
            // Start from the head and keep on deleting
            // the Nodes until we reach the tail
            while (head->next != tail)
            {
                // Shift the head forward
                head->next = head->next->next;

                // Delete head->next's previous and
                // point it to head
                delete head->next->previous;
                head->next->previous = head;
                counter++;
            }
        }

        return counter;
    }
};

int main()
{
    // Create a new Sentinel List
    SentinelLinkedList<string> list;

    // Add some values to the list
    string value;
    while (cout << "Enter value to add (0 to stop) : ",
           cin >> value,
           value != "n")
    {
        list.pushBack(value);
        list.printForward();
    }

    while (cout << "Enter value to remove (0 to stop) : ",
           cin >> value,
           value != "n")
    {
        list.remove(value);
        list.printForward();
    }

    cout << list.clear() << endl;
    list.printForward();

    return 0;
}