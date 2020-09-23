# matrix
a matrix.h for c++

重载了<<,+,-,*,[]运算符，加入了一些处理函数

示例：
matrix<int> m(2,2,0);//新建x=2，y=2的矩阵，并令初始值全为0
matrix<float> n(2,2);//默认初始值为0
n.format(2.0);//将n中所有元素格式化为2
n[1][1]=10.0;//n第二行第二列元素赋值为0
cout<<n<<endl; 
  //输出n
  //[2.0 ,2.0
  // 2.0 ,10.0]
cout<<n.deter();
  //输出对应行列式的值
cout<<n.leaf_m(0,1);
  //输出代数余子式
m=n.trans();//将m指向n的转置（不是赋值）
m=n.clone();//复制n并将m指向n的复制（新空间）
  
