#include <iostream>
#include <string>
#include <limits>

using namespace std;

template <typename T>
class Collection {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    int elementCount;

    bool isPresent(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

public:
    Collection() : head(nullptr), elementCount(0) {}

    ~Collection() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void insertElement(const T& value) {
        if (!isPresent(value)) {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            ++elementCount;
            cout << value << " has been added to the collection." << endl;
        }
        else {
            cout << value << " is already in the collection." << endl;
        }
    }

    void removeElement(const T& value) {
        Node** current = &head;
        while (*current) {
            if ((*current)->data == value) {
                Node* toDelete = *current;
                *current = (*current)->next;
                delete toDelete;
                --elementCount;
                cout << value << " has been removed from the collection." << endl;
                return;
            }
            current = &((*current)->next);
        }
        cout << value << " was not found in the collection." << endl;
    }

    int size() const {
        return elementCount;
    }

    bool containsElement(const T& value) const {
        return isPresent(value);
    }

    void displayCollection() const {
        cout << "Items in the collection: [";
        Node* current = head;
        while (current) {
            cout << current->data;
            if (current->next) {
                cout << ", ";
            }
            current = current->next;
        }
        cout << "]" << endl;
    }

    bool operator==(const Collection& other) const {
        if (elementCount != other.elementCount) {
            return false;
        }

        Node* current = head;
        while (current) {
            if (!other.isPresent(current->data)) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    bool operator!=(const Collection& other) const {
        return !(*this == other);
    }
};

template <typename T>
void manage_collection() {
    Collection<T> collection;
    int option;
    T input;
        /* Add a new item to the set.If the item is already in the set then nothing happens.
         Remove an item from the set.
         Return the number of items in the set.
         Determine if an item is a member of the set.
         Return a pointer to a dynamically created array containing each item in the set.The caller of this
        function is responsible for de - allocating the memory.*/
    while (true) {
        cout << "Collection Operations Menu: " << endl;
        cout << "1. Add an item" << endl;
        cout << "2. Remove an item" << endl;
        cout << "3. Check  avability of an item " << endl;
        cout << "4. The number of items in the collection" << endl;
        cout << "5. All items in the collection" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> option)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (option) {
        case 1:
            cout << "Enter an item to add: ";
            while (!(cin >> input)) {
                cout << "Invalid input. Please enter a valid value: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            collection.insertElement(input);
            break;

        case 2:
            cout << "Enter an item to remove: ";
            while (!(cin >> input)) {
                cout << "Invalid input. Please enter a valid value: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            collection.removeElement(input);
            break;

        case 3:
            cout << "Enter an item to check: ";
            while (!(cin >> input)) {
                cout << "Invalid input. Please enter a valid value: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (collection.containsElement(input)) {
                cout << input << " is in the collection." << endl;
            }
            else {
                cout << input << " is not in the collection." << endl;
            }
            break;

        case 4:
            cout << "Number of items in the collection: " << collection.size() << endl;
            break;

        case 5:
            collection.displayCollection();
            break;

        case 6:
            cout << "Exiting..." << endl;
            return;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    int typeSelection;

    cout << "Choose the data type for the collection: " << endl;
    cout << "1. Integer" << endl;
    cout << "2. String" << endl;
    cout << "3. Double" << endl;
    cout << "Enter your choice: ";
    while (!(cin >> typeSelection)) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (typeSelection) {
    case 1:
        manage_collection<int>();
        break;
    case 2:
        manage_collection<string>();
        break;
    case 3:
        manage_collection<double>();
        break;
    default:
        cout << "Invalid choice. Exiting..." << endl;
        return 1;
    }

    return 0;
}
