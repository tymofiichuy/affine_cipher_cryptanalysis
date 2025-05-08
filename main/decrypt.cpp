#include "affine_cipher.hpp"

using namespace std;

int main(){
    affine_cipher af;
    af.set_key(2, 3);
    af.decrypt("ciphertext.txt", "decrypted_text.txt");

    return 0;
}