#include <iostream>
#include "ip.h"
#include "subnet.h"
#include "utilities.h"

#ifdef DEBUG
	#include <cassert>
#endif

int main(int argc, char* argv[]) {
	// TESTS
	#ifdef DEBUG
	const IPv4 a1{"192.168.73.15"};
	const IPv4 a2{"192.168.0.0"};
	const IPv4 a3{"191.168.0.1"};

	// IPv4 tests ------------------------------------------------------
	
	assert((a1.to_string() == std::string("192.168.73.15")) && "String cast TEST");
	assert(((uint32_t)a1 == 0xC0A8490F) && "uint32_t cast TEST");

	assert((a1 == a1) && "Equality TEST");
	assert((a1 > a2) && "Greater than in same byte TEST");
	assert((a2 < a1) && "Less than in same byte TEST");
	assert((a1 > a3) && "Greater than in different byte TEST");
	assert((a3 < a1) && "Less than in different byte TEST");

	const IPv4 a4 = a1;
	assert((a4 == a1) && "Assignment TEST");

	std::cout << "[ OK ] IPv4 tests\n";

	// Subnet tests ----------------------------------------------------

	const Subnet sb{IPv4("192.168.73.15"), 22};

	assert((sb.to_string() == std::string("192.168.72.0/22")) && "String cast TEST");
	assert((sb.get_first_valid().to_string() == std::string("192.168.72.0")) && "First valid address TEST");
	assert((sb.get_last_valid().to_string() == std::string("192.168.75.255")) && "Last valid address TEST");
	assert(sb.is_ip_within(IPv4("192.168.73.15")) && "IP is inside of subnet boundaries TEST");
	assert(!sb.is_ip_within(IPv4("192.168.70.15")) && "IP is outside of subnet boundaries TEST");
	assert(sb.is_ip_within(IPv4("192.168.75.255")) && "IP is on the subnet boundaries TEST");
	Subnet sb1{IPv4("192.168.73.15"), 22};
	sb1.set_prefix(16);
	assert((sb1.to_string() == std::string("192.168.0.0/16")) && "Subnet prefix decremental change TEST");
	sb1.set_prefix(26);
	assert((sb1.to_string() == std::string("192.168.73.0/26")) && "Subnet prefix incremental change TEST");
	sb1.set_prefix(0);
	assert((sb1.to_string() == std::string("0.0.0.0/0")) && "Subnet with prefix zero (special case) TEST");

	std::cout << "[ OK ] Subnet tests\n";

	#endif // DEBUG

	std::string in_filename {""};
	std::string out_filename{"/data/out.txt"};	
	std::string gen_filename{"/data/autogen.txt"};
	
	if (argc > 1) {
		in_filename = argv[1];
	}
	
	auto input = read_input_file(in_filename);
	int N = input.first;
	IPv4 address_in_file = input.second;
	std::cout << "N = " << N << "; IP = " << address_in_file.to_string() << '\n';
	
	std::set<Subnet> subnets = generate_n_random_subnets(N);
	Subnet parent_net{address_in_file, 32};

	for (int i = 31; i >= 0; --i) {
		parent_net.set_prefix(i);
		auto it = subnets.find(parent_net);
		if (it != subnets.end()) {
			parent_net = *it;
			break;
		}
	}

	std::cout << "The most narrow subnet, containing given address is: " << parent_net.to_string() << '\n';

	write_output_file(out_filename, address_in_file.to_string(), parent_net.to_string());
	write_output_file(gen_filename, subnets);


	return 0;
}