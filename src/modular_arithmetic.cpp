#include "affine_cipher.hpp"

using namespace std;

int modular_arithmetic::gcd(int a, int b){
    int r_curr = a, r_next = b, temp;
    while(r_next!=0){
        temp = r_next;
        r_next = r_curr%r_next;
        r_curr = temp;
    }
    return r_curr;
}

int modular_arithmetic::invert(int in, int mod){
    int r_curr = in, r_next = mod, u_curr = 1, u_next = 0, temp;
    while(r_next!=0){
        temp = u_next;
        u_next = u_curr-(r_curr/r_next)*u_next;
        u_curr = temp;
        temp = r_next;
        r_next = r_curr%r_next;
        r_curr = temp;
    }
    if(r_curr == 1){
        if(u_curr<0){
            return u_curr + mod;
        }
        else{
            return u_curr;            
        }
    }
    else{
        return 0;
    }
}

void modular_arithmetic::linear_congruence(int a, int b, int mod, std::vector<int>& x){
    int div = gcd(a, mod), x_0;
    if(div == 1){
        x.push_back((invert(a, mod)*b)%mod);
    }
    else{
        if(b%div==0){
            a = a/div;
            b = b/div;
            mod = mod/div;
            x_0 = (invert(a, mod)*b)%mod;
            for(int i = 0; i < div; i++){
                x.push_back(x_0+i*div);
            }
        }
    }
}

int modular_arithmetic::add(int a, int b, int mod){
    return (a+b)%mod;
}

int modular_arithmetic::sub(int a, int b, int mod){
    int temp = (a-b)%mod;
    if(temp>=0){
        return temp;
    }
    else{
        return temp + mod;
    }
}