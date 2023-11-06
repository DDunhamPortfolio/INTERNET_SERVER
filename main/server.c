#include <stdio.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "mdns.h"
#include "toggleLed.h"
#include "cJSON/cJSON.h"
#include "pushBtn.h"
#include "web_handler.h"
#include "socket.h"
#include "server.h"

static const char *TAG = "SERVER";

httpd_handle_t server = NULL;

void init_server(){
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_ERROR_CHECK(httpd_start(&server, &config));

    httpd_uri_t default_url = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = on_default_url
    };
    httpd_register_uri_handler(server, &default_url);

    httpd_uri_t toggle_led_url = {
        .uri = "/api/toggle-led",
        .method = HTTP_POST,
        .handler = on_toggle_led_url
    };
    httpd_register_uri_handler(server, &toggle_led_url);

    httpd_uri_t web_socket_url = {
        .uri = "/ws",
        .method = HTTP_GET,
        .handler = on_web_socket_url,
        .is_websocket = true
    };
    httpd_register_uri_handler(server, &web_socket_url);
}

void start_mdns_service(){
    mdns_init();
    mdns_hostname_set("dan-esp32");
    mdns_instance_name_set("DANS ESP32");
}