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
The Solution is built inside a docker container, run instructions:

```
$ ls data/
in.txt
$ docker run -v `pwd`/data:/data ${YOUR_NAME}/${YOUR_IMAGE}:${IMAGE_VERSION}
$ echo $?
0
$ ls data/
in.txt out.txt autogen.txt
$
```
Temporarily building a container is possible by running `./tools/run_docker.sh` from the project root.
