#include "test_suite.h"
#include "test_ip.h"
#include "test_subnet.h"

std::vector<TestGroup> gather_test_groups() {
	std::vector<TestGroup> my_tests;
	
	my_tests.push_back(TG_IPv4);
	my_tests.push_back(TG_Subnet);

	return my_tests;
}

TestStats run_tests(std::vector<TestGroup> tests) {
	size_t tests_passed = 0, tests_total = 0;
	for (auto it: tests) {
		auto result = it.run();
		tests_passed += result.passed;
		tests_total += result.total;
	}
	return TestStats{tests_passed, tests_total};
}

#ifdef DEBUG
	#include <cassert>
#endif

int main(int argc, char* argv[]) {
	auto stats = run_tests( gather_test_groups() );
	std::cout << "Passed: " << stats.passed << " of " << stats.total << " tests\n";


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

    return 0;
}