cmd_/home/samuel/Desktop/damas/driver/driver.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o /home/samuel/Desktop/damas/driver/driver.ko /home/samuel/Desktop/damas/driver/driver.o /home/samuel/Desktop/damas/driver/driver.mod.o ;  true