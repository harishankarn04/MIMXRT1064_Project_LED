/**
 * @file    ReceivingMessageQueue.h
 * @brief   EMP receive queue module for buffering incoming UDP messages before parsing.
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 */

#ifndef RECEIVING_MESSAGE_QUEUE_H
#define RECEIVING_MESSAGE_QUEUE_H

#include <stdint.h>
#include "lwip/ip_addr.h"

#define MAX_UDP_PAYLOAD_SIZE      1536U
#define MAX_RECEIVE_QUEUE_SIZE    10U

/**
 * @brief Enqueues a new raw UDP message into the receive queue.
 *
 * @param pubData     Pointer to the received UDP payload.
 * @param us_len      Length of the payload in bytes.
 * @param pxSrcIp     Pointer to the source IP address.
 * @param usSrcPort   Source UDP port number.
 *
 * @return uint8_t    1 = Success, 0 = Failure (invalid input or queue full)
 */
uint8_t ReceivingMessageQueue_EnqueueUDPBuffer(const uint8_t *pubData, uint16_t us_len,
                            const ip_addr_t *pxSrcIp, uint16_t usSrcPort);

/**
 * @brief Dequeues the next available raw UDP message from the queue.
 *
 * @param pubData     Pointer to the buffer to copy the payload into.
 * @param pusLen      Pointer to store the payload length.
 * @param pxSrcIp     Pointer to store the source IP address.
 * @param pusSrcPort  Pointer to store the source UDP port.
 *
 * @return uint8_t    1 = Success, 0 = Failure (queue empty or null pointer)
 */
uint8_t ReceivingMessageQueue_DequeueUDPBuffer(uint8_t *pubData, uint16_t *pusLen,
                            ip_addr_t *pxSrcIp, uint16_t *pusSrcPort);

/**
 * @brief Checks if the receiving queue is empty.
 *
 * @return uint8_t    1 = Queue is empty, 0 = Queue has one or more messages
 */
uint8_t ReceivingMessageQueue_IsEmpty(void);

/**
 * @brief Initializes the receiving message queue.
 *
 * Resets queue state and clears the buffer.
 */
void ReceivingMessageQueue_Init(void);

#endif // RECEIVING_MESSAGE_QUEUE_H
