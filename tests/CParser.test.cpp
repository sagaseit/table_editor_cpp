#include "CParser.h"

#include <cassert>

int main(){
    CParser p1;
    assert(!p1.commands_only("EXIT"));
}