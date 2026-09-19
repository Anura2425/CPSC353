#include "viginere.hpp"


int main(void){
    // change this if u wanna do a diff alphabet
    std::string alphabet = " abcdefghijklmnopqrstuvwxyz";

    // keygen
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Keygen Info:\n\n";
    int test_key_len = 3;
    std::string key = vigenere_generate_key(alphabet, test_key_len);
    std::cout << "  Key Length : " << test_key_len << "\n";
    std::cout << "  Generated Key    : \"" << key << "\"\n\n";

    // encode/decode
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Normal Encode Decode Test:\n\n";
    std::string plaintext = "Hello my name is Gavin this is a test for the viginere cipher to test if decoding and encoding works as intended";
    std::string encoded = vigenere_encode(key, plaintext, alphabet);
    std::string decoded = vigenere_decode(key, encoded, alphabet);
    std::cout << "  Original : \"" << plaintext << "\"\n";
    std::cout << "  Encoded  : \"" << encoded << "\"\n";
    std::cout << "  Decoded  : \"" << decoded << "\"\n\n";

    // auto decode
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Auto Decode Test:\n\n";
    std::string auto_decoded = viginere_auto_decode(encoded, alphabet);
    std::cout << "  Recovered Text: \"" << auto_decoded << "\"\n";

    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Auto Decode On ciphertext.txt Test:\n\n";
    // ciphertext.txt
    std::ifstream file("ciphertext.txt");
    if (file.is_open()) {
        std::string cipher_file_text((std::istreambuf_iterator<char>(file)),
                                      std::istreambuf_iterator<char>());
        file.close();
        std::string result = viginere_auto_decode(cipher_file_text, alphabet);
        std::cout << "\n--- Decoded Plaintext Result ---\n" << result << "\n";
    } else {
        std::cout << "ciphertext.txt not found\n";
    }
    return 0;
}