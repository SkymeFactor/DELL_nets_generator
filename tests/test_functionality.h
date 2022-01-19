#pragma once
#include "test_suite.h"
#include "utilities.h"


std::set<Subnet> generate_n_random_subnets_fake(unsigned int N = 0) {
    return std::set<Subnet> {
        Subnet{IPv4("202.107.187.0"), 25},
        Subnet{IPv4("16.0.0.0"), 4},
        Subnet{IPv4("138.104.0.0"), 13},
        Subnet{IPv4("128.0.0.0"), 2},
        Subnet{IPv4("73.128.0.0"), 9},
        Subnet{IPv4("26.35.20.152"), 29},
        Subnet{IPv4("23.64.0.0"), 12},
        Subnet{IPv4("22.0.0.0"), 7},
        Subnet{IPv4("20.244.128.0"), 17},
        Subnet{IPv4("7.67.149.0"), 25},
    };
}


TEST_GROUP_START(TG_Functionality) {
    
    TEST_CASE_START(Narrow_Subnet_ip_zero) {

        std::set<Subnet> test_sample = generate_n_random_subnets_fake(10);
        Subnet parent_net{IPv4("0.0.0.0"), 32};
        
        for (int i = 31; i >= 0; --i) {
            parent_net.set_prefix(i);
            auto it = test_sample.find(parent_net);
            if (it != test_sample.end()) {
                parent_net = *it;
                break;
            }
        }

        ASSERT(parent_net.to_string() == std::string("0.0.0.0/0"));

    } TEST_CASE_END(),


    TEST_CASE_START(Narrow_Subnet_ip_max) {

        std::set<Subnet> test_sample = generate_n_random_subnets_fake(10);
        Subnet parent_net{IPv4("255.255.255.255"), 32};
        
        for (int i = 31; i >= 0; --i) {
            parent_net.set_prefix(i);
            auto it = test_sample.find(parent_net);
            if (it != test_sample.end()) {
                parent_net = *it;
                break;
            }
        }

        ASSERT(parent_net.to_string() == std::string("128.0.0.0/2"));

    } TEST_CASE_END(),


    TEST_CASE_START(Narrow_Subnet_ip_falls_in_few_subnets) {

        std::set<Subnet> test_sample = generate_n_random_subnets_fake(10);
        Subnet parent_net{IPv4("23.72.192.50"), 32};
        
        for (int i = 31; i >= 0; --i) {
            parent_net.set_prefix(i);
            auto it = test_sample.find(parent_net);
            if (it != test_sample.end()) {
                parent_net = *it;
                break;
            }
        }

        ASSERT(parent_net.to_string() == std::string("23.64.0.0/12"));

    } TEST_CASE_END(),


    TEST_CASE_START(Narrow_Subnet_ip_falls_out_of_list) {

        std::set<Subnet> test_sample = generate_n_random_subnets_fake(10);
        Subnet parent_net{IPv4("127.168.0.1"), 32};
        
        for (int i = 31; i >= 0; --i) {
            parent_net.set_prefix(i);
            auto it = test_sample.find(parent_net);
            if (it != test_sample.end()) {
                parent_net = *it;
                break;
            }
        }

        ASSERT(parent_net.to_string() == std::string("0.0.0.0/0"));

    } TEST_CASE_END(),


    TEST_CASE_START(Narrow_Subnet_ip_is_in_the_list) {

        std::set<Subnet> test_sample = generate_n_random_subnets_fake(10);
        Subnet parent_net{IPv4("26.35.20.152"), 29};
        
        for (int i = 31; i >= 0; --i) {
            parent_net.set_prefix(i);
            auto it = test_sample.find(parent_net);
            if (it != test_sample.end()) {
                parent_net = *it;
                break;
            }
        }

        ASSERT(parent_net.to_string() == std::string("26.35.20.152/29"));

    } TEST_CASE_END()

} TEST_GROUP_END();