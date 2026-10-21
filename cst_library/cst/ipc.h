#pragma once

#include "type.h"

namespace cst {

    #define IPC_SUCCESS 0
    #define IPC_ERROR 1

    // creates a IPC, Posix Socket or Windows equivelant, return is the rpc id ("file descriptor")
    i32 create_ipc(const char *name);

    // closes a IPC, Posix Socket or Windows equivelant, return is true
    i32 close_ips(const i32 ipc_id);

    i32 create_ipc_smap(const i32 ipc_id, void **shared_memory, dint size);
    i32 delete_ipc_smap(const i32 ipc_id, void **shared_memory, dint size);
    
    i32 write_ipc(const i32 ipc_id, char *out_buffer, dint *size);
    i32 read_ipc(const i32 ipc_id, char *in_buffer, dint *size);

    
}