/* Use a crystal if one is installed.  Much more accurate timing
 * results. */
#define BSP430_PLATFORM_BOOT_CONFIGURE_LFXT1 1

/* Application does output: support spin-for-jumper */
#define configBSP430_PLATFORM_SPIN_FOR_JUMPER 1

/* Support console output */
#define configBSP430_CONSOLE 1

/* Monitor uptime and provide generic ACLK-driven timer.  Also enable
 * its CC0 HAL so we can use that for alarms. */
#define configBSP430_UPTIME 1
#define configBSP430_UPTIME_USE_DEFAULT_CC0_ISR 1

/* Enable an 8-character rx buffer for the console */
#define BSP430_CONSOLE_RX_BUFFER_SIZE 8

/* Enable an 80-character command buffer */
#define BSP430_CLI_CONSOLE_BUFFER_SIZE 80

/* Enable command completion */
#define configBSP430_CLI_COMMAND_COMPLETION 1

/* Get platform defaults */
#include <bsp430/platform/bsp430_config.h>