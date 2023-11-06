idf_component_register(SRCS ${SOURCE_FILES} 
                    "wifi_connect_err.c" "connect.c" "wifi_connect.c" 
                    "main.c" "toggleLed.c" "pushBtn.c" 
                    "web_handler.c" "socket.c" "server.c"
                    INCLUDE_DIRS "."
                    REQUIRES
                    "driver"
                    "esp_https_server"
                    "esp_http_server"
                    "esp_netif"
                    "esp_wifi"
                    "log"
                    "nvs_flash"
                    )
