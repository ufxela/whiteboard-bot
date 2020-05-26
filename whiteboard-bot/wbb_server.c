#include "wbb-extra.h"
#include "sw-uart-int.h"
#include "pi-message.h"
#include "libesp.h"
#include "libhttp.h"

// these should probably not be here
#define TX 10
#define RX 9
#define ESP_BAUD 115200

typedef response_t (*response_handler_t)(request_t * req);

typedef struct{
    char * path;
    method_t method;
    response_handler_t handler;
} route_t;

static response_t root_handler(request_t * req);

static response_t points_handler(request_t * req);

response_t reset_handler(request_t * req);

unsigned char index_html[] = {
  0x3c, 0x21, 0x2d, 0x2d, 0x20, 0x43, 0x6f, 0x64, 0x65, 0x20, 0x64, 0x65, 0x70, 0x6c, 0x6f, 0x79
, 0x65, 0x64, 0x20, 0x6f, 0x6e, 0x20, 0x74, 0x68, 0x65, 0x20, 0x70, 0x69, 0x20, 0x2d, 0x2d, 0x3e
, 0x0a, 0x3c, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x3e, 0x62, 0x6f, 0x64, 0x79, 0x20, 0x7b, 0x62, 0x61
, 0x63, 0x6b, 0x67, 0x72, 0x6f, 0x75, 0x6e, 0x64, 0x3a, 0x20, 0x62, 0x6c, 0x61, 0x63, 0x6b, 0x3b
, 0x20, 0x7d, 0x3c, 0x2f, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x3e, 0x0a, 0x3c, 0x73, 0x63, 0x72, 0x69
, 0x70, 0x74, 0x0a, 0x20, 0x20, 0x73, 0x72, 0x63, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a
, 0x2f, 0x2f, 0x63, 0x6f, 0x64, 0x65, 0x2e, 0x6a, 0x71, 0x75, 0x65, 0x72, 0x79, 0x2e, 0x63, 0x6f
, 0x6d, 0x2f, 0x6a, 0x71, 0x75, 0x65, 0x72, 0x79, 0x2d, 0x33, 0x2e, 0x34, 0x2e, 0x31, 0x2e, 0x6d
, 0x69, 0x6e, 0x2e, 0x6a, 0x73, 0x22, 0x0a, 0x20, 0x20, 0x69, 0x6e, 0x74, 0x65, 0x67, 0x72, 0x69
, 0x74, 0x79, 0x3d, 0x22, 0x73, 0x68, 0x61, 0x32, 0x35, 0x36, 0x2d, 0x43, 0x53, 0x58, 0x6f, 0x72
, 0x58, 0x76, 0x5a, 0x63, 0x54, 0x6b, 0x61, 0x69, 0x78, 0x36, 0x59, 0x76, 0x6f, 0x36, 0x48, 0x70
, 0x70, 0x63, 0x5a, 0x47, 0x65, 0x74, 0x62, 0x59, 0x4d, 0x47, 0x57, 0x53, 0x46, 0x6c, 0x42, 0x77
, 0x38, 0x48, 0x66, 0x43, 0x4a, 0x6f, 0x3d, 0x22, 0x0a, 0x20, 0x20, 0x63, 0x72, 0x6f, 0x73, 0x73
, 0x6f, 0x72, 0x69, 0x67, 0x69, 0x6e, 0x3d, 0x22, 0x61, 0x6e, 0x6f, 0x6e, 0x79, 0x6d, 0x6f, 0x75
, 0x73, 0x22, 0x3e, 0x3c, 0x2f, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x3e, 0x0a, 0x3c, 0x73, 0x63
, 0x72, 0x69, 0x70, 0x74, 0x3e, 0x24, 0x28, 0x66, 0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x28
, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x76, 0x61, 0x72, 0x20, 0x75, 0x72, 0x6c, 0x20
, 0x3d, 0x20, 0x22, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f, 0x75, 0x66, 0x78, 0x65, 0x6c
, 0x61, 0x2e, 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x2e, 0x69, 0x6f, 0x22, 0x3b, 0x0a, 0x20, 0x20
, 0x20, 0x20, 0x76, 0x61, 0x72, 0x20, 0x62, 0x61, 0x73, 0x65, 0x20, 0x3d, 0x20, 0x24, 0x28, 0x27
, 0x3c, 0x62, 0x61, 0x73, 0x65, 0x20, 0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x27, 0x20, 0x2b, 0x20
, 0x75, 0x72, 0x6c, 0x20, 0x2b, 0x20, 0x27, 0x22, 0x3e, 0x27, 0x29, 0x3b, 0x20, 0x2f, 0x2f, 0x20
, 0x6e, 0x65, 0x65, 0x64, 0x65, 0x64, 0x20, 0x74, 0x6f, 0x20, 0x66, 0x69, 0x78, 0x20, 0x72, 0x65
, 0x6c, 0x61, 0x74, 0x69, 0x76, 0x65, 0x20, 0x75, 0x72, 0x6c, 0x20, 0x69, 0x6d, 0x70, 0x6f, 0x72
, 0x74, 0x73, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x73, 0x2c, 0x20
, 0x65, 0x74, 0x63, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x24, 0x28, 0x22, 0x68, 0x65, 0x61, 0x64
, 0x22, 0x29, 0x2e, 0x61, 0x70, 0x70, 0x65, 0x6e, 0x64, 0x28, 0x62, 0x61, 0x73, 0x65, 0x29, 0x3b
, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x24, 0x28, 0x22, 0x62, 0x6f, 0x64, 0x79, 0x22, 0x29, 0x2e, 0x6c
, 0x6f, 0x61, 0x64, 0x28, 0x22, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f, 0x75, 0x66, 0x78
, 0x65, 0x6c, 0x61, 0x2e, 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x2e, 0x69, 0x6f, 0x2f, 0x77, 0x68
, 0x69, 0x74, 0x65, 0x62, 0x6f, 0x61, 0x72, 0x64, 0x2d, 0x62, 0x6f, 0x74, 0x2f, 0x3f, 0x71, 0x3d
, 0x22, 0x20, 0x2b, 0x20, 0x4d, 0x61, 0x74, 0x68, 0x2e, 0x72, 0x61, 0x6e, 0x64, 0x6f, 0x6d, 0x28
, 0x29, 0x2c, 0x20, 0x66, 0x75, 0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x28, 0x29, 0x20, 0x7b, 0x0a
, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x61, 0x73, 0x65, 0x2e, 0x72, 0x65, 0x6d
, 0x6f, 0x76, 0x65, 0x28, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x29, 0x3b, 0x0a, 0x7d
, 0x29, 0x3b, 0x0a, 0x3c, 0x2f, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x3e
};
unsigned int index_html_len = 572;

