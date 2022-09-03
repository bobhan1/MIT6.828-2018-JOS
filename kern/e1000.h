#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#include "kern/pci.h"

#define E1000_VEN_ID            0x8086 
#define E1000_DEV_ID_82540EM    0x100E

#define E1000_CTRL     0x00000  /* Device Control - RW */
#define E1000_CTRL_DUP 0x00004  /* Device Control Duplicate (Shadow) - RW */
#define E1000_STATUS   0x00008  /* Device Status - RO */

#define E1000_REG(offset)    (*(volatile uint32_t *)(e1000_bar0 + offset))

int pic_e1000_attach(struct pci_func *pcif);


#endif  // SOL >= 6
