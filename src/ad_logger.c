/*********************************************************
**              AD Logger Implementation                **
**              Author: Arkaprava Das                   **
**********************************************************/

#include "../include/ad_logger.h"
#include <pthread.h>

/* Global categories */
zlog_category_t *g_log_general   = NULL;
zlog_category_t *g_log_transport = NULL;
zlog_category_t *g_log_tun       = NULL;
zlog_category_t *g_log_kex       = NULL;
zlog_category_t *g_log_crypt     = NULL;
zlog_category_t *g_log_auth      = NULL;
zlog_category_t *g_log_routing   = NULL;

/* Mutex and init flag */
static pthread_mutex_t g_logger_lock = PTHREAD_MUTEX_INITIALIZER;
static int g_logger_initialized = 0;

int ad_logger_init(const char *conf_path)
{
    if (!conf_path)
        return -3;

    pthread_mutex_lock(&g_logger_lock);

    /* Already initialized? */
    if (g_logger_initialized) {
        pthread_mutex_unlock(&g_logger_lock);
        return 0;
    }

    int err = zlog_init(conf_path);
    if (err != 0) {
        pthread_mutex_unlock(&g_logger_lock);
        return err;
    }

    g_log_general   = zlog_get_category("ad_vpn_general");
    g_log_transport = zlog_get_category("ad_transport");
    g_log_tun       = zlog_get_category("ad_tun");
    g_log_kex       = zlog_get_category("ad_kex");
    g_log_crypt     = zlog_get_category("ad_crypt");
    g_log_auth      = zlog_get_category("ad_auth");
    g_log_routing   = zlog_get_category("ad_routing");

    if (!g_log_general || !g_log_transport || !g_log_tun || !g_log_kex || !g_log_crypt || !g_log_auth || !g_log_routing) {
        zlog_fini();
        g_log_general = g_log_transport = g_log_tun = g_log_kex = g_log_crypt = g_log_auth = g_log_routing = NULL;
        pthread_mutex_unlock(&g_logger_lock);
        return -2;
    }

    g_logger_initialized = 1;

    /* Safe to log now */
    zlog_info(g_log_general, "AD Logger initialized");

    pthread_mutex_unlock(&g_logger_lock);
    return 0;
}

int ad_logger_reload(const char *conf_path)
{
    if (!conf_path)
        return -3;

    pthread_mutex_lock(&g_logger_lock);

    if (!g_logger_initialized) {
        pthread_mutex_unlock(&g_logger_lock);
        return -2;
    }

    int ret = zlog_reload(conf_path);

    if (ret == 0 && g_log_general)
        zlog_info(g_log_general, "AD Logger configuration reloaded");

    pthread_mutex_unlock(&g_logger_lock);
    return ret;
}

void ad_logger_fini()
{
    pthread_mutex_lock(&g_logger_lock);

    if (!g_logger_initialized) {
        pthread_mutex_unlock(&g_logger_lock);
        return;
    }

    if (g_log_general)
        zlog_info(g_log_general, "AD Logger shutting down");

    zlog_fini();

    g_log_general   = NULL;
    g_log_transport = NULL;
    g_log_tun       = NULL;
    g_log_kex       = NULL;
    g_log_crypt     = NULL;
    g_log_auth      = NULL;
    g_log_routing   = NULL;

    g_logger_initialized = 0;

    pthread_mutex_unlock(&g_logger_lock);
}
