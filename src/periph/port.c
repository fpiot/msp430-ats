#include <bsp430/periph/port.h>

/* !BSP430! periph=port */
/* !BSP430! instance=PORT1,PORT2,PORT3,PORT4,PORT5,PORT6,PORT7,PORT8,PORT9,PORT10,PORT11 */

/* !BSP430! insert=periph_ba_hpl_defn */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [periph_ba_hpl_defn] */
#if configBSP430_PERIPH_PORT1 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT1 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT1_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT1 */

#if configBSP430_PERIPH_PORT2 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT2 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT2_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT2 */

#if configBSP430_PERIPH_PORT3 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT3 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT3_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT3 */

#if configBSP430_PERIPH_PORT4 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT4 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT4_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT4 */

#if configBSP430_PERIPH_PORT5 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT5 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT5_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT5 */

#if configBSP430_PERIPH_PORT6 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT6 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT6_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT6 */

#if configBSP430_PERIPH_PORT7 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT7 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT7_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT7 */

#if configBSP430_PERIPH_PORT8 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT8 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT8_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT8 */

#if configBSP430_PERIPH_PORT9 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT9 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT9_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT9 */

#if configBSP430_PERIPH_PORT10 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT10 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT10_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT10 */

#if configBSP430_PERIPH_PORT11 - 0
volatile xBSP430periphPORT * const xBSP430periph_PORT11 = (volatile xBSP430periphPORT *)_BSP430_PERIPH_PORT11_BASEADDRESS;
#endif /* configBSP430_PERIPH_PORT11 */

/* END AUTOMATICALLY GENERATED CODE [periph_ba_hpl_defn] */
/* !BSP430! end=periph_ba_hpl_defn */

/* !BSP430! insert=hal_port_5xx_defn */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hal_port_5xx_defn] */
#if configBSP430_PERIPH_PORT1 - 0
static struct xBSP430port5xxState state_PORT1 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT1_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT1 = &state_PORT1;
#endif /* configBSP430_PERIPH_PORT1 */

#if configBSP430_PERIPH_PORT2 - 0
static struct xBSP430port5xxState state_PORT2 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT2_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT2 = &state_PORT2;
#endif /* configBSP430_PERIPH_PORT2 */

#if configBSP430_PERIPH_PORT3 - 0
static struct xBSP430port5xxState state_PORT3 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT3_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT3 = &state_PORT3;
#endif /* configBSP430_PERIPH_PORT3 */

#if configBSP430_PERIPH_PORT4 - 0
static struct xBSP430port5xxState state_PORT4 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT4_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT4 = &state_PORT4;
#endif /* configBSP430_PERIPH_PORT4 */

#if configBSP430_PERIPH_PORT5 - 0
static struct xBSP430port5xxState state_PORT5 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT5_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT5 = &state_PORT5;
#endif /* configBSP430_PERIPH_PORT5 */

#if configBSP430_PERIPH_PORT6 - 0
static struct xBSP430port5xxState state_PORT6 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT6_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT6 = &state_PORT6;
#endif /* configBSP430_PERIPH_PORT6 */

#if configBSP430_PERIPH_PORT7 - 0
static struct xBSP430port5xxState state_PORT7 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT7_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT7 = &state_PORT7;
#endif /* configBSP430_PERIPH_PORT7 */

#if configBSP430_PERIPH_PORT8 - 0
static struct xBSP430port5xxState state_PORT8 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT8_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT8 = &state_PORT8;
#endif /* configBSP430_PERIPH_PORT8 */

#if configBSP430_PERIPH_PORT9 - 0
static struct xBSP430port5xxState state_PORT9 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT9_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT9 = &state_PORT9;
#endif /* configBSP430_PERIPH_PORT9 */

#if configBSP430_PERIPH_PORT10 - 0
static struct xBSP430port5xxState state_PORT10 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT10_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT10 = &state_PORT10;
#endif /* configBSP430_PERIPH_PORT10 */

#if configBSP430_PERIPH_PORT11 - 0
static struct xBSP430port5xxState state_PORT11 = {
		.port = (volatile xBSP430periphPORT_5XX_8 *)_BSP430_PERIPH_PORT11_BASEADDRESS,
	};
xBSP430portHandle const xBSP430port_PORT11 = &state_PORT11;
#endif /* configBSP430_PERIPH_PORT11 */

/* END AUTOMATICALLY GENERATED CODE [hal_port_5xx_defn] */
/* !BSP430! end=hal_port_5xx_defn */

