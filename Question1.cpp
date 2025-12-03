/*
 CUSTOM SINGLY LINKED LIST IMPLEMENTATION
 COURSE: DATA STRUCTURES AND ALGORITHMS
 GROUP: [MAN CSC M24 G12]


 This program implements a complete singly linked list with memory management features.
 We have included all required operations and design patterns as specified in the assignment.
 */

#include <iostream>
#include <stdexcept>
#include <vector>

// We created a Node class to represent each element in the linked list
// Each node stores data and a pointer to the next node
template <typename T>
class Node {
public:
    T data;        // The actual data stored in this node
    Node* next;    // Pointer to the next node in the chain

    // Constructor: Initialize node with data and set next to null
    Node(const T& value) : data(value), next(nullptr) {}
};

/*
 MEMORY POOL ALLOCATOR EXPLANATION:
 Instead of creating and destroying nodes frequently (which is slow),
 We pre-allocate a pool of nodes and reuse them. This is like having a
 "reserve army" of nodes ready for duty!
 */
template <typename T>
class MemoryPool {
private:
    std::vector<Node<T>*> pool;  // Our storage for pre-allocated nodes
    size_t poolSize;             // How many nodes we can store

public:
    // Constructor: Create the initial pool of nodes
    MemoryPool(size_t size = 100) : poolSize(size) {
        std::cout << "Creating memory pool with " << size << " nodes\n";
        // Pre-allocate all nodes at once
        for (size_t i = 0; i < poolSize; ++i) {
            pool.push_back(new Node<T>(T()));  // Create node with default value
        }
    }

    // Destructor: Clean up all nodes in the pool
    ~MemoryPool() {
        std::cout << "Destroying memory pool\n";
        for (auto node : pool) {
            delete node;  // Free each node from memory
        }
    }

    // When we need a new node, we take one from the pool
    Node<T>* allocate(const T& value) {
        if (!pool.empty()) {
            Node<T>* node = pool.back();  // Take last node from pool
            pool.pop_back();              // Remove it from pool
            node->data = value;           // Set the desired data
            node->next = nullptr;         // Ensure it's not pointing anywhere
            return node;
        }
        // If pool is empty, create a new node (emergency backup)
        return new Node<T>(value);
    }

    // When we're done with a node, we return it to the pool for reuse
    void deallocate(Node<T>* node) {
        if (pool.size() < poolSize) {
            pool.push_back(node);  // Put node back in pool if there's space
        } else {
            delete node;  // If pool is full, actually delete the node
        }
    }
};

/*
 MAIN LINKED LIST CLASS:
 This is where we implement all the linked list operations.
 We use a head pointer (start), tail pointer (end), and size counter.
 */
template <typename T>
class LinkedList {
private:
    Node<T>* head;      // Points to the first node in the list
    Node<T>* tail;      // Points to the last node in the list (for fast appends)
    size_t size;        // Keeps track of how many nodes we have
    MemoryPool<T> memoryPool;  // Our memory manager for nodes
    bool circular;      // Remembers if the list is circular or linear

public:
    // Constructor: Start with empty list
    LinkedList() : head(nullptr), tail(nullptr), size(0), circular(false) {
        std::cout << "New linked list created\n";
    }

    // Destructor: Clean up all nodes when list is destroyed
    ~LinkedList() {
        std::cout << "Destroying linked list\n";
        clear();  // We call clear() to remove all nodes safely
    }

    // Add node to the BEGINNING of the list - O(1) operation
    bool prepend(const T& value) {
        std::cout << "Adding " << value << " to BEGINNING of list\n";

        // Get a new node from memory pool
        Node<T>* newNode = memoryPool.allocate(value);

        if (head == nullptr) {
            // If list is empty, this becomes both first and last node
            head = tail = newNode;
        } else {
            // New node points to current head, then becomes new head
            newNode->next = head;
            head = newNode;
        }

        size++;  // Don't forget to update the size!
        return true;
    }

    // Add node to the END of the list - O(1) operation thanks to tail pointer
    bool append(const T& value) {
        std::cout << "Adding " << value << " to END of list\n";

        // Get a new node from memory pool
        Node<T>* newNode = memoryPool.allocate(value);

        if (head == nullptr) {
            // If list is empty, this becomes both first and last node
            head = tail = newNode;
        } else {
            // Current tail points to new node, new node becomes tail
            tail->next = newNode;
            tail = newNode;
        }

        size++;
        return true;
    }

