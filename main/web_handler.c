#include <stdio.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "mdns.h"
#include "toggleLed.h"
#include "cJSON/cJSON.h"
#include "pushBtn.h"
//#include "web_handler.h"
#include "socket.h"
#include "server.h"

static const char *TAG = "HANDLER";


esp_err_t on_default_url(httpd_req_t *req){
    ESP_LOGI(TAG, "URL %s", req->uri);
    httpd_resp_sendstr(req,"hello world");
    return ESP_OK;
}

esp_err_t on_toggle_led_url(httpd_req_t *req){
    char buffer[100];
    memset(&buffer, 0, sizeof(buffer));
    httpd_req_recv(req, buffer, req->content_len);
    cJSON *payload = cJSON_Parse(buffer);
    cJSON *is_on_json = cJSON_GetObjectItem(payload,"is_on");
    bool is_on = cJSON_IsTrue(is_on_json);
    cJSON_Delete(payload);
    toggle_led(is_on);
    httpd_resp_set_status(req,"204 NO CONTENT");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}