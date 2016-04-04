/* hrf69.h  03/04/2016  D.J.Whale
 *
 * Interface for HopeRF RFM69 radio
 */

//# Precise register descriptions can be found in:
//# www.hoperf.com/upload/rf/RFM69W-V1.3.pdf
//# on page 63 - 74

#ifndef _HRF69_H
#define _HRF69_H

#include "system.h"

typedef uint8_t HRF_RESULT;

typedef struct
{
  uint8_t addr;
  uint8_t value;
} HRF_CONFIG_REC;


// Register addresses
#define HRF_ADDR_FIFO                   = 0x00
#define HRF_ADDR_OPMODE                 = 0x01
#define HRF_ADDR_REGDATAMODUL           = 0x02
#define HRF_ADDR_BITRATEMSB             = 0x03
#define HRF_ADDR_BITRATELSB             = 0x04
#define HRF_ADDR_FDEVMSB                = 0x05
#define HRF_ADDR_FDEVLSB                = 0x06
#define HRF_ADDR_FRMSB                  = 0x07
#define HRF_ADDR_FRMID                  = 0x08
#define HRF_ADDR_FRLSB                  = 0x09
#define HRF_ADDR_AFCCTRL                = 0x0B
#define HRF_ADDR_LNA                    = 0x18
#define HRF_ADDR_RXBW                   = 0x19
#define HRF_ADDR_AFCFEI                 = 0x1E
#define HRF_ADDR_IRQFLAGS1              = 0x27
#define HRF_ADDR_IRQFLAGS2              = 0x28
#define HRF_ADDR_RSSITHRESH             = 0x29
#define HRF_ADDR_PREAMBLELSB            = 0x2D
#define HRF_ADDR_SYNCCONFIG             = 0x2E
#define HRF_ADDR_SYNCVALUE1             = 0x2F
#define HRF_ADDR_SYNCVALUE2             = 0x30
#define HRF_ADDR_SYNCVALUE3             = 0x31
#define HRF_ADDR_SYNCVALUE4             = 0x32
#define HRF_ADDR_PACKETCONFIG1          = 0x37
#define HRF_ADDR_PAYLOADLEN             = 0x38
#define HRF_ADDR_NODEADDRESS            = 0x39
#define HRF_ADDR_FIFOTHRESH             = 0x3C

// Masks to set and clear bits
#define HRF_MASK_REGDATAMODUL_OOK       = 0x08
#define HRF_MASK_REGDATAMODUL_FSK       = 0x00
#define HRF_MASK_WRITE_DATA             = 0x80
#define HRF_MASK_MODEREADY              = 0x80
#define HRF_MASK_FIFONOTEMPTY           = 0x40
#define HRF_MASK_FIFOLEVEL              = 0x20
#define HRF_MASK_FIFOOVERRUN            = 0x10
#define HRF_MASK_PACKETSENT             = 0x08
#define HRF_MASK_TXREADY                = 0x20
#define HRF_MASK_PACKETMODE             = 0x60
#define HRF_MASK_MODULATION             = 0x18
#define HRF_MASK_PAYLOADRDY             = 0x04

// Radio modes
#define HRF_MODE_STANDBY                = 0x04	// Standby
#define HRF_MODE_TRANSMITER             = 0x0C	// Transmiter
#define HRF_MODE_RECEIVER               = 0x10	// Receiver

// Values to store in registers
//TODO some of these are energenie radio config specific

#define HRF_VAL_REGDATAMODUL_FSK        = 0x00	// Modulation scheme FSK
#define HRF_VAL_REGDATAMODUL_OOK        = 0x08	// Modulation scheme OOK
#define HRF_VAL_FDEVMSB30               = 0x01	// frequency deviation 5kHz 0x0052 -> 30kHz 0x01EC
#define HRF_VAL_FDEVLSB30               = 0xEC	// frequency deviation 5kHz 0x0052 -> 30kHz 0x01EC
#define HRF_VAL_FRMSB434                = 0x6C	// carrier freq -> 434.3MHz 0x6C9333
#define HRF_VAL_FRMID434                = 0x93	// carrier freq -> 434.3MHz 0x6C9333
#define HRF_VAL_FRLSB434                = 0x33	// carrier freq -> 434.3MHz 0x6C9333
#define HRF_VAL_FRMSB433                = 0x6C	// carrier freq -> 433.92MHz 0x6C7AE1
#define HRF_VAL_FRMID433                = 0x7A	// carrier freq -> 433.92MHz 0x6C7AE1
#define HRF_VAL_FRLSB433                = 0xE1	// carrier freq -> 433.92MHz 0x6C7AE1
#define HRF_VAL_AFCCTRLS                = 0x00	// standard AFC routine
#define HRF_VAL_AFCCTRLI                = 0x20	// improved AFC routine
#define HRF_VAL_LNA50                   = 0x08	// LNA input impedance 50 ohms
#define HRF_VAL_LNA50G                  = 0x0E	// LNA input impedance 50 ohms, LNA gain -> 48db
#define HRF_VAL_LNA200                  = 0x88	// LNA input impedance 200 ohms
#define HRF_VAL_RXBW60                  = 0x43	// channel filter bandwidth 10kHz -> 60kHz  page:26
#define HRF_VAL_RXBW120                 = 0x41	// channel filter bandwidth 120kHz
#define HRF_VAL_AFCFEIRX                = 0x04	// AFC is performed each time RX mode is entered

