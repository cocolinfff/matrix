
#include"matrix.h"
#include"fx_matrix.h"
template<class T>
  matrix<T> matrix<T>::mean(){
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
    }




//maybe这个cpp是用来连接两个.h的桥梁
//一切matrix中要用到fx的函数都在此处定义