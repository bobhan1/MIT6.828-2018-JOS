#include <kern/e1000.h>
#include <kern/pmap.h>

// LAB 6: Your driver code here

volatile void *e1000_bar0;

static void
e1000_bar0_w(int index, int value)
{
	E1000_REG(index) = value;
	E1000_REG(E1000_CTRL);  // wait for write to finish, by reading
}

int 
pic_e1000_attach(struct pci_func *pcif)
{
	pci_func_enable(pcif);
	e1000_bar0 = mmio_map_region(pcif->reg_base[0], pcif->reg_size[0]);
	cprintf("status: %08x\n", E1000_REG(E1000_STATUS));
	return 0;
}
