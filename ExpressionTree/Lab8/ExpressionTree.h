//--------------------------------------------------------------------
//
//  Laboratory 8                                     ExpressionTree.h
//
//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive helpers for the
//  public member functions
//
//  Instructor copy with the recursive helper function declarations.
//  The student version does not have those, but has a place to write
//  the declarations in the private section.
//
//--------------------------------------------------------------------

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>

using namespace std;

#pragma warning( disable : 4290 )

template <typename DataType>
class ExprTree {
  public:

    // Constructor
    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ();
    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();              // Clear tree
    void commute();
    bool isEquivalent(const ExprTree& source) const;

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

	bool isEmpty() const;

  private:

    class ExprTreeNode {
      public:
        // Constructor
        ExprTreeNode ( char elem,
                       ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        // Data members
        char dataItem;          // Expression tree data item
        ExprTreeNode *left,     // Pointer to the left child
                     *right;    // Pointer to the right child
    };

    // Recursive helper functions for the public member functions -- insert
    // prototypes of these functions here.
	void showHelper ( ExprTreeNode *p, int level ) const;

    void buildHelper(ExprTreeNode*& p);

    void exprHelper(ExprTreeNode* p) const;

    float evalHelper(ExprTreeNode* p) const;

    void clearHelper(ExprTreeNode* p);

    void commuteHelper(ExprTreeNode* p);

    void copyHelper(ExprTreeNode*& p);

    bool isEquivalentHelper(const ExprTreeNode* x, const ExprTreeNode* y) const;
    // Data member
    ExprTreeNode *root;   // Pointer to the root node
};

#endif		// #ifndef EXPRESSIONTREE_H
