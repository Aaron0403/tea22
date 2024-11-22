#include <fmt/format.h>
#include <iostream>

// Definition des ListNode_t
typedef struct ListNode {
    unsigned int data;
    struct ListNode* pNext;
} ListNode_t;

// Definition der List_t
typedef struct List {
    ListNode_t* pHead;
    ListNode_t* pTail;
    unsigned int size;
} List_t;

// Funktion: Liste erstellen
List_t* createList() {
    List_t* list = new List_t;
    list->pHead = nullptr;
    list->pTail = nullptr;
    list->size = 0;
    return list;
}

// Funktion: Neuen Knoten erstellen
ListNode_t* createNode(unsigned int data) {
    ListNode_t* node = new ListNode_t;
    node->data = data;
    node->pNext = nullptr;
    return node;
}

// Funktion: Element an beliebiger Position einfügen
void insertToList(List_t* list, unsigned int data, unsigned int position) {
    ListNode_t* newNode = createNode(data);

    if (position == 0 || list->pHead == nullptr) { // Am Anfang einfügen
        newNode->pNext = list->pHead;
        list->pHead = newNode;
        if (list->size == 0) {
            list->pTail = newNode;
        }
    } else if (position >= list->size) { // Am Ende einfügen
        list->pTail->pNext = newNode;
        list->pTail = newNode;
    } else { // In der Mitte einfügen
        ListNode_t* current = list->pHead;
        for (unsigned int i = 0; i < position - 1; ++i) {
            current = current->pNext;
        }
        newNode->pNext = current->pNext;
        current->pNext = newNode;
    }
    list->size++;
}

// Funktion: Element mit bestimmtem Wert löschen
bool deleteFromList(List_t* list, unsigned int data) {
    if (list->pHead == nullptr) {
        return false; // Liste ist leer
    }

    ListNode_t* current = list->pHead;
    ListNode_t* previous = nullptr;

    while (current != nullptr) {
        if (current->data == data) {
            if (previous == nullptr) { // Zu löschendes Element ist am Anfang
                list->pHead = current->pNext;
                if (list->pHead == nullptr) {
                    list->pTail = nullptr; // Liste ist jetzt leer
                }
            } else {
                previous->pNext = current->pNext;
                if (current->pNext == nullptr) {
                    list->pTail = previous; // Zu löschendes Element ist am Ende
                }
            }
            delete current;
            list->size--;
            return true; // Erfolgreich gelöscht
        }
        previous = current;
        current = current->pNext;
    }
    return false; // Element nicht gefunden
}

// Funktion: Liste durchlaufen und Elemente ausgeben
void iterateList(const List_t* list) {
    ListNode_t* current = list->pHead;
    fmt::print("Liste (size={}): ", list->size);
    while (current != nullptr) {
        fmt::print("{} ", current->data);
        current = current->pNext;
    }
    fmt::print("\n");
}

// Funktion: Liste löschen
void deleteList(List_t* list) {
    ListNode_t* current = list->pHead;
    while (current != nullptr) {
        ListNode_t* toDelete = current;
        current = current->pNext;
        delete toDelete;
    }
    delete list;
}

auto main(int argc, char** argv) -> int {
    fmt::print("Hello, {}!\n", argv[0]);

    // Liste erstellen
    List_t* list = createList();

    // Elemente einfügen
    insertToList(list, 10, 0); // Einfügen am Anfang
    insertToList(list, 20, 1); // Einfügen am Ende
    insertToList(list, 15, 1); // Einfügen in der Mitte

    fmt::print("Nach Einfügen:\n");
    iterateList(list);

    // Element löschen
    deleteFromList(list, 15);
    fmt::print("Nach Löschen von 15:\n");
    iterateList(list);

    // Liste löschen
    deleteList(list);
    fmt::print("Liste gelöscht.\n");

    return 0;
}