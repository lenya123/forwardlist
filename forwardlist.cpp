#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class ForwardList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& value) : data(value), next(nullptr) {}
    };
    std::unique_ptr<Node> head;

public:
    ForwardList() : head(nullptr) {}

    void pushFront(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    void popFront() {
        if (empty()) {
            return;
        }
        head = std::move(head->next);
    }

    bool empty() const {
        return head == nullptr;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }
};

int main() {
    ForwardList<int> list;
    list.pushFront(5);
    list.pushFront(2);
    list.pushFront(3);
    std::cout << list.front() << std::endl;
    list.popFront();
    std::cout << list.front() << list.empty() << std::endl;
  
    return 0;
}
