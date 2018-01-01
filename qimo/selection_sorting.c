/*
 * @Author: songmingyu 
 * @Date: 2018-01-01 13:42:57 
 * @Last Modified by: songmingyu
 * @Last Modified time: 2018-01-01 13:54:32
 * yingying
 */


#include<stdio.h>

int main(){
    int number[10]={6,4,2,7,9,1,3,5,8,0};
    int min=0;
    for(int i=0;i<9;++i){
        min=i;
        for(int j=i;j<=9;++j){
            if(number[min]>number[j]){
                min=j;
            }
        }
        int temp=number[min];
        number[min]=number[i];
        number[i]=temp;
    }
    for(int i=0;i<10;++i){
        printf("%d ",number[i]);
    }
    return 0;
}