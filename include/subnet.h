#pragma once
#include "ip.h"
#include <string>



class Subnet {
private:
	IPv4 _address;
	IPv4 _net_address;
	IPv4 _broadcast;
	int  _prefix = 0;
public:
    Subnet() = default;
	Subnet(const IPv4& address, const int prefix): _address{address} {
		set_prefix(prefix);
	};

	std::string to_string() const;
	IPv4 get_first_valid() const;
	IPv4 get_last_valid() const;
	int get_prefix() const;
	bool is_ip_within(const IPv4& address) const;

	bool operator<(const Subnet& net) const;
	bool operator==(const Subnet& net) const;

	void set_prefix(const int prefix);
};



std::string Subnet::to_string() const {
    std::string str{get_first_valid().to_string()};
    str.push_back('/');
    str.append(std::to_string(_prefix));
    return str;
}

IPv4 Subnet::get_first_valid() const {
	return _net_address;
}

IPv4 Subnet::get_last_valid() const {
	return _broadcast;
}

int Subnet::get_prefix() const {
	return _prefix;
}

bool Subnet::is_ip_within(const IPv4& address) const {
	return (address >= get_first_valid()) && (address <= get_last_valid());
}

bool Subnet::operator<(const Subnet& net) const {
	return net.get_first_valid() < this->get_first_valid();
}

bool Subnet::operator==(const Subnet& net) const {
	return (_prefix == net.get_prefix()) && (get_first_valid() == net.get_first_valid());
}

void Subnet::set_prefix(const int prefix) {
	uint32_t mask = 0xFFFFFFFF << (32 - prefix);
	_prefix = prefix;
	if (prefix == 0) {
		_net_address = IPv4(0);
		_broadcast = IPv4(0xFFFFFFFF);
	} else {
		_net_address = IPv4(_address & mask);
		_broadcast = IPv4(_address | ~mask);
	}
}
