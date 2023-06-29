#include "CNum.h"
#include "cassert"

int main(){

    CNum num1;
    assert(num1.isNum("1432452"));
    assert(num1.isNum("   1  "));
    assert(!num1.isNum("\"PA2\""));

}