#ifndef CS540_MAP_H
#define CS540_MAP_H

#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept> // out_of_range exception

#include <stdio.h>
#include <stdlib.h> // rand()

namespace cs540 {

    template <typename Key_T, typename Mapped_T>
    class Map {

        typedef std::pair<const Key_T, Mapped_T> ValueType;
        struct Node;
        struct DataNode;

        struct link_t {
            Node* prev;
            Node* next;
            link_t() : prev(nullptr), next(nullptr) {}
            link_t(Node* p, Node* n) : prev(p), next(n) {}
        }; // link_t

        // base node that does not contain data (sentinel node)
        struct Node {
            std::vector<link_t> links; // prev and next pointers at each level
 
            Node() { links.push_back(link_t()); initSentinel(0); }
            
            Node* getNext(int level) const {
                if(level < 0) return nullptr;

                assert((size_t)level < this->links.size());
                return this->links[level].next;
            }

            void setNext(Node* n, int level) {
                if(level < 0) return;

                assert((size_t)level < this->links.size());
                this->links[level].next = n;
            }  
 
            Node* getPrev(int level) const {
                if(level < 0) return nullptr;

                assert((size_t)level < this->links.size());
                return this->links[level].prev;
            }

            void setPrev(Node* n, int level) {
                if(level < 0) return;

                assert((size_t)level < this->links.size());
                this->links[level].prev = n;
            }  
           
            int getMaxLevel() const {
                return links.size()-1;
            }
 
            // insert n before this node
            void insertBefore(Node* n, int level) {
                if(level < 0) return;

                n->setPrev(this->getPrev(level), level);
                n->setNext(this, level);
                this->getPrev(level)->setNext(n, level);
                this->setPrev(n, level);
            }

            // insert into list in sorted order, starting from this node
            //std::pair<DataNode*, bool> insert(const ValueType& pair, int level, DataNode* node) {
            //    Node* ptr = this;
            //    DataNode* n = node;
            //    ptr = ptr->getNext(level); // point to first node (not the sentinel)

            //    while(ptr != this) {
            //        DataNode* d = dynamic_cast<DataNode*>(ptr);
            //        Key_T key = d->getKey();
            //        if(key == pair.first) { // key already exists
            //            //std::cout << "key=" << pair.first << " already exists" << std::endl;
            //            return std::make_pair(d, false); // false because nothing was inserted
            //        }

            //        if(pair.first < key) {
            //            if(!n) n = new DataNode(pair.first, pair.second);
            //            ptr->insertBefore(n, level); 
            //            return std::make_pair(n, true); // true because inserted
            //        }
            //       
            //        ptr = ptr->getNext(level);
            //    }
            //    
            //    // is greater than existing elements ; insert at the end of list 
            //    if(!n) n = new DataNode(pair.first, pair.second);
            //    this->insertBefore(n, level);
            //    return std::make_pair(n, true); // true because inserted
            //}
           
            void initSentinel(int level) {
                this->setPrev(this, level);
                this->setNext(this, level);
            }

            virtual ~Node() {}

        }; // struct Node

        // node that contains data
        struct DataNode : public Node {
            ValueType key_val; // Map element as key-value pair

            DataNode(Key_T k, Mapped_T m) : Node(), key_val(std::make_pair(k, m)) {}

            ValueType& getElement() {
                return this->key_val;
            } 

            Key_T getKey() {
                return this->key_val.first;
            }
           
            Mapped_T getVal() {
                return this->key_val.second;
            }

        }; // struct DataNode
        
        // Map ; runtime is in terms of N = # of elements    
        private:
            // Skip List
            int _num_items; // number of unique items
            Node* _sentinel; // Node that holds an array of sentinel node pointers for each level in the skip list
 
            /* Map helper methods */
            
            // add a level to the skip list
            void _addLevel() {
                _sentinel->links.push_back(link_t(_sentinel, _sentinel));
            }

            void _removeLevel() {
                if(_sentinel->links.size() <= 1) return;
                _sentinel->links.pop_back();
                assert(_sentinel->links.size() > 0);
            }

            // returns an indexable level value 
            int _getMaxLevel() const {
                return _sentinel->getMaxLevel();
            }
            
            void _eraseAtLevel(Node* n, int level) {
                n->getPrev(level)->setNext(n->getNext(level), level); // n->prev->next = n->next;
                n->getNext(level)->setPrev(n->getPrev(level), level); // n->next->prev = n->prev;
                n->setPrev(nullptr, level); // n->prev = n->next = 0;
                n->setNext(nullptr, level);
            }

