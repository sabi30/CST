#pragma once
#include "type.h"
#include "list.h"

namespace cst {
    struct slot {
        u32 generation;
        bool active;
    };

    struct handle {
        u32 index;
        u32 generation;
    };
    
    template<typename T, typename IS = u32>
    struct slotmap {
        cst::list<slot> slots;          
        cst::list<T> data;  
        cst::list<IS> free_list;

        void init() {
            data.init();
            free_list.init();
            slots.init();
        }

        handle create(const T item) {
            IS index;

            if (!free_list.empty()) {
                index = free_list.back();
                free_list.pop_back();
            } else {
                index = static_cast<IS>(slots.size());
                slots.insert({});
                data.resize(slots.size());
            }
        
            slots[index]->active = true;
            *data[index] = item;

            return handle{ index, slots[index]->generation };
        }

        void destroy(const handle h) {
            if (h.index >= slots.size()) return;
            slot& slot = *slots[h.index];
    
            if (!slot.active || slot.generation != h.generation) {
                return;
            }
    
            slot.active = false;
            slot.generation++; 
            free_list.push_back(h.index);
        }

        T* get(handle h) {
            if (h.index >= slots.size()) return nullptr;
            slot& slot = *slots[h.index];
    
            if (!slot.active || slot.generation != h.generation) {
                return nullptr; 
            }
    
            return data[h.index];
        }

        void clear() {
            data.clear();
            free_list.clear();
            slots.clear();
        }
        
    };
}