#ifndef MATRIX
#define MATRIX//避免重引用，提高拓展性

#include <stdarg.h>//平时没人用这个库吧，不定参数用

#define DELTA 0.00000001//求导用

#define ADD 1
#define MINUS 2
#define MUTIPLY 3
#define TRANS 4
#define NUM_MUTIPLY 5//这个5其实没什么用但是暂时留着
#define MEAN 6
#define DETER 7

template <class T>
class matrix{
    private:
          int x, y;//xy不允许随意修改以防止未知问题
          matrix *new_m;

      public:
          int is_grad; //auto_grad因为grad功能的可能的bug还没有正式启用
          T **data;      //data是公共属性
          int isroot;   //在dfs寻找有向节点是判断是否为根
          matrix *leaf[2];//可能会存在两个父节点，DFS可以搜索到原节点
          int leaf_way; //dfs搜索时判断以何种方式搜索
          int leaf_num; //记录数乘时常数的值,很显然有重大bug,禁止使用


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
              is_grad = 0;
              isroot = 0;
              leaf[0] = NULL;
              leaf[1] = NULL;
              leaf_way = 0;
        }//构造函数，析构函数暂未写，考虑到是否还有更多元素加入类


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
    }//一种可行的输入流方式，但是注意fmt是自己输入的类型而非将要转换成的类型


    matrix operator+( matrix &b){
        //delete (new_m);
        /*********
         * 此处delete之后直接报错
         * 我没有理解此处为何不能delete new_m，等待答疑
         * *******/
        new_m = new matrix(b.x, b.y);
        if(this->x==b.x&&this->y==b.y){
            for (int i = 0; i < b.x;i++){
                for (int j=0;j<b.y;j++){
                    new_m->data[i][j] = this->data[i][j] + b.data[i][j];
                }
            }
        }      
        new_m->leaf[0] = this;
        new_m->leaf[1] = &b;
        new_m->leaf_way = ADD;
        return *new_m;
    }//矩阵加法重载


    matrix operator-( matrix &b){
        //matrix<T> new_m(b.x,b.y);
        new_m = new matrix(b.x, b.y, 0);
        if(this->x==b.x&&this->y==b.y){
            for (int i = 0; i < b.x;i++){
                for (int j=0;j<b.y;j++){
                    new_m->data[i][j] = this->data[i][j] - b.data[i][j];
                }
            }
        }

        new_m->leaf[0] = this;
        new_m->leaf[1] = &b;
        new_m->leaf_way = MINUS;

        return *new_m;
    }//矩阵减法重载
    //当两者不能相加时，未采用广播机制，而是输出加号后者同型，值全为0的数组

    template <typename mt>
    matrix operator*( mt b){
        new_m = new matrix(b.x, b.y, 0);
            for (int i = 0; i < this->x;i++){
                for (int j = 0; j < this->y;j++){
                    new_m->data[i][j] = this->data[i][j]*b;
                }
            }

        new_m->leaf[0] = this;
        new_m->leaf_num = b;
        new_m->leaf_way = NUM_MUTIPLY;

        return *new_m;
    }//矩阵的数乘，暂时不能使用，已经确定存在bug



     matrix operator*( matrix &b)  {
        new_m = new matrix(b.x, b.y, 0);
        if(this->y==b.x){
            for (int i = 0; i < this->x;i++){
                for (int j = 0; j < b.y;j++){
                    for (int v = 0; v < b.x; v++){
                        new_m->data[i][j] += this->data[i][v] * b.data[v][j];
                    }
                }
            }
        }

        new_m->leaf[0] = this;
        new_m->leaf[1] = &b;
        new_m->leaf_way = MUTIPLY;

        return *new_m;
    }//矩阵的乘法

    matrix clone(){
        new_m = new matrix(this->x, this->y);
        for (int i = 0; i < this->x;i++){
           for (int j = 0; j < this->y;j++){
               new_m->data[i][j] = this->data[i][j];
           }
        }

        return *new_m;
    }//矩阵的第一种赋值，通过缓存节点仅赋值data

    matrix* clone_link(){
        new_m = new matrix(this->x, this->y);
        for (int i = 0; i < this->x;i++){
           for (int j = 0; j < this->y;j++){
               new_m->data[i][j] = this->data[i][j];
           }
        }

        return new_m;
    }//矩阵第二种赋值,通过缓存节点仅赋值data，输出为指针


    matrix clone_same(){
       new_m = new matrix(this->x, this->y);
        for (int i = 0; i < this->x; i++){
           for (int j = 0; j < this->y;j++){
               new_m->data[i][j] = this->data[i][j];
           }
        }

        new_m->leaf[0] = this->leaf[0];
        new_m->leaf[1] = this->leaf[1];
        new_m->leaf_way = this->leaf_way;

        return *new_m;
    } //矩阵的第三种赋值，继承？通过缓存节点继承所有节点关系但是互不相干



    T* operator[](int num){
        return this->data[num];
    }//[]的重载，类比于数组，此处没有采用泄露警告，参考了c++中数组的越界使用