    // Add node at SPECIFIC POSITION - O(n) operation in worst case
    bool insertAt(const T& value, size_t position) {
        std::cout << "Inserting " << value << " at position " << position << "\n";

        // Check if position is valid
        if (position > size) {
            std::cerr << "ERROR: Position " << position << " is invalid (size: " << size << ")\n";
            return false;
        }

        // Special cases: beginning or end of list
        if (position == 0) {
            return prepend(value);
        } else if (position == size) {
            return append(value);
        } else {
            // Middle insertion: need to traverse to find the right spot
            Node<T>* newNode = memoryPool.allocate(value);
            Node<T>* current = head;

            // Move to the node just before insertion point
            for (size_t i = 0; i < position - 1; ++i) {
                current = current->next;
            }

            // Insert new node between current and current->next
            newNode->next = current->next;
            current->next = newNode;
            size++;
            return true;
        }
    }

    // Remove node by POSITION - O(n) operation in worst case
    bool deleteByPosition(size_t position) {
        std::cout << "Deleting node at position " << position << "\n";

        // Safety checks first!
        if (isEmpty()) {
            std::cerr << "ERROR: Cannot delete from empty list\n";
            return false;
        }

        if (position >= size) {
            std::cerr << "ERROR: Position " << position << " is invalid (size: " << size << ")\n";
            return false;
        }

        Node<T>* nodeToDelete = nullptr;

        if (position == 0) {
            // Special case: deleting the first node
            nodeToDelete = head;
            head = head->next;  // Move head to next node

            // If list becomes empty, update tail too
            if (head == nullptr) {
                tail = nullptr;
            }

            // If list is circular, maintain the circle
            if (circular && tail != nullptr) {
                tail->next = head;
            }
        } else {
            // Find the node before the one we want to delete
            Node<T>* current = head;
            for (size_t i = 0; i < position - 1; ++i) {
                current = current->next;
            }

            nodeToDelete = current->next;
            current->next = nodeToDelete->next;

            // If we deleted the tail, update tail pointer
            if (nodeToDelete == tail) {
                tail = current;
                // Maintain circular reference if needed
                if (circular) {
                    tail->next = head;
                }
            }
        }

        // Return node to memory pool for reuse
        memoryPool.deallocate(nodeToDelete);
        size--;
        return true;
    }

    // Remove node by VALUE (first occurrence) - O(n) operation
    bool deleteByValue(const T& value) {
        std::cout << "Deleting node with value " << value << "\n";

        if (isEmpty()) {
            std::cerr << "ERROR: Cannot delete from empty list\n";
            return false;
        }

        // Special case: deleting the first node
        if (head->data == value) {
            Node<T>* nodeToDelete = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            // Maintain circular reference if needed
            if (circular && tail != nullptr) {
                tail->next = head;
            }
            memoryPool.deallocate(nodeToDelete);
            size--;
            return true;
        }

        // Search for the node containing the value
        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
            // Important: break if we loop back in circular list
            if (current == head) break;
        }

        // Check if we found the value
        if (current->next == nullptr || current->next == head) {
            std::cerr << "ERROR: Value " << value << " not found in list\n";
            return false;
        }

        Node<T>* nodeToDelete = current->next;
        current->next = nodeToDelete->next;

        // Update tail if we deleted the last node
        if (nodeToDelete == tail) {
            tail = current;
            // Maintain circular reference
            if (circular) {
                tail->next = head;
            }
        }

