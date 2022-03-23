//  Created by Lucas Cesar Belvedere on 2/22/22.
//  Last updated: 3/23/22.

#ifndef Map_h
#define Map_h

using KeyType = std::string;
using ValueType = double;


// CLASS MAP.
class Map{
private:
    
    // Binary Tree Node.
    struct Node{
        ValueType value;
        KeyType key;
        Node *left, *right;
        Node (KeyType key, ValueType value);
        ~Node();
        void PrintNodeInfo();
    };
    
    
    // private member variables.
    Node* root;
    
    int sizeTree;
    
    // private mutators.
    bool SearchNode(Node*&, Node*&, const KeyType&) const;
    
    bool AddNode(const KeyType& key, ValueType val);
    
    bool DeleteNode(const KeyType& key);
    
    Node* DeleteTree(Node*&);
    
    Node* CopyTree(const Node*);
    
    bool GetTraversal(int&, Node*&, KeyType&, ValueType&) const;
    
public:
    
    Map();              // Create an empty map (i.e., one with no key/value pairs)
    
    Map(const Map& src); // Copy constructor
    
    Map& operator=(const Map& src); // Assignment operator
    
    ~Map(); // destructor

    bool empty() const; // Return true if the map is empty, otherwise false.

    int size() const;   // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map).

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value it currently maps to, but instead map to
      // the value of the second parameter; return true in this case.
      // If key is not equal to any key currently in the map then add it and
      // return true. In fact this function always returns true.

    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.

    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.

    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map that that key maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.

    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of one of the key/value pairs in the map and return
      // true.  Otherwise, leave the key and value parameters unchanged and
      // return false.  (See below for details about this function.)

    void swap(Map& other);
      // Exchange the contents of this map with the other one.
    
    void Dump() const;
      // Testcases.
};

bool combine(const Map& m1, const Map& m2, Map& result);

void subtract(const Map& m1, const Map& m2, Map& result);

#endif /* Map_h */
