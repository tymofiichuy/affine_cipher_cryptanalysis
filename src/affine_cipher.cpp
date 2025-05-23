#include "affine_cipher.hpp"

using namespace std;

bool affine_cipher::validate_bigram(wchar_t* bigram, int size){
    if(bigram[0]<0x430||bigram[0]>0x44F){
        return false;
    }
    if(size == 1){
        return true;
    }
    if(bigram[1]<0x430||bigram[1]>0x44F){
        return false;
    }
    if(size == 2){
        return true;
    }
    return false;
}

int affine_cipher::wch_to_ind(wchar_t wch){
    //swap 26 and 27
    if(wch == 0x44B){
        return 27;
    }
    if(wch == 0x44C){
        return 26;
    }
    if(wch > 0x449){
        return wch-0x431;
    }
    else{
        return wch-0x430;
    }
}

wchar_t affine_cipher::ind_to_wch(int ind){
    //swap 26 and 27
    if(ind == 27){
        return static_cast<wchar_t>(0x44B);
    }
    if(ind == 26){
        return static_cast<wchar_t>(0x44C);
    }
    if(ind > 25){
        return static_cast<wchar_t>(ind+0x431);
    }
    else{
        return static_cast<wchar_t>(ind+0x430);
    }
}

void affine_cipher::set_key(int a, int b){
    if(modular_arithmetic::gcd(a, alphabet)!=1){
        throw runtime_error("Invalid key");
    }
    a_key = a;
    a_key_inverted = modular_arithmetic::invert(a, alphabet);
    b_key = b;
}

void affine_cipher::encrypt(string in_file, string out_file){
    wifstream instr(in_file);
    wofstream outstr(out_file);
    if(!instr || !outstr){
        throw runtime_error("Unable to open file");
    }
    instr.imbue(locale("en_US.UTF-8"));
    outstr.imbue(locale("en_US.UTF-8"));

    wchar_t wch[2];
    int size, bigram;
    while(true){
        instr.read(wch, 2);
        size = static_cast<int>(instr.gcount());
        if(size == 0){
            break;
        }

        if(!validate_bigram(wch, size)){
            continue;
        }

        else{
            if(size == 2){
                bigram = (a_key*(alphabet*wch_to_ind(wch[0])+wch_to_ind(wch[1]))+b_key)%mod;
                outstr << ind_to_wch(bigram/alphabet) << ind_to_wch(bigram%alphabet);
            }
            else if(size == 1){
                bigram = (a_key*wch_to_ind(wch[0])+b_key)%mod;
                outstr << ind_to_wch(bigram%alphabet);
            }
        }
    }
}

void affine_cipher::decrypt(string in_file, string out_file){
    wifstream instr(in_file);
    wofstream outstr(out_file);
    if(!instr || !outstr){
        throw runtime_error("Unable to open file");
    }
    instr.imbue(locale("en_US.UTF-8"));
    outstr.imbue(locale("en_US.UTF-8"));

    wchar_t wch[2];
    int size, bigram;
    while(true){
        instr.read(wch, 2);
        size = static_cast<int>(instr.gcount());
        if(size == 0){
            break;
        }

        if(!validate_bigram(wch, size)){
            continue;
        }
        
        else{
            if(size == 2){
                bigram = (modular_arithmetic::invert(a_key, mod)*modular_arithmetic::sub(alphabet*wch_to_ind(wch[0])+wch_to_ind(wch[1]), b_key, mod))%mod;
                outstr << ind_to_wch(bigram/alphabet) << ind_to_wch(bigram%alphabet);
            }
            else if(size == 1){
                bigram = (modular_arithmetic::invert(a_key, mod)*modular_arithmetic::sub(wch_to_ind(wch[0]), b_key, mod))%mod;
                outstr << ind_to_wch(bigram%alphabet);
            }
        }
    }
}