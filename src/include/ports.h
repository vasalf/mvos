#include <stdint.h>

uint8_t read_from_port(uint16_t port);
void send_to_port(uint16_t port, uint8_t to_send);
uint8_t get_response(uint16_t port, uint8_t to_send);

