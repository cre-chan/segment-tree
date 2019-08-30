#include <iostream>
#include <SegTree.hpp>
using namespace std;

int data[]={1,2,3,4,5};

int main() {
    SegTree a(data, sizeof(data)/ sizeof(data[0]));

    cout<<"sum of [1,3] is "<<a.query(1,3)<<endl;
    cout<<"sum of [1,1] is "<<a.query(1,1)<<endl;
    a.update(2,5);
    cout<<"sum of [0,4] is "<<a.query(0,4)<<endl;
    return 0;
}