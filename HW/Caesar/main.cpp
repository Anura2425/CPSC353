#include "caeser.hpp"

int main(void){
    int key = gen_key();
    std::string cipher_text = enc("the pantsless man fears not the pickpocket", key);
    std::cout << "Generated key: " << key << std::endl;
    std::cout << "Ciphertext: " << cipher_text << std::endl;
    std::cout << "Decrypted: " << dec(cipher_text, key) << std::endl;

    //auto dec
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Auto Dec Results: " << std::endl;
    std::string plain_text = auto_dec(cipher_text);
    std::cout << "Decrypted: " << plain_text << std::endl;
    return 0;
}