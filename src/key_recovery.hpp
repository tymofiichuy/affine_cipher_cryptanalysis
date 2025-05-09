#pragma once

#include<iostream>
#include<fstream>
#include<cwchar>
#include<string>
#include<vector>
#include<cmath>

class text_recognition{
private:
    float language_frequency[31] = {0.07453f, 0.01823f, 0.04068f, 0.02069f, 0.03384f, 0.08169f, 0.00917f, 0.01742f, 
                                    0.06970f, 0.01011f, 0.03134f, 0.05313f, 0.03348f, 0.06632f, 0.11582f, 0.02768f, 
                                    0.04733f, 0.05324f, 0.05676f, 0.02671f, 0.00267f, 0.01068f, 0.00281f, 0.01310f, 
                                    0.00815f, 0.00342f, 0.02084f, 0.02087f, 0.00473f, 0.00493f, 0.01991f};

    float index_of_coincidence(float* frequency);
public:
    static int wch_to_ind(wchar_t wch);
    bool recognize(std::string file, float threshold);
};

struct bigram{
    float frq;
    int first;
    int last;

    bigram(int i = 0, int j = 0, float freq = 0.0f);
};

class key_recovery{
private:
    int alphabet = 31;
    int mod = alphabet*alphabet;
    bigram frequency[31][31];
    bigram top_language_frequency[5] = {{17, 18, 0.01197f}, {13, 14, 0.01225f}, {18, 14, 0.01391f}, {13, 0, 0.01130f}, {5, 13, 0.00871f}};
public:
    void find_frequency(std::string file);
    void top_frequency(std::vector<bigram>& out);
    void decrypt(std::string in_file, std::string out_file, int& a_key, int& b_key, int skip);

    key_recovery();
};