# Chapter 5 : Trees
## Terminology
- **Definition(Tree)**
    - A tree si afinite set of noe or more nodes 
        - There is a specially designated node called root.
        - The remaining nodes are partitioned into n>=0 disjoint sets T~1~, ..., T~n~, 
        where each of these sets is a tree.
        - T~1~, ..., T~n~ are the subtrees of the root.
- **Subtrees are prohibited from ever connecting together**
- **Every node in the tree is the root of some subtree**
- **The degree of a node**
    - The number of subtress of the node.
- **The degree of a tree**
    - The maximum degree of the nodes in the tree.
- **A leaf/terminal node**
    - A node with degree zero
- **The parent (children) of a node**
    - Given a node X and its subtrees T~1~, ..., T~n~, 
      which are rooted at node r~1~, ..., r~n~, respectively.
    - X is the parent of r~1~, ..., and r~n~.
    - In other words, r~1~, ..., and r~n~ are X's children.
- **Siblings**
    - Children of the same parent.
- **The ancestors of a node**
    - All the nodes along the path from the root the node.
- **The descendents of a node**
    - All the nodes that are in its subtrees.
- **The level of a node**
    - The root is at level one.
    - Otherwise, the level is the level if its parent plus one.
- **The height/depth of a tree**
    - The maximum level of any nodes in the tree.
## Representation of Trees
- **List Representation**
    - Write a tree as a list in which each of the subtrees is also a list.
    - Example: (A (B (E (K, L), F), C (G), D( H (M), I, J))) => p.5-4 Fig5.2
## Representation of Trees in Memory
- **Linked lists**
    - A node with varying number of fields.
    - Each link represents a child of the node.
- **Left Child-Right Sibling Representation**
    - Exactly two link or pointer fields per node.
    - The order of children in a tree is not important.
        - Any of the children of a node could be its leftmost child
          and any of its siblings could be the closest right sibling.
## Binary Trees
### Introduction
- **Definition(Binary Trees)**
    - A binary tree is a finite set of nodes that is either empty or consists of 
      a root and two disjoint binary trees called the left subtree and the right subtree.
- **The chief characteristics of a binary tree**
    - The degree of any given node must not exceed two.
    - The order of subtrees is not irrelevant any more.
    - May have zero nodes.
- **The binary tree ADT (p.5-10, ADT 5.1)**
- **A binary tree vs. A tree**
    - An empty tree is invalid while a binary tree may have zero nides.
    - The order of subtrees is irrelevant in a tree while the prder of children 
      is distinguishable in a binary tree.
- **Two special types of binary trees**
    - Skewed trees
        - skewed to the left or to the right.
    - Complete binary trees
        - All the leaf nodes are on two adjacent levels.
### Properties
- **Lemma 5.2 : Maximum number number of nodes**
    - If first level is level 1.
    - The maximum number of nodes on level *i* of a binary tree is 2^i-1^, *i ≧ 1*.
    - The maximum number of nodes in a binary tree of depth *k* is 2^k^-1, *k ≧ 1*.
- **Lemma 5.3 : Relation between number of leaf nodes and nodes of degree 2**
    - For any nonempty binary tree *T*, if *n~0~* is the number of leaf nodes and 
      *n~2~* is the number of nodes of degree 2, then *n~0~ = n~2~+1*.
- **Definition (Full Binary Trees)**
    - A full binary tree of depth *k* is a binary tree of depth *k* having *2^k^-1* nodes, *k ≧ 1*.
    - A numbering scheme
        - Starting with the root on level 1, continue with the nodes on level 2, and so on.
        - Nodes on any level are numbered from left ro right.
        - p.5-13 Fig. 5.11
- **Definition (Complete Binary Trees)**
    - A binary tree with *n* nodes and depth *k* is complete if its nodes correspond to 
      the nodes numbered from *1* to *n* in the binary tree if depth *k*.
### Representation
- **Array Representation**
    - A one-dimensional array
        - The 0th position of the array is a dummy element.
    - **Lemma 5.4 :**
        - If a complete binary tree with *n* nodes (depth = [log~2~*n*+1]) is represented     sequentially, then for any node with index *i*, 1 ≦ *i* ≦ n, we have:
            - parent (*i*) is at [i/2] if *i* != 1. If *i* = 1, *i* is at the root and has    no parent.