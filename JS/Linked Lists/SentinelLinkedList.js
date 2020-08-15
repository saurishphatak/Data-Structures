/*
 * --------------------------------------------------------------------------------
 * File :         SentinelLinkedList.js
 * Project :      JS
 * Author :       Saurish Phatak
 *
 *
 * Description : Sentinel Linked List in JavaScript
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

// Represents a value in the List
class ListNode {
    constructor(value) {
        this.value = value;
        this.previous = this.next = null;
    }
}

// Represents a Sentinel Linked List
class SentinelLinkedList {
    // Point to the head and tail dummy nodes
    #head;
    #tail;

    constructor() {
        // Create dummy head and tail nodes
        this.#head = { previous: null, value: undefined, next: null };
        this.#tail = { previous: null, value: undefined, next: null };

        // Initially head and tail point to each other
        this.#head.next = this.#tail;
        this.#tail.previous = this.#head;
    }

    // Adds a Node to the back of the List
    pushBack(value) {
        // Create a newNode
        let newNode = new ListNode(value);

        // Think of the List as a wall
        // Make the newNode climb up the wall
        newNode.next = this.#tail;
        newNode.previous = this.#tail.previous;

        // Now pull the newNode up the wall
        this.#tail.previous.next = newNode;
        this.#tail.previous = newNode;
    }

    // Removes a value from the List
    remove(value) {

        // Search for the value
        for (let current = this.#head.next; current != this.#tail; current = current.next) {
            // Value found
            if (value == current.value) {
                // Disconnect current Node from the List
                current.previous.next = current.next;
                current.next.previous = current.previous;

                return true;
            }
        }

        // Value not found in the List
        return false;
    }

    // Prints the List forward
    printForward() {
        let output = "";

        for (let current = this.#head.next; current != this.#tail; current = current.next) {
            output += current.value;

            if (current.next != this.#tail)
                output += "<->";
        }

        console.log(output);
    }

    // Prints the List backward
    printBackward() {
        let output = " ";

        for (let current = this.#tail.previous; current != this.#head; current = current[previous]) {
            output += current[value];

            if (current[previous] != this.#head)
                output += "<->";
        }

        console.log(output);
    }

    // Removes all the values from the List
    removeAll() {
        // Start from head.next and keep on disconnecting
        // Nodes from the List until tail is reached
        while (this.#head.next != this.#tail) {
            // Make head.next point to head.next.next
            this.#head.next = this.#head.next.next;

            // Disconnect the previous Node from the List
            this.#head.next.previous.next = null;
            this.#head.next.previous = null;
        }
    }
}

// Create a Sentinel Linked List
let list = new SentinelLinkedList();

list.pushBack(5);
list.pushBack(7);
list.pushBack(1);

list.printForward();

list.removeAll();
list.printForward();

list.remove(7);
list.printForward();

list.remove(1);
list.printForward();

list.remove(5);
list.printForward();
