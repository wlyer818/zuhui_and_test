#include <iostream>
#include <string>

struct Node {
    Node(std::string name) : m_name(name) {}
    std::string m_name;
    Node* next = nullptr;
    Node* pre = nullptr;
};

// ================== 前向声明 ==================
class Mylist;
class Iterator;
class ForwardIterator;
class ReverseIterator;

// ================== 1. 迭代器基类（纯声明） ==================
class Iterator {
public:
    Iterator(Mylist* ptr);
    virtual ~Iterator();
    Node* current();
    virtual Node* first() = 0;
    virtual Node* next() = 0;
    virtual bool isDone() = 0;
protected:
    Mylist* m_list = nullptr;
    Node* m_current = nullptr;
};

// ================== 2. 具体迭代器类（纯声明） ==================
class ForwardIterator : public Iterator {
public:
    ForwardIterator(Mylist* ptr);
    Node* first() override;
    Node* next() override;
    bool isDone() override;
};

class ReverseIterator : public Iterator {
public:
    ReverseIterator(Mylist* ptr);
    Node* first() override;
    Node* next() override;
    bool isDone() override;
};

// ================== 3. 容器类（完整定义） ==================
class Mylist {
public:
    Mylist() = default;
    ~Mylist();  // 析构函数声明
    
    int getCount() { return m_count; }
    Node* head() { return m_head; }
    Node* tail() { return m_tail; }
    
    Node* pushFront(std::string data);
    Node* pushBack(std::string data);
    Node* insert(Node* item, std::string data);
    
    Iterator* getIterator(bool isreverse = false);

protected:
    int m_count = 0;
    Node* m_head = nullptr;
    Node* m_tail = nullptr;
};

// ================== 4. 所有函数实现（放在最后） ==================

// Iterator 基类实现
Iterator::Iterator(Mylist* ptr) : m_list(ptr) {}
Iterator::~Iterator() {}
Node* Iterator::current() { return m_current; }

// ForwardIterator 实现
ForwardIterator::ForwardIterator(Mylist* ptr) : Iterator(ptr) {}

Node* ForwardIterator::first() {
    m_current = m_list->head();
    return m_current;
}

Node* ForwardIterator::next() {
    m_current = m_current->next;
    return m_current;
}

bool ForwardIterator::isDone() {
    return m_current == m_list->tail()->next;
}

// ReverseIterator 实现
ReverseIterator::ReverseIterator(Mylist* ptr) : Iterator(ptr) {}

Node* ReverseIterator::first() {
    m_current = m_list->tail();
    return m_current;
}

Node* ReverseIterator::next() {
    m_current = m_current->pre;
    return m_current;
}

bool ReverseIterator::isDone() {
    return m_current == m_list->head()->pre;
}

// Mylist 实现
Mylist::~Mylist() {
    // 清理链表内存...
    Node* current = m_head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

Node* Mylist::pushFront(std::string data) {
    Node* node = new Node(data);
    if (m_head == nullptr) {
        m_head = m_tail = node;
    } else {
        node->next = m_head;
        m_head->pre = node;
        m_head = node;
    }
    m_count++;
    return node;
}

Node* Mylist::pushBack(std::string data) {
    Node* node = new Node(data);
    if (m_tail == nullptr) {
        m_head = m_tail = node;
    } else {
        m_tail->next = node;
        node->pre = m_tail;
        m_tail = node;
    }
    m_count++;
    return node;
}

Node* Mylist::insert(Node* item, std::string data) {
    if (item == m_head) return pushBack(data);
    if (item == m_tail) return pushBack(data);
    
    Node* node = new Node(data);
    node->next = item->next;
    item->next->pre = node;
    item->next = node;
    node->pre = item;
    m_count++;
    return node;
}

Iterator* Mylist::getIterator(bool isreverse) {
    if (isreverse)
        return new ReverseIterator(this);
    else 
        return new ForwardIterator(this);
}

// ================== 5. main 函数 ==================
int main() {
    Mylist* list = new Mylist;
    list->pushBack("jin");
    Node* now = list->pushFront("kaiduo");
    list->insert(now, "jack");
    
    std::cout << "正向遍历：" << std::endl;
    Iterator* it = list->getIterator(false);
    for (auto begin = it->first(); !it->isDone(); it->next()) {
        std::cout << " " << it->current()->m_name << std::endl;
    }
    delete it;
    
    std::cout << "反向遍历：" << std::endl;
    it = list->getIterator(true);
    for (auto begin = it->first(); !it->isDone(); it->next()) {
        std::cout << " " << it->current()->m_name << std::endl;
    }
    delete it;
    
    delete list;
    return 0;
}