            // used as a helper so public function can either return Iterator or ConstIterator 
            std::pair<Node*, bool>  _find(const Key_T& key, int insertAtLevel) const {
                //std::cout << "Finding key=" << key << std::endl;
                Node* ptr = _sentinel;
                int level = _getMaxLevel();
                
                while(level >= 0) {
                    Node* next = ptr->getNext(level);
                    if(next == _sentinel) {
                        if(level == insertAtLevel) return std::make_pair(_sentinel, false);
                        level--;
                        continue;
                    }
                   
                    DataNode* d = dynamic_cast<DataNode*>(next);
                    if(key < d->getKey()) {
                        if(level == insertAtLevel) return std::make_pair(d, false);
                        level--;
                        continue;
                    }
 
                    //std::cout << "level=" << level << ",next->key=" << next->getKey() << std::endl;
                    if(key == d->getKey()) {
                        //std::cout << "Found key=" << key << "!" << std::endl;
                        return std::make_pair(d, true);
                    }
                    else {
                        ptr = next;
                    }
                }

                // return end() Iterator
                //std::cout << "key=" << key << " was not found..." << std::endl;
                return std::make_pair(_sentinel, false);
            }

            void _initSentinel() {
                if(_sentinel != nullptr) {
                    printf("Must free old sentinel to restart sentinel.\n");
                    return;
                }
                _sentinel = new Node();
                int level = _getMaxLevel();
                _sentinel->initSentinel(level);
            }

        public:
            // Iterators point to the Node in the skip list ; always at level 0
            class Iterator {
                private:
                    Node* _node;
                public:
                    Node* getNode() const { return _node; }
                    Iterator(Node* n) : _node(n) {}
                    Iterator(const Iterator& it) = default;
                    
                    Iterator& operator=(const Iterator& it) = default;           
 
                    ValueType& operator*() const {
                        DataNode* d = dynamic_cast<DataNode*>(_node);
                        return d->key_val;

                    }

                    ValueType* operator->() const {
                        DataNode* d = dynamic_cast<DataNode*>(_node);
                        return &d->key_val;
                    }

                    Iterator& operator++() {
                        _node = _node->getNext(0);
                        return *this;
                    }
    
                    Iterator operator++(int) {
                        Iterator it = Iterator(_node);
                        _node = _node->getNext(0);
                        return it;
                    }

                    Iterator& operator--() {
                        _node = _node->getPrev(0);
                        return *this;
                    }

                    Iterator operator--(int) {
                        Iterator it = Iterator(_node);
                        _node = _node->getPrev(0);
                        return it;
                    }
 
                    ~Iterator() = default;
            }; // class Iterator
            
            class ConstIterator : public Iterator {
                public:
                    ConstIterator(Node* n) : Iterator(n) {}
                    ConstIterator(const Iterator& it) : Iterator(it.getNode()) {}
            }; // class ConstIterator
            
            // ReverseIterator goes in the opposite direction: ++ gets the previous node ; -- gets the next node
            class ReverseIterator : public Iterator {
                public:
                    ReverseIterator(Node* n) : Iterator(n) {}
                    ReverseIterator(const ReverseIterator& it) : Iterator(it.getNode()) {}
                   
                    ReverseIterator& operator++() {
                        Iterator::operator--();
                        return *this;
                    }
                
                    ReverseIterator operator++(int) {
                        ReverseIterator it = ReverseIterator(this->getNode());
                        Iterator::operator--();
                        return it;
                    }

                    ReverseIterator& operator--() {
                        Iterator::operator++();
                        return *this;
                    }

                    ReverseIterator operator--(int) {
                        ReverseIterator it = ReverseIterator(this->getNode());
                        Iterator::operator++();
                        return it;
                    }
            }; // class ReverseIterator

            /* Comparison Iterators */ 

            friend bool operator==(const Iterator& it1, const Iterator& it2) {
                return it1.getNode() == it2.getNode();
            }
 
            friend bool operator!=(const Iterator& it1, const Iterator& it2) {
                return !(it1 == it2);
            }

            Map(): _num_items(0), _sentinel(nullptr) {
                //printf("Map()\n");
                _initSentinel();
                
            }

            Map(const Map& m) : _num_items(0), _sentinel(nullptr) { // copy constructor; O(N) 
                _initSentinel();

                Iterator it = m.begin();
                while(it != m.end()) {
                    ValueType key_val = *it;
                    this->insert(key_val);
                    it++;
                }
            }
         
            // create a map with a list of key-value pairs 
            Map(std::initializer_list<std::pair<const Key_T, Mapped_T>> list) : _num_items(0), _sentinel(nullptr) {
                _initSentinel();
                for(ValueType v : list) {
                    ValueType key_val = std::make_pair(v.first, v.second);
                    //std::cout << "key=" << key_val.first << ",value=" << key_val.second << std::endl;
                    this->insert(key_val); // increments num_items
                }
            }
 
