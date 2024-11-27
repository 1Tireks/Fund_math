#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstddef>

class RC4 {
private:
    std::vector<std::byte> S;
    int x;
    int y;

    void init(const std::vector<std::byte>& key);

public:
    RC4(const std::vector<std::byte>& key) : S(256), x(0), y(0) {
        init(key);
    }

    std::byte generate_byte();
};

class encoder {
private:
    std::vector<std::byte> key_;
public:
    encoder(const std::vector<std::byte>& key) : key_(key) {}

    void encode(const std::string& input_file, const std::string& output_file, bool is_encrypt);

    void set_key(const std::vector<std::byte>& key) {
        key_ = key;
    }
};

void RC4::init(const std::vector<std::byte>& key) {
    if (key.empty()) {
        std::cerr << "Ключ не может быть пустым\n";
        return;
    }

    for (int k = 0; k < 256; ++k) {
        S[k] = static_cast<std::byte>(k);
    }

    int j = 0;
    for (int k = 0; k < 256; ++k) {
        j = (j + static_cast<int>(S[k]) + static_cast<int>(key[k % key.size()])) % 256;
        std::swap(S[k], S[j]);
    }

    x = 0; // необходимо если будем изменять ключ
    y = 0; // необходимо если будем изменять ключ
}

std::byte RC4::generate_byte() {
    x = (x + 1) % 256;
    y = (y + static_cast<int>(S[x])) % 256;
    std::swap(S[x], S[y]);

    return S[(static_cast<int>(S[x]) + static_cast<int>(S[y])) % 256];
}

void encoder::encode(const std::string& input_file, const std::string& output_file, bool is_encrypt) {
    std::ifstream infile(input_file, std::ios::binary);
    if (!infile) {
        std::cerr << "Не удалось открыть входной файл\n";
        return;
    }

    std::ofstream outfile(output_file, std::ios::binary);
    if (!outfile) {
        std::cerr << "Не удалось открыть выходной файл\n";
        infile.close();
        return;
    }

    RC4 rc4(key_);

    char byte;
    while (infile.get(byte)) {
        std::byte keystream_byte = rc4.generate_byte();
        byte ^= static_cast<char>(keystream_byte);
        outfile.put(byte);
    }

    infile.close();
    outfile.close();
}

int main() {
    std::vector<std::byte> key1 = {std::byte{0x1}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5}, std::byte{0x2}, std::byte{0x3}, std::byte{0x4}, std::byte{0x5}};
    encoder _secret(key1);

    _secret.encode("input.txt", "encrypted.txt", true);
    _secret.encode("encrypted.txt", "decrypted.txt", false);

    return 0;
}