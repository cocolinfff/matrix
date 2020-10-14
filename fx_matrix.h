#ifndef FX_MATRIX
#define FX_MATRIX
#include"matrix.h"



template<class mt>
//template<class mt>
class matrix;
template<class mt>

class fx{
    public:
    double data;
    matrix<mt> *leaf[2];
    int leaf_way;

    void operator=(matrix<mt> &b){
        this->data = b.data[0][0];
        this->leaf[0] = b.leaf[0];
        this->leaf[1] = b.leaf[1];
        //leaf_way = 1;
        
    }
    /*
    double dfs(matrix<mt> &b){
        switch (b.leaf_way){
            case ADD:
                return dfs(b.leaf[0])+dfs(b.leaf[1]);
                break;
            case MINUS:
                return dfs(b.leaf[0])-dfs(b.leaf[1]);
                break;
            case MUTIPLY:
                return dfs(b.leaf[0])*dfs(b.leaf[1]);
                break;
            case TRANS:
                return dfs(b.leaf[0].trans());
                break;
            case NUM_MUTIPLY:
                return dfs(b.leaf[0] *b.leaf_num);
                break;
            case MEAN:
                return b.leaf[0].mean();
                break;
        }
    }
    */

   
};
#endif