            Map& operator=(const Map& m) {
                if(this != &m) { // prevent errors on self-assignemnt
                    // free old resources
                    this->clear();
                    delete _sentinel;
                    _sentinel = nullptr;
                    _num_items = 0; // reset size ; insert() increments num_items again
                    _initSentinel();
                    
                    // copy values
                    Iterator it = m.begin();
                    while(it != m.end()) {
                        ValueType key_val = *it;
                        this->insert(key_val);
                        it++;
                    }
                }
                return *this;
            }
 
            /* Map methods */

            /* Size */

            size_t size() const {
                return _num_items;
            }
        
            bool empty() const {
                return _num_items == 0;
            }

            /* Iterators */
            
            Iterator begin() {
                return Iterator(_sentinel->getNext(0));
            }

            Iterator end() {
                return Iterator(_sentinel);
            }
 
            ConstIterator begin() const {
                return ConstIterator(_sentinel->getNext(0));
            }

            ConstIterator end() const {
                return ConstIterator(_sentinel);
            }

            ReverseIterator rbegin() {
                return ReverseIterator(_sentinel->getNext(0));
            }

            ReverseIterator rend() {
                return ReverseIterator(_sentinel);
            }

            /* Element Access */
                
            Iterator find(const Key_T& key) {
                std::pair<Node*, bool> n = _find(key, -1);
                bool found = n.second;
                
                if(!found) return this->end();
                else return Iterator(n.first);
            }
       
            ConstIterator find(const Key_T& key) const {
                std::pair<Node*, bool> n = _find(key, -1);
                bool found = n.second;
                
                if(!found) return this->end();
                else return ConstIterator(n.first);
            }

            Mapped_T& at(const Key_T& key) {
                std::pair<Node*, bool> n = _find(key, -1);
                bool found = n.second;

                if(!found) throw std::out_of_range("Key was not found.");
                else {
                    // since it was found, can guarantee that it is a DataNode
                    DataNode* d = dynamic_cast<DataNode*>(n.first);
                    return d->key_val.second;
                }
            }
            
            const Mapped_T& at(const Key_T& key) const {
                //printf("Const verison of at()\n");
                std::pair<Node*, bool> n = _find(key, -1);
                bool found = n.second;

                if(!found) throw std::out_of_range("Key was not found.");
                else {
                    // since it was found, can guarantee that it is a DataNode
                    DataNode* d = dynamic_cast<DataNode*>(n.first);
                    return d->key_val.second;
                }
            }

            Mapped_T& operator[](const Key_T& key) {
                Iterator it = find(key);
                if(it.getNode() == end().getNode()) { // does not exist ; add to map
                    std::pair<Iterator, bool> ins = insert(std::make_pair(key, Mapped_T()));
                    assert(ins.second == true); // ensure that this key was inserted properly
                    return (*ins.first).second; // returns value
                } else { // this key exists
                    return (*it).second;
                }
            }

            /* Modifiers */

            std::pair<Iterator, bool> insert(const ValueType& pair) {
                //std::cout << "insert(): {key=" << pair.first << ",val=" << pair.second << "}" << std::endl;
               
                // insert at bottom-most level 
                std::pair<Node*, bool> inserted = _find(pair.first, 0); // returns the node where this key must be inserted before
                if(inserted.first != _sentinel) {
                    DataNode* d = dynamic_cast<DataNode*>(inserted.first); // safe to cast to DataNode since it is not the sentinel
                    if(d->getKey() == pair.first) { // key already exists
                        return std::make_pair(Iterator(inserted.first), false);
                    }
                }
                // insert new node
                DataNode* n = new DataNode(pair.first, pair.second);
                inserted.first->insertBefore(n, 0); // insert at bottom-most level

                _num_items++;
               
                // insert at upper levels
                int level = 1;
                while(rand() % 2 == 0) { // keep creating a new level with 50% chance
                    if(level > _getMaxLevel()) { // no sentinel at this level ; create one
                        this->_addLevel();
                    } 
                    n->links.push_back(link_t());
                    std::pair<Node*, bool> inserted = _find(pair.first, level);
                    inserted.first->insertBefore(n, level);
                    //assert(ptr->links.size()-1 == (size_t)level);
                    //_sentinel->insert(pair, level, ptr);
                    ////printf("Inserted at level %d\n", level);
                    level++;
                }
 
 
                //// insert at the bottom-most level
                //std::pair<DataNode*, bool> inserted = _sentinel->insert(pair, 0, nullptr); // nullptr indicates to create a new node
                //if(!inserted.second) { // if key already exists
                //    return std::make_pair(Iterator(inserted.first), inserted.second);
                //}
                //
                //_num_items++;
                //
                //DataNode* ptr = inserted.first;
                //int level = 1;
                //while(rand() % 2 == 0) { // keep creating a new level with 50% chance
                //    if(level > _getMaxLevel()) { // no sentinel at this level ; create one
                //        this->_addLevel();
                //    } 
                //    ptr->links.push_back(link_t());
                //    assert(ptr->links.size()-1 == (size_t)level);
                //    _sentinel->insert(pair, level, ptr);
                //    //printf("Inserted at level %d\n", level);
                //    level++;
                //}

                //return std::make_pair(Iterator(inserted.first), inserted.second);
                return std::make_pair(Iterator(n), true);
            }

