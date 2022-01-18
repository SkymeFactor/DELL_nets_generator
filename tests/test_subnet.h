#pragma once
#include "test_suite.h"
#include "subnet.h"


TEST_GROUP_START(TG_Subnet) {

    TEST_CASE_START(Get_subnet_prefix_valid) {

        const Subnet sb{IPv4("192.168.73.15"), 22};
        ASSERT(sb.get_prefix() == 22);

    } TEST_CASE_END(),


    TEST_CASE_START(Get_subnet_prefix_zero) {

        const Subnet sb{IPv4("192.168.73.15"), 0};
        ASSERT(sb.get_prefix() == 0);

    } TEST_CASE_END(),


    TEST_CASE_START(Get_subnet_prefix_max) {

        const Subnet sb{IPv4("192.168.73.15"), 32};
        ASSERT(sb.get_prefix() == 32);

    } TEST_CASE_END(),


    TEST_CASE_START(Get_subnet_prefix_invalid_big) {

        const Subnet sb{IPv4("192.168.73.15"), 1000};
        ASSERT(sb.get_prefix() == 32);

    } TEST_CASE_END(),


    TEST_CASE_START(Get_subnet_prefix_invalid_negative) {

        const Subnet sb(IPv4("192.168.73.15"), -1000);
        ASSERT(sb.get_prefix() == 32);

    } TEST_CASE_END(),
    
    
    TEST_CASE_START(Set_subnet_prefix_valid) {

        Subnet sb{IPv4("192.168.73.15"), 22};
        sb.set_prefix(16);
        ASSERT(sb.get_prefix() == 16);

    } TEST_CASE_END(),


    TEST_CASE_START(Set_subnet_prefix_zero) {

        Subnet sb{IPv4("192.168.73.15"), 22};
        sb.set_prefix(0);
        ASSERT(sb.get_prefix() == 0);

    } TEST_CASE_END(),


    TEST_CASE_START(Set_subnet_prefix_max) {

        Subnet sb{IPv4("192.168.73.15"), 22};
        sb.set_prefix(32);
        ASSERT(sb.get_prefix() == 32);

    } TEST_CASE_END(),


    TEST_CASE_START(Set_subnet_prefix_invalid_big) {

        Subnet sb{IPv4("192.168.73.15"), 22};
        sb.set_prefix(1000);
        ASSERT(sb.get_prefix() == 32);

    } TEST_CASE_END(),


    TEST_CASE_START(Set_subnet_prefix_invalid_negative) {

        Subnet sb{IPv4("192.168.73.15"), 22};
        sb.set_prefix(-1000);
        ASSERT(sb.get_prefix() == 32);

    } TEST_CASE_END(),


    TEST_CASE_START(Subnet_to_string_cast_with_valid_prefix) {

        const Subnet sb{IPv4("192.168.73.15"), 22};
        ASSERT(sb.to_string() == std::string("192.168.72.0/22"));

    } TEST_CASE_END(),
    

    TEST_CASE_START(Subnet_to_string_cast_with_prefix_zero) {
        
        const Subnet sb{IPv4("192.168.73.15"), 0};
        ASSERT(sb.to_string() == std::string("0.0.0.0/0"));

    } TEST_CASE_END(),
    

    TEST_CASE_START(Subnet_to_string_cast_with_prefix_max) {
        
        const Subnet sb{IPv4("192.168.73.15"), 32};
        ASSERT(sb.to_string() == std::string("192.168.73.15/32"));

    } TEST_CASE_END(),
    

    TEST_CASE_START(Subnet_to_string_cast_with_invalid_prefix_big) {
        
        const Subnet sb{IPv4("192.168.73.15"), 1000};
        ASSERT(sb.to_string() == std::string("192.168.73.15/32"));

    } TEST_CASE_END(),
    

    TEST_CASE_START(Subnet_to_string_cast_with_invalid_prefix_negative) {
        
        const Subnet sb(IPv4("192.168.73.15"), -1000);
        ASSERT(sb.to_string() == std::string("192.168.73.15/32"));

    } TEST_CASE_END(),


    TEST_CASE_START(First_valid_address_with_valid_prefix) {
        
        const Subnet sb{IPv4("192.168.73.15"), 22};
        ASSERT(sb.get_first_valid().to_string() == std::string("192.168.72.0"));

    } TEST_CASE_END(),


    TEST_CASE_START(First_valid_address_with_prefix_zero) {
        
        const Subnet sb{IPv4("192.168.73.15"), 0};
        ASSERT(sb.get_first_valid().to_string() == std::string("0.0.0.0"));

    } TEST_CASE_END(),


    TEST_CASE_START(First_valid_address_with_prefix_max) {
        
        const Subnet sb{IPv4("192.168.73.15"), 32};
        ASSERT(sb.get_first_valid().to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),


    TEST_CASE_START(First_valid_address_with_invalid_big_prefix) {
        
        const Subnet sb{IPv4("192.168.73.15"), 1000};
        ASSERT(sb.get_first_valid().to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),


    TEST_CASE_START(First_valid_address_with_invalid_negative_prefix) {
        
        const Subnet sb(IPv4("192.168.73.15"), -1000);
        ASSERT(sb.get_first_valid().to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),


    TEST_CASE_START(Last_valid_address_with_valid_prefix) {
        
        const Subnet sb{IPv4("192.168.73.15"), 22};
        ASSERT(sb.get_last_valid().to_string() == std::string("192.168.75.255"));

    } TEST_CASE_END(),


    TEST_CASE_START(Last_valid_address_with_prefix_zero) {
        
        const Subnet sb{IPv4("192.168.73.15"), 0};
        ASSERT(sb.get_last_valid().to_string() == std::string("255.255.255.255"));

    } TEST_CASE_END(),


    TEST_CASE_START(Last_valid_address_with_prefix_max) {
        
        const Subnet sb{IPv4("192.168.73.15"), 32};
        ASSERT(sb.get_last_valid().to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),


    TEST_CASE_START(Last_valid_address_with_invalid_big_prefix) {
        
        const Subnet sb{IPv4("192.168.73.15"), 1000};
        ASSERT(sb.get_last_valid().to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),


    TEST_CASE_START(Last_valid_address_with_invalid_negative_prefix) {
        
        const Subnet sb(IPv4("192.168.73.15"), -1000);
        ASSERT(sb.get_last_valid().to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),


    TEST_CASE_START(IP_is_within_subnet_boundaries_true) {
        
        const Subnet sb(IPv4("192.168.73.15"), 22);
        ASSERT(sb.is_ip_within(IPv4("192.168.73.15")));

    } TEST_CASE_END(),


    TEST_CASE_START(IP_is_within_subnet_boundaries_false) {
        
        const Subnet sb(IPv4("192.168.73.15"), 22);
        ASSERT(!sb.is_ip_within(IPv4("192.168.70.15")));

    } TEST_CASE_END(),


    TEST_CASE_START(IP_is_within_subnet_boundaries_on_the_lower_edge) {
        
        const Subnet sb(IPv4("192.168.73.15"), 22);
        ASSERT(sb.is_ip_within(IPv4("192.168.72.0")));

    } TEST_CASE_END(),


    TEST_CASE_START(IP_is_within_subnet_boundaries_on_the_higher_edge) {
        
        const Subnet sb(IPv4("192.168.73.15"), 22);
        ASSERT(sb.is_ip_within(IPv4("192.168.75.255")));

    } TEST_CASE_END(),


    TEST_CASE_START(Subnets_same_ip_equality_check_true) {
        
        const Subnet sb1(IPv4("192.168.73.15"), 22);
        const Subnet sb2(IPv4("192.168.73.15"), 22);
        ASSERT(sb1 == sb2);

    } TEST_CASE_END(),


    TEST_CASE_START(Subnets_same_ip_equality_check_false) {
        
        const Subnet sb1(IPv4("192.168.73.15"), 22);
        const Subnet sb2(IPv4("192.168.73.15"), 16);
        ASSERT(!(sb1 == sb2));

    } TEST_CASE_END(),


    TEST_CASE_START(Subnets_different_ip_equality_check_false) {
        
        const Subnet sb1(IPv4("192.168.73.15"), 22);
        const Subnet sb2(IPv4("73.15.192.168"), 22);
        ASSERT(!(sb1 == sb2));

    } TEST_CASE_END(),
    
    
    TEST_CASE_START(Subnets_less_than_true) {
        
        const Subnet sb1(IPv4("192.168.73.15"), 22);
        const Subnet sb2(IPv4("73.15.192.168"), 22);
        ASSERT(sb1 < sb2);

    } TEST_CASE_END(),


    TEST_CASE_START(Subnets_less_than_false) {
        
        const Subnet sb1(IPv4("73.15.192.168"), 22);
        const Subnet sb2(IPv4("192.168.73.15"), 22);
        ASSERT(!(sb1 < sb2));

    } TEST_CASE_END()

} TEST_GROUP_END()
