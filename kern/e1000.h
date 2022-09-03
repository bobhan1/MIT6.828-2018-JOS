#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#include "kern/pci.h"

#define E1000_VEN_ID 0x8086
#define E1000_DEV_ID_82540EM 0x100E

#define E1000_CTRL 0x00000     /* Device Control - RW */
#define E1000_CTRL_DUP 0x00004 /* Device Control Duplicate (Shadow) - RW */
#define E1000_STATUS 0x00008   /* Device Status - RO */
#define E1000_TCTL 0x00400     /* TX Control - RW */
#define E1000_TIPG 0x00410     /* TX Inter-packet gap -RW */

#define E1000_TDBAL 0x03800 /* TX Descriptor Base Address Low - RW */
#define E1000_TDBAH 0x03804 /* TX Descriptor Base Address High - RW */
#define E1000_TDLEN 0x03808 /* TX Descriptor Length - RW */
#define E1000_TDH 0x03810   /* TX Descriptor Head - RW */
#define E1000_TDT 0x03818   /* TX Descripotr Tail - RW */

#define TDA_LEN 64 /* the length of the transmit descriptor array */

#define E1000_REG(offset) (void *)(e1000_bar0 + offset)

int pic_e1000_attach(struct pci_func *pcif);
void e1000_transmit_init();

struct e1000_tx_desc
{
    uint64_t addr;
    uint16_t length;
    uint8_t cso;
    uint8_t cmd;
    uint8_t status;
    uint8_t css;
    uint16_t special;
} __attribute__((packed));

struct e1000_tdlen_desc
{
    uint32_t zero : 7;
    uint32_t len : 13;
    uint32_t rsv : 12;
};

struct e1000_tctl_desc
{
    uint32_t reserved1 : 1;
    uint32_t en : 1;
    uint32_t reserved2 : 1;
    uint32_t psp : 1;
    uint32_t ct : 8;
    uint32_t cold : 10;
    uint32_t swxoff : 1;
    uint32_t reserved3 : 1;
    uint32_t rtlc : 1;
    uint32_t nrtu : 1;
    uint32_t reserved4 : 6;
};

struct e1000_tipg_desc
{
    uint32_t ipgt : 10;
    uint32_t ipgr1 : 10;
    uint32_t ipgr2 : 10;
    uint32_t reserved : 2;
};

#endif // SOL >= 6
