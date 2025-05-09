#include "key_recovery.hpp"
#include "affine_cipher.hpp"

using namespace std;

// int text_recognition::wch_to_ind(wchar_t wch){
//     if(wch > 0x449){
//         return wch-0x431;
//     }
//     else{
//         return wch-0x430;
//     }
// }

int text_recognition::wch_to_ind(wchar_t wch){
    if(wch > 0x449){
        return wch-0x431;
    }
    //swap 26 and 27
    if(wch == 0x44B){
        return 27;
    }
        if(wch == 0x44C){
        return 26;
    }
    else{
        return wch-0x430;
    }
}

float text_recognition::index_of_coincidence(float* frequency){
    float index = 0;
    for(int i = 0; i < 31; i++){
        index += frequency[i]*frequency[i];
    }
    return index;
}

bool text_recognition::recognize(string file, float threshold){
    float text_frequency[31] = {}, language_index = index_of_coincidence(language_frequency), text_index;

    wifstream instr(file);
    if(!instr){
        throw runtime_error("Unable to open file");
    }
    instr.imbue(locale("en_US.UTF-8"));

    wchar_t wch;
    int counter = 0;
    while(instr.read(&wch, 1)){
        if(wch<0x430||wch>0x44F){
            continue;
        }
        else{
            counter++;
            text_frequency[wch_to_ind(wch)]++;
        }
    }
    for(int i = 0; i < 31; i++){
        text_frequency[i]/=counter;
    }

    text_index = index_of_coincidence(text_frequency);
    if(abs(language_index-text_index)<threshold){
        return true;
    }
    else{
        return false;
    }
}

bigram::bigram(int i, int j, float freq):first(i),last(j),frq(freq){};

key_recovery::key_recovery(){
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 31; j++){
            frequency[i][j] = bigram(i, j);
        }
    }
}

void key_recovery::find_frequency(string file){
    wifstream instr(file);
    if(!instr){
        throw runtime_error("Unable to open file");
    }
    instr.imbue(locale("en_US.UTF-8"));

    wchar_t wch[2];
    int counter = 0;
    while(instr.read(wch, 2)){
        counter++;
        frequency[text_recognition::wch_to_ind(wch[0])][text_recognition::wch_to_ind(wch[1])].frq++;
    }
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 31; j++){
            frequency[i][j].frq/=counter;
        }
    }
}

void key_recovery::top_frequency(vector<bigram>& out){
    out.clear();
    for(int i = 0; i < 5; i++){
        bigram temp;
        out.push_back(temp);
    }
    for(int i = 0; i < 31; i++){
        for(int j = 0; j < 31; j++){
            if(frequency[i][j].frq>out[4].frq){
                out[4] = frequency[i][j];
                for(int k = 3; k >= 0; k--){
                    if(out[k].frq<out[k+1].frq){
                        swap(out[k], out[k+1]);
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
}

void key_recovery::decrypt(std::string in_file, std::string out_file, int& a_key, int& b_key, int skip){
    find_frequency(in_file);
    vector<bigram> top;
    vector<int> solution;
    top.reserve(5);
    top_frequency(top);

    int flag = 0;

    affine_cipher af;
    text_recognition tr;
    int x_sub, y_sub;
    for(int i_0 = 0; i_0 < 5; i_0++){
        for(int j_0 = i_0+1; j_0 < 5; j_0++){
            for(int i_1 = 0; i_1 < 5; i_1++){
                for(int j_1 = i_1+1; j_1 < 5; j_1++){
                    //cout << "1";
                    x_sub = modular_arithmetic::sub(top_language_frequency[i_0].first*31+top_language_frequency[i_0].last, top_language_frequency[j_0].first*31+top_language_frequency[j_0].last, mod);
                    y_sub = modular_arithmetic::sub(top[i_1].first*31+top[i_1].last, top[j_1].first*31+top[j_1].last, mod);
                    //cout << "2";
                    solution.resize(0);
                    modular_arithmetic::linear_congruence(x_sub, y_sub, mod, solution);
                    //cout << "3";
                    for(vector<int>::iterator iter = solution.begin(); iter != solution.end(); iter++){
                        //cout << "4";
                        b_key = modular_arithmetic::sub((top[i_1].first*31+top[i_1].last), *iter*(top_language_frequency[i_0].first*31+top_language_frequency[i_0].last), mod);
                        try{
                            af.set_key(*iter, b_key);
                        }
                        catch(runtime_error err){
                            continue;
                        }
                        //cout << "5";
                        af.decrypt(in_file, out_file);
                        //cout << "6";
                        if(tr.recognize(out_file, 0.005f)){
                            if(flag >= skip){
                                a_key = *iter;
                                //cout << i_0 << " " << j_0 << "  " << i_1 << " " << j_1;
                                return;                                
                            }
                            else{
                                flag++;
                            }
                        }
                    }
                }
            }
        }
    }
}