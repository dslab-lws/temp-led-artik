#include "gpio.h"
void gpio_write(int port, int value)
{
char str[4];
static char devpath[16];
snprintf(devpath, 16, "/dev/gpio%d", port);
int fd = open(devpath, O_RDWR);
ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);
write(fd, str, snprintf(str, 4, "%d", value != 0) + 1);
close(fd);
}
int gpio_read(int port)
{
char buf[4];
char devpath[16];
snprintf(devpath, 16, "/dev/gpio%d", port);
int fd = open(devpath, O_RDWR);
read(fd, buf, sizeof(buf));
close(fd);
return buf[0]=='1';
}
