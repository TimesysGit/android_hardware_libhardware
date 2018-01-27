/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_INCLUDE_BT_IAP2_H
#define ANDROID_INCLUDE_BT_IAP2_H

__BEGIN_DECLS

/* error code - OK/Error */
typedef enum {
    BTIAP2_ERROR_NONE = 0,
    BTIAP2_ERROR_LINK_SYNC_FAILED,
    BTIAP2_ERROR_AUTH_FAILED,
    BTIAP2_ERROR_IDENT_FAILED,
    BTIAP2_ERROR_EA_FAILED,
} btiap2_error_t;

typedef enum {
    BTIAP2_CONNECTION_STATE_DISCONNECTED = 0,
    BTIAP2_CONNECTION_STATE_CONNECTING,
    BTIAP2_CONNECTION_STATE_CONNECTED,
    BTIAP2_CONNECTION_STATE_DISCONNECTING
} btiap2_connection_state_t;

typedef enum {
    BTIAP2_SERVICE_STATE_DISCONNECTED = 0,
    BTIAP2_SERVICE_STATE_CONNECTED,
} btiap2_service_state_t;

/** Callback for connection state change.
 *  state will have one of the values from BtIap2ConnectionState
 */
typedef void (* btiap2_connection_state_callback)(btiap2_connection_state_t state, bt_bdaddr_t *bd_addr);

/** Callback for service state change.
 */
typedef void (* btiap2_service_state_callback)(btiap2_service_state_t state, bt_bdaddr_t *bd_addr, int fd);

/** Callback for received data chunk.
 ****************** NOT USED
 */
typedef void (* btiap2_data_callback)(unsigned int len, unsigned char *data);

/** Callback for error recd from IAP2
 */
typedef void (* btiap2_error_callback)(btiap2_error_t code, char *error_string);

/** BT-IAP2 callback structure. */
typedef struct {
    /** set to sizeof(BtIap2Callbacks) */
    size_t      size;
    btiap2_connection_state_callback       connection_state_cb;
    btiap2_service_state_callback          service_state_cb;
    btiap2_data_callback                   data_cb;
    btiap2_error_callback                  error_cb;
} btiap2_callbacks_t;

typedef struct {

    /** set to sizeof(BtIap2Interface) */
    size_t          size;
    /**
     * Register the BtIap2 callbacks
     */
    bt_status_t (*init)( btiap2_callbacks_t* callbacks );

    /** connect to iDevice */
    bt_status_t (*connect)( bt_bdaddr_t *bd_addr );

    /** dis-connect from iDevice */
    bt_status_t (*disconnect)( bt_bdaddr_t *bd_addr );

    /** send data using EA session */
    // NOT USED
    bt_status_t (*send_data)(unsigned int len, unsigned char *data);

    /** Closes the interface. */
    void  (*cleanup)( void );
} btiap2_interface_t;

__END_DECLS

#endif /* ANDROID_INCLUDE_BT_IAP2_H */
