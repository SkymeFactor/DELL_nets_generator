#include "test_suite.h"
#include "test_ip.h"
#include "test_subnet.h"
#include "test_utilities.h"
#include "test_functionality.h"

std::vector<TestGroup> gather_test_groups() {
	std::vector<TestGroup> my_tests;
	
	my_tests.push_back(TG_IPv4);
	my_tests.push_back(TG_Subnet);
	my_tests.push_back(TG_Utilities);
	my_tests.push_back(TG_Functionality);

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


int main(int argc, char* argv[]) {
	auto stats = run_tests( gather_test_groups() );
	std::cout << "Passed: " << stats.passed << " of " << stats.total << " tests\n";

    return 0;
}