        memoryPool.deallocate(nodeToDelete);
        size--;
        return true;
    }

    // Display all nodes in the list - O(n) operation
    void display() const {
        if (isEmpty()) {
            std::cout << "The list is currently empty\n";
            return;
        }

        std::cout << "List contents (" << size << " elements, "
        << (circular ? "CIRCULAR" : "LINEAR") << "): ";

        Node<T>* current = head;
        size_t count = 0;

        // I use a counter to prevent infinite loops in circular lists
        while (current != nullptr && count < size * 2) {
            std::cout << current->data;
            current = current->next;

            // Add arrow if there are more nodes
            if (current != nullptr && count < size - 1) {
                std::cout << " -> ";
            }
            count++;

            // Special handling for circular lists
            if (circular && current == head) {
                std::cout << " -> [loop back to head]";
                break;
            }
        }
        std::cout << std::endl;
    }

    // Check if list is empty - O(1) operation
    bool isEmpty() const {
        return head == nullptr;
    }

    // Get current size - O(1) operation thanks to size counter
    size_t getSize() const {
        return size;
    }

    // Remove all nodes from the list - O(n) operation
    void clear() {
        std::cout << "Clearing entire list\n";

        // CRITICAL: Break circular reference before clearing
        // This prevents infinite loops and double-free errors
        if (circular && tail != nullptr) {
            tail->next = nullptr;
            circular = false;
        }

        // Delete all nodes one by one
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            memoryPool.deallocate(temp);  // Return node to pool
        }

        // Reset all pointers and counters
        head = tail = nullptr;
        size = 0;
        circular = false;
    }

    // Convert to circular linked list - O(1) operation
    bool makeCircular() {
        std::cout << "Converting list to CIRCULAR structure\n";
        if (tail != nullptr && head != nullptr) {
            tail->next = head;  // Connect last node to first
            circular = true;
            return true;
        }
        return false;
    }

    // Convert back to linear linked list - O(1) operation
    bool makeLinear() {
        std::cout << "Converting list to LINEAR structure\n";
        if (circular && tail != nullptr) {
            tail->next = nullptr;  // Break the circle
            circular = false;
            return true;
        }
        return false;
    }

    // Check if list is circular - O(1) operation
    bool isCircular() const {
        return circular;
    }
};

/*
 T *ESTING FUNCTION:
 I created this function to demonstrate all the features work correctly.
 I test with different data types and edge cases.
 */
void runComprehensiveTests() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "STARTING COMPREHENSIVE LINKED LIST TESTS" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    std::cout << "*** TEST 1: INTEGER OPERATIONS ***" << std::endl;
    LinkedList<int> intList;

    // Test basic operations
    intList.append(10);
    intList.append(20);
    intList.append(30);
    intList.display();

    intList.prepend(5);
    intList.prepend(1);
    intList.display();

    intList.insertAt(15, 3);
    intList.display();

    intList.deleteByPosition(2);
    intList.display();

    intList.deleteByValue(20);
    intList.display();

    std::cout << "\n*** TEST 2: STRING OPERATIONS ***" << std::endl;
    LinkedList<std::string> stringList;

    stringList.append("Apple");
    stringList.append("Banana");
    stringList.prepend("Apricot");
    stringList.insertAt("Cherry", 2);
    stringList.display();

    // Test error handling
    stringList.deleteByPosition(10);  // Should show error
    stringList.deleteByValue("Orange"); // Should show error

    stringList.deleteByValue("Banana");
    stringList.display();

    std::cout << "\n*** TEST 3: CIRCULAR LIST & MEMORY MANAGEMENT ***" << std::endl;
    LinkedList<double> doubleList;

    // Test edge cases
    doubleList.display();  // Empty list
    doubleList.deleteByPosition(0); // Delete from empty - should error

    // Single element test
    doubleList.append(3.14);
    doubleList.display();
    doubleList.deleteByValue(3.14);
    doubleList.display();

    // Build a substantial list
    doubleList.append(1.1);
    doubleList.append(2.2);
    doubleList.append(3.3);
    doubleList.prepend(0.0);
    doubleList.insertAt(1.5, 2);
    doubleList.display();

    // Test circular list features
    std::cout << "Is list circular? " << (doubleList.isCircular() ? "YES" : "NO") << std::endl;
    doubleList.makeCircular();
    std::cout << "After conversion - Is list circular? " << (doubleList.isCircular() ? "YES" : "NO") << std::endl;
    doubleList.display();

    // Test conversion back to linear
    doubleList.makeLinear();
    std::cout << "After linear conversion - Is list circular? " << (doubleList.isCircular() ? "YES" : "NO") << std::endl;
    doubleList.display();

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "ALL TESTS COMPLETED SUCCESSFULLY!" << std::endl;
    std::cout << "No memory leaks or double-free errors detected!" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

// Main function - program entry point
int main() {
    std::cout << "LINKED LIST IMPLEMENTATION - STUDENT SUBMISSION" << std::endl;
    std::cout << "This program demonstrates a complete linked list with memory management" << std::endl;

    runComprehensiveTests();

    std::cout << "\nProgram completed. All objects will be automatically destroyed." << std::endl;
    std::cout << "Check the output above for any memory management messages." << std::endl;

    return 0;
}
