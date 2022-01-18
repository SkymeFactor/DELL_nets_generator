#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <any>


#define TEST_GROUP_START(group_name) TestGroup group_name(std::string(#group_name), std::vector<Test>
#define TEST_GROUP_END() );
#define TEST_CASE_START(test_name) Test(std::string(#test_name), [](std::any param)
#define TEST_CASE_END(...) __VA_ARGS__)
#define ASSERT(x) return x


std::any dummy_setup() {return nullptr;};
void dummy_teardown(std::any) {}


typedef struct {
    size_t passed;
    size_t total;
} TestStats;


class Test {
public:
    std::string test_name;
    std::function<bool(std::any)> test_func;
    std::function<std::any()> setup;
    std::function<void(std::any)> teardown;
    
    Test(std::string name, std::function<bool(std::any)> func, std::function<std::any()>
        setup_func = dummy_setup, std::function<void(std::any)> teardown_func = dummy_teardown):
            test_name(name), test_func(func), setup(setup_func), teardown(teardown_func) {};

};


class TestGroup {
private:
    std::string name;
    std::vector<Test> tests;
    size_t num_passed = 0;
public:

    TestGroup(std::string group_name, std::vector<Test> list_of_tests):
        name(group_name), tests(list_of_tests) {};

    TestStats run() {
        std::cout << "[========================] Running " << tests.size() << " tests from Test Group " << name << "\n";
        
        for (auto it: tests) {
            bool is_ok = false;
            std::any params = it.setup();
            
            try {
                is_ok = it.test_func(params);
            } catch (std::exception& e) {
                std::cerr << "\n[ ERROR ] Unhandled exception in test " << it.test_name << ": " << e.what() << '\n';
            }

            if (is_ok) {
                num_passed++;
                std::cout << "[ OK ] ";
            } else
                std::cout << "[ FAILED ] ";
            
            std::cout << "Test " << it.test_name << " has finished\n";
            it.teardown(params);
        }

        std::cout << "[------------------------] " << num_passed << " / " << tests.size() << " tests passed\n\n";
        return TestStats{num_passed, tests.size()};
    };

};
