/*********************************************************
 **               AD Logger Module                      **
 **               Author: Arkaprava Das                 **
 *********************************************************/

#ifndef AD_LOGGER_H
#define AD_LOGGER_H

#include "../../../prebuilt/zlog/include/zlog.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize logging system */
int ad_logger_init(const char *conf_path);
int ad_logger_reload(const char *conf_path);
void ad_logger_fini();

/* Global log categories */
extern zlog_category_t *g_log_general;
extern zlog_category_t *g_log_transport;
extern zlog_category_t *g_log_tun;
extern zlog_category_t *g_log_kex;
extern zlog_category_t *g_log_crypt;
extern zlog_category_t *g_log_auth;
extern zlog_category_t *g_log_routing;

/* ============================
 * Logging Macros: GENERAL
 * ============================ */
#define AD_LOG_GENERAL_DEBUG(fmt, ...) \
    zlog_debug(g_log_general, fmt, ##__VA_ARGS__)

#define AD_LOG_GENERAL_INFO(fmt, ...) \
    zlog_info(g_log_general, fmt, ##__VA_ARGS__)

#define AD_LOG_GENERAL_WARN(fmt, ...) \
    zlog_warn(g_log_general, fmt, ##__VA_ARGS__)

#define AD_LOG_GENERAL_ERROR(fmt, ...) \
    zlog_error(g_log_general, fmt, ##__VA_ARGS__)

#define AD_LOG_GENERAL_FATAL(fmt, ...) \
    zlog_fatal(g_log_general, fmt, ##__VA_ARGS__)

/* ============================
 * Logging Macros: TRANSPORT
 * ============================ */
#define AD_LOG_TRANSPORT_DEBUG(fmt, ...) \
    zlog_debug(g_log_transport, fmt, ##__VA_ARGS__)

#define AD_LOG_TRANSPORT_INFO(fmt, ...) \
    zlog_info(g_log_transport, fmt, ##__VA_ARGS__)

#define AD_LOG_TRANSPORT_WARN(fmt, ...) \
    zlog_warn(g_log_transport, fmt, ##__VA_ARGS__)

#define AD_LOG_TRANSPORT_ERROR(fmt, ...) \
    zlog_error(g_log_transport, fmt, ##__VA_ARGS__)

#define AD_LOG_TRANSPORT_FATAL(fmt, ...) \
    zlog_fatal(g_log_transport, fmt, ##__VA_ARGS__)

/* ============================
 * Logging Macros: TUN
 * ============================ */
#define AD_LOG_TUN_DEBUG(fmt, ...) \
    zlog_debug(g_log_tun, fmt, ##__VA_ARGS__)

#define AD_LOG_TUN_INFO(fmt, ...) \
    zlog_info(g_log_tun, fmt, ##__VA_ARGS__)

#define AD_LOG_TUN_WARN(fmt, ...) \
    zlog_warn(g_log_tun, fmt, ##__VA_ARGS__)

#define AD_LOG_TUN_ERROR(fmt, ...) \
    zlog_error(g_log_tun, fmt, ##__VA_ARGS__)

#define AD_LOG_TUN_FATAL(fmt, ...) \
    zlog_fatal(g_log_tun, fmt, ##__VA_ARGS__)

/* ============================
 * Logging Macros: KeX
 * ============================ */
#define AD_LOG_KEX_DEBUG(fmt, ...) \
    zlog_debug(g_log_kex, fmt, ##__VA_ARGS__)

#define AD_LOG_KEX_INFO(fmt, ...) \
    zlog_info(g_log_kex, fmt, ##__VA_ARGS__)

#define AD_LOG_KEX_WARN(fmt, ...) \
    zlog_warn(g_log_kex, fmt, ##__VA_ARGS__)

#define AD_LOG_KEX_ERROR(fmt, ...) \
    zlog_error(g_log_kex, fmt, ##__VA_ARGS__)

#define AD_LOG_KEX_FATAL(fmt, ...) \
    zlog_fatal(g_log_kex, fmt, ##__VA_ARGS__)

/* ============================
 * Logging Macros: CRYPT
 * ============================ */
#define AD_LOG_CRYPT_DEBUG(fmt, ...) \
    zlog_debug(g_log_crypt, fmt, ##__VA_ARGS__)

#define AD_LOG_CRYPT_INFO(fmt, ...) \
    zlog_info(g_log_crypt, fmt, ##__VA_ARGS__)

#define AD_LOG_CRYPT_WARN(fmt, ...) \
    zlog_warn(g_log_crypt, fmt, ##__VA_ARGS__)

#define AD_LOG_CRYPT_ERROR(fmt, ...) \
    zlog_error(g_log_crypt, fmt, ##__VA_ARGS__)

#define AD_LOG_CRYPT_FATAL(fmt, ...) \
    zlog_fatal(g_log_crypt, fmt, ##__VA_ARGS__)

/* ============================
 * Logging Macros: AUTH
 * ============================ */
#define AD_LOG_AUTH_DEBUG(fmt, ...) \
    zlog_debug(g_log_auth, fmt, ##__VA_ARGS__)

#define AD_LOG_AUTH_INFO(fmt, ...) \
    zlog_info(g_log_auth, fmt, ##__VA_ARGS__)

#define AD_LOG_AUTH_WARN(fmt, ...) \
    zlog_warn(g_log_auth, fmt, ##__VA_ARGS__)

#define AD_LOG_AUTH_ERROR(fmt, ...) \
    zlog_error(g_log_auth, fmt, ##__VA_ARGS__)

#define AD_LOG_AUTH_FATAL(fmt, ...) \
    zlog_fatal(g_log_auth, fmt, ##__VA_ARGS__)

/* ============================
 * Logging Macros: Routing
 * ============================ */
#define AD_LOG_ROUTING_DEBUG(fmt, ...) \
    zlog_debug(g_log_routing, fmt, ##__VA_ARGS__)

#define AD_LOG_ROUTING_INFO(fmt, ...) \
    zlog_info(g_log_routing, fmt, ##__VA_ARGS__)

#define AD_LOG_ROUTING_WARN(fmt, ...) \
    zlog_warn(g_log_routing, fmt, ##__VA_ARGS__)

#define AD_LOG_ROUTING_ERROR(fmt, ...) \
    zlog_error(g_log_routing, fmt, ##__VA_ARGS__)

#define AD_LOG_ROUTING_FATAL(fmt, ...) \
    zlog_fatal(g_log_routing, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* AD_LOGGER_H */