//TODO: These might be energenie config specific
#define HRF_VAL_RSSITHRESH220           = 0xDC	// RSSI threshold 0xE4 -> 0xDC (220)
#define HRF_VAL_PREAMBLELSB3            = 0x03	// preamble size LSB 3
#define HRF_VAL_PREAMBLELSB5            = 0x05	// preamble size LSB 5
#define HRF_VAL_SYNCCONFIG2             = 0x88	// Size of the Synch word = 2 (SyncSize + 1)
#define HRF_VAL_SYNCCONFIG4             = 0x98	// Size of the Synch word = 4 (SyncSize + 1)
#define HRF_VAL_SYNCVALUE1FSK           = 0x2D	// 1st byte of Sync word
#define HRF_VAL_SYNCVALUE2FSK           = 0xD4	// 2nd byte of Sync word
#define HRF_VAL_SYNCVALUE1OOK           = 0x80	// 1nd byte of Sync word
#define HRF_VAL_PACKETCONFIG1FSK        = 0xA2	// Variable length, Manchester coding, Addr must match NodeAddress
#define HRF_VAL_PACKETCONFIG1FSKNO      = 0xA0	// Variable length, Manchester coding
#define HRF_VAL_PACKETCONFIG1OOK        = 0		// Fixed length, no Manchester coding
#define HRF_VAL_PAYLOADLEN255           = 0xFF	// max Length in RX, not used in Tx
#define HRF_VAL_PAYLOADLEN66            = 66	// max Length in RX, not used in Tx
#define HRF_VAL_PAYLOADLEN_OOK          = (13 + 8 * 17)	// Payload Length
#define HRF_VAL_NODEADDRESS01           = 0x01	// Node address used in address filtering
#define HRF_VAL_NODEADDRESS04           = 0x04	// Node address used in address filtering
#define HRF_VAL_FIFOTHRESH1             = 0x81	// Condition to start packet transmission: at least one byte in FIFO
#define HRF_VAL_FIFOTHRESH30            = 0x1E	// Condition to start packet transmission: wait for 30 bytes in FIFO


extern void HRF_writereg(uint8_t addr, uint8_t data);

extern uint8_t HRF_readreg(uint8_t addr);

extern void HRF_writefifo_burst(uint8_t* buf uint8_t len);

//TODO unnecessary level of runtime indirection?
//TODO where is the buffer memory defined?
//perhaps pass in buffer memory and maxlen
//how do we know the actual length of buffer written to?
//pass in ptr to len variable
extern uint8_t* HRF_readfifo_burst(void);

extern HRF_RESULT HRF_checkreg(uint8_t addr, uint8_t mask, uint8_t value);

extern void HRF_pollreg(uint8_t addr, uint8_t mask, uint8_t value);

extern void HRF_wait_ready(void);

extern void HRF_wait_txready(void);

extern void HRF_change_mode(uint8_t mode);

extern void HRF_clear_fifo(void);

extern HRF_RESULT HRF_check_payload(void);


//TODO unnecessary level of runtime indirection?
//TODO where is the buffer memory defined?
//perhaps pass in buffer memory and maxlen
//how do we know the actual length of buffer written to?
//pass in ptr to len variable
extern uint8_t* HRF_receive_payload(void);

extern void HRF_send_payload(uint8_t* payload, uint8_t len);

extern void HRF_config(HRF_CONFIG_REC* config, uint8_t len);

#endif

/***** END OF FILE *****/

