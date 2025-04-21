#pragma once
#include "Ship.hpp"


using namespace std;
using namespace std::chrono;

struct ListNode {
    int key;
    ListNode* next;

    ListNode(int val) : key(val), next(nullptr) {}
};

class LinkedList : public Ship {
private:
    ListNode* head;

public:
    LinkedList();
    ~LinkedList();

    void setSet();
    void populateList();
    void deleteList();
    void insert(int key);
    int search(int key);
    int getPower() override;
};
