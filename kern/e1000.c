#include <kern/e1000.h>
#include <kern/pmap.h>

// LAB 6: Your driver code here

volatile void *e1000_bar0;

struct e1000_tx_desc tda[TDA_LEN]; // transmit descriptor array

int pic_e1000_attach(struct pci_func *pcif)
{
    pci_func_enable(pcif);
    e1000_bar0 = mmio_map_region(pcif->reg_base[0], pcif->reg_size[0]);
    cprintf("status: %08x\n", *(uint32_t *)E1000_REG(E1000_STATUS));

    e1000_transmit_init();
    return 0;
}

/*
    refer to '8254x Family of Gigabit Ethernet Controllers Software Developer’s Manual'
    14.5 Transmit Initialization
*/
void e1000_transmit_init()
{
    // init the Transmit Descriptor Base Address (TDBAL/TDBAH) registers
    uint32_t *tdbal = (uint32_t *)E1000_REG(E1000_TDBAL);
    *tdbal = PADDR(tda);
    uint32_t *tdbah = (uint32_t *)E1000_REG(E1000_TDBAH);
    *tdbah = 0;

    // init the Transmit Descriptor Length (TDLEN) register
    struct e1000_tdlen_desc *tdlen = (struct e1000_tdlen_desc *)E1000_REG(E1000_TDLEN);
    tdlen->len = TDA_LEN;

    // init The Transmit Descriptor Head and Tail (TDH/TDT) registers
    uint32_t *tdh = (uint32_t *)E1000_REG(E1000_TDH);
    *tdh = 0;
    uint32_t *tdt = (uint32_t *)E1000_REG(E1000_TDT);
    *tdt = 0;

    // Configure the Collision Distance (TCTL.COLD)
    struct e1000_tctl_desc *tctl = (struct e1000_tctl_desc *)E1000_REG(E1000_TCTL);
    tctl->en = 1;
    tctl->psp = 1;
    tctl->ct = 0x10;
    tctl->cold = 0x40; // for full duplex operation

    struct e1000_tipg_desc *tipg = (struct e1000_tipg_desc *)E1000_REG(E1000_TIPG);
    tipg->ipgt = 10;
    tipg->ipgr1 = 4;
    tipg->ipgr2 = 6;
}