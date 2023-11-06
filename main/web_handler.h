#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include "esp_err.h"
#include "esp_http_server.h"

esp_err_t on_default_url(httpd_req_t *req);
esp_err_t on_toggle_led_url(httpd_req_t *req);

#endif