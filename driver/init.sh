setxkbmap -model abnt2 -layout br &&
sudo mknod /dev/damas c 60 0 &&
sudo chmod 666 /dev/damas &&
make &&
sudo insmod driver.ko &&
echo "123123"> /dev/damas