typedef enum {
    GOTO,
    LIFT,
    PLACE,
} wbb_action_type_t;

typedef struct wbb_action_t {
    struct wbb_action_t * next;
    wbb_action_type_t type;
    int x; // optional arg
    int y; // optional arg
} wbb_action_t;

#define E wbb_action_t // BADDD... cause now we can't include syscall-record.h, since it also #define E. Q.h should be refactored s.t. doesn't need to #define E.
#include "Q.h"

Q_t wbb_positions;

static route_t routes[] = {
    {.path = "/", .method = METHOD_GET, .handler = root_handler},
    {.path = "/points", .method = METHOD_POST, .handler = points_handler},
    {.path = "/poll", .method = METHOD_GET, .handler = reset_handler},
    { 0 }
};

static route_t * get_matching_route(request_t * req){
    for(route_t * i = routes; *((unsigned *) i) != 0; i++){
        if(strcmp(i->path, req->path) == 0 && i->method == req->method){
            return i;
        }
    }
    return NULL; //no matches found
}

static header_t * get_matching_header(request_t * req, char * key){
    for(header_t * i = req->headers[0]; *((unsigned *) i) != 0; i++){
        if(strcmp(i->key, key) == 0){
            return i;
        }
    }
    return NULL;
}

response_t root_handler(request_t * req){
    //need to send back response w/ js link to the actual webpage.
    response_t res;
    res.body = kmalloc(index_html_len);
    memcpy(res.body, index_html, index_html_len);
    res.content_length = strlen(res.body);
    res.status_code = 200;
    res.status_text = "OK";
    return res;
}

#define MAX_ARG_PART_LEN 8

// todo: maybe have this truncate instead of trash?
static int isValidCharacter(char c){
    if('0' <= c && c <= '9'){
        return 1;
    }else if(c == ',' || c == 'l' || c == 'p' || c == '-' || c == ' '){
        return 1;
    }else{
        return 0;
    }
}

