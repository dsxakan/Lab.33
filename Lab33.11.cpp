
#include <iostream>

template<typename X>
class List {
private:
    class Node {
    public:
        X data;
        Node* next;
    };

    Node* headList;
    Node* tailList;
    Node* currentList;

public:
    // Конструктор по умолчанию
    List() : headList(nullptr), tailList(nullptr), currentList(nullptr) {}

    // Конструктор копирования
    List(const List& other) {
        headList = nullptr;
        tailList = nullptr;
        currentList = nullptr;

        Node* temp = other.headList;
        while (temp != nullptr) {
            AddToLast(temp->data);
            temp = temp->next;
        }
    }

    // Оператор присвоения
    List<X>& operator=(const List& other) {
        if (this == &other) return *this;

        Clear();

        Node* temp = other.headList;
        while (temp != nullptr) {
            AddToLast(temp->data);
            temp = temp->next;
        }

        return *this;
    }

    // Деструктор
    ~List() {
        Clear();
    }

    // Добавление элемента в голову списка
    void AddToHead(const X& elem) {
        Node* newNode = new Node();
        newNode->data = elem;
        newNode->next = headList;

        if (headList == nullptr) tailList = newNode;

        headList = newNode;
    }

    // Добавление элемента в хвост списка
    void AddToLast(const X& elem) {
        Node* newNode = new Node();
        newNode->data = elem;
        newNode->next = nullptr;

        if (headList == nullptr) {
            headList = newNode;
            tailList = newNode;
            currentList = newNode;
        }
        else {
            tailList->next = newNode;
            tailList = newNode;
        }
    }

    // Добавление на текущую позицию
    void AddToCurrent(const X& elem) {
        if (currentList == nullptr) AddToLast(elem);
        else {
            Node* newNode = new Node();
            newNode->data = elem;

            if (currentList->next != nullptr) newNode->next = currentList->next;
            else {
                tailList = newNode;
                newNode->next = nullptr;
            }

            currentList->next = newNode;
        }
    }

    // Удаление "головы" (первый элемент) списка
    void DelHead() {
        if (headList != nullptr) {
            Node* temp = headList;
            headList = headList->next;
            if (currentList == temp) currentList = headList;
            delete temp;
        }
    }

    // Удаление "хвоста" (последний элемент) списка
    void DelLast() {
        if (headList == nullptr || headList == tailList) DelHead();
        else {
            Node* temp = headList;
            while (temp->next != tailList) temp = temp->next;

            delete tailList;
            tailList = temp;
            temp->next = nullptr;
            currentList = tailList;
        }
    }

    // Удаление текущего элемента
    void DelCurrent() {
        if (currentList == headList) DelHead();
        else if (currentList == tailList) DelLast();
        else if (currentList != nullptr) {
            Node* temp = headList;
            while (temp->next != currentList) temp = temp->next;

            temp->next = currentList->next;
            delete currentList;

            currentList = temp->next;
        }
    }

    // Удалить заданный элемент
    void Del(const X& elem) {
        Node* temp = headList;
        while (temp != nullptr) {
            if (temp->data == elem) {
                if (temp == headList) {
                    DelHead();
                    temp = headList;
                }
                else if (temp == tailList) {
                    DelLast();
                    temp = tailList;
                }
                else {
                    Node* prev = headList;
                    while (prev->next != temp) prev = prev->next;

                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                }
            }
            else temp = temp->next;
        }
    }

    // Удаление элемента на заданной позиции
    bool Del(long position) {
        if (position < 0 || position > GetSize() - 1) return false;

        if (position == 0) DelHead();
        else if (position == GetSize() - 1) DelLast();
        else {
            Node* temp = headList;
            for (long i = 0; i < position - 1; i++) temp = temp->next;

            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }

        return true;
    }

    // Сдвиг указателя current на следующий элемент
    bool next() {
        if (currentList != nullptr && currentList->next != nullptr) {
            currentList = currentList->next;
            return true;
        }

        return false;
    }

    // Сдвиг указателя current на первый элемент
    void toBegin() {
        currentList = headList;
    }

    // Сдвиг указателя current на последний элемент
    void toEnd() {
        currentList = tailList;
    }

    // Возвращает позицию найденного элемента
    long Find(const X& elem) {
        Node* temp = headList;
        long position = 0;
        while (temp != nullptr) {
            if (temp->data == elem) return position;
            temp = temp->next;
            position++;
        }
        return -1;
    }

    // Метод обращения к текущему элементу
    X& getElement() {
        return currentList->data;
    }

    // Метод проверяет список на пустоту
    bool isEmpty() {
        return headList == nullptr;
    }

    // Метод очищения списка
    void Clear() {
        while (headList != nullptr) {
            Node* temp = headList;
            headList = headList->next;
            delete temp;
        }
        tailList = nullptr;
        currentList = nullptr;
    }

    // Метод возвращает количество элементов в списке
    long GetSize() {
        long size = 0;
        Node* temp = headList;
        while (temp != nullptr) {
            size++;
            temp = temp->next;
        }
        return size;
    }

    // Вывод списка
    void PrintList() {
        Node* temp = headList;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Создание и использование объекта списка


    List<int> myList;

    // Добавление элементов в список
    myList.AddToLast(1);
    myList.AddToLast(2);
    myList.AddToHead(0);
    myList.AddToCurrent(3);
    myList.AddToLast(4);

    // Вывод списка
    myList.PrintList();

    // Перемещение к концу и удаление текущего элемента
    myList.toEnd();
    myList.DelCurrent();

    // Вывод списка после удаления
    myList.PrintList();

    // Удаление элемента со значением 1
    myList.Del(1);

    // Вывод списка после удаления
    myList.PrintList();

    // Очистка списка
    myList.Clear();

    // Вывод пустого списка
    myList.PrintList();

    return 0;
}
