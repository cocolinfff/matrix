template<class T>
class matrix{
    private:
        ;

    public:
        int x, y;
        T **data;//暂时把属性作为公共属性，可能不会调整

        matrix(int in_x, int in_y,T first=0)
        {
            x = in_x;
            y = in_y;
            data = new T *[x];
            for (int i = 0; i < x;i++){
                data[i] = new T[y];
                for (int j = 0; j < y;j++){
                    data[i][j] = first;
                }
            }
  //          data[0][0] = first;
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

    matrix operator+(const matrix &b){
        matrix<T> new_m(b.x,b.y);
        if(this->x==b.x&&this->y==b.y){
            for (int i = 0; i < b.x;i++){
                for (int j=0;j<b.y;j++){
                    new_m.data[i][j] = this->data[i][j] + b.data[i][j];
                }
            }
        }
     //   else
     //       cout << "error!\n";
        return new_m;
    }//矩阵加法重载


    matrix operator-(const matrix &b){
        matrix<T> new_m(b.x,b.y);
        if(this->x==b.x&&this->y==b.y){
            for (int i = 0; i < b.x;i++){
                for (int j=0;j<b.y;j++){
                    new_m.data[i][j] = this->data[i][j] - b.data[i][j];
                }
            }
        }
        else
            cout << "error!\n";//这是报错警告，此处屏蔽掉，若有需要可打开
        return new_m;
    }//矩阵减法重载
    //当两者不能相加时，未采用广播机制，而是输出加号后者同型，值全为0的数组


    matrix operator*(const matrix &b){
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
        else
            cout << "error!"<<endl;
        return new_m;
    }//矩阵的乘法，bug待定

    matrix clone(){
        matrix<T> new_m(this->x,this->y,0);
        for (int i = 0; i < this->y;i++){
           for (int j = 0; j < this->x;j++){
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
    int deter(){
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
    
};

