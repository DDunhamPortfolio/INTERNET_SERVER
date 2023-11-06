#include <stdio.h>
#include "wifi_connect.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "toggleLed.h"
#include "pushBtn.h"
#include "web_handler.h"
#include "socket.h"
#include "server.h"


void app_main(void){
    ESP_ERROR_CHECK(nvs_flash_init());
    init_led();
    init_btn();
    wifi_connect_init();
    wifi_connect_ap("ESP32_DUN", "password");
    start_mdns_service();
    init_server();
}
