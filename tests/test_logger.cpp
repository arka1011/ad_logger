#include "../../../prebuilt/googletest/googletest/include/gtest/gtest.h"
#include <sys/stat.h>
#include <unistd.h>

extern "C" {
#include "../include/ad_logger.h"
}

/* -----------------------------
 * Test: Valid Initialization
 * ----------------------------- */
TEST(LoggerTest, InitValidConfig)
{
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));

    // Categories should be non-null after init
    EXPECT_NE(nullptr, g_log_general);
    EXPECT_NE(nullptr, g_log_transport);
    EXPECT_NE(nullptr, g_log_tun);

    ad_logger_fini();
}

/* -----------------------------
 * Test: Init with invalid config
 * ----------------------------- */
TEST(LoggerTest, InitInvalidConfig)
{
    ASSERT_NE(0, ad_logger_init("config/nonexistent.conf"));
}

/* -----------------------------
 * Test: Reload with valid config
 * ----------------------------- */
TEST(LoggerTest, ReloadValidConfig)
{
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));
    ASSERT_EQ(0, ad_logger_reload("configs/ad_zlog_config.conf"));

    ad_logger_fini();
}

/* -----------------------------
 * Test: Reload without init
 * ----------------------------- */
TEST(LoggerTest, ReloadWithoutInit)
{
    // Ensure logger is NOT initialized
    ad_logger_fini();

    ASSERT_LT(ad_logger_reload("configs/ad_zlog_config.conf"), 0);
}

/* -----------------------------
 * Test: Double initialization
 * Must not fail or reinitialize
 * ----------------------------- */
TEST(LoggerTest, DoubleInit)
{
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));  // Should be safe

    ad_logger_fini();
}

/* -----------------------------
 * Test: Double fini
 * Should not crash
 * ----------------------------- */
TEST(LoggerTest, DoubleFini)
{
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));

    ad_logger_fini();
    ad_logger_fini();  // Should be harmless
}

/* -----------------------------
 * Test: Thread-safety smoke test
 * Multiple threads calling init
 * ----------------------------- */
#include <thread>

TEST(LoggerTest, ThreadSafeInit)
{
    auto worker = []() {
        for (int i = 0; i < 20; i++) {
            ad_logger_init("configs/ad_zlog_config.conf");
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);

    t1.join();
    t2.join();
    t3.join();

    EXPECT_NE(nullptr, g_log_general);
    EXPECT_NE(nullptr, g_log_transport);
    EXPECT_NE(nullptr, g_log_tun);

    ad_logger_fini();
}

/* -----------------------------
 * Test: Thread-safe reload
 * ----------------------------- */
TEST(LoggerTest, ThreadSafeReload)
{
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));

    auto worker = []() {
        for (int i = 0; i < 20; i++) {
            ad_logger_reload("configs/ad_zlog_config.conf");
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    ad_logger_fini();
}

/* Helper: get file size safely */
static long get_file_size(const char *path)
{
    struct stat st;
    if (stat(path, &st) != 0)
        return -1;
    return st.st_size;
}

/* -----------------------------------------
 * Test: Logging macros should NOT crash 
 * even before logger initialization
 * ----------------------------------------- */
TEST(LoggerMacrosTest, MacrosBeforeInitShouldNotCrash)
{
    EXPECT_NO_FATAL_FAILURE({
        AD_LOG_GENERAL_DEBUG("Before init debug");
        AD_LOG_GENERAL_INFO("Before init info");
        AD_LOG_TUN_WARN("Warning before init");
        AD_LOG_TRANSPORT_ERROR("Error before init");
    });
}

/* -----------------------------------------
 * Test: Logging macros actually produce output
 * ----------------------------------------- */
TEST(LoggerMacrosTest, MacrosWriteToFile)
{
    const char *log_file = "./ad_vpn.log";

    // Clean old file
    unlink(log_file);

    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));

    long size_before = get_file_size(log_file);
    if (size_before < 0) size_before = 0;

    AD_LOG_GENERAL_DEBUG("Test debug message %d", 1);
    AD_LOG_TRANSPORT_INFO("Transport info log %s", "hello");
    AD_LOG_TUN_WARN("Tun warning message");

    sleep(1); // Allow zlog async flush

    long size_after = get_file_size(log_file);

    EXPECT_GT(size_after, size_before);

    ad_logger_fini();
}

/* -----------------------------------------
 * Test: Logging after reload still works
 * ----------------------------------------- */
TEST(LoggerMacrosTest, MacrosWorkAfterReload)
{
    const char *log_file = "./ad_vpn.log";
    unlink(log_file);

    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));

    long before = get_file_size(log_file);
    if (before < 0) before = 0;

    ASSERT_EQ(0, ad_logger_reload("configs/ad_zlog_config.conf"));

    AD_LOG_GENERAL_INFO("Log after reload!");
    AD_LOG_TUN_ERROR("Tun error after reload");

    sleep(1);

    long after = get_file_size(log_file);
    EXPECT_GT(after, before);

    ad_logger_fini();
}

/* -----------------------------------------
 * Test: Macros still work across multiple 
 * init/fini cycles
 * ----------------------------------------- */
TEST(LoggerMacrosTest, MacrosAcrossInitCycles)
{
    const char *log_file = "./ad_vpn.log";
    unlink(log_file);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));

        AD_LOG_TRANSPORT_DEBUG("Cycle %d transport debug", i);
        AD_LOG_TUN_INFO("Cycle %d tun info", i);

        ad_logger_fini();
    }

    sleep(1);

    EXPECT_GT(get_file_size(log_file), 0);
}

/* -----------------------------------------
 * Test: Logging with NULL categories after fini 
 * should not crash
 * ----------------------------------------- */
TEST(LoggerMacrosTest, MacrosAfterFiniSafe)
{
    ASSERT_EQ(0, ad_logger_init("configs/ad_zlog_config.conf"));
    ad_logger_fini();

    EXPECT_EQ(nullptr, g_log_general);
    EXPECT_EQ(nullptr, g_log_transport);
    EXPECT_EQ(nullptr, g_log_tun);

    EXPECT_NO_FATAL_FAILURE({
        AD_LOG_GENERAL_ERROR("This should not crash even after fini");
        AD_LOG_TUN_DEBUG("Logging after fini");
    });
}
