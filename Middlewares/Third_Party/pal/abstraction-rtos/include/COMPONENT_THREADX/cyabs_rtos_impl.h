/***********************************************************************************************//**
 * \file cyabs_rtos_impl.h
 *
 * \brief
 * Internal definitions for RTOS abstraction layer.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "tx_api.h"
#if defined (COMPONENT_CAT5)
#include "cyabs_rtos_impl_cat5.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
*                 Constants
******************************************************/
#define CY_RTOS_MIN_STACK_SIZE  TX_MINIMUM_STACK /**< Minimum stack size in bytes */
#define CY_RTOS_ALIGNMENT       0x00000008UL     /**< Minimum alignment for RTOS objects */
#define CY_RTOS_ALIGNMENT_MASK  0x00000007UL     /**< Checks for 8-byte alignment */


/******************************************************
*                 Type Definitions
******************************************************/

#if !defined (COMPONENT_CAT5)
// RTOS thread priority. See /ref cy_thread_priority_t in the
// cyabs_rtos_impl_cat5.h for the CAT5 thread priority definitions
typedef enum
{
    CY_RTOS_PRIORITY_MIN         = TX_MAX_PRIORITIES - 1,         /**< Minumum allowable Thread
                                                                     priority */
    CY_RTOS_PRIORITY_LOW         = (TX_MAX_PRIORITIES * 6 / 7),   /**< A low priority Thread */
    CY_RTOS_PRIORITY_BELOWNORMAL = (TX_MAX_PRIORITIES * 5 / 7),   /**< A slightly below normal
                                                                     Thread priority */
    CY_RTOS_PRIORITY_NORMAL      = (TX_MAX_PRIORITIES * 4 / 7),   /**< The normal Thread priority */
    CY_RTOS_PRIORITY_ABOVENORMAL = (TX_MAX_PRIORITIES * 3 / 7),   /**< A slightly elevated Thread
                                                                     priority */
    CY_RTOS_PRIORITY_HIGH        = (TX_MAX_PRIORITIES * 2 / 7),   /**< A high priority Thread */
    CY_RTOS_PRIORITY_REALTIME    = (TX_MAX_PRIORITIES * 1 / 7),   /**< Realtime Thread priority */
    CY_RTOS_PRIORITY_MAX         = 0                              /**< Maximum allowable Thread
                                                                     priority */
} cy_thread_priority_t;
#endif // if !defined (COMPONENT_CAT5)

typedef struct
{
    uint32_t     maxcount;
    TX_SEMAPHORE tx_semaphore;
} cy_semaphore_t;

typedef struct
{
    ULONG* mem;
    // ThreadX buffer size is a power of 2 times word size,
    // this is used to prevent memory corruption when get message from queue.
    size_t   itemsize;
    TX_QUEUE tx_queue;
} cy_queue_t;

typedef struct
{
    bool     oneshot;
    TX_TIMER tx_timer;
} cy_timer_t;

typedef TX_THREAD*              cy_thread_t;
typedef ULONG                   cy_thread_arg_t;
typedef TX_MUTEX                cy_mutex_t;
typedef TX_EVENT_FLAGS_GROUP    cy_event_t;
typedef ULONG                   cy_timer_callback_arg_t;
typedef uint32_t                cy_time_t;
typedef UINT                    cy_rtos_error_t;

#ifdef __cplusplus
} // extern "C"
#endif
