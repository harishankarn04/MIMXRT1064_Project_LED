/**
 * @file    tftp_test.h
 * @brief   Header for TFTP test initialization.
 *
 * This file declares the function to initialize a test setup
 * for both the TFTP server and client.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef ETHERNETINTERFACE_TEST_TFTP_TEST_H_
#define ETHERNETINTERFACE_TEST_TFTP_TEST_H_

//------------------------------------ [ INCLUDE FILES ] ----------------------------

//------------------------------------ [ PROTOTYPES ] --------------------------------

void TftpInit(const ip_addr_t *psServerIPAddr);

#endif /* ETHERNETINTERFACE_TEST_TFTP_TEST_H_ */
