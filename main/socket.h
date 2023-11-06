#ifndef SOCKET_H
#define SOCKET_H

#include "esp_err.h"
#include "esp_http_server.h"

esp_err_t send_ws_message(char *message);
esp_err_t on_web_socket_url(httpd_req_t *req);

#endif