#include "key_recovery.hpp"

using namespace std;

int main(){
    key_recovery kr;
    int a_key, b_key;
    kr.decrypt("ciphertext.txt", "out.txt", a_key, b_key);

    return 0;
}