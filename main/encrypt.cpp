#include "affine_cipher.hpp"

using namespace std;

int main(){
    affine_cipher af;
    af.set_key(2, 3);
    af.encrypt("plaintext.txt", "ciphertext.txt");

    return 0;
}