/**
 * @file    ReceivingMessageQueue.c
 * @brief   EMP receive queue implementation for buffering incoming UDP messages
 *
 * (C) Copyright Centum T&S Group 2025. All rights reserved.
 * This computer program may not be used, copied, distributed, translated, transmitted or assigned
 * without the prior written authorization of Centum T&S Group.
 *
 **/

#include "ReceivingMessageQueue.h"
#include "common/CommonDefs.h"
#include <string.h>

/**
 * @struct sRawUdpMessage
 * @brief Internal structure representing a single raw UDP message and its metadata.
 */
typedef struct
{
    uint8_t  aubPayload[MAX_UDP_PAYLOAD_SIZE];
    uint16_t usLength;
    ip_addr_t tsSourceIp;
    uint16_t usSourcePort;
} sRawUdpMessage;

/* -------- Static Queue Storage -------- */
static sRawUdpMessage s_receiveQueue[MAX_RECEIVE_QUEUE_SIZE];
static uint8_t s_ubHead;
static uint8_t s_ubTail;
static uint8_t s_ubCount;

/* -------- Function Implementations -------- */
/**
 * @brief Initialize the receiving message queue.
 *
 * Resets the queue indices, count, and clears the internal buffer.
 * Must be called before using any other queue functions.
 *
 * @return void
 */
void ReceivingMessageQueue_Init(void)
{
    s_ubHead = 0U;
    s_ubTail = 0U;
    s_ubCount = 0U;
    memset(s_receiveQueue, 0, sizeof(s_receiveQueue));
}

/**
 * @brief Enqueue a raw UDP message into the receiving queue.
 *
 * Copies the given UDP payload and its metadata (source IP and port)
 * into the next available slot in the circular queue.
 *
 * @param[in]  pubData   Pointer to the UDP payload buffer.
 * @param[in]  us_len    Length of the payload in bytes.
 * @param[in]  pxSrcIp   Pointer to the source IP address.
 * @param[in]  usSrcPort Source UDP port.
 *
 * @return 1U if the enqueue operation was successful, 0U otherwise.
 *
 * @note Enqueue will fail if:
 *       - The input pointers are NULL.
 *       - The payload length is invalid or exceeds MAX_UDP_PAYLOAD_SIZE.
 *       - The queue is already full.
 */
uint8_t ReceivingMessageQueue_EnqueueUDPBuffer(const uint8_t *pubData, uint16_t us_len,
                            const ip_addr_t *pxSrcIp, uint16_t usSrcPort)
{
    uint8_t ub_result = 0U;

    if ((pubData != NULL) && (pxSrcIp != NULL))
    {
        if ((us_len > 0U) && (us_len <= MAX_UDP_PAYLOAD_SIZE) && (s_ubCount < MAX_RECEIVE_QUEUE_SIZE))
        {
            sRawUdpMessage *pst_msg = &s_receiveQueue[s_ubTail];

            (void)memcpy(pst_msg->aubPayload, pubData, us_len);
            pst_msg->usLength     = us_len;
            pst_msg->tsSourceIp   = *pxSrcIp;
            pst_msg->usSourcePort = usSrcPort;

            s_ubTail = (s_ubTail + 1U) % MAX_RECEIVE_QUEUE_SIZE;
            s_ubCount++;

            ub_result = 1U;
        }
        else
        {
            COSLOG_ERROR("Invalid length or queue full. Len = %u, Count = %u\r\n",
                         us_len, s_ubCount);
        }
    }
    else
    {
        COSLOG_ERROR("NULL pointer input. Data = %p, SrcIp = %p\r\n",
                     (void*)pubData, (void*)pxSrcIp);
    }

    return ub_result;
}

/**
 * @brief Dequeue a raw UDP message from the receiving queue.
 *
 * Retrieves the oldest message from the queue and copies its payload
 * and metadata (source IP and port) into the provided output buffers.
 *
 * @param[out] pubData    Pointer to buffer where payload will be copied.
 * @param[out] pusLen     Pointer to store the payload length.
 * @param[out] pxSrcIp    Pointer to store the source IP address.
 * @param[out] pusSrcPort Pointer to store the source UDP port.
 *
 * @return 1U if dequeue operation was successful, 0U otherwise.
 *
 * @note Dequeue will fail if:
 *       - The queue is empty.
 *       - Any of the output pointers are NULL.
 */
uint8_t ReceivingMessageQueue_DequeueUDPBuffer(uint8_t *pubData, uint16_t *pusLen,
                            ip_addr_t *pxSrcIp, uint16_t *pusSrcPort)
{
    uint8_t result = 0U;

    if ((s_ubCount > 0U) && (pubData != NULL) && (pusLen != NULL)
        && (pxSrcIp != NULL) && (pusSrcPort != NULL))
    {
        sRawUdpMessage *pst_msg = &s_receiveQueue[s_ubHead];

        (void)memcpy(pubData, pst_msg->aubPayload, pst_msg->usLength);
        *pusLen     = pst_msg->usLength;
        *pxSrcIp    = pst_msg->tsSourceIp;
        *pusSrcPort = pst_msg->usSourcePort;

        s_ubHead = (s_ubHead + 1U) % MAX_RECEIVE_QUEUE_SIZE;
        s_ubCount--;
        result = 1U;
    }
    else
    {
        COSLOG_ERROR("Queue empty or invalid output pointer "
                     "(queueNotEmpty=%u)\r\n", (s_ubCount > 0U) ? 1U : 0U);
    }

    return result;
}

/**
 * @brief Check if the receiving message queue is empty.
 *
 * @return 1U if the queue is empty, 0U otherwise.
 */
uint8_t ReceivingMessageQueue_IsEmpty(void)
{
    uint8_t status = 0U;

    if (s_ubCount == 0U)
    {
        status = 1U;
    }

    return status;
}
