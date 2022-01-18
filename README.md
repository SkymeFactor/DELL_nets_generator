### Task:
1. Generate N random subnets (i.e. “a.b.c.d/prefix”). N - configurable parameter.
2. For a given IPv4 address select the most narrow subnet from previously generated.

Input file structure (N, IPv4):
```
$ cat in.txt
10
1.2.3.4
```
Output file structure (input IPv4, subnet IPv4):
```
$ cat out.txt
1.2.3.4
1.2.3.0/24
```
Generated subnets are written into `autogen.txt`:
```
$ cat autogen.txt
10.20.0.0/16
1.2.3.0/24
```
### Build
The Solution is pre-built inside a docker container, in order to run it follow the instructions:
```
$ ls data/
in.txt
$ docker run -v `pwd`/data:/data skymefactor/subnet_gen:latest
$ echo $?
0
$ ls data/
in.txt out.txt autogen.txt
$
```
Or, it can be built from the project root, like shown below:
```
$ make
$ ./tools/run_docker.sh
```
### Tests
Unit tests can be built and performed by specifying the `test` target to the make command and 
thereafter executing resulting binary as follows:
```
$ make test
$ ./build/test_subnet_gen.elf
```
This target is disabled by default.

All tests are created with the `test_suite.h `, which is a self-made easy-to-use microframework. Tests' structure
follows the pattern in example below:
```
TEST_GROUP_START(group_name) {
    TEST_CASE_START(test_case_name_1) {
        // Actual test case
        ASSERT(true);
    } TEST_CASE_END(),

    TEST_CASE_START(test_case_name_2) {
        bool is_ok = false;
        // Actual test case
        ASSERT(is_ok == std::any_cast<bool>(param));
    } TEST_CASE_END(,std::any (*setup_function)(),[](std::any) {}),
} TEST_GROUP_END();
```
Important to notice that the starting comma is necessary when applying `setup` and `teardown` functions (in exact same order). Aforementioned functions might be useful as far as the returned value from setup is passed through the test-case as a parameter and then into teardown where it can be safely destroyed or whatever useful. For each test-case these functions are called individually. Inside a test-case the returned value is available as `std::any param`.

After defining the test group it's quite easy to include it into the test suite. This implies that you have to just push it's name into the vector in function `gather_test_groups()` like a usual variable:
```
my_tests.push_back(group_name);
```
---
Skyme Factor, 2022