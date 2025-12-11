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

#ifdef __cplusplus
}
#endif

#endif /* AD_LOGGER_H */