            // insert objects between range_beg and range_end (exclusive)
            template <typename IT_T>
            void insert(IT_T range_beg, IT_T range_end) {
                IT_T it = range_beg;
                while(it != range_end){
                    this->insert(*it);
                    it++;
                }
            }

            void erase(Iterator pos) {
                if(pos == end()) return;
                
                Node* n = pos.getNode();
                //std::cout << "Removing " << key << std::endl;

                int level = n->getMaxLevel();
                while(level >= 0) {
                    _eraseAtLevel(n, level);
                    if(_sentinel->getNext(level) == _sentinel) {
                        //printf("Empty at level %d. Removing level.\n", level);
                        _removeLevel();
                    }
                    level--;
                }
                delete n;

                _num_items--;
            }

            void erase(const Key_T& key) {
                Iterator it = find(key);
                if(it.getNode() == this->end().getNode()) {
                    throw std::out_of_range("Key was not found.\n");
                }
                erase(it);
            }

            void clear() {
                if(_num_items == 0) {
                    //printf("No items to clear.\n");
                    return;
                }

                // only need to free level 0 (since the upper levels are just pointers to existing nodes that were allocated at level 0)
                int level = 0;
                Node* ptr = _sentinel->links[level].next;
                while(ptr != _sentinel) {
                    Node* next = ptr->getNext(level);
                    delete ptr;
                    ptr = next;
                }
                
                // remove all levels of the sentinel
                _sentinel->links.clear();
                _sentinel->links.push_back(link_t()); // reset link
                level = _getMaxLevel();
                _sentinel->initSentinel(level); // initalize links to sentinel
            
                // reset number of unique items to zero
                _num_items = 0;
            }  
            
            /* Comparison */
            
            friend bool operator==(const Map& m1, const Map& m2) {
                if(m1.size() != m2.size()) return false;
                Iterator it1 = m1.begin();
                Iterator it2 = m2.begin();
                while(it1 != m1.end() && it2 != m2.end()) {
                    if(*it1 != *it2) {
                        return false;
                    }
                    it1++;
                    it2++;
                }
                return true;
            }

            friend bool operator!=(const Map& m1, const Map& m2) {
                return !(m1 == m2);
            }

            friend bool operator<(const Map& m1, const Map& m2) {
                if(m1.size() != m2.size()) {
                    if(m1.size() < m2.size()) return true;
                    else return false;
                }
                
                // at this point, m1 and m2 have the same size ; must compare each element
                Iterator it1 = m1.begin();
                Iterator it2 = m2.begin();
                while(it1 != m1.end() && it2 != m2.end()) {
                    ValueType v1 = *it1;
                    ValueType v2 = *it2;
                    if(v1 < v2) return true;
                    else if(v2 < v1) return false;
                    // else they are the same element ; continue
                    it1++;
                    it2++;
                }
                return false; // m1 and m2 are equal
            }

            /* Helper methods for debugging */
 
            void printLevel(int level) const {
                //if(level > _getMaxLevel()) return;
                //
                //Node* ptr = _sentinel->getNext(level);
                //printf("Level %i: ", level);
                //while(ptr != _sentinel) {
                //    DataNode* d = dynamic_cast<DataNode*>(ptr);
                //    std::cout << "[key=" << d->getKey() << ",val=" << d->getVal() << "] -> ";
                //    ptr = ptr->getNext(level);
                //}
                //printf("||\n");
            } 

            void print() const {
                //printf("\n--- Number of unique items: %d ---\n", _num_items);
                //for(int i=_getMaxLevel(); i>=0; i--) {
                //    this->printLevel(i);
                //}
                //printf("-----\n\n");
            }

            ~Map() {
                this->clear();
                delete _sentinel;
            }

    }; // class Map

} // namespace cs540

#endif // CS540_MAP_H