/**********
 下面的重载可能是天坑QAQ
 
 **********/

    void operator=(const matrix b){
       // delete (this->data);//大概不会内存泄漏吧
        delete data;
        data = new T *[b.x];
        for (int i = 0; i < b.x; i++) {
            data[i] = new T [b.y];
            for (int j = 0; j < b.y; j++){
                data[i][j] = 0;
            }
        }
        this->x = b.x;
        this->y = b.y;
       for (int i=0; i < this->x; i++)
       {
           for (int j=0; j < this->y; j++){
               this->data[i][j] = b.data[i][j];
            }
        }
        
        this->leaf[0] = b.leaf[0];
        this->leaf[1] = b.leaf[1];//值得一提的是，此处指针load了b.leaf储存的地址，因此b变化也不会影响this的值
        this->leaf_way = b.leaf_way;
    }//矩阵的第四种赋值，不依赖于任何缓存的赋值，直接load数据，不会因为缓存节点的变化而改变，建议与前三种配合使用


    //20.10.02未采用引用，因为此处不需要对b的值进行处理
    //20.10.14已经用new补正

    void format(T fmt){
        for (int i = 0; i < this->x;i++){
           for (int j = 0; j < this->y;j++){
               this->data[i][j] = fmt;
           }
        }
    } //格式化矩阵为任意数字


    matrix trans(){
        new_m = new matrix(this->y, this->x);
        for (int i = 0; i < this->y;i++){
           for (int j = 0; j < this->x;j++){
                new_m->data[i][j] = this->data[j][i];
            }
        }
        new_m->leaf[0] = this;
        new_m->leaf_way = TRANS;
        return *new_m;
    }//转置矩阵


   matrix leaft_m(int l_x,int l_y){
        new_m = new matrix(this->x - 1, this->y - 1);
        int b_x = 0, b_y = 0;
        for (int i = 0; i < this->x ;i++){
            if(i==l_x) {
                continue;
            }
            for (int j = 0; j < this->y ;j++){
                if(j==l_y){
                    continue;
                }
                new_m->data[b_x][b_y] = this->data[i][j];
                b_y++;
            }
            b_y = 0;//初始化是个好习惯
            b_x++;
        }
        return *new_m;
    }//代数余子式


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
    }


    matrix mean() {
        T sum;
        //matrix<T> new_matrix(1,1,0);
        new_m = new matrix(1, 1);
        for (int i = 0; i < this->x;i++){
            for (int j = 0; j < this->y;j++){
                sum += this->data[i][j];
            }
        }
        new_m->data[0][0] = (T)(sum/(this->x*this->y));
        new_m->leaf[0] = this;
        new_m->leaf_way = MEAN;
        return *new_m;
   }//mean是一个求均值函数，最后返回一个1x1的矩阵


#ifndef AUTO_PROCESS
   matrix auto_easify(){
       new_m = new matrix(this->x, this->y);
       new_m =this->clone_link();
       double buffer = 0;
       int signal = -1;

       for (int i = 0; i < this->x; i++)
       {
           for (int j = i + 1; j < this->x; j++)
           {
               for (int k = 0; k < this->y; k++)
               {
                   if (new_m->data[i][k] != 0)
                   {
                       if (new_m->data[j][k] == 0)
                       {
                           goto continu;
                       }
                       buffer = (double)new_m->data[j][k] / new_m->data[i][k];
                       signal = k;
                       break;
                   }
               }
               if (signal + 1 > 0)
               {
                   for (int k = signal; k < this->y; k++)
                   {
                       new_m->data[j][k] -= buffer * new_m->data[i][k];
                   }
               }
           continu: buffer=0;
               signal = -1;
           }
       }
       return *new_m;
   }//自动将矩阵化简为阶梯形并返回一个新矩阵
   //使用初等行变换
#endif
//宏控制选择是否开启过程，在include之前需要定义AUTO_PROCESS


    matrix normal_matrix_l(int line_1,int line_2,double mutiply){
        //matrix<T> new_matrix(this->x, this->x, 0);
        new_m = new matrix(this->x, this->y);
        for (int i = 0; i < this->x;i++){
            new_m->data[i][i] = 1;
        }
        new_m->data[line_2][line_1] = mutiply;
        return *new_m;
    }//根据母矩阵的x创造一个X * X的初等矩阵，即将line_1乘以mutiply加到line_2上去

