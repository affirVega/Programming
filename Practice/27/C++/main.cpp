#include <iostream>
#include <vector>
using namespace std;

#define if if(
#define for for(
#define print(A) cout<<A<<flush
#define println(A) cout<<A<<endl
#define input(N) (print(N),cin>>temp,temp)
#define vec vector<int64_t> vec

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
        
        for j = 0; j < 5 and j < vec.size(); ++j                                ){
            if value > vec[j]                                                   ){
                vec.insert(vec.begin() + j, value)                              ;
                break                                                           ;}}
                
        if j == 5 or j == vec.size()                                            ){
            vec.push_back(value)                                                ;}
            
        if vec.size() > 5                                                       ){
            vec.erase(vec.begin())                                              ;}
            
        for int i = 0; i < vec.size(); ++i                                      ){
            cout << vec[i] << ' '                                               ;}
            
        cout << endl                                                            ;}}


