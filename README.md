# Segment Tree
## Scenario

Imagine that you're given a random array $1,4,5\dots5,2$. And you'll be asked about sum in a specific interval. For example, I want to know the sum of $[0 ,2]$. The naive method would be to add up $1,4,5$ and we get 10. If there's only one query about the sum, this is OK. But what if there were 100 queries? Say, $[1,4],[2,5]\dots[5,7]$. The naive method would be inappropriate. So we'll introduce a data structure, segment tree.

SegTree basically divides a segment into many sub-segments. Each node of a SegTree is a segment and its two children are left part and right part of this segment. Say, a node `parent`represents a segment $\left[0,9\right]$, then its left child represents $[0,4]$ and its right child represents $[5,9]$. The partition recurses until a segment is of length $1$ .

## Definition

Segment Tree declaration in ADT (Algebraic Data Type)

```haskell
type Bound = B uint uint
type SegTree = Internal Bound int SegTree SegTree |
               Leaf int 
```
A SegTree can either be internal or leaf.  An `Internal` can be divided into left and right so there're two fields of SegTree in the definition `Internal Bound int SegTree Segtree`. `int` field is the sum of nums in the Interval. It's also the sum of left's sum and right's sum. In contrast, `Leaf` corresponds to element in the array and has no children because it is atomic.

Declaration in c++ looks like this:

```c++
class SegTree {
    enum {
        Internal, Leaf
    } kind;
    union {
        struct {
            uint lower_bound;
            uint upper_bound;
            int sum;
            SegTree *left;
            SegTree *right;
        } InternalNode;
        struct {
            int value;
        } LeafNode;
    } data;
}
```

## Basic Operations

 **Build SegTree**: Given an array $a_0,a_1,a_2\dots a_n$, to build a segment tree. The algorithm can be described as below:

1. If the array is of length 1,then create a `Leaf` with sum equal to the only element.
2. Otherwise, "split" the array in half, build segment tree respectively on two parts and make them left child and right child. Add up the left child's sum and right child's sum to calculate the sum of this array.

The time complexity of this operation is $O(n)$ where $n$ is length of the array. The analysis is simple. Since the segment tree always divides the array in half, every `Internal` always has a degree of $2$. And there're $n$ leaves. According to the property, a binary tree always has one more leaf node than nodes with degree of $2$. It's easy to conclude that the tree consists of $2n-1$ nodes. In order to traverse the $2n-1$ nodes, we takes $O(n)$ time.

**Query Interval**:

**Update Element**: