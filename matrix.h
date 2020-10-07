
#ifndef MATRIX
#define MATRIX
#include"fx_matrix.h"
#include <stdarg.h>//平时没人用这个库吧
#define DELTA 0.00000001

#define ADD 1
#define MINUS 2
#define MUTIPLY 3
#define TRANS 4
#define NUM_MUTIPLY 5
#define MEAN 6

template <class T>
class matrix{
    private:
          int x, y;//xy不允许随意修改以防止未知问题
          

      public:
          int auto_grad; //再度抄袭torch的autograd
          T **data;      //暂时把data作为公共属性，可能不会调整
          int root;
          matrix *leaf[2];//可能会存在两个父节点，DFS应该可以搜索到原节点
          int leaf_way;
          int leaf_num;

          matrix(int in_x, int in_y, T first = 0)
          {
              x = in_x;
              y = in_y;
              data = new T *[x];
              for (int i = 0; i < x; i++)
              {
                  data[i] = new T[y];
                  for (int j = 0; j < y; j++)
                  {
                      data[i][j] = first;
                  }
              }
              auto_grad = 0;
              root = 0;
              leaf[0] = NULL;
              leaf[1] = NULL;
              leaf_way = 0;
              //         
        }//构造函数，

    friend ostream &operator<<( ostream &output,const matrix &D ){ 
        output << "[" ;
        for (int i = 0; i < D.x;i++){
             for (int j = 0; j < D.y;j++){
                 output << D.data[i][j] ;
                 if(i!=D.x-1||j!=D.y-1)
                     output << ", ";
             }
             if(i!=D.x-1) 
                 output << endl ;
        }
        output << "]";
        return output;            
    }//重载输出，没有重载输入，因为输入比较麻烦，思考合理的输入方式ing
   // template<typename...Args>

    void input(char fmt, ...){
        va_list v;
        va_start(v, fmt);
        for (int i = 0; i < this->x;i++){
            for (int j = 0; j < this->y;j++){
                switch(fmt){
                    case 'i':this->data[i][j] =  va_arg(v, int);
                        break;
                    case 'd':this->data[i][j] =  (double)va_arg(v, double);
                        break;
                    
                }
            }
        }
        return;
    }


    matrix operator+( matrix &b){
        matrix<T> new_m(b.x,b.y);
        if(this->x==b.x&&this->y==b.y){
            for (int i = 0; i < b.x;i++){
                for (int j=0;j<b.y;j++){
                    new_m.data[i][j] = this->data[i][j] + b.data[i][j];
                }
            }
        

        }
        new_m.leaf[0] = this;
        new_m.leaf[1] = &b;
        new_m.leaf_way = ADD;

        //   else
        //       cout << "error!\n";
        return new_m;
    }//矩阵加法重载


    matrix operator-( matrix &b){
        matrix<T> new_m(b.x,b.y);
        if(this->x==b.x&&this->y==b.y){
            for (int i = 0; i < b.x;i++){
                for (int j=0;j<b.y;j++){
                    new_m.data[i][j] = this->data[i][j] - b.data[i][j];
                }
            }
        }

        
        new_m.leaf[0] = this;
        new_m.leaf[1] = &b;
        new_m.leaf_way = MINUS;


        //else
          //  cout << "error!\n";//这是报错警告，此处屏蔽掉，若有需要可打开
        return new_m;
    }//矩阵减法重载
    //当两者不能相加时，未采用广播机制，而是输出加号后者同型，值全为0的数组

    template <typename mt>
    matrix operator*( mt b){
        matrix<T> new_m(this->x,this->y,0);
      //  if(this->y==b.x){
            for (int i = 0; i < this->x;i++){
                for (int j = 0; j < this->y;j++){
                    new_m[i][j] = this->data[i][j]*b;
                 //   cout << endl;
                }
            }
      //      printf("test");
     //   }

        new_m.leaf[0] = this;
        new_m.leaf_num = b;
        new_m.leaf_way = NUM_MUTIPLY;
        //else
          //  cout << "error!"<<endl;
        return new_m;
    }//矩阵的数乘，bug待定

    template <typename mt>
    matrix operator*( fx<mt> b){
        matrix<T> new_m(this->x,this->y,0);
      //  if(this->y==b.x){
            for (int i = 0; i < this->x;i++){
                for (int j = 0; j < this->y;j++){
                    new_m[i][j] = this->data[i][j]*b.data;
                 //   cout << endl;
                }
            }
      //      printf("test");
     //   }

        new_m.leaf[0] = this;
        new_m.leaf_num = b;
        new_m.leaf_way = NUM_MUTIPLY;
        //else
          //  cout << "error!"<<endl;
        return new_m;
    }//矩阵的数乘，bug待定

     matrix operator*( matrix &b){
        matrix<T> new_m(this->x,b.y,0);
        if(this->y==b.x){
            for (int i = 0; i < this->x;i++){
                for (int j = 0; j < b.y;j++){
                    for (int v = 0; v < b.x; v++){
                      //   cout << new_m[i][j]<<endl;
                        new_m[i][j] += this->data[i][v] * b.data[v][j];
                 //          cout << i << " " << j <<":"<<new_m[i][j]<< endl;
                    }
                }
            }
      //      printf("test");
        }

        new_m.leaf[0] = this;
        new_m.leaf[1] = &b;
        new_m.leaf_way = MUTIPLY;
        //else
          //  cout << "error!"<<endl;
        return new_m;
    }//矩阵的乘法,bug待定

    matrix clone(){
        matrix<T> new_m(this->x,this->y,0);
        for (int i = 0; i < this->x;i++){
           for (int j = 0; j < this->y;j++){
               new_m[i][j] = this->data[i][j];
           }
        }
        return new_m;
    }

    T* operator[](int num){
        return this->data[num];
    }//[]的重载，类比于数组，此处没有采用泄露警告，参考了c++中数组的越界使用

    void operator=(const matrix &b){
        delete (this->data);//大概不会内存泄漏吧
        this->data = b.data;
        this->x = b.x;
        this->y = b.y;
    }//注意！此=不是赋值，而是引用

 

    void format(T fmt){
        for (int i = 0; i < this->x;i++){
           for (int j = 0; j < this->y;j++){
               this->data[i][j] = fmt;
           }
        }
    } //格式化矩阵为任意数字

    matrix trans(){
        matrix<T> new_m(this->y, this->x);
        for (int i = 0; i < this->y;i++){
           for (int j = 0; j < this->x;j++){
                new_m[i][j] = this->data[j][i];
            }
        }
        new_m.leaf[0] = this;
    //    new_m.leaf[1] = b;
        new_m.leaf_way = TRANS;
        return new_m;
    }//转置矩阵

   matrix leaft_m(int l_x,int l_y){
        matrix<T> new_m(this->x - 1, this->y - 1);
        int b_x = 0, b_y = 0;
        for (int i = 0; i < this->x ;i++){
            if(i==l_x) {
          //     i++;
                continue;
            }
            for (int j = 0; j < this->y ;j++){
                if(j==l_y){
           //         j++;
                    continue;
                }
                new_m.data[b_x][b_y] = this->data[i][j];
               // cout << b_x << b_y;
                b_y++;
            }
            b_y = 0;//初始化是个好习惯
            b_x++;
        }
        return new_m;
        //wait to write
    }
    T deter(){
        if(this->x==this->y){
            if(this->x==1){
                return this->data[0][0];
            }
            else{
                int sum=0;
                for (int i = 0; i < this->y;i++){
                    sum += (i % 2 ? 1 : -1)*this->data[0][i]* this->leaft_m(0, i).deter();
                }
                return sum;
            }
        }//求行列式，若不满足则无输出

        return 0;
    }//wait to write

   matrix mean() {
       T sum;
        matrix<T> new_matrix(1,1,0);
        for (int i = 0; i < this->x;i++){
            for (int j = 0; j < this->y;j++){
                sum += this->data[i][j];
            }
        }
        new_matrix.data[0][0] = (T)(sum/(this->x*this->y));
        new_matrix.leaf[0] = this;
        new_matrix.leaf_way = MEAN;
        return new_matrix;
   }//mean是一个求均值函数，最后返回一个1x1的矩阵


   matrix auto_easify(){
       matrix<T> new_matrix(this->x, this->y, 0);
       /*
       for (int i = 0; i < this->x;i++){
           for (int j = 0; j < this->y;j++){
               new_matrix[i][j] = this->data[i][j];
           }
        }
        //cout << "buffer" << endl;
    */
       new_matrix = this->clone();
       double buffer = 0;
       int signal = -1;

       for (int i = 0; i < this->x; i++)
       {
           for (int j = i + 1; j < this->x; j++)
           {
               for (int k = 0; k < this->y; k++)
               {
                   if (new_matrix[i][k] != 0)
                   {
                       if (new_matrix[j][k] == 0)
                       {
                           goto continu;
                       }
                       buffer = (double)new_matrix[j][k] / new_matrix[i][k];

                       signal = k;
                       break;
                   }
               }
               if (signal + 1 > 0)
               {
                   for (int k = signal; k < this->y; k++)
                   {
                       new_matrix[j][k] -= buffer * new_matrix[i][k];
                   }
               }
           continu: buffer=0;
               signal = -1;
           }
       }
       return new_matrix;
   }//自动将矩阵化简为阶梯形并返回一个新矩阵


    matrix normal_matrix_l(int line_1,int line_2,double mutiply){
        matrix<T> new_matrix(this->x, this->x, 0);
        for (int i = 0; i < this->x;i++){
            new_matrix[i][i] = 1;
        }
        new_matrix[line_2][line_1] = mutiply;
        return new_matrix;
    }//根据母矩阵的x创造一个X * X的初等矩阵，即将line_1乘以mutiply加到line_2上去

    matrix auto_easify_process(){
       matrix<T> new_matrix(this->x, this->y, 0);
       new_matrix = this->clone();
       double buffer = 0;
       int signal = -1;

       for (int i = 0; i < this->x; i++)
       {
           for (int j = i + 1; j < this->x; j++)
           {
               for (int k = 0; k < this->y; k++)
               {
                   if (new_matrix[i][k] != 0)
                   {
                       if (new_matrix[j][k] == 0)
                       {
                           goto continu;
                       }
                       buffer = (double)new_matrix[j][k] / new_matrix[i][k];
                        cout << new_matrix.normal_matrix_l(i,j,-buffer)<<endl<<endl;
                       
                       signal = k;
                       
                       break;
                   }
               }
               if (signal + 1 > 0)
               {
                   for (int k = signal; k < this->y; k++)
                   {
                       new_matrix[j][k] -= buffer * new_matrix[i][k];
                   }
               }
           continu: buffer=0;
               signal = -1;
           }
       }
       return new_matrix;
   }//与自动化简相似，输出中间左乘的所有初等矩阵，需要iostream库

/*
   matrix dfs(){
       if(this->root){

       }
       else{
            switch (this->leaf_way){
            case ADD:
                return dfs(this->leaf[0])+dfs(this->leaf[1]);
                break;
            case MINUS:
                return dfs(this->leaf[0])-dfs(this->leaf[1]);
                break;
            case MUTIPLY:
                return this->leaf[0]->dfs()*this->leaf[1]->dfs();
                break;
            case TRANS:
                return dfs(this->leaf[0].trans());
                break;
            case NUM_MUTIPLY:
                return this->leaf_num*dfs(this->leaf[0]);
                break;
            case MEAN:
                return this->leaf[0].mean();
                break;
            }
        }
    }

    /*
    matrix grad(double &fx){
        matrix<double> new_m;
        for (int i = 0; i < former.x; i++){
            for (int j = 0; i < former.y;j++){
                ;
            }
        }
        return new_m;
    }
    */
   
};



#endif