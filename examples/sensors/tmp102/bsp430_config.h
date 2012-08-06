/* Use a crystal if one is installed.  Much more accurate timing
 * results. */
#define BSP430_PLATFORM_BOOT_CONFIGURE_LFXT1 1

/* Application does output: support spin-for-jumper */
#define configBSP430_PLATFORM_SPIN_FOR_JUMPER 1

/* Support console output */
#define configBSP430_CONSOLE 1

/* What we use to access the TMP102 */
#define APP_TMP102_I2C_PERIPH_HANDLE BSP430_PERIPH_USCI_B0
#define configBSP430_HAL_USCI_B0 1
/* Use SMCLK/40 (=100 kHz) for the I2C speed */
#define APP_TMP102_I2C_PRESCALER 40
/* Address for the thing.  0x48 when ADD0 is shorted to GND. */
#define APP_TMP102_I2C_ADDRESS 0x48

/* Get platform defaults */
#include <bsp430/platform/bsp430_config.h>