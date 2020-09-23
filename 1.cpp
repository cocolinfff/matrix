#include<iostream>
using namespace std;
#include "matrix.h"
int main(){
    matrix<int> m(5, 5, 1);
    matrix<int> n(2, 2, 3);
  //  n[1][1] = 0;
   // cout << n.leaft_m(0, 0) << endl;
   // cout << n.deter()<<endl;
   // n.format(1);

    cout << n<<endl;
    n = m.clone();
    cout << n;
    //  cin.get();
    //   matrix<int> n(3, 3);
    //  n = m;
    //  n[3][2] = 5;
    //  m[3][3] = 1;
    //  cout<<m[3][3]<<endl;
    //  cout << n <<endl<< m.trans();
    //      cout << m+n;
    return 0;
}