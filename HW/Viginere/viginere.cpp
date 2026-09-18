#include "viginere.hpp"

int get_index(char c) {
    if (c == ' ') return 0;
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (c >= 'a' && c <= 'z') return (c - 'a') + 1;
    return -1;
}

int score(char c){
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

    switch (c) {
        case ' ': return 13;
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

std::string vigenere_generate_key(std::string alphabet, int key_length){
    
    return "";
}
std::string vigenere_encode(std::string key, std::string plain_text){
    return "";
}
std::string vigenere_decode(std::string key, std::string cipher_text){
    return "";
}
std::string viginere_auto_decode(std::string cipher_text){
    return "";
}