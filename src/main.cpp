#include <iostream>
#include "ip.h"
#include "subnet.h"
#include "utilities.h"


int main(int argc, char* argv[]) {

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