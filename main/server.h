#ifndef SERVER_H
#define SERVER_H

#include "esp_http_server.h"

extern httpd_handle_t server;
void init_server();
void start_mdns_service();

#endif