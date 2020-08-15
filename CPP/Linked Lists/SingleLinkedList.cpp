/*
 * --------------------------------------------------------------------------------
 * File :         SingleLinkedList.cpp
 * Project :      CPP
 * Author :       Saurish Phatak
 *
 *
 * Description : Single Linked List in C++
 * --------------------------------------------------------------------------------
 *
 * Revision History :
 * 2020-August-12	[SP] : Added clear() and main()
 * 2020-August-01	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;

// Node represents a value in the Link List
struct Node
{
    // Holds the value of the Node
    int value;

    // Points to the next Node
    Node *next;

    // Constructor
    Node(int v)
    {
        this->value = v;
        this->next = nullptr;
    }
};

// Represents a Single Linked List
class SingleLinkedList
{
    // Points to the Head of a List
    Node *head;

    // Points to the Tail of a List
    Node *tail;

public:
    // Constructor
    SingleLinkedList()
    {
        // Head and Tail are nullptr as the List is initially empty
        this->head = this->tail = nullptr;
    }

    // Method to add a Node in the List at the Back
    void pushBack(int value)
    {
        // Holds the newNode
        Node *newNode;

        // Create a new Node
        if (nullptr == (newNode = new Node(value)))
        {
            // Allocation failed
            return;
        }

        // Check if the Head is nullptr
        if (!head)
        {
            // This is the FIRST Node in the List
            // Point the Head to it
            this->head = newNode;
        }

        // Else, the List already has Nodes in it
        else
        {
            // Point the tail's next to the newNode
            // This creates a link between the old tail
            // and the newNode (new tail)
            tail->next = newNode;
        }

        tail = newNode;
    }

    // Method to remove a Node from the List
    bool remove(int valueToRemove)
    {
        // Search for the value in the List
        for (Node *current = head, *previous = head; current; current = current->next)
        {
            // Value found!
            if (current->value == valueToRemove)
            {
                // If this is the ONLY Node in the List
                if (head == current && tail == current)
                {
                    // Delete the head
                    delete head;

                    // Set head and tail to nullptr
                    head = tail = nullptr;
                    return true;
                }

                // If this value is actually the head
                if (head == current)
                {
                    // Point the head to head's next
                    head = head->next;

                    // Delete the current Node
                    delete current;
                    return true;
                }

                // If the value is actually the tail
                if (current == tail)
                {
                    // Point tail to previous
                    tail = previous;

                    // Make tail's next as nullptr
                    tail->next = nullptr;

                    // Delete the current Node
                    delete current;
                    return true;
                }

                // If the value is in the middle of the List
                // Point the previous's next to current's next
                previous->next = current->next;

                // Delete the current Node
                delete current;
                return true;
            }

            // Point previous to current for the next iteration
            previous = current;
        }

        // Value not found
        return false;
    }

    // Method to print a List in the forward direction
    void printForward()
    {
        // Start from the Head and go upto the Tail
        for (Node *current = head; current; current = current->next)
        {
            // Print the current Node's value
            cout << current->value << " ";
        }
        cout << endl;
    }

    // Clears the entire List
    int clear()
    {
        int counter = 0;

        // If the List exists
        if (head && tail)
        {
            // Start from the head and keep on deleting the Nodes
            // until we reach the tail
            for (auto current = head; current != tail; current = head)
            {
                // Shift the head forward
                head = head->next;

                // Delete current
                delete current;

                counter++;
            }

            delete head;
            counter++;
            head = tail = nullptr;
        }

        return counter;
    }
};

int main()
{
    // Create a new Single Linked List
    SingleLinkedList list;

    list.pushBack(5);
    list.pushBack(7);
    list.pushBack(1);

    list.printForward();

    cout << list.clear() << endl;
    list.printForward();

    list.remove(5);
    list.printForward();

    list.remove(1);
    list.printForward();

    list.remove(7);
    list.printForward();

    list.clear();

    return 0;
}
