#pragma once

#include<vector>
#include<cwchar>
#include<string>
#include<fstream>
#include<iostream>

class modular_arithmetic{
public:
    static int gcd(int a, int b);
    static int invert(int in, int mod);
    static void linear_congruence(int a, int b, int mod, std::vector<int>& x);
    static int add(int a, int b, int mod);
    static int sub(int a, int b, int mod);
};

class affine_cipher{
private:
    int alphabet = 31;
    int mod = alphabet*alphabet;
    int a_key;
    int a_key_inverted;
    int b_key;

    bool validate_bigram(wchar_t* bigram, int size);
    int wch_to_ind(wchar_t wch);
    wchar_t ind_to_wch(int ind);
public:
    void set_key(int a, int b); 
    void encrypt(std::string in_file, std::string out_file);
    void decrypt(std::string in_file, std::string out_file);
};