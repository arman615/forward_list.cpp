#include <iostream>

template<class T>
class List {
public:
    List();

    ~List();

    void push_front(T data);

    void pop_front();

    void clear();

    void insert(T data, int index);

    void removeAt(int index);

    int getSize();

    bool empty();

    T &operator[](const int);

private:
    class Node {
    public:
        Node *pNext;
        T data;

        Node(T data = T(), Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }

        ~Node() { delete pNext; }

    };

    Node *head;
    int size;
};

template<class T>
List<T>::List() {
    head = nullptr;
    size = 0;
}

template<class T>
List<T>::~List() {
    clear();
}

template<class T>
void List<T>::push_front(T data) {
    head = new Node(data, head);
    ++size;
}

template<class T>
void List<T>::pop_front() {
    if (head != nullptr) {
        Node *temp = head;
        head = head->pNext;
        delete temp;
        --size;
    }
}

template<class T>
void List<T>::clear() {
    while (size) {
        pop_front();
    }
}

template<class T>
void List<T>::insert(T data, int index) {
    if (index <= 0) {
        push_front(data);
    } else if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    } else {
        Node *previous = head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
        Node *newdata = new Node(data, previous->pNext);
        previous->pNext = newdata;
        ++size;
    }
}

template<class T>
void List<T>::removeAt(int index) {
    if (index <= 0) {
        pop_front();
    } else if (index >= size - 1) {
        throw std::out_of_range("Index out of bounds");
    } else {
        Node *previous = head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
        Node *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        --size;
    }
}

template<class T>
int List<T>::getSize() {
    return size;
}

template<class T>
bool List<T>::empty() {
    return (size != 0);
}

template<class T>
T &List<T>::operator[](const int index) {
    int counter = 0;
    Node *current = head;
    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
    throw std::out_of_range("Index out of bounds");
}

int main() {
    List<int> lst;

    lst.push_front(5);
    lst.push_front(10);
    lst.push_front(3);
    lst.insert(7, 2);

    std::cout << "Elements in the list: ";
    for (int i = 0; i < lst.getSize(); ++i) {
        std::cout << lst[i] << " ";
    }
    std::cout << std::endl;

    lst.pop_front();
    lst.removeAt(1);

    std::cout << "Final elements in the list: ";
    for (int i = 0; i < lst.getSize(); ++i) {
        std::cout << lst[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