// ? maybe go to points in this handler, and only send response when job completed.
response_t points_handler(request_t * req){
    output("Received a points request\n");

    unsigned length = strlen(req->body);
    char * arg = kmalloc(length);
    memset(arg, 0, length);
    memcpy(arg ,req->body, length);

    // do error checking on data
    for(int i = 0; i < length; i++){
        if(!isValidCharacter(arg[i])){
            output("RECIEVED INVALID CHARACTER '%c'\nin position %d \nfull string: %s", arg[i], i, arg);
            if(arg[i-1] == ',' && (arg[i-2] == 'l' || arg[i-2] == 'p')){
                length = i; // case that we can probably recover. optimistic approach: truncate here and hope it draws what we want. lmao.
            }else{
                response_t dump;
                dump.content_length = 0;
                dump.status_code = 400;
                dump.status_text = "ERROR";
                return dump;
            }
        }
    }

    int num, total;

    char * comma_i = strchr(arg, ',');
    char num_str[MAX_ARG_PART_LEN];
    memset(num_str, 0, MAX_ARG_PART_LEN);
    memcpy(num_str, arg, comma_i - arg);
    num = atoi(num_str);

    arg = comma_i + 1;
    comma_i = strchr(arg, ',');
    char total_str[MAX_ARG_PART_LEN];
    memset(total_str, 0, MAX_ARG_PART_LEN);
    memcpy(total_str, arg, comma_i - arg);
    total = atoi(total_str);

    assert(num < total); //dumb

    // ugly, but prevents hanging
    unsigned start = timer_get_usec();
    #define POINTS_TIMEOUT 100000
    output("here\n");
    while(timer_get_usec() - start < POINTS_TIMEOUT){

        int x, y;
        arg = comma_i + 1;
        comma_i = strchr(arg, ',');
        if(strlen(comma_i + 1) == 0){
            break;
        }
        char x_str[MAX_ARG_PART_LEN];
        memset(x_str, 0, MAX_ARG_PART_LEN);
        memcpy(x_str, arg, comma_i - arg);
        if(x_str[0] == 'l'){
            wbb_action_t * lift = kmalloc(sizeof(wbb_action_t));
            lift->type = LIFT;
            Q_append(&wbb_positions, lift);
            continue;
        }else if(x_str[0] == 'p'){
            wbb_action_t * place = kmalloc(sizeof(wbb_action_t));
            place->type = PLACE;
            Q_append(&wbb_positions, place);
            continue;
        }else{
            x = atoi(x_str);
        }

        arg = comma_i + 1;
        comma_i = strchr(arg, ',');
        char y_str[MAX_ARG_PART_LEN];
        memset(y_str, 0, MAX_ARG_PART_LEN);
        if(comma_i == NULL){
            memcpy(y_str, arg, strlen(arg));
        }else{
            if(strlen(comma_i + 1) == 0){
                break;
            }
            memcpy(y_str, arg, comma_i - arg);
        }
        y = atoi(y_str);

        wbb_action_t * _goto = kmalloc(sizeof(wbb_action_t));
        _goto->type = GOTO;
        _goto->x = x;
        _goto->y = y;
        Q_append(&wbb_positions, _goto);
        if(comma_i == NULL){
            break;
        }
    }

    output("here now\n");

    // hack, gross. for some reason I'm missing the last lift. Could also solve this on the frontend by double sending lift.
    wbb_action_t * lift = kmalloc(sizeof(wbb_action_t));
    lift->type = LIFT;
    Q_append(&wbb_positions, lift);


    output("lift appended\n");
    
    //return response
    response_t dump;
    dump.content_length = 0;
    dump.status_code = 200;
    dump.status_text = "OK";
    return dump;
}

response_t reset_handler(request_t * req){
    clean_reboot();
}

static void setup_wbb_server(esp_t * e, unsigned port){
    esp_hard_reset(e);
    if(!esp_connect_to_wifi(e)){
        panic("can't connect to the wifi network!\n");
    }
    if(!esp_start_tcp_server(e, port)){
        panic("can't start tcp server!\n");
    }
}

static void get_connection(esp_t * e, unsigned * ch){
    output("Going to wait for a connection. Connect to me locally at http://%s/ or at http://75.188.62.170:88/\n", e->ip_address);
    output("Note: you should wait about 10 seconds before connecting, actually\n");
    while(!wait_for_conn(e, ch)) {
        cmd_echo_line(e, "no connection");
        esp_usleep(1000);
    }
}

