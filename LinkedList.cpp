#include "LinkedList.hpp"

LinkedList::LinkedList()
    : Ship("LinkedList", 4, 300, 100, 500, 'L'),
      head(nullptr) {
    setSet();
    populateList();
}

LinkedList::~LinkedList() {
    deleteList();
}

void LinkedList::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);
    }
}

void LinkedList::populateList() {
    for (int i = 0; i < set.getSize(); ++i) {
        insert(set.getElement(i));
    }
}

void LinkedList::deleteList() {
    ListNode* current = head;
    while (current) {
        ListNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
}

void LinkedList::insert(int key) {
    ListNode* newNode = new ListNode(key);
    newNode->next = head;
    head = newNode;
}

int LinkedList::search(int key) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    ListNode* current = head;

    while (current != nullptr) {
        ++lastIterations;
        if (key == current->key) {
            foundLastValue = true;
            break;
        }
        current = current->next;
    }

    auto stop = high_resolution_clock::now();
    lastSearchTime = duration<double, std::milli>(stop - start).count();

    return lastIterations;
}

int LinkedList::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target);
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}
