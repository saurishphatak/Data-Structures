/*
 * --------------------------------------------------------------------------------
 * File :         SingleLinkedList.js
 * Project :      DS
 * Author :       Saurish Phatak 
 * 
 * 
 * Description : Single Linked List in JavaScript
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

// Represents a value in the Linked List
class ListNode {
    constructor(value) {
        this.value = value;
        this.next = null;
    }
}

// Represents the Linked List
class SingleLinkedList {

    #head;
    #tail;

    constructor() {
        // head and tail point to the first 
        // and last nodes respectively in the list
        this.#head = this.#tail = null;
    }

    // Adds a value to the back of the List
    pushBack(value) {
        // Create a new Node
        let newNode = new ListNode(value);

        // Add the newNode in the List
        // If the head and tail are null
        if (!this.#head && !this.#tail) {
            // Then this is the first node in the List
            this.#head = newNode;
        }

        // There are already nodes in the list
        // Just add newNode to the back of the list
        else
            this.#tail.next = newNode;

        this.#tail = newNode;
    }

    // Removes a value from the List
    remove(value) {
        // Search for the value in the List
        for (let current = this.#head, previous = current; current; current = current.next) {
            // If value found
            if (value == current.value) {
                // If this is the ONLY Node in the List
                if (this.#head.value == this.#tail.value) {
                    // Set head and tail to null
                    this.#head = this.#tail = null;

                    return true;
                }

                // If this value is the tail
                if (current == this.#tail) {
                    // Point tail to previous and set its next to null
                    this.#tail = previous;
                    this.#tail.next = null;

                    return true;
                }

                // If this value is the head
                if (current == this.#head) {
                    // Make the head jump ahead
                    this.#head = this.#head.next;

                    // Set current.next to null
                    current.next = null;

                    return true;
                }

                // If this node is in the middle of the Linked List
                // Set previous.next to current.next
                previous.next = current.next;
                return true;
            }

            // Else make previous as current
            previous = current;
        }

        // Value not found 
        return false;
    }

    // Prints the List forward
    printForward() {
        let output = "";

        for (let current = this.#head; current; current = current.next) {
            output += (current.value);

            if (current.next)
                output += " -> ";
        }

        console.log(output);
    }

    // Remove all the values
    removeAll() {
        // Start from the head and keep on deleting the values till tail
        // is not reached
        for (let current = this.#head; current != this.#tail; current = this.#head) {
            this.#head = this.#head.next;
            current.next = null;
        }

        // Finally set head and tail to null
        this.#head = this.#tail = null;
    }
}

// Create a new List
let list = new SingleLinkedList();

list.pushBack(5);
list.pushBack(7);
list.pushBack(1);

list.printForward();

list.remove(5);
list.printForward();

list.removeAll();
list.printForward();

console.log("Done");