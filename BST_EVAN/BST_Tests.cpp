#include <iostream>
#include <cassert>
#include "BST_EVAN.hpp"

void testBST() {
    BST<int> bst;

    // Test 1: Insert a single value
    bst.insert(10);
    assert(bst.find(10) == 10);

    // Test 2: Insert multiple values
    bst.insert(5);
    bst.insert(15);
    assert(bst.find(5) == 5);
    assert(bst.find(15) == 15);

    // Test 3: Check duplicate insert exception
    try {
        bst.insert(10);
        assert(false); // Should not reach here
    }
    catch (const ValueExistsError&) {
        assert(true);
    }

    // Test 4: Check existence of values
    assert(bst.exists(10));
    assert(!bst.exists(20));

    // Test 5: Remove a leaf node
    bst.remove(5);
    assert(!bst.exists(5));

    // Test 6: Remove a node with one child
    bst.insert(12);
    bst.remove(15);
    assert(!bst.exists(15));
    assert(bst.exists(12));

    // Test 7: Remove a node with two children
    bst.insert(15);
    bst.insert(13);
    bst.remove(12);
    assert(!bst.exists(12));
    assert(bst.exists(13));

    // Test 8: Check in-order traversal
    std::vector<int> values;
    bst.traverseInOrder([&](const BST<int>&, std::shared_ptr<BST<int>::Node> node) {
        values.push_back(node->getData());
        return true;
        });
    assert((values == std::vector<int>{10, 13, 15}));

    // Test 9: Check tree size
    assert(bst.size() == 3);

    // Test 10: Check clearing the tree
    bst.clear();
    assert(bst.empty());

    // Test 11: Test isLeaf function
    bst.insert(30);
    bst.insert(20);
    assert(bst.isLeaf(bst.find_node(20)));

    // Test 12: Test isRoot function
    assert(bst.isRoot(bst.find_node(30)));

    // Test 13: Check tree size after re-insertion
    bst.insert(40);
    assert(bst.size() == 3);

    // Test 14: Check level-order traversal
    bst.insert(10);
    bst.insert(50);
    values.clear();
    bst.traverseLevelOrder([&](const BST<int>&, std::shared_ptr<BST<int>::Node> node) {
        values.push_back(node->getData());
        return true;
        });

    std::cout << "All BST tests passed!" << std::endl;
}

//int main() {
//    testBST();
//    return 0;
//}