#if (((configBSP430_PERIPH_PORT1 - 0) && (configBSP430_HAL_PORT1_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT2 - 0) && (configBSP430_HAL_PORT2_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT3 - 0) && (configBSP430_HAL_PORT3_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT4 - 0) && (configBSP430_HAL_PORT4_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT5 - 0) && (configBSP430_HAL_PORT5_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT6 - 0) && (configBSP430_HAL_PORT6_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT7 - 0) && (configBSP430_HAL_PORT7_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT8 - 0) && (configBSP430_HAL_PORT8_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT9 - 0) && (configBSP430_HAL_PORT9_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT10 - 0) && (configBSP430_HAL_PORT10_ISR - 0)) \
	 || ((configBSP430_PERIPH_PORT11 - 0) && (configBSP430_HAL_PORT12_ISR - 0)) \
	 )
static int
#if __MSP430X__
__attribute__ ( ( __c16__ ) )
#endif /* CPUX */
/* __attribute__((__always_inline__)) */
port_isr (xBSP430portHandle device,
		  int iv)
{
	int rv = 0;
	if (0 != iv) {
		int bit = (iv - 2) / 2;
		xBSP430portInterruptCallback cb = device->isr[bit];
		if (NULL != cb) {
			rv = cb(device, bit);
		}
	}
	return rv;
}
#endif /* PORT ISR */

#define BSP430_PORT_ISR_BIC_MASK 0x00F8

