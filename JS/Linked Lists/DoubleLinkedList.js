/*
 * --------------------------------------------------------------------------------
 * File :         DoubleLinkedList.js
 * Project :      DS
 * Author :       Saurish Phatak
 *
 *
 * Description : Double Linked List in JavaScript
 * --------------------------------------------------------------------------------
 *
 * Revision History :
 * 2020-August-01	[SP] : Created
 * --------------------------------------------------------------------------------
 * Copyright (c) 2020 Saurish Phatak
 *
 * License :
 *
 *    This code is meant for learning.
 *    Do NOT Copy Paste it as it may not help in understanding the code.
 *    Understand and type it yourself.
 *
 * DISCLAIMER :
 *    This code may contain unintentional and intentional bugs.
 *    There are no guarantees of this code working properly.
 * --------------------------------------------------------------------------------
 */

// Represents a value in the Double Linked List
function ListNode(value) {
    // Holds the value of the Node
    this.value = value;

    // Pointers to the next and previous nodes in the List
    this.previous = this.next = null;
}

// Represents a Double Linked List
class DoubleLinkedList {
    // Pointers to the head and tail of the List
    #head;
    #tail;

    constructor() {
        // Initially the List is empty
        this.#head = this.#tail = null;
    }

    // Adds a value to the back of the List
    pushBack(value) {
        // Create a new Node
        let newNode = new ListNode(value);

        // If the head and tail are empty
        if (!this.#head && !this.#tail)
            // This is the first Node in the List
            this.#head = newNode;

        // There are already values in the List
        // Add the newNode at the tail
        else {
            // Link the tail and the newNode with each other
            this.#tail.next = newNode;
            newNode.previous = this.#tail;
        }

        // Point the tail to newNode
        this.#tail = newNode;
    }

    // Removes value from the List
    remove(value) {
        // Search for the value in the List
        for (let current = this.#head; current; current = current.next) {
            // Value found
            if (value == current.value) {
                // If this is the ONLY value in the List
                if (this.#head == this.#tail) {
                    // Set head and tail to null
                    this.#head = this.#tail = null;

                    return true;
                }

                // If this value is at the tail
                if (current == this.#tail) {
                    // Set tail to its previous and make its next hull
                    this.#tail = this.#tail.previous;
                    this.#tail.next = null;

                    return true;
                }

                // If this value is at the head
                if (current == this.#head) {
                    // Make the head jump ahead
                    this.#head = this.#head.next;

                    // Disconnect current entirely from the List
                    this.#head.previous = null;
                    current.next = null;

                    return true;
                }

                // The value is in the middle of the List
                // Make the current's surrounding nodes 
                // point to each other
                current.next.previous = current.previous;
                current.previous.next = current.next;

                return true;
            }
        }

        // Value not found
        return false;
    }

    // Print the List forward
    printForward() {
        let output = "";
        for (let current = this.#head; current; current = current.next) {
            output += current.value;

            if (current.next)
                output += " <-> ";
        }

        console.log(output);
    }

    // Print the List backward
    printBackward() {
        let output = "";
        for (let current = this.#tail; current; current = current.previous) {
            output += current.value;

            if (current.previous)
                output += " <-> ";
        }

        console.log(output);
    }

    // Clear the List
    removeAll() {
        // Start from the head and delete each node upto tail
        while (this.#head != this.#tail) {
            // Move the head forward and disconnect it from 
            // the previous node
            this.#head = this.#head.next;
            this.#head.previous.next = null;
            this.#head.previous = null;
        }

        // Set head and tail to null
        this.#head = this.#tail = null;
    }
}

// Create a new List
let list = new DoubleLinkedList();

list.pushBack(5);
list.pushBack(7);
list.pushBack(1);

list.printForward();

list.remove(5);
list.printBackward();


list.remove(7);
list.printForward();


console.log("Done");