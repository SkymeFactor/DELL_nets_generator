FROM ubuntu

COPY . /subnet_gen

ENTRYPOINT bash -c "/subnet_gen/build/subnet_gen.elf /data/in.txt"