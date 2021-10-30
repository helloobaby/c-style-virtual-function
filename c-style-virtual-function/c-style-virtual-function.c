#include<stdio.h>

struct base
{
    void** vptr;
};

struct son1
{
    struct base;
};

void base_print()
{
    printf("I am %s\n",__func__);
}

void son1_print()
{
    printf("I am %s\n",__func__);
}

//
//父类的虚函数表
//
const void (*RTTI[])(void)=
{
    base_print
};

//
//子类的虚函数表
//编译器先将父类的拷贝，然后子类有重写的函数再在表中替换为子类的
//
void (*RTTI2[])(void) =
{
    son1_print//instead of base_print
};

int main()
{
    struct base* ptr;
    struct son1 test_son;
    struct base test_base;  

    test_son.vptr = RTTI2;
    test_base.vptr = RTTI;

    ptr = &test_son;
    ((void(*)(void))(*(ptr->vptr)))();
    ptr = &test_base; 
    ((void(*)(void))(*(ptr->vptr)))();

}

