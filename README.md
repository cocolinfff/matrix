 ![Colin](http://ys-j.ys168.com/564684521/jgrhppu44451J85I3OU/logo.png)  
     matrix  
======
a cmatrix.h for c++  
 <1.0版本>
 --------
重载了<<,+,-,*,[]运算符，加入了一些处理函数  
  
示例：  
```C++  
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
  ```
<1.1版本>  
-------
* 修改:  
     ```C++  
     n.clone()//只将每一项重新赋值，暂时取消了改变空间  
              // 乘法新加入了两种重载，针对数字或者特殊数字类型fx  
   m=n*3;  
  ```
* 新增：
```C++  
     n.mean()//对每个元素之和求均值并返回一个1x1的矩阵  
     n.autoeasify()//自动化简矩阵为阶梯型矩阵  
     n.input('i',1,1,2,3,  
                 4,5,2,1,  
                 2,3,4,5);//赋值矩阵，'i'表示数据输入类型为int目前仅支持int和double('d')  
     n.autoeasify_process()//自动化简矩阵并用cout输出中间步骤左乘的初等矩阵  
     n.normal_matrix_l(line_1,line_2,mutiply)//根据n的x属性创建一个初等矩阵，line_2加上line_1乘以mutiply，用于左乘  
     fx s;//特殊数字储存格式，默认为double型，在矩阵运算中代替普通数字作为数乘运算的跟踪  
 ```
* 预告：自动求梯度功能以及dfs函数  
   
