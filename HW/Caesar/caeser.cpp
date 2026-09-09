#include "caeser.hpp"

const std::string ALPHABET = " abcdefghijklmnopqrstuvwxyz";

int get_index(char c) {
    // this just to help map the chars to their numbers (makes sure we stay in our alphabet and dont get other ascii chars)
    if (c == ' ') return 0;
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (c >= 'a' && c <= 'z') return (c - 'a') + 1;
    return -1;
}

int score(char c){
    // basic freq analysis scoring function
    // theres prob better ways to do this (like taking into account structural aspects) but this does the trick for the most part
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        switch (c) {
            case '_': return 13;
            case 'e': return 12;
            case 't': return 11;
            case 'a': return 10;
            case 'o': return 9;
            case 'i': return 8;
            case 'n': return 7;
            case 's': return 6;
            case 'h': return 5;
            case 'r': return 4;
            case 'd': return 3;
            case 'l': return 3;
            case 'u': return 2;
            case 'c': return 2;
            case 'm': return 2;
            case 'f': return 2;
            case 'y': return 1;
            case 'w': return 1;
            case 'g': return 1;
            case 'p': return 1;
            case 'b': return 1;
            case 'v': return 1;
            case 'k': return 1;
            case 'x': return 0;
            case 'q': return 0;
            case 'j': return 0;
            case 'z': return 0;
            default:  return 0;
        }
    }
}

int gen_key(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return std::rand() % 27;
}

std::string enc(std::string plain_text, int key){
    std::string cipher_text = "";
    for (char c : plain_text){
        int index = get_index(c);
        if (index == -1) {
            cipher_text.push_back(c);
            continue;
        }
        int shifted_index = (index + key) % 27;
        cipher_text.push_back(ALPHABET.at(shifted_index));
    }
    return cipher_text;
}

std::string enc_file(std::string file_name, int key){
    //TODO: implement
    return "";
}

std::string dec(std::string cipher_text, int key){
    std::string plain_text = "";
    for (char c : cipher_text){
        int index = get_index(c);
        if (index == -1) {
            plain_text.push_back(c);
            continue;
        }
        int shifted_index = (index - key) % 27;
        // loop back around
        if (shifted_index < 0) {
            shifted_index += 27;
        }
        plain_text.push_back(ALPHABET.at(shifted_index));
    }
    return plain_text;
}

std::string dec_file(std::string file_name, int key){
    //TODO: implement
    return "";
}

std::string auto_dec(std::string cipher_text){
    std::string plain_text = "";
    std::string temp_plain_text = "";
    int best_key;
    int best_score = 0;
    for (int test_key = 0; test_key < 27; test_key++){
        int curr_score = 0;
        for (char c : cipher_text){
            int index = get_index(c);
            if (index == -1) {
                temp_plain_text.push_back(c);
                continue;
            }
            int shifted_index = (index - test_key) % 27;
            // loop back around
            if (shifted_index < 0) {
                shifted_index += 27;
            }
            curr_score = curr_score + score(ALPHABET.at(shifted_index));
            temp_plain_text.push_back(ALPHABET.at(shifted_index));
        }
        if (curr_score > best_score){
            best_score = curr_score;
            best_key = test_key;
            plain_text = temp_plain_text;
        }
        temp_plain_text.clear();
    }
    std::cout << "The best key found was: " << best_key << std::endl;
    std::cout << "With the score: " << best_score << std::endl;
    return plain_text;

}

