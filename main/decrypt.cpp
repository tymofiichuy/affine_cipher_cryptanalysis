#include "affine_cipher.hpp"

using namespace std;

int main(){
    affine_cipher af;
    af.set_key(757, 518);
    af.decrypt("ciphertext.txt", "decrypted_text.txt");

    return 0;
}