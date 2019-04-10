#ifndef GPIO_H_
#define GPIO_H_
#include <fcntl.h>
#include <tinyara/gpio.h>
#define HIGH 1
#define LOW 0
void gpio_write(int port, int value);
int gpio_read(int port);
#endif /*GPIO_H_*/
