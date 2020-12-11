#include <iostream>
#include <vector>
using namespace std;

#define if if(
#define for for(
#define print(A) cout<<A<<flush
#define println(A) cout<<A<<endl
#define input(N) (print(N),cin>>temp,temp)
#define vec vector<int64_t> vec
#define len(P) P.size()

// Как же я люблю программировать на Python++

int main()                                                                      {
    int64_t temp                                                                ;
    int64_t n = input("Введите число n: ")                                      ;
    int64_t value = input("Введите n чисел, разделённые пробелом:\n> ")         ;
    
    vec = {value}                                                               ;
    println(value)                                                              ;
                                                                                #undef vec
    for int64_t i = 1; i < n; ++i                                               ){
        cin >> value                                                            ;
        int j                                                                   ;
        
        for j = 0; j < 5 and j < len(vec); ++j                                  ){
            if value > vec[j]                                                   ){
                vec.insert(vec.begin() + j, value)                              ;
                break                                                           ;}}
                
        if j == 5 or j == len(vec)                                              ){
            vec.push_back(value)                                                ;}
            
        if len(vec) > 5                                                         ){
            vec.erase(vec.begin())                                              ;}
            
        for int i = 0; i < len(vec); ++i                                        ){
            print(vec[i]); print(' ')                                           ;}
            
        println(' ')                                                            ;}}


