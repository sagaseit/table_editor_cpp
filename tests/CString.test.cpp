#include "CString.h"

#include <cassert>

int main(){

    CString s1;
    assert(s1.removeQuotes("\"PA2\"") == "PA2");
    assert(s1.removeQuotes("""") == "");
}