// SPDX-License-Identifier: GPL-2.0
/* Copyright (C) 2018-2019 Jiaxun Yang <jiaxun.yang@flygoat.com> */
/* Access PCI Config Space - libpci */

#include "nb_smu_ops.h"

pci_obj_t init_pci_obj(){
    pci_obj_t obj;
    obj = pci_alloc();
    pci_init(obj);
    return obj;
}

nb_t get_nb(pci_obj_t obj){
    nb_t nb;
    nb = pci_get_dev(obj, 0, 0, 0, 0);
    pci_fill_info(nb, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
    return nb;
}

int free_pci_obj(pci_obj_t obj){
    pci_cleanup(obj);
    return 0;
}

u32 nb_reg_read(nb_t nb, u32 addr)
{
    pci_write_long(nb, NB_PCI_REG_ADDR_ADDR, (addr & (~0x3)));
    return pci_read_long(nb, NB_PCI_REG_DATA_ADDR);
}

void nb_reg_write(nb_t nb, u32 addr, u32 data)
{
    pci_write_long(nb, NB_PCI_REG_ADDR_ADDR, addr);
    pci_write_long(nb, NB_PCI_REG_DATA_ADDR, data);
}
