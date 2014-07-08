// Copyright 2014 Dirk Hutter, Dominic Eschweiler
// Interface class to access register files via bar memory transfers
#ifndef REGISTER_FILE_BAR_HPP
#define REGISTER_FILE_BAR_HPP

#include <sys/mman.h>

#include <flib/register_file.hpp>
#include <flib/pci_bar.hpp>


namespace flib
{

    class register_file_bar : public register_file
    {

    public:

        register_file_bar(pci_bar* bar, sys_bus_addr base_addr)
        : m_base_addr(base_addr)
        {
            m_bar = static_cast<uint32_t*>(bar->get_mem_ptr());
            m_bar_size = bar->get_size();
        }

        int
        get_mem(sys_bus_addr addr, void *dest, size_t dwords) override
        {
            /** sys_bus hw only supports single 32 bit reads */
            sys_bus_addr sys_addr = m_base_addr + addr;
            if( ((sys_addr + dwords) << 2) < m_bar_size)
            {
                for (size_t i = 0; i < dwords; i++)
                { *(static_cast<uint32_t*>(dest) + i) = m_bar[sys_addr + i]; }
                return 0;
            }
            else
            { return -1; }
        }

        int
        set_mem(sys_bus_addr addr, const void *source, size_t dwords) override
        {
            sys_bus_addr sys_addr = m_base_addr + addr;
            if( ((sys_addr + dwords) << 2) < m_bar_size)
            {
                memcpy(reinterpret_cast<uint8_t*>(m_bar) + (sys_addr<<2), source, dwords<<2);
                return msync( (reinterpret_cast<uint8_t*>(m_bar) + ((sys_addr<<2) & PAGE_MASK)), PAGE_SIZE, MS_SYNC);
            }
            else
            { return -1; }
        }

    protected:
        uint32_t*    m_bar; // 32 bit addressing
        size_t       m_bar_size;
        sys_bus_addr m_base_addr;
    };
}
#endif /** REGISTER_FILE_BAR_HPP */
