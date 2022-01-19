#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <random>
#include "ip.h"
#include "subnet.h"



std::set<Subnet> generate_n_random_subnets(unsigned const int N) {
    std::random_device device;
    std::default_random_engine engine(device());
    std::uniform_int_distribution<uint32_t> dist_address(1, UINT32_MAX - 1);
    std::uniform_int_distribution<unsigned int> dist_prefix(1, 31);

    std::set<Subnet> n_random;
    
    while (n_random.size() < static_cast<size_t>(N)) {
        Subnet subnet{dist_address(engine), dist_prefix(engine)};
        n_random.insert(subnet);
    }

    return n_random;
}


std::pair<unsigned int, IPv4> read_input_file(const std::string& filename) {
	unsigned int N;
	std::string address;
	std::ifstream fin{filename};
    if (fin.fail()) {
        std::cerr << "Cannot open file with given filename\n";
        exit(1);
    }

	fin >> N;
	fin >> address;
	fin.close();
	
	return std::make_pair(N, IPv4(address));
}


std::ofstream& operator<<(std::ofstream& out, const std::set<Subnet>& vec) {
	for (auto it: vec) {
		out << it.to_string() << '\n';
	}
	out.seekp(-1, std::ios_base::end);
	return out;
}


template <class ...Args>
void write_output_file(const std::string& filename, const Args&... args) {
	std::ofstream fout {filename, std::ios_base::out};
    if (fout.fail()) {
        std::cerr << "Cannot save file\n";
        exit(1);
    }

	((fout << args << '\n'), ...);

	fout.close();
}