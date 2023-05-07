#include <iostream>
#include "person.h"

int main(int argc, char* argv[]){
    Person son {"tangbao"};
    std::cout<<son.getName()<<std::endl;
    son.setName("tangdou");
    std::cout<<son.getName()<<std::endl;
    return 0;
}