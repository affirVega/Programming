//*
#include <iostream>
#include <vector>
//*/
using namespace std;
std::vector<int64_t> temp_vec;
int64_t temp;

#define map(Func, Iter) 	( 			\
		temp_vec.clear(),			\
		for (auto elem : Iter) {		\
			temp_vec.push_back(Func(elem));	\
		}, temp_vec 				\
	)
#define if 				if(
#define for 			for(
// __VA_OPT__(content) заменяется на content если __VA_ARGS__ не пустой
// __VA_ARGS__ аргументы, разделённые запятыми

// Как это работает: подставляется оператор и затем первый элемент из varargs.
// Если что-то есть в вараргах (первого элемента там нет), тогда запускаем ещё одну
// рекурсивную функцию и повторяем операцию.
// Нормальную рекурсию в дефайнах сделать не получается. Я гуглил, искал -- никто не смог.
#define RECURSIVE_0(operator, x)		operator x
#define RECURSIVE_1(operator, x, ...)	x __VA_OPT__( operator RECURSIVE_0(operator, __VA_ARGS__) )
#define RECURSIVE_2(operator, x, ...)	x __VA_OPT__( operator RECURSIVE_1(operator, __VA_ARGS__) )
#define RECURSIVE_3(operator, x, ...)	x __VA_OPT__( operator RECURSIVE_2(operator, __VA_ARGS__) )
#define RECURSIVE_4(operator, x, ...)	x __VA_OPT__( operator RECURSIVE_3(operator, __VA_ARGS__) )
#define RECURSIVE_5(operator, x, ...)	x __VA_OPT__( operator RECURSIVE_4(operator, __VA_ARGS__) )

#define print(x, ...)		cout << x __VA_OPT__( << RECURSIVE_5(<<, __VA_ARGS__)) << flush
#define println(x, ...) 	cout << x __VA_OPT__( << RECURSIVE_5(<<, __VA_ARGS__)) << endl
#define input(N) 			(print(N),cin>>temp,temp)
#define vec 				vector<int64_t> vec
#define len(P) 				P.size()
#define append 				push_back
#define insert(Index, Val) 	insert(vec.begin() + Index, Val)


// Как же я люблю программировать на Python++

int main()                                                                      {
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
                vec.insert(j, value)                                            ;
                break                                                           ;}}
                
        if j == 5 or j == len(vec)                                              ){
            vec.append(value)                                                   ;}
            
        if len(vec) > 5                                                         ){
            vec.erase(vec.begin())                                              ;}
            
        for int i = 0; i < len(vec); ++i                                        ){
            print(vec[i], ' ')                                                  ;}
            
        println(' ')                                                            ;}}


