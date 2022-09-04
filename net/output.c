#include "ns.h"
#include <inc/lib.h>

extern union Nsipc nsipcbuf;

void transmit_packet(void *data, size_t len)
{
	int r;
	while((r = sys_try_transmit_packet(0, data, len)) < 0) {
		// if (r != -E_TRANSMIT_QUEUE_FULL) {
		// 	panic("transmit_packet: %e!\n", r);
		// }
		// cprintf("hang\n");
		sys_yield();
	}
}


void serve_output(union Nsipc *req)
{
	struct jif_pkt *pkt = &req->pkt;
	transmit_packet(pkt->jp_data, pkt->jp_len);
}

void
output(envid_t ns_envid)
{
	binaryname = "ns_output";
	envid_t from;
	int r, perm;
	int req;

	// LAB 6: Your code here:
	// 	- read a packet from the network server
	//	- send the packet to the device driver

	while(1) {
		req = ipc_recv(&from, &nsipcbuf, &perm);
		if (!(perm & PTE_P)) {
			cprintf("Invalid request from %08x: no argument page\n", from);
			continue; // just leave it hanging...
		}
		if (req == NSREQ_OUTPUT) {
			serve_output(&nsipcbuf);
		} else {
			panic("output only serve for NSREQ_OUTPUT\n");
		}
	}
}

