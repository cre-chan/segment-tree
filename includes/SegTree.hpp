//
// Created by cre-chan on 19-8-28.
//

#ifndef SEGTREE_SEGTREE_HPP
#define SEGTREE_SEGTREE_HPP

#include <iostream>
#include <stdexcept>

using namespace std;

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

    //返回某一节点的和
    int& sum() {
        return kind == Leaf ? data.LeafNode.value : data.InternalNode.sum;
    }

    uint midpoint(){
        if(kind==Leaf)
            throw invalid_argument("Calling SegTree::midpoint() on a Leaf");

        return (data.InternalNode.upper_bound+data.InternalNode.lower_bound)/2
               +(data.InternalNode.upper_bound-data.InternalNode.lower_bound)%2;
    }
public:

    //递归建树
    SegTree(int arr[], uint sz, uint base = 0) {
        if (sz == 1) {
            kind = Leaf;
            data.LeafNode.value = arr[0];
        } else {
            auto &internal = data.InternalNode;

            kind = Internal;
            internal.lower_bound = base;
            internal.upper_bound = base + sz - 1;

            internal.left = new SegTree(arr, sz / 2, base);
            internal.right = new SegTree(arr + sz / 2, sz - sz / 2, base + sz / 2);
            internal.sum = internal.left->sum() + internal.right->sum();
        }
    }

    int query(uint l,uint r){
        //叶子节点，直接返回
        if(kind==Leaf)
            return this->sum();

        if(data.InternalNode.upper_bound==r&&data.InternalNode.lower_bound==l)
            return this->sum();

        uint mid=this->midpoint();

        if(r<mid)
            return data.InternalNode.left->query(l,r);

        if(l>=mid)
            return data.InternalNode.right->query(l,r);

        return data.InternalNode.left->query(l,mid-1)+data.InternalNode.right->query(mid,r);
    }

    void update(uint index,int value){
        if (kind==Leaf)
            this->sum()=value;
        else{
            uint mid=this->midpoint();

            if(index<mid)
                data.InternalNode.left->update(index,value);
            else
                data.InternalNode.right->update(index,value);

            this->sum()=data.InternalNode.left->sum()+data.InternalNode.right->sum();
        }
    }

    ~SegTree() {
        if (kind == Internal) {
            delete data.InternalNode.left;
            delete data.InternalNode.right;
        }
    }
};

#endif //SEGTREE_SEGTREE_HPP
