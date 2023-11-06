#include <stdio.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "mdns.h"
#include "toggleLed.h"
#include "cJSON/cJSON.h"
#include "pushBtn.h"
#include "web_handler.h"
//#include "socket.h"
#include "server.h"

static const char *TAG = "SOCKET";
//extern httpd_handle_t server;

#define WS_MAX_SIZE 1024
static int client_session_id;

esp_err_t send_ws_message(char *message){
    if(!client_session_id){
        ESP_LOGE(TAG, "no client_session_id");
        return -1;
    }
    httpd_ws_frame_t ws_message ={
        .final = true,
        .fragmented = false,
        .len = strlen(message),
        .payload = (uint8_t *)message,
        .type = HTTPD_WS_TYPE_TEXT
    };
    return httpd_ws_send_frame_async(server, client_session_id, &ws_message);
}

esp_err_t on_web_socket_url(httpd_req_t *req){
    client_session_id = httpd_req_to_sockfd(req);
    if(req->method == HTTP_GET){
        return ESP_OK;
    }
    httpd_ws_frame_t ws_pkt;
    memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
    ws_pkt.type = HTTPD_WS_TYPE_TEXT;
    ws_pkt.payload = malloc(WS_MAX_SIZE);
    httpd_ws_recv_frame(req, &ws_pkt, WS_MAX_SIZE);
    printf("ws payload: %.*s\n", ws_pkt.len, ws_pkt.payload);
    free(ws_pkt.payload);

    char *response = "connected OK 😊";
    httpd_ws_frame_t ws_response = {
        .final = true,
        .fragmented = false,
        .type = HTTPD_WS_TYPE_TEXT,
        .payload = (uint8_t *)response,
        .len = strlen(response)
    };
    return httpd_ws_send_frame(req, &ws_response);
}