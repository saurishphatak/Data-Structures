/*
 * --------------------------------------------------------------------------------
 * File :         GenericDoubleLinkedList.cpp
 * Project :      CPP
 * Author :       Saurish Phatak 
 * 
 * 
 * Description : Generic Double Linked List in C++
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

    // Holds the value of the Node
    V value;

    // Points to the next Node
    Node<V> *next;

    // Constructor
    Node(V v)
    {
        // Initially the previous and next
        // don't point to anything
        this->previous = nullptr;
        this->value = v;
        this->next = nullptr;
    }
};
// Represents a Double Linked List
template <class V>
class DoubleLinkedList
{
    // Points to the Head
    Node<V> *head;

    // Points to the Tail
    Node<V> *tail;

public:
    // Default Constructor
    DoubleLinkedList()
    {
        // Head and Tail are initially nullptr
        // as the List is empty
        head = tail = nullptr;
    }

    // Method to add a Node at the Back of the List
    void pushBack(V value)
    {
        // Holds the new Node
        Node<V> *newNode;

        // Allocate memory for the new Node
        if (nullptr == (newNode = new Node<V>(value)))
            return;

        // If this is the First Node in the List
        if (head == nullptr && tail == nullptr)
        {
            // Make the head point to the newNode
            head = newNode;
        }

        // If the List already contains Nodes
        else
        {
            // Point the newNode's previous to tail's previous
            newNode->previous = tail;

            // Connect newNode's previous Node to newNode
            newNode->previous->next = newNode;
        }

        // Point the tail to newNode
        tail = newNode;
    }

    // Method to remove a Node from the List
    bool remove(V value)
    {
        // Search for the value
        for (Node<V> *current = head; current; current = current->next)
        {
            // Value found!
            if (current->value == value)
            {
                // If this is the Only Node in List
                if (head == current && tail == current)
                {
                    // Delete the current Node
                    // set head and tail to nullptr
                    delete current;
                    head = nullptr;
                    tail = nullptr;
                    return true;
                }

                // If the value is at the tail
                if (current == tail)
                {
                    // Make the tail point to current's previous
                    tail = current->previous;

                    // Set tail's next to nullptr
                    tail->next = nullptr;

                    // Delete the current Node
                    delete current;
                    return true;
                }

                // If the value is at the head
                if (current == head)
                {
                    // Make the head point to current's next
                    head = current->next;

                    // Set the head's previous to nullptr
                    head->previous = nullptr;

                    // Delete the current Node
                    delete current;
                    return true;
                }

                // The value is in the middle
                // Point the current's previous Node to it's next
                current->previous->next = current->next;

                // Point the current's next Node to it's previous
                current->next->previous = current->previous;
                return true;
            }
        }

        // Value not in the List
        return false;
    }

    // Method to print the List in Forward Direction
    void printForward()
    {
        // Start from the head and go upto tail
        for (Node<V> *current = head; current; current = current->next)
        {
            // Print the current Node's value
            cout << current->value << " ";

            if (current->next)
                cout << " <=> ";
        }
        cout << endl;
    }

    // Method to clear the entire List
    int clear()
    {
        int counter = 0;

        // If the List is not empty
        if (head && tail)
        {
            // Start from the head and keep on deleting Nodes
            // till we reach the tail
            while (head != tail)
            {
                // Move the head forward
                head = head->next;

                // Delete head's previous
                // and set it to null
                delete head->previous;
                head->previous = nullptr;
                counter++;
            }

            // Delete head
            delete head;
            head = tail = nullptr;
            counter++;
        }

        return counter;
    }
};

int main()
{
    // Create a new Double Linked List
    DoubleLinkedList<string> list;

    // Add some values to the List
    string value;
    while (cout << "Enter value to add to the List (0 to stop) : ",
           cin >> value,
           value != "NULL")
    {
        list.pushBack(value);
        list.printForward();
    }

    cout << list.clear() << endl;
    list.printForward();

    return 0;
}