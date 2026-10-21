#pragma once

#include "type.h"

namespace cst {
    // translator
    u64 translate_str_to_ip(const char*);
    
    // creates a server file descriptor
    dint create_server(const u64 ip, const u16 port, u32 *out_fd);

    // server client requests
    dint accept_client(const dint fd);
    dint close_client(const dint fd);

    // client connects to a server
    dint connect_server(const u64 ip, const u16 port);

    // basics
    void send(const dint fd, const void *buffer, const dint size);
    void recv(const dint fd, const void *out_buffer, const dint size);


    
}