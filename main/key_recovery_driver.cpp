#include "key_recovery.hpp"

using namespace std;

int main(){
    key_recovery kr;
    int a_key = 0, b_key = 0;
    kr.decrypt("ciphertext.txt", "out.txt", a_key, b_key, 0);
    cout << "Key: " << a_key << " " << b_key;

    return 0;
}