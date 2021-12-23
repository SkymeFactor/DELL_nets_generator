#!/bin/bash
docker build ./ -t subnet_gen
docker run --rm -v `pwd`/tests:/data subnet_gen:latest
docker rmi subnet_gen:latest