#pragma once
#include <filesystem>
#include "test_suite.h"
#include "utilities.h"
#include "ip.h"


TEST_GROUP_START(TG_Utilities) {

    TEST_CASE_START(Read_input_file_true) {
        // Setup
        std::string fname{"test.txt"};
        std::ofstream fout(fname);
        std::pair<int, IPv4> test_sample{10, IPv4("1.2.3.4")};
        
        if (fout.fail()) {
            throw(std::runtime_error("Cannot create test file - Test ignored"));
        }
        fout << test_sample.first << '\n' << test_sample.second.to_string();
        fout.close();

        // Act
        std::pair<int, IPv4> read_sample = read_input_file(fname);

        // Teardown
        std::filesystem::remove(fname);
        
        ASSERT(test_sample.first == read_sample.first && test_sample.second == read_sample.second);
    } TEST_CASE_END(),


    TEST_CASE_START(Write_output_file_from_empty_set_true) {
        // Setup
        std::string fname{"test.txt"};
        std::set<Subnet> test_sample;
        
        // Act
        write_output_file(fname, test_sample);
        bool is_ok = std::filesystem::is_empty(fname);

        // Teardown
        std::filesystem::remove(fname);

        ASSERT(is_ok);
    } TEST_CASE_END(),


    TEST_CASE_START(Write_output_file_from_Subnet_true) {
        // Setup
        std::string fname{"test.txt"};
        Subnet test_sample{IPv4("1.2.3.4"), 10};
        std::ifstream fin;
        std::string temp;
        
        // Act
        write_output_file(fname, test_sample.to_string());
        fin.open(fname);
        if (fin.fail()){
            throw(std::runtime_error("Cannot read from created test file - Test ignored"));
        }
        fin >> temp;
        fin.close();

        // Teardown
        std::filesystem::remove(fname);

        ASSERT(temp == test_sample.to_string());
    } TEST_CASE_END(),


    TEST_CASE_START(Write_output_file_from_full_set_true) {
        // Setup
        std::string fname{"test.txt"};
        std::set<Subnet> test_sample{
            Subnet{IPv4("1.2.3.4"), 10},
            Subnet{IPv4("5.6.7.8"), 22},
            Subnet{IPv4("9.10.11.12"), 16},
            Subnet{IPv4("16.15.14.13"), 30}
        };
        std::ifstream fin;
        bool is_ok = true;
        std::string temp;
        
        // Act
        write_output_file(fname, test_sample);
        fin.open(fname);
        if (fin.fail()){
            throw(std::runtime_error("Cannot read from created test file - Test ignored"));
        }

        for (auto it: test_sample) {
            fin >> temp;
            is_ok &= (temp == it.to_string());
        }        
        fin.close();

        // Teardown
        std::filesystem::remove(fname);

        ASSERT(is_ok);
    } TEST_CASE_END(),


    TEST_CASE_START(Generate_zero_subnets_true) {

        ASSERT(generate_n_random_subnets(0).size() == 0);

    } TEST_CASE_END(),


    TEST_CASE_START(Generate_some_subnets_true) {

        ASSERT(generate_n_random_subnets(10).size() == 10);

    } TEST_CASE_END()

} TEST_GROUP_END();