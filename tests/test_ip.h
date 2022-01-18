#include "test_suite.h"
#include "ip.h"


TEST_GROUP_START(TG_IPv4) {
    
    TEST_CASE_START(IPv4_to_string_cast) {

        const IPv4 val{"192.168.73.15"};
        ASSERT(val.to_string() == std::string("192.168.73.15"));

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_to_uint32_t_cast) {
        
        const IPv4 val{"192.168.73.15"};
        ASSERT((uint32_t)val == 0xC0A8490F);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_constructors_equality_cast) {

        const IPv4 val1{"192.168.73.15"};
        const IPv4 val2{(uint32_t)val1};
        ASSERT((uint32_t)val1 == (uint32_t)val2);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_equality_test_positive) {

        const IPv4 val{"192.168.73.15"};
        ASSERT(val == val);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_equality_test_negative) {

        const IPv4 val1{"192.168.73.15"};
	    const IPv4 val2{"192.168.0.0"};
        ASSERT(val1 != val2);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_greater_then_positive) {

        const IPv4 val1{"192.168.73.15"};
	    const IPv4 val2{"192.168.0.15"};
        ASSERT(val1 > val2);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_greater_then_negative) {

        const IPv4 val1{"192.168.73.15"};
	    const IPv4 val2{"192.168.74.15"};
        ASSERT(!(val1 > val2));

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_less_then_positive) {

        const IPv4 val1{"192.168.0.15"};
	    const IPv4 val2{"192.168.73.15"};
        ASSERT(val1 < val2);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_less_then_negative) {

        const IPv4 val1{"192.168.74.15"};
	    const IPv4 val2{"192.168.73.15"};
        ASSERT(!(val1 < val2));

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_greater_then_zero) {

        const IPv4 val1{"192.168.73.15"};
	    const IPv4 val2{"0.0.0.0"};
        ASSERT(val1 > val2);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_less_then_maximum) {

        const IPv4 val1{"192.168.0.1"};
	    const IPv4 val2{"255.255.255.255"};
        ASSERT(val1 < val2);

    } TEST_CASE_END(),

    TEST_CASE_START(IPv4_assignment_test) {

        const IPv4 val1{"192.168.0.1"};
	    const IPv4 val2 = val1;
        ASSERT(val1 == val2);

    } TEST_CASE_END()

} TEST_GROUP_END()
