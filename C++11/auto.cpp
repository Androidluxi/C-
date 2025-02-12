//
// Created by lux on 25-1-17.
//

#include "keyword.h"

//C++11中，标准委员会赋予了auto全新的含义即：auto不再是一个存储类型指示符，而是作为一个新的类型指示符来指示编译器，auto声明的变量必
//须由编译器在编译时期推导而得。

int TestAuto() {
    return 10;
}

/**
 * auto 的定义
 * */
void test_1() {
    /* 使用auto定义变量时必须对其进行初始化，在编译阶段编译器需要根据初始化表达式来推导auto的实际类型*/
    /* 因此auto并非是一种“类型”的声明，而是一个类型声明时的“占位符”，编译器在编译期会将auto替换为变量实际的类型。 */
    int a = 10;
    auto b = a;
    auto c = 'a';
    auto d = TestAuto();
    //这里的typeid(b).name()是获取b的类型
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    //auto e; 无法通过编译，使用auto定义变量时必须对其进行初始化
}


/**
 * auto 与指针、引用
 * 用auto声明指针类型时，用auto和auto*没有任何区别，但用auto声明引用类型时则必须加&
 * */
void test_2() {
    int x = 10;
    auto a = &x;
    auto *b = &x;
    auto &c = x;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << "-----------------------" << endl;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    *a = 20;
    *b = 30;
    c = *a;
    cout << "-----------------------" << endl;
    cout << *a << endl;
    cout << &b << endl;
    cout << c << endl;
}

/*auto不能推导的场景*/
void test_3()
{
    auto a = 1, b = 2;
  //  auto c = 3, d = 4.0; // 该行代码会编译失败，因为c和d的初始化表达式类型不同

}

/*此处代码编译失败，auto不能作为形参类型，因为编译器无法对a的实际类型进行推导*/

// void TestAuto(auto a){}

// auto不能直接用来声明数组
void test_4()
{
    int a[] = {1,2,3};
   // auto b[] = {4，5，6};
}
//int main() {
//    // test_1();
//    // test_2();
//    // test_3();
//    return 0;
//}