/* !BSP430! insert=hal_port_5xx_isr_defn */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hal_port_5xx_isr_defn] */
#if (configBSP430_PERIPH_PORT1 - 0) && (configBSP430_HAL_PORT1_ISR - 0)
static void
__attribute__((__interrupt__(PORT1_VECTOR)))
isr_PORT1 (void)
{
	int rv = port_isr(xBSP430port_PORT1, P1IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT1_ISR */

#if (configBSP430_PERIPH_PORT2 - 0) && (configBSP430_HAL_PORT2_ISR - 0)
static void
__attribute__((__interrupt__(PORT2_VECTOR)))
isr_PORT2 (void)
{
	int rv = port_isr(xBSP430port_PORT2, P2IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT2_ISR */

#if (configBSP430_PERIPH_PORT3 - 0) && (configBSP430_HAL_PORT3_ISR - 0)
static void
__attribute__((__interrupt__(PORT3_VECTOR)))
isr_PORT3 (void)
{
	int rv = port_isr(xBSP430port_PORT3, P3IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT3_ISR */

#if (configBSP430_PERIPH_PORT4 - 0) && (configBSP430_HAL_PORT4_ISR - 0)
static void
__attribute__((__interrupt__(PORT4_VECTOR)))
isr_PORT4 (void)
{
	int rv = port_isr(xBSP430port_PORT4, P4IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT4_ISR */

#if (configBSP430_PERIPH_PORT5 - 0) && (configBSP430_HAL_PORT5_ISR - 0)
static void
__attribute__((__interrupt__(PORT5_VECTOR)))
isr_PORT5 (void)
{
	int rv = port_isr(xBSP430port_PORT5, P5IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT5_ISR */

#if (configBSP430_PERIPH_PORT6 - 0) && (configBSP430_HAL_PORT6_ISR - 0)
static void
__attribute__((__interrupt__(PORT6_VECTOR)))
isr_PORT6 (void)
{
	int rv = port_isr(xBSP430port_PORT6, P6IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT6_ISR */

#if (configBSP430_PERIPH_PORT7 - 0) && (configBSP430_HAL_PORT7_ISR - 0)
static void
__attribute__((__interrupt__(PORT7_VECTOR)))
isr_PORT7 (void)
{
	int rv = port_isr(xBSP430port_PORT7, P7IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT7_ISR */

#if (configBSP430_PERIPH_PORT8 - 0) && (configBSP430_HAL_PORT8_ISR - 0)
static void
__attribute__((__interrupt__(PORT8_VECTOR)))
isr_PORT8 (void)
{
	int rv = port_isr(xBSP430port_PORT8, P8IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT8_ISR */

#if (configBSP430_PERIPH_PORT9 - 0) && (configBSP430_HAL_PORT9_ISR - 0)
static void
__attribute__((__interrupt__(PORT9_VECTOR)))
isr_PORT9 (void)
{
	int rv = port_isr(xBSP430port_PORT9, P9IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT9_ISR */

#if (configBSP430_PERIPH_PORT10 - 0) && (configBSP430_HAL_PORT10_ISR - 0)
static void
__attribute__((__interrupt__(PORT10_VECTOR)))
isr_PORT10 (void)
{
	int rv = port_isr(xBSP430port_PORT10, P10IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT10_ISR */

#if (configBSP430_PERIPH_PORT11 - 0) && (configBSP430_HAL_PORT11_ISR - 0)
static void
__attribute__((__interrupt__(PORT11_VECTOR)))
isr_PORT11 (void)
{
	int rv = port_isr(xBSP430port_PORT11, P11IV);
	__bic_status_register_on_exit(rv & BSP430_PORT_ISR_BIC_MASK);
	portYIELD_FROM_ISR((rv & BSP430_PORT_ISR_YIELD) ? pdTRUE : pdFALSE);
}
#endif /* configBSP430_HAL_PORT11_ISR */

/* END AUTOMATICALLY GENERATED CODE [hal_port_5xx_isr_defn] */
/* !BSP430! end=hal_port_5xx_isr_defn */

volatile xBSP430periphPORTIE *
xBSP430periphLookupPORTIE (xBSP430periphHandle periph)
{
#if defined(__MSP430_HAS_MSP430XV2_CPU__)
/* !BSP430! insert=periph_ba_hpl_demux */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [periph_ba_hpl_demux] */
#if configBSP430_PERIPH_PORT1 - 0
	if (BSP430_PERIPH_PORT1 == periph) {
		return xBSP430periph_PORT1;
	}
#endif /* configBSP430_PERIPH_PORT1 */

#if configBSP430_PERIPH_PORT2 - 0
	if (BSP430_PERIPH_PORT2 == periph) {
		return xBSP430periph_PORT2;
	}
#endif /* configBSP430_PERIPH_PORT2 */

#if configBSP430_PERIPH_PORT3 - 0
	if (BSP430_PERIPH_PORT3 == periph) {
		return xBSP430periph_PORT3;
	}
#endif /* configBSP430_PERIPH_PORT3 */

#if configBSP430_PERIPH_PORT4 - 0
	if (BSP430_PERIPH_PORT4 == periph) {
		return xBSP430periph_PORT4;
	}
#endif /* configBSP430_PERIPH_PORT4 */

#if configBSP430_PERIPH_PORT5 - 0
	if (BSP430_PERIPH_PORT5 == periph) {
		return xBSP430periph_PORT5;
	}
#endif /* configBSP430_PERIPH_PORT5 */

#if configBSP430_PERIPH_PORT6 - 0
	if (BSP430_PERIPH_PORT6 == periph) {
		return xBSP430periph_PORT6;
	}
#endif /* configBSP430_PERIPH_PORT6 */

#if configBSP430_PERIPH_PORT7 - 0
	if (BSP430_PERIPH_PORT7 == periph) {
		return xBSP430periph_PORT7;
	}
#endif /* configBSP430_PERIPH_PORT7 */

#if configBSP430_PERIPH_PORT8 - 0
	if (BSP430_PERIPH_PORT8 == periph) {
		return xBSP430periph_PORT8;
	}
#endif /* configBSP430_PERIPH_PORT8 */

#if configBSP430_PERIPH_PORT9 - 0
	if (BSP430_PERIPH_PORT9 == periph) {
		return xBSP430periph_PORT9;
	}
#endif /* configBSP430_PERIPH_PORT9 */

#if configBSP430_PERIPH_PORT10 - 0
	if (BSP430_PERIPH_PORT10 == periph) {
		return xBSP430periph_PORT10;
	}
#endif /* configBSP430_PERIPH_PORT10 */

#if configBSP430_PERIPH_PORT11 - 0
	if (BSP430_PERIPH_PORT11 == periph) {
		return xBSP430periph_PORT11;
	}
#endif /* configBSP430_PERIPH_PORT11 */

/* END AUTOMATICALLY GENERATED CODE [periph_ba_hpl_demux] */
/* !BSP430! end=periph_ba_hpl_demux */
#else /* 5xx */
#error Not implemented
#endif /* 5xx */
	return NULL;
}

volatile xBSP430periphPORT *
xBSP430periphLookupPORT (xBSP430periphHandle periph)
{
#if defined(__MSP430_HAS_MSP430XV2_CPU__)
	return NULL;
#else /* 5xx */
#error Not implemented
#endif /* 5xx */
	return NULL;
}
