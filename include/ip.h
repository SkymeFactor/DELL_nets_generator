#pragma once
#include <string>
#include <sstream>



class IPv4 {
public:
	uint32_t data = 0;
public:
	IPv4() = default;
	IPv4(const uint32_t address);
	explicit IPv4(const std::string& str);

	IPv4& operator=(const IPv4& address) = default;
    bool operator<(const IPv4& address) const;
    bool operator==(const IPv4& address) const;
    bool operator>(const IPv4& address) const;
	std::string to_string() const;
    operator uint32_t() const;
};



IPv4::IPv4(const uint32_t address) {
    data = address;
}

IPv4::IPv4(const std::string& str) {
    std::istringstream ss{str};
    std::string tmp = "";
    try {
        for (int i = 3; i >= 0; i--) {
            std::getline(ss, tmp, '.');
            this->data |= static_cast<unsigned char>(std::stoi(tmp)) << i * 8;
        }
    } catch (std::exception& e) {
        std::cerr << "Unable to read ip address: " << e.what() << '\n';
    }
}

bool IPv4::operator<(const IPv4& address) const {
    return this->data < address.data;
}

bool IPv4::operator==(const IPv4& address) const {
    return this->data == address.data;
}

bool IPv4::operator>(const IPv4& address) const {
    return this->data > address.data;
}

std::string IPv4::to_string() const {
    std::string str;

    for (int i = 3; i >= 0; i--) {
        str.append(std::to_string((data >> i * 8) & 0xFF));
        str.push_back('.');
    }
    str.pop_back(); // Remove the trailing dot

    return str;
}

IPv4::operator uint32_t() const {
    return data;
}