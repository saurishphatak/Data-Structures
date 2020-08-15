/*
 * --------------------------------------------------------------------------------
 * File :         CircularSingleLinkedList.js
 * Project :      JS
 * Author :       Saurish Phatak
 *
 *
 * Description : Circular Single Linked List in JavaScript
 * --------------------------------------------------------------------------------
 *
 * Revision History :
 * 2020-August-02	[SP] : Created
 * --------------------------------------------------------------------------------
 * Copyright (c) 2020 Saurish Phatak
 *
 * License :
 *
 *    This code is meant for learning.
 *    Do NOT Copy Paste it as it may not help in understanding the code.
 *    You are required to understand and type it yourself.
 *
 * DISCLAIMER :
 *    This code may contain unintentional and intentional bugs.
 *    There are no guarantees of this code working properly.
 * --------------------------------------------------------------------------------
 */

// Represents a Node in the List
class ListNode {
    constructor(value) {
        // Points to the next Node
        // Initially null
        this.next = null;

        // Holds the value
        this.value = value;
    }
}

// Represents a Circular Single Linked List
class CircularSingleLinkedList {
    // Pointers to the head and tail of the Node
    #head;
    #tail;

    constructor() {
        // Initially head and tail are null
        this.#head = this.#tail = null;
    }

    // Adds a Node at the back of the List
    pushBack(value) {
        // Create a new Node
        let newNode = new ListNode(value);

        // If the head and tail are null
        // It means, the List is empty
        if (!this.#head && !this.#tail)
            this.#head = newNode;

        // Else, there are already Nodes in the List
        else {
            this.#tail.next = newNode;
        }

        // Point tail to newNode
        this.#tail = newNode;

        // This is what makes the List "Circular"
        this.#tail.next = this.#head;
    }

    // Removes a value from the List
    remove(value) {
        // If the list is not already empty
        if (this.#head) {
            let current = this.#head;
            let previous = this.#tail;

            // Search for the value in the List
            do {
                // Value found 
                if (value == current.value) {

                    // If this is the ONLY Node in the List
                    if (this.#head == this.#tail) {
                        // Set head and tail to null
                        // But first set tail.next to null
                        // as it could end up as a "Cyclic Reference"
                        this.#tail.next = null;
                        this.#head = this.#tail = null;

                        return true;
                    }

                    // If the value is at the tail
                    if (current == this.#tail) {

                        // Disconnet current Node from the List
                        // and make the tail go one Node back
                        previous.next = current.next;
                        this.#tail = previous;

                        return true;
                    }

                    // If this value is at the head
                    if (current == this.#head) {
                        // Make the head jump one Node ahead
                        this.#head = this.#head.next;

                        // Make the previous node's next point to head
                        previous.next = this.#head;

                        // Finally set current.next to null
                        current.next = null;

                        return true;
                    }

                    // The value is in the middle of the List
                    previous.next = current.next;

                    return true;
                }

                previous = current;
                current = current.next;

            } while (current != this.#head);
        }

        // Value not found in the List
        // of the List is empty
        return false;
    }

    // Prints the List forward
    printForward() {
        // Only if the list is not empty
        if (this.#head) {
            let current = this.#head;
            let output = "";
            do {
                output += current.value;

                if (current.next != this.#head)
                    output += " -> ";

                current = current.next;
            } while (current != this.#head);

            console.log(output);
        }
    }

    // Clears the List
    clear() {
        // If the list is not already empty
        if (this.#head) {
            // Start from the head and keep on shifting it ahead
            // until tail is reached
            let current = this.#head;

            do {
                this.#head = this.#head.next;
                current.next = null;

                current = this.#head;
            } while (this.#head != this.#tail);

            // Set tail's next to null
            // Else, the original head will not be GC collected
            this.#tail.next = null;

            // Now set tail and head to null
            this.#head = this.#tail = null;
        }
    }
}

// Make a new List
let list = new CircularSingleLinkedList();

list.pushBack(5);
list.pushBack(7);
list.pushBack(1);

list.printForward();

list.clear();
list.printForward();

list.remove(7);
list.printForward();

list.remove(5);
list.printForward();

list.remove(1);
list.printForward();