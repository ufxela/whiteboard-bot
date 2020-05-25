#ifndef __LIBHTTP_H__
#define __LIBHTTP_H__

#include "libesp.h"
#include "libc-extra.h"

typedef enum {
    HTTP_ERROR_NONE,
    HTTP_ERROR_DISCONNECT,
    HTTP_NO_REQUEST,
} http_error_t;

typedef enum {
    METHOD_GET,
    METHOD_POST,
    METHOD_PUT,
    METHOD_DELETE,
    METHOD_OPTIONS,
    METHOD_PATCH
} method_t;

static const inline char *stringFromMethod(method_t m) {
    static const char *strings[] = { "GET", "POST", "PUT", "DELETE", "OPTIONS", "PATCH" };
    return strings[m];
}

static const inline unsigned methodFromString(char* m) {
    static const char *strings[] = { "GET", "POST", "PUT", "DELETE", "OPTIONS", "PATCH" };
    unsigned index = 0;
    while ( index < 6 && strcmp(strings[index], m) != 0 ) ++index;
    return ( index == 6 ? -1 : index );
}

typedef struct {
    char * key;
    char * val;
} header_t;

typedef struct{
    const char * dst;
    unsigned port;
} dst_t;

typedef struct {
    dst_t dst; // Sender
    method_t method;
    char * path;

    unsigned num_headers;
    header_t ** headers;
    unsigned content_length;  
    char *body;
} request_t;

typedef struct {
    dst_t dst;
    unsigned status_code;
    char * status_text;

    unsigned num_headers;
    header_t ** headers;
    unsigned content_length;
    char *body;
} response_t;

/*
 * Sends http request over ESP
 */
http_error_t http_send_request(esp_t * e, request_t req);

/*
 * Sends http response over ESP
 */
http_error_t http_send_response(esp_t * e, response_t res);

/*
 * Reads http request over ESP
 */
http_error_t http_read_request(esp_t * e, unsigned ch, request_t *req);

// non blocking version, returns HTTP_NO_REQUEST if none
http_error_t http_read_request_no_block(esp_t * e, unsigned ch, request_t *req);

/*
 * Reads http response over ESP
 */
http_error_t http_read_response(esp_t * e, unsigned ch, response_t *req);


/*
 * Sends http request over ESP
 */
http_error_t http_send_request(esp_t * e, request_t req);

/*
 * Sends http response over ESP
 */
http_error_t http_send_response(esp_t * e, response_t res);

/*
 * Parses HTTP request from string
 */
int http_parse_request(const char * buf, request_t *req);

/*
 * Parses HTTP request from string
 */
int http_parse_response(const char * buf, response_t *res);

/*
 * Serializes HTTP request to string
 */
int http_serialize_request(request_t req, char *buf);

/*
 * Serializes HTTP response to string
 */
int http_serialize_response(response_t res, char *buf);

#endif 