﻿/**
 * libatbus_channel_export.h
 *
 *  Created on: 2014年8月13日
 *      Author: owent
 */


#pragma once

#ifndef LIBATBUS_CHANNEL_EXPORT_H
#define LIBATBUS_CHANNEL_EXPORT_H

#pragma once

#include <cstddef>
#include <ostream>
#include <stdint.h>
#include <string>
#include <utility>

#include "libatbus_adapter_libuv.h"

#include "libatbus_config.h"

#include "libatbus_channel_types.h"

namespace atbus {
    namespace channel {
        // utility functions
        extern ATBUS_MACRO_API bool make_address(const char *in, channel_address_t &addr);
        extern ATBUS_MACRO_API void make_address(const char *scheme, const char *host, int port, channel_address_t &addr);

        // memory channel
        extern ATBUS_MACRO_API int mem_configure_set_write_timeout(mem_channel *channel, uint64_t ms);
        extern ATBUS_MACRO_API uint64_t mem_configure_get_write_timeout(mem_channel *channel);
        extern ATBUS_MACRO_API int mem_configure_set_write_retry_times(mem_channel *channel, size_t times);
        extern ATBUS_MACRO_API size_t mem_configure_get_write_retry_times(mem_channel *channel);
        extern ATBUS_MACRO_API uint16_t mem_info_get_version(mem_channel *channel);
        extern ATBUS_MACRO_API uint16_t mem_info_get_align_size(mem_channel *channel);
        extern ATBUS_MACRO_API uint16_t mem_info_get_host_size(mem_channel *channel);

        extern ATBUS_MACRO_API int mem_attach(void *buf, size_t len, mem_channel **channel, const mem_conf *conf);
        extern ATBUS_MACRO_API int mem_init(void *buf, size_t len, mem_channel **channel, const mem_conf *conf);
        extern ATBUS_MACRO_API int mem_send(mem_channel *channel, const void *buf, size_t len);
        extern ATBUS_MACRO_API int mem_recv(mem_channel *channel, void *buf, size_t len, size_t *recv_size);
        extern ATBUS_MACRO_API std::pair<size_t, size_t> mem_last_action();
        extern ATBUS_MACRO_API void mem_show_channel(mem_channel *channel, std::ostream &out, bool need_node_status, size_t need_node_data);

        extern ATBUS_MACRO_API void mem_stats_get_error(mem_channel *channel, mem_stats_block_error &out);

#ifdef ATBUS_CHANNEL_SHM
        // shared memory channel
        extern ATBUS_MACRO_API int shm_configure_set_write_timeout(shm_channel *channel, uint64_t ms);
        extern ATBUS_MACRO_API uint64_t shm_configure_get_write_timeout(shm_channel *channel);
        extern ATBUS_MACRO_API int shm_configure_set_write_retry_times(shm_channel *channel, size_t times);
        extern ATBUS_MACRO_API size_t shm_configure_get_write_retry_times(shm_channel *channel);
        extern ATBUS_MACRO_API uint16_t shm_info_get_version(shm_channel *channel);
        extern ATBUS_MACRO_API uint16_t shm_info_get_align_size(shm_channel *channel);
        extern ATBUS_MACRO_API uint16_t shm_info_get_host_size(shm_channel *channel);

        extern ATBUS_MACRO_API int shm_attach(key_t shm_key, size_t len, shm_channel **channel, const shm_conf *conf);
        extern ATBUS_MACRO_API int shm_init(key_t shm_key, size_t len, shm_channel **channel, const shm_conf *conf);
        extern ATBUS_MACRO_API int shm_close(key_t shm_key);
        extern ATBUS_MACRO_API int shm_send(shm_channel *channel, const void *buf, size_t len);
        extern ATBUS_MACRO_API int shm_recv(shm_channel *channel, void *buf, size_t len, size_t *recv_size);
        extern ATBUS_MACRO_API std::pair<size_t, size_t> shm_last_action();
        extern ATBUS_MACRO_API void shm_show_channel(shm_channel *channel, std::ostream &out, bool need_node_status, size_t need_node_data);

        extern ATBUS_MACRO_API void shm_stats_get_error(shm_channel *channel, shm_stats_block_error &out);
#endif

        // stream channel(tcp,pipe(unix socket) and etc. udp is not a stream)
        extern ATBUS_MACRO_API void io_stream_init_configure(io_stream_conf *conf);

        extern ATBUS_MACRO_API int io_stream_init(io_stream_channel *channel, adapter::loop_t *ev_loop, const io_stream_conf *conf);

        // it will block and wait for all connections are disconnected success.
        extern ATBUS_MACRO_API int io_stream_close(io_stream_channel *channel);

        extern ATBUS_MACRO_API int io_stream_run(io_stream_channel *channel, adapter::run_mode_t mode = adapter::RUN_NOWAIT);

        extern ATBUS_MACRO_API int io_stream_listen(io_stream_channel *channel, const channel_address_t &addr, io_stream_callback_t callback,
                                    void *priv_data, size_t priv_size);

        extern ATBUS_MACRO_API int io_stream_connect(io_stream_channel *channel, const channel_address_t &addr, io_stream_callback_t callback,
                                     void *priv_data, size_t priv_size);

        extern ATBUS_MACRO_API int io_stream_disconnect(io_stream_channel *channel, io_stream_connection *connection, io_stream_callback_t callback);
        extern ATBUS_MACRO_API int io_stream_disconnect_fd(io_stream_channel *channel, adapter::fd_t fd, io_stream_callback_t callback);
        extern ATBUS_MACRO_API int io_stream_try_write(io_stream_connection *connection);
        extern ATBUS_MACRO_API int io_stream_send(io_stream_connection *connection, const void *buf, size_t len);
        extern ATBUS_MACRO_API size_t io_stream_get_max_unix_socket_length();

        extern ATBUS_MACRO_API void io_stream_show_channel(io_stream_channel *channel, std::ostream &out);
    } // namespace channel
} // namespace atbus


#endif /* LIBATBUS_CHANNEL_EXPORT_H_ */