static my_sw_uart_t * inits(){
    kmalloc_init();
    my_sw_uart_t u = my_sw_uart_init(TX, RX, ESP_BAUD);
    my_sw_uart_t * swu = kmalloc(sizeof(my_sw_uart_t));
    memcpy(swu, &u, sizeof(my_sw_uart_t));
    sw_uart_int_init(swu);
    return swu;
}

#define ESP_READ_TIMEOUT -1

static void esp_putk(my_sw_uart_t * esp, char * command){
    for(int i = 0; command[i] != 0; i++){
        sw_uart_put8(esp, command[i]);
    }
}

//int so that we can return -1 on error; otherwise returns char
static int esp_read_char_timeout(my_sw_uart_t * esp, unsigned usec){
    unsigned start = timer_get_usec();
    int data;
    while((data = sw_uart_get8_int(esp)) == -1){
        if(timer_get_usec() - start > usec){
            return ESP_READ_TIMEOUT; //timeout
        }
    }
    return data;
}

//populates buf with at most maxbytes of data, also timeouts. 
static int esp_read_timeout(my_sw_uart_t * esp, void * buf, unsigned maxbytes, unsigned usec){
    char * charbuf = (char *) buf;
    for(int i = 0; i < maxbytes; i++){
        int data = esp_read_char_timeout(esp, usec);
        if(data == ESP_READ_TIMEOUT){
            return i;
        }
        charbuf[i] = (char) data;
    }
    return maxbytes;
}

static void esp_request_and_response(my_sw_uart_t * esp, char * command, unsigned usec){
    int command_len = strlen(command);
    assert(command[command_len - 1] == '\n');
    assert(command[command_len - 2] == '\r');
    // output("\nCommand: %s", command);
    esp_putk(esp, command);

    char response[1024];
    int nbytes = esp_read_timeout(esp, response, 1024, usec);
    // for(int i = 0; i < nbytes; i++){
    //     output("%c", response[i]);
    // }
}

void wbb_execute_action(wbb_t * wbb, wbb_action_t * action){
    // output("executing action %d %d\n", action->x, action->y);
    if(action->type == PLACE){
        wbb_place_pen(wbb);
    }else if(action->type == LIFT){
        wbb_lift_pen(wbb);
    }else if(action->type == GOTO){
        if(action->x > 1000 || action->y > 700){ // hacky filtering, but we know that canvas is 1000x700. 
            return; 
        }
        wbb_go_to_coords_relative(wbb, 15*action->x, -15*action->y);
    }else{
        unimplemented();
    }
}

void wbb_server(wbb_t * wbb){
    my_sw_uart_t * swu = inits();
    esp_request_and_response(swu, "AT\r\n", 100000); //hack: if we take this out, sw uart doesn't get initalized right :/. what I really should do is do a reset sw uart queue thing
    output("Starting server (takes about 15 seconds for next output)\n");
    esp_set_verbose(0); //change to 0 for a cleaner interface, 1 for all output (for debugging purposes)
    lex_t l; 
    esp_handle_t h;
    h.type = SW_UART;
    h.sw_uart = swu;
    lex_init(&l, h);
    esp_t e = esp_mk(&l, ESP_WIFI_NETWORK, ESP_WIFI_PASSWORD);
    unsigned port = ESP_DEFAULT_PORT; 

    setup_wbb_server(&e, port);

    //wait for a connection from esp
    unsigned ch;
    get_connection(&e, &ch);

    //now, we've established a connection. Get incoming requests, do necessary actions and respond to them
    while(1){
        //continually and synchronously accept requests, then execute their handlers, then send back their responses
        //also continually check queue of actions and if there is an action, then execute it and then continue on.

        while(!Q_empty(&wbb_positions)){
            wbb_action_t * action = Q_start(&wbb_positions);
            Q_pop(&wbb_positions);
            wbb_execute_action(wbb, action);
        }

        request_t req; 
        http_error_t err;
        if((err = http_read_request_no_block(&e, ch, &req)) == HTTP_ERROR_NONE){
            output("received request at route %s\n", req.path);
            route_t * route = get_matching_route(&req);
            if(route != NULL){ //check that route exists
                response_t res = route->handler(&req);
                err = http_send_response(&e, res);
            }else{
                // output("route %s ignored b/c doesn't exist\n", req.path);
            }
        }
        //if there was a disconnection, then call get_connection(&e, ch)
        if(err == HTTP_ERROR_DISCONNECT){
            get_connection(&e, &ch);
        }
    }    
}