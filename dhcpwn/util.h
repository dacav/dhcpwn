#ifndef _DHCPWN_MISC_H
#define _DHCPWN_MISC_H

#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>

double random_real(double min, double max);
uint8_t random_uint8();
void random_bytes(uint8_t *dst, size_t size);

#endif // _DHCPWN_MISC_H
