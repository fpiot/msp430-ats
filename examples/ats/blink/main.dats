#include "share/atspre_define.hats"
#include "share/atspre_staload.hats"

%{^
#include <bsp430/platform.h>
#include <bsp430/utility/led.h> /* We're going to use LEDs so we need the interface file */
#include <bsp430/clock.h> /* We want to know the nominal clock speed so we can delay. */
%}

macdef BSP430_CLOCK_NOMINAL_MCLK_HZ = $extval(ulint, "BSP430_CLOCK_NOMINAL_MCLK_HZ")
macdef nBSP430led = $extval(char, "nBSP430led")
val nBSP430ledi = char2int0 nBSP430led

extern fun BSP430_CORE_WATCHDOG_CLEAR: () -> void = "mac#"
extern fun BSP430_CORE_DELAY_CYCLES: (ulint) -> void = "mac#"
extern fun vBSP430platformInitialize_ni: () -> void = "mac#"
extern fun vBSP430ledSet: (int, int) -> void = "mac#"

implement main0 () = {
  fun loop (led: int): void = {
    (* A common complaint is that "blink doesn't work!" when the issue
     * is that the watchdog is resetting the board.  Don't let that
     * happen to you. *)
    val () = BSP430_CORE_WATCHDOG_CLEAR ()
    (* If there are multiple LEDs, turn each LED on in turn, wait a
     * half second, then turn it off and move to the next LED.  If
     * there's only one LED, the invert state handles the on as well
     * as the off. *)
    val () = if 1 < nBSP430ledi then vBSP430ledSet (led, 1)
    val () = BSP430_CORE_DELAY_CYCLES (BSP430_CLOCK_NOMINAL_MCLK_HZ / 2UL)
    (* -1 means "invert state", which in this case will turn it off *)
    val () = vBSP430ledSet (led, ~1)
    val nled = if led = nBSP430led then 0 else led + 1
    val () = loop nled
  }
  (* First thing you do in main is configure the platform.
   * Note that this configures the LEDs. *)
  val () = vBSP430platformInitialize_ni ()
  val () = loop 0
}