#ifdef AUTO_PROCESS
    matrix auto_easify(){
       //matrix<T> new_matrix(this->x, this->y, 0);
       new_m = new matrix(this->x, this->y);
       new_m = this->clone_link();
       double buffer = 0;
       int signal = -1;
       for (int i = 0; i < this->x; i++)
       {
           for (int j = i + 1; j < this->x; j++)
           {
               for (int k = 0; k < this->y; k++)
               {
                   if (new_m->data[i][k] != 0)
                   {
                       if (new_m->data[j][k] == 0)
                       {
                           goto continu;
                       }
                       buffer = (double)new_m->data[j][k] / new_m->data[i][k];
                        cout << new_m->normal_matrix_l(i,j,-buffer)<<endl<<endl;
                       
                       signal = k;
                       
                       break;
                   }
               }
               if (signal + 1 > 0)
               {
                   for (int k = signal; k < this->y; k++)
                   {
                       new_m->data[j][k] -= buffer * new_m->data[i][k];
                   }
               }
           continu: buffer=0;
               signal = -1;
           }
       }
       return *new_m;
   }//与自动化简相似(但绝对不一样)，输出中间左乘的所有初等矩阵，需要iostream库
#endif


   matrix dfs(){
       /*****************************************************************
       *dfs()是一个被用于搜索节点并返回当前矩阵通过原来计算式重新计算的函数   *
       *可以视作指向一个数学上的函数表达式的指针                            *
       *dfs可以实时根据x取值的变化得到更新的函数值                          *
       *dfs通过每一个节点的leaf[]和leaf_way判断并向前读取，直到遇到根节点为止*
       ******************************************************************/
        matrix<T> buffer(1, 1, 0);
        matrix<T> new_x(1, 1, 0);
        matrix<T> b(1, 1, 0);
        //delete new_m;
        //依然没有想通为什么不能delete
        new_m = NULL;
        if (this->isroot)
        {
            return this->clone_same();
        }
       else{
            switch (this->leaf_way){

            case ADD:
                new_x = this->leaf[0]->dfs().clone_same();
                b = this->leaf[1]->dfs().clone_same();
                new_m = new matrix(b.x, b.y, 0);
                for (int i = 0; i < b.x; i++){
                    for (int j = 0; j < b.y; j++){
                        new_m->data[i][j] = new_x.data[i][j] + b.data[i][j];
                    }
                }
                return new_m->clone();


            case MINUS:
                new_x = this->leaf[0]->dfs().clone_same();
                b = this->leaf[1]->dfs().clone_same();
                new_m = new matrix(b.x, b.y, 0);
                for (int i = 0; i < b.x; i++){
                    for (int j = 0; j < b.y; j++){
                        new_m->data[i][j] = new_x.data[i][j] - b.data[i][j];
                    }
                }   
                return new_m->clone();


            case MUTIPLY:                
                new_x = this->leaf[0]->dfs().clone_same();
                b = this->leaf[1]->dfs().clone_same();
                new_m = new matrix(new_x.y, b.x, 0);
                for (int i = 0; i <b.x; i++){
                    for (int j = 0; j < b.y; j++){
                        for (int v = 0; v < b.x; v++) {
                            new_m->data[i][j] += new_x.data[i][v] * b.data[v][j];
                        }
                    }
                }   
                return new_m->clone();


            case TRANS:
                return this->leaf[0]->dfs().trans();


            case MEAN:
                return this->leaf[0]->dfs().mean();

            //deter需要特殊的格式才能够进入这个环节，所以尚未加入
            //此处num_mutiply没有加入，若有兴趣加入，可采用fx格式加入，但C++对模板的跨文件支持性差，所以做起来容错性低，有难度
            }
        }
        return buffer;
    }

    matrix auto_grad(matrix<T> &b){
        matrix<T> new_matrix(1,1,0);
        matrix<T> matrix_grad(b.x, b.y, 0);
        b.isroot = 1;//标记b为根节点
        new_matrix[0][0]=this->dfs().data[0][0];
        for (int i = 0; i < b.x;i++){
            for (int j = 0; j < b.y;j++){
                b[i][j] += DELTA;
                matrix_grad[i][j]=( this->dfs().data[0][0]-new_matrix[0][0] ) / DELTA;
                b[i][j] -= DELTA;
            }
        }
        b.isroot = 0;//取消b为根节点
        return matrix_grad;
    }
};



#endif