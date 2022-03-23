//  Created by Lucas Cesar Belvedere on 2/22/22.
//  Last updated: 3/23/22.

#include <iostream>
#include "Map.h"
#include <string>
#include <cassert>
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
        "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
        "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
    CHECKTYPE(&Map::size,           int  (Map::*)() const);
    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));

    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}

// MAIN ROUTINE.
int main(){
    Map m1;
    m1.Dump();
}

void Map::Dump() const{
    for(int x = 1; x<=16 ; x++)
        switch (x) {
            case 1: {
                Map* bst_map = new Map();
                assert(bst_map->empty() == true);
                assert(bst_map->insert("H", 2.22));
                assert(bst_map->insert("D", 3.21));
                assert(bst_map->insert("M", 4.1));
                assert(bst_map->insert("A", 8.9));
                assert(bst_map->empty() == false);
                assert(bst_map->size() == 4);
                break;
            }

            case 2:{
                Map m;
                m.insert("A", 10);
                m.insert("B", 44);
                m.insert("C", 10);
                std::string all = "";
                double total = 0;
                for (int n = 0; n < m.size(); n++)
                {
                    std::string k;
                    double v;
                    m.get(n, k, v);
                    all += k;
                    total += v;
                }
                std::cerr << all << total << std::endl;
                break;
            }

            case 3:{ // TESTCASE 3: SWAP FUNCTION
                Map m1;
                m1.insert("Fred", 2.956);
                Map m2;
                m2.insert("Ethel", 3.538);
                m2.insert("Lucy", 2.956);
                m1.swap(m2);
                assert(m1.size() == 2);
                assert(m1.contains("Ethel"));
                assert(m1.contains("Lucy"));
                assert(m2.size() == 1);
                assert(m2.contains("Fred"));
                assert(m2.update("Fred", 222) == true);
                assert(m2.contains("Fred") && m2.size() == 1);
                assert(m2.insertOrUpdate("Fred", 234) == true);
                assert(m2.insertOrUpdate("Hugo", 234) == true);
                assert(m2.contains("Fred") && m2.size() == 2);
                break;
                
            }

            case 4:{
                Map gpas;
                gpas.insert("Fred", 2.956);
                assert(!gpas.contains(""));
                gpas.insert("Ethel", 3.538);
                gpas.insert("", 4.000);
                gpas.insert("Lucy", 2.956);
                assert(gpas.contains(""));
                gpas.erase("Fred");
                assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  && gpas.contains(""));
                break;
            }
            case 5:{
                Map gpas;
                gpas.insert("Fred", 2.956);
                gpas.insert("Ethel", 3.538);
                double v;
                std::string k1;
                assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
                std::string k2;
                assert(gpas.get(1,k2,v)  &&  k2 == k1);
                break;
            }
            case 6:{
                Map m1;
                assert(m1.insert("Hello", 123.3) == true);
                assert(m1.insert("Hi", 321.1) == true);
                Map m2 = m1;
                assert(m2.contains("Hello") || &m2 != &m1);
                break;
            }
            case 7:{
                // combine test case.
                Map m1, m2, result;
                assert(m1.insert("Fred", 123));
                assert(m1.insert("Ethel", 456));
                assert(m1.insert("Lucy", 789));
                assert(m2.insert("Lucy", 789));
                assert(m2.insert("Ricky", 321));
                assert(combine(m1,m2,result)==true);
                assert(result.size()==4);
                assert(result.contains("Fred"));
                assert(result.contains("Ethel"));
                assert(result.contains("Lucy"));
                assert(result.contains("Ricky"));
                break;
            }
            case 8:{
                // combine test case 2.
                Map m1, m2, result;
                assert(m1.insert("Fred", 123));
                assert(m1.insert("Ethel", 456));
                assert(m1.insert("Lucy", 789));
                assert(m2.insert("Lucy", 654));
                assert(m2.insert("Ricky", 321));
                assert(combine(m1,m2,result)==false);
                assert(result.size()==3);
                assert(result.contains("Fred"));
                assert(result.contains("Ethel"));
                assert(result.contains("Ricky"));
                break;
            }
            case 9:{
                // combine test case 3.
                Map m1, m2, result;
                combine(m1,m2,result);
                assert(result.empty());
                assert(result.insert("Fred", 21));
                assert(result.insert("Ethel",12));
                combine(m1,m2,result);
                assert(result.size()==0);
                assert(m1.insert("Fred", 123));
                assert(m1.insert("Ethel", 456));
                assert(m1.insert("Lucy", 789));
                combine(m1,m2,result);
                assert(result.size()==3);
                break;
            }
            case 10:{
                // subtract test case.
                Map m1, m2, result;
                assert(m1.insert("Fred", 123));
                assert(m1.insert("Ethel", 456));
                assert(m1.insert("Lucy", 789));
                assert(m2.insert("Lucy", 789));
                assert(m2.insert("Ricky", 321));
                assert(m2.insert("Ethel", 654));
                subtract(m1,m2,result);
                assert(result.size()==1);
                
                Map m3, m4;
                assert(m3.insert("Fred", 123));
                assert(m3.insert("Vanvleet", 432));
                subtract(m3,m4,result);
                assert(result.size()==2);
                break;
            }
            case 11:{
                Map m;
                assert(m.insert("Fred", 123));
                assert(m.insert("Ethel", 456));
                assert(m.size() == 2);
                double d = 42;
                assert(m.get("Fred", d)  &&  d == 123);
                d = 42;
                std::string s1;
                assert(m.get(0, s1, d)  &&
                       ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
                std::string s2;
                assert(m.get(1, s2, d)  &&  s1 != s2  &&
                       ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
                break;
            }
            case 12:{
                Map m1;
                assert(m1.insert("Fred", 123));
                assert(m1.insert("Vanvleet", 33));
                assert(m1.insert("Great Player", 815));
                Map m2(m1);
                assert(m1.size()==3 && m2.size()==3 && &m1 != &m2);
                assert(m2.contains("Fred") == true);
                break;
            }
            case 13:{
                Map m1;
                assert(m1.empty() == true);
                assert(m1.insert("Fred", 123) == true);
                assert(m1.insert("Fred", 123) == false);
                assert(m1.empty() == false);
                assert(m1.size() == 1);
                assert(m1.update("Hi", 123) == false);
                assert(m1.update("Fred", 321) == true);
                assert(m1.size() == 1);
                assert(m1.insertOrUpdate("Fred", 432) == true);
                assert(m1.size() == 1);
                assert(m1.insertOrUpdate("Const", 33) == true);
                assert(m1.size() == 2);
                assert(m1.contains("Fred") == true && m1.contains("Const") == true);
                assert(m1.erase("None") == false && m1.erase("Fred") == true);
                assert(m1.size() == 1);
                break;
            }
            case 14:{
                Map m1;
                KeyType k;
                assert(m1.insert("Fred", 123) == true && m1.size() == 1);
                assert(m1.insert("Const", 33) == true && m1.size() == 2);
                assert(m1.insert("Zebra", 44) == true && m1.size() == 3);
                assert(m1.contains("Lucas") == false);
                assert(m1.erase("Const") == true && m1.size() == 2);
                assert(m1.erase("Zebra") == true && m1.size() == 1);
                assert(m1.insert("Const", 123) == true && m1.size() == 2);
                assert(m1.insert("Danger", 33) == true && m1.size() == 3);
                assert(m1.erase("Const") == true && m1.size() == 2);
                break;
            }
            case 15:{
                Map m1;
                KeyType k;
                ValueType v;
                assert(m1.insert("Fred", 123) == true && m1.size() == 1);
                assert(m1.insert("Const", 33) == true && m1.size() == 2);
                assert(m1.insert("Zebra", 44) == true && m1.size() == 3);
                assert(m1.contains("Lucas") == false);
                assert(m1.erase("Fred") == true && m1.size() == 2);
                assert(m1.get(0, k, v) == true && k == "Const");
                break;
            }
            case 16:{
                Map m1, result;
                assert(m1.insert("Fred", 123) == true && m1.size() == 1);
                assert(m1.insert("Const", 33) == true && m1.size() == 2);
                assert(m1.insert("Zebra", 44) == true && m1.size() == 3);
                subtract(m1,m1,result);
                assert(result.size() == 0);
                combine(m1,m1,result);
                assert(result.size() == 3 && result.contains("Fred") == true && result.contains("Const") == true && result.contains("Zebra") == true);
                subtract(m1,result,result);
                assert(result.size() == 0);
                break;
            }
    }
}

Map::Node::~Node(){
    left = nullptr;
    right = nullptr;
}

Map::Node::Node(KeyType key, ValueType value){
    this->key = key;
    this->value = value;
    left = nullptr;
    right = nullptr;
}

bool Map::AddNode(const KeyType& key, ValueType val){ // cnode should be the root.
    if(root == nullptr){ // no nodes in tree.
        root = new Node(key, val);
        ++sizeTree;
        return true;
    }
    
    Node *current = root, *parent = nullptr;
    // traverses to find a node with that value. if not found, adds to the tree.
    while(current != nullptr){
        if(key == current->key)
            return false;
        else if(key < current->key){
            parent = current;
            current = current->left;
            if(current == nullptr){
                current = new Node(key, val);
                parent->left = current;
                ++sizeTree;
                return true;
            }
        }
        else{
            parent = current;
            current = current->right;
            if(current == nullptr){
                current = new Node(key, val);
                parent->right = current;
                ++sizeTree;
                return true;
            }
        }
    }
    return true;
}

Map::Node* Map::CopyTree(const Node* rhs){
    if(rhs == nullptr) // base case.
        return nullptr;

    // recursive case.
    Node* p = new Node(rhs->key, rhs->value);
    p->left = CopyTree(rhs->left);
    p->right = CopyTree(rhs->right);
    return p;
}

Map::Node* Map::DeleteTree(Node*& rhs){
    if(rhs == nullptr) // base case.
        return nullptr;
    
    // recursive case.
    DeleteTree(rhs->left);
    DeleteTree(rhs->right);
    delete rhs;
    rhs = nullptr;
    return rhs;
}

bool Map::SearchNode(Node*& current, Node*& parent, const KeyType& key) const{
    // binary search. big O(log n). worst case scenario is big O(n).
    while(current != nullptr){
        if(key == current->key)
            return true;
        else if(key < current->key){
            parent = current;
            current = current->left;
        }
        else{
            parent = current;
            current = current->right;
        }
    }
    return false;
}

bool Map::DeleteNode(const KeyType& key){
    if(root == nullptr) // nothing to delete.
        return false;
    
    Node* parent = nullptr;
    Node* current = root;
    if(SearchNode(current, parent, key)){
        --sizeTree;
        // case 1: leaf.
        if(current->left == nullptr && current->right == nullptr){
            if(parent == nullptr)
                root = nullptr;
            else if(parent->left == current)
                parent->left = nullptr;
            else if(parent->right == current)
                parent->right = nullptr;
            delete current;
            return true;
        }
        // case 2: one node is not nullptr.
        else if(current->left == nullptr || current->right == nullptr){
            if(parent == nullptr){
                if(current->left != nullptr)
                    root = current->left;
                else
                    root = current->right;
            }
            else if(parent->left == current){
                if(current->left != nullptr)
                    parent->left = current->left;
                else
                    parent->left = current->right;
            }
            else if(parent->right == current){
                if(current->left != nullptr)
                    parent->right = current->left;
                else
                    parent->right = current->right;
            }
            delete current;
            return true;
        }
        // case 3: two nodes linked to it.
        else{
            Node* ptr = current->left;
            Node* ptr_q = nullptr;
            while(ptr->right != nullptr){
                ptr_q = ptr;
                ptr = ptr->right;
            }
            current->key = ptr->key;
            current->value = ptr->value;
            if(ptr->left != nullptr && ptr_q == nullptr)
                current->left = ptr->left;
            else if(ptr->left != nullptr){
                ptr_q->right = ptr->left;
                ptr->left = nullptr;
            }
            else if(current->left == ptr)
                current->left = nullptr;
            delete ptr;
            return true;
        }
    }
    return false;
}

bool Map::GetTraversal(int& i, Node*& current, KeyType& key, ValueType& value) const{
    // base cases.
    if(current == nullptr){
        ++i;
        return false;
    }
    if(i<0)
        return false;
    if(i == 0){
        key = current->key;
        value = current->value;
        return true;
    }
    
    // recursive cases. works like a nested for loop.
    bool trav = GetTraversal(--i, current->left, key, value);
    bool trav_ = GetTraversal(--i, current->right, key, value);
    if(trav || trav_)
        return true;
    return false;
}


// MAP IMPLEMENTATIONS
Map::Map(){
    root = nullptr;
    sizeTree = 0;
}

Map::Map(const Map& src){
    // copies tree using CopyTree function.
    root = CopyTree(src.root);
    sizeTree = src.sizeTree;
}

Map& Map::operator=(const Map& src){
    if(&src == this) // base case.
        return *this;

    // uses delete tree to empty the tree of 'this' map so assignment operator works right.
    DeleteTree(root);
    root = CopyTree(src.root);
    sizeTree = src.sizeTree;
    return *this;
}

Map::~Map(){
    DeleteTree(root);
    sizeTree = 0;
}

bool Map::empty() const{
    // if root is pointing to nothing, means the tree is empty.
    if(root == nullptr)
        return true;
    return false;
}

int Map::size() const{
    // returns size of the tree.
    return sizeTree;
}

bool Map::insert(const KeyType& key, const ValueType& value){
    return AddNode(key, value);
}

bool Map::update(const KeyType& key, const ValueType& value){
    Node* current = root;
    Node* parent = nullptr;
    // if node is found, changes value of it.
    bool b = this->SearchNode(current, parent, key);
    if(b == true)
        current->value = value;
    return b;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    
    Node* current = root;
    Node* parent = nullptr;
    // searches for node
    bool b = this->SearchNode(current, parent, key);
    if(b == true) // if finds it, update value.
        current->value = value;
    else // otherwise, creates a new node.
        this->AddNode(key, value);
    return true;
}

bool Map::erase(const KeyType& key){
    return DeleteNode(key);
}

bool Map::contains(const KeyType& key) const{
    // contains uses the function SearchNode to check if there is a node with that key.
    Node* current = root;
    Node* parent = nullptr;
    bool b = this->SearchNode(current, parent, key);
    return b;
}

bool Map::get(const KeyType& key, ValueType& value) const{
    Node* current = root;
    Node* parent = nullptr;
    // searches for a key in the tree.
    bool b = this->SearchNode(current, parent, key);
    if(b){ // if found, returns the value of that key.
        value = current->value;
        return true;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const{
    Node* current = root;
    return GetTraversal(i, current, key, value);
}

void Map::swap(Map& other){
    if(&other == this) // checks for aliasing.
        return;
    
    // swaps roots.
    Node* m = other.root;
    other.root = this->root;
    this->root = m;
    
    // swaps sizes.
    int n = other.sizeTree;
    other.sizeTree = this->sizeTree;
    this->sizeTree = n;
}

bool combine(const Map& m1, const Map& m2, Map& result){
//    if(&m1 == &m2 || &m2 == &result || &m1 == &result) // checks for aliasing.
//        return false;
    
    Map m1c = m1, m2c = m2, resultc;
    KeyType k, q;
    ValueType v, u;
    bool b = true;
    bool c = true;
    
    
    // nested loops that compares values between both maps.
    // in case that a map contains a unique pair, adds to result.
    // first nested loop for m1 to be copied.
    for(int n = 0; n < m1.size(); n++){
        m1c.get(n, k, v);
        for(int m = 0; m < m2.size(); m++){
            m2c.get(m, q, u);
            if(k == q && v != u){
                b = false;
                c = false;
                m1c.erase(k);
                m2c.erase(q);
                break;
            }
        }
        if(c)
            resultc.insert(k,v);
        else c = true;
    }
    
    // second nested loop for m2 to be copied.
    for(int n = 0; n < m2.size(); n++){
        m2c.get(n, k, v);
        for(int m = 0; m < m1.size(); m++){
            m1c.get(m, q, u);
            if(k == q && v != u){
                b = false;
                c = false;
                m1c.erase(k);
                m2c.erase(q);
                break;
            }
        }
        if(c)
            resultc.insert(k,v);
        else c = true;
    }
    result.swap(resultc);
    return b;
}

void subtract(const Map& m1, const Map& m2, Map& result){
//    if(&m1 == &m2 || &m2 == &result || &m1 == &result) // checks for aliasing.
//        return;
    
    Map m1c = m1, m2c = m2, resultc;
    KeyType k, q;
    ValueType v, u;
    bool b = false;
    
    // nested loops that compares values between both maps.
    // in case that a map contains a unique pair, adds to result.
    // first nested loop for m1 to be copied.
    for(int n = 0; n < m1.size(); n++){
        m1c.get(n, k, v);
        for(int m = 0; m < m2.size(); m++){
            m2c.get(m, q, u);
            if(k == q){
                b = true;
                break;
            }
        }
        if(b)
            b = false;
        else resultc.insert(k,v);
    }
    result.swap(resultc);
}

