#include <iostream>
#include <string>

// next week - p 2

std::string belaso_encrypt(const std::string& plaintext, const std::string& key) {
	std::string ciphertext;

	for (int i = 0; i < plaintext.size(); ++i) {
		char plain_char = plaintext[i];
		char key_char = key[i % key.size()];
		int cipher_char = plain_char + key_char - 'a' + 1;
		char cipher_true = (char) ((cipher_char > 'z') ? cipher_char - 'z' + 'a' - 2 : cipher_char);

		ciphertext += cipher_true;
	}

	return ciphertext;
}

std::string belaso_decrypt(const std::string& ciphertext, const std::string& key) {
	std::string plaintext;
	for (int i = 0; i < ciphertext.size(); ++i) {
		char plain_char = ciphertext[i];
		char key_char = key[i % key.size()];
		int cipher_char = plain_char - key_char + 'a' - 1;
		char cipher_true = (char) ((cipher_char < 'a') ? cipher_char + 'z' - 'a' + 2 : cipher_char);

		plaintext += cipher_true;
	}

	return plaintext;
}

int main() {
	std::string plaintext = "computational";
	std::string key = "cipher";

	std::string ciphertext = belaso_encrypt(plaintext, key);
	std::string decrypted = belaso_decrypt(ciphertext, key);

	std::cout << "Original Text: " << plaintext << std::endl;
	std::cout << "Encrypted Text: " << ciphertext << std::endl;
	std::cout << "Decrypted Text: " << decrypted << std::endl;

	return 0;
}
