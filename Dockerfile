FROM ubuntu

COPY . /subnet_gen

ENTRYPOINT bash -c '[ -f /subnet_gen/build/test_subnet_gen.elf ] && /subnet_gen/build/test_subnet_gen.elf; \
/subnet_gen/build/subnet_gen.elf /data/in.txt'