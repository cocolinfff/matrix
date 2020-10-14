#include<iostream>
using namespace std;
   #define AUTO_PROCESS
#include "matrix.h"

int main(){
    matrix<double> n(4, 4, 1);
    matrix<double> t(4, 4, 1);
    matrix<double> m(1,1,0);
    n.input('i', 2, 3, -1, -7,
                 3, 1, 2, -7,
                 4, 1, -3, 6,
                 1, -2, 5, -5);
    t = (n * n);
    m = t.mean();
    n.isroot = 1;
   // cout << t;
  //  cout << m.leaf[0]->clone()<<endl;
    //cout << m;
  //  cout << m.dfs()<<endl;
   // cout << m.auto_grad(n)<<endl;

       cout <<n.auto_easify();

    //  n[1][1] = 0 
    // cout << n.leaft_m(0, 0) << endl;
    // cout << n.deter()<<endl;
    //n.format(1);

    /*  cout << n<<endl;
    n = m.clone();
    cout << n<<endl;
    n.input(1, 2, 3, 4, 5, 
    1, 2, 3, 4, 5,
    1, 2, 3, 4, 5,
    1, 2, 3, 4, 5,
    1, 2, 3, 4, 5);
    cout << n<<endl;
    cout << m * n<<endl;
    n = m;
    m.input(0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            0, 0, 0, 0);
    n = m.clone();
    n.input(2, 1, 0, 0,
            0, 2, 1, 0,
            0, 0, 2, 1,
            0, 0, 0, 2);
*/
    /* cout << (m * n)<<endl;
    cout << m.mean().data;
    cout << m<<endl;
    cout << m.mean().data;
    cout << n * m<<endl;
    cout << m.mean().data;
    cout << m<<endl;
    cout << m.mean().data;
    */
    /*  
       n.input('i',1,2,0,3,
    
                4,7,1,10,
                0,1,-1,10000,
                2,3,100,4);
   // cout << (n ) << endl;
    cout<<n.auto_easify_process()<<endl;
    */
    //  cout << n.normal_matrix_s(1, 2, 1);
    //  fx<int> ff = m.mean();
    //cout << ff.data<<endl;
    // cout << n .mean();
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