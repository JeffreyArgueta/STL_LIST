#ifndef LIST_H
#define LIST_H

#include <cstddef>

template<typename Tp>
class list {
    private:
        template<typename Tp_n>
        class Node {
            private:
                Tp value;
                Node<Tp_n>* next;
                Node<Tp_n>* prev;
            public:
                Node(const Tp_n& v, Node* n = nullptr, Node* p = nullptr) {
                    this->value = v;
                    this->next = n;
                    this->prev = p;
                }
                friend class list;
        };
        template<typename Tp_i>
        class Iterator {
            private:
                Node<Tp_i>* node;
            public:
                using pointer       = Tp_i*;
                using reference     = Tp_i&;
                
                Iterator(Node<Tp_i>* n = nullptr) { this->node = n; }

                reference operator*() const { return this->node->value; }
                pointer operator->() { return &this->node->value; }

                Iterator& operator++() {
                    if (this->node != nullptr) { this->node = this->node->next; }
                    return *this;
                }
                Iterator& operator--() {
                    if (this->node != nullptr) { this->node = this->node->prev; }
                    return *this;
                }
                bool operator==(const Iterator& other) const { return (this->node == other.node); }
                bool operator!=(const Iterator& other) const { return (this->node != other.node); }
                friend class list;
        };
        Node<Tp>* first;
        Node<Tp>* last;
        std::size_t size;
    public:
        using iterator  = Iterator<Tp>;
        using node      = Node<Tp>*;

        list() {
            this->first = nullptr;
            this->last = nullptr;
            this->size = 0;
        }
        ~list() { this->clear(); }
        void push_front(Tp pfv) {
            node n = new Node<Tp>(pfv);
            if (this->empty()) { this->first = this->last = n; }
            else {
                n->next = this->first;
                this->first->prev = n;
                this->first = n;
            }
            this->size++;
        }
        void push_back(Tp pbv) {
            node n = new Node<Tp>(pbv);
            if (this->empty()) { this->first = this->last = n; }
            else {
                this->last->next = n;
                n->prev = this->last;
                this->last = n;
            }
            this->size++;
        }
        void pop_front() { this->erase(iterator(this->first)); }
        void pop_back() { this->erase(iterator(this->last)); }
        void erase(iterator pos) {
            if (!this->empty()) {
                node nd = pos.node;
                if (this->front() == this->back()) { this->first = this->last = nullptr; }
                else {
                    if (nd->prev) { nd->prev->next = nd->next; }
                    else { this->first = nd->next; }

                    if (nd->next) { nd->next->prev = nd->prev; }
                    else { this->last = nd->prev; }
                }
                delete nd;
                this->size--;
            }
        }
        bool empty() { return (this->first == nullptr); }
        void clear() { while (!empty()) { this->pop_front(); } }
        std::size_t getSize() { return this->size; }
        
        iterator begin() { return iterator(this->front()); }
        iterator end() { return iterator(this->back()->next); }

        node front() {
            if (this->empty()) { return nullptr; }
            return this->first;
        }
        node back() {
            if (this->empty()) { return nullptr; }
            return this->last;
        }
};

#endif // !LIST_H
