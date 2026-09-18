#include "caeser.hpp"

int main(void){
    int key = gen_key();

    // standard iostream enc and dec
    std::string cipher_text = enc("mnemonic", key);
    std::cout << "Generated key: " << key << std::endl;
    std::cout << "Ciphertext: " << cipher_text << std::endl;
    std::cout << "Decrypted: " << dec(cipher_text, key) << std::endl;

    // iostream auto dec
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Auto Dec Results: " << std::endl;
    std::string plain_text = auto_dec(cipher_text);
    std::cout << "Decrypted: " << plain_text << std::endl;

    // file enc, dec
    std::string cipher_text_from_file = enc_file("TestFiles/enc_test.txt", key);
    std::ofstream out_file("TestFiles/dec_test.txt");
    out_file << cipher_text_from_file;
    out_file.close();
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Encrypted from enc_test file: " << cipher_text_from_file << std::endl;
    std::cout << "Decrypted from dec_test file: " << dec_file("TestFiles/dec_test.txt", key) << std::endl;
    
    // file autodec
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Auto Dec File Results: " << std::endl;
    std::string auto_plain_text_file = auto_dec_file("TestFiles/dec_test.txt");
    std::cout << "Auto Decrypted from file: " << auto_plain_text_file << std::endl;
    return 0;
}