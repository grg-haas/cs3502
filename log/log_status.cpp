#include "log_status.h"

#include "../utils/base_conversions.h"
#include "../utils/lock.h"

#include "../cpu/types/instr_types.h"

#include <iostream>

static lock *print_lock = new lock;

void print_instr(instr *instruction)
{
    switch(instruction->op)
    {
        case RD:
        {
            auto args = (io_args *) instruction->args;
            std::cout << "RD reg1=" << args->reg1
                      << " reg2=" << args->reg2
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case WR:
        {
            auto args = (io_args *) instruction->args;
            std::cout << "WR reg1=" << args->reg1
                      << " reg2=" << args->reg2
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case ST:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "ST breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case LW:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "LW breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case MOV:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "MOV sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case ADD:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "ADD sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case SUB:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "SUB sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case MUL:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "MUL sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case DIV:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "DIV sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case AND:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "AND sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case OR:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "OR sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case MOVI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "MOVI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case ADDI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "ADDI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case MULI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "MULI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case DIVI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "DIVI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case LDI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "LDI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case SLT:
        {
            auto args = (r_args *) instruction->args;
            std::cout << "SLT sreg1=" << args->sreg1
                      << " sreg2=" << args->sreg2
                      << " dreg=" << args->dreg << "\n";
            break;
        }

        case SLTI:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "SLTI breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case HLT:
        {
            std::cout << "HLT\n";
            break;
        }

        case NOP:
        {
            std::cout << "NOP\n";
            break;
        }

        case JMP:
        {
            auto args = (j_args *) instruction->args;
            std::cout << "JMP addr=0x" << dec_to_hex(args->addr) << "\n";
        }

        case BEQ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BEQ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BNE:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BNE breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BEZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BEZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BNZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BNZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BGZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BGZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }

        case BLZ:
        {
            auto args = (i_args *) instruction->args;
            std::cout << "BLZ breg=" << args->breg
                      << " dreg=" << args->dreg
                      << " addr=0x" << dec_to_hex(args->addr) << "\n";
            break;
        }
    }
}

void log_status::log_cpu_fetch(unsigned int core_id, unsigned int pcb_id, unsigned int pc)
{
    if(LOG_CPU_FETCH)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (cpu_fetch): PCB " << pcb_id
                  << " fetching instruction at 0x" << dec_to_hex(pc)
                  << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_decode(unsigned int core_id, char *fetch, void *instruction)
{
    if(LOG_CPU_DECODE)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (decode): decoded instruction ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << fetch[i];
        }
        std::cout << " to ";
        print_instr((instr *) instruction);

        print_lock->notify();
    }
}

void log_status::log_cpu_execute(unsigned int core_id, void *instruction, int reg[16])
{
    if(LOG_CPU_EXECUTE)
    {
        print_lock->wait();

        switch(((instr *) instruction)->op)
        {
            case RD:
            {
                auto args = (io_args *) ((instr *) instruction)->args;
                if(args->reg2 == 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute RD):\t"
                              << " read from addr 0x" << dec_to_hex(args->addr)
                              << " to reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute RD):\t"
                              << " read from addr in reg " << args->reg2
                              << " = 0x" << dec_to_hex(reg[args->reg2])
                              << " to reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << "\n";
                }
                break;
            }

            case WR:
            {
                auto args = (io_args *) ((instr *) instruction)->args;
                if(args->reg2 == 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute WR):\t"
                              << " wrote val in reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << " to addr 0x" << dec_to_hex(args->addr)
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute WR):\t"
                              << " wrote val in reg " << args->reg1
                              << " = " << reg[args->reg1]
                              << " to addr in reg " << args->reg2
                              << " = 0x" << dec_to_hex(reg[args->reg2])
                              << "\n";
                }
                break;
            }

            case ST:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute ST):\t"
                          << " wrote val in reg " << args->breg
                          << " = " << reg[args->breg]
                          << " to addr in reg " << args->dreg
                          << " = 0x" << dec_to_hex(reg[args->dreg]) << "\n";
                break;
            }

            case LW:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute LW):\t"
                          << " read from addr in reg " << args->breg
                          << " = " << reg[args->breg]
                          << " + offset " << args->addr
                          << " = 0x" << dec_to_hex(reg[args->breg] + args->addr)
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MOV:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MOV):\t"
                          << " moved reg" << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << "\n";
                break;
            }

            case ADD:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute ADD):\t"
                          << " added reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case SUB:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute SUB):\t"
                          << " subtracted reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MUL:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MUL):\t"
                          << " multiplied reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case DIV:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute DIV):\t"
                          << " divided reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case AND:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute AND):\t"
                          << " and'd reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case OR:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute OR):\t"
                          << " or'd reg " << args->sreg1
                          << " = " << reg[args->sreg1]
                          << " and reg " << args->sreg2
                          << " = " << reg[args->sreg2]
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MOVI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MOVI):\t"
                          << " moved val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case ADDI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute ADDI):\t"
                          << " added val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case MULI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute MULI): "
                          << " multiplied val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case DIVI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute DIVI): "
                          << " divided val " << args->addr
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";
                break;
            }

            case LDI:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute LDI):\t"
                          << " moved addr 0x" << dec_to_hex(args->addr)
                          << " to reg " << args->dreg
                          << " = " << reg[args->dreg]
                          << "\n";

                break;
            }

            case SLT:
            {
                auto args = (r_args *) ((instr *) instruction)->args;
                if(reg[args->sreg1] < reg[args->sreg2])
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute SLT):\t"
                              << " set reg " << args->dreg << " to val 1"
                              << " since reg " << args->sreg1 << " = " << reg[args->sreg1]
                              << " < reg " << args->sreg2 << " = " << reg[args->sreg2]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute SLT):\t"
                              << " set reg " << args->dreg << " to val 0"
                              << " since reg " << args->sreg1 << " = " << reg[args->sreg1]
                              << " >= reg " << args->sreg2 << " = " << reg[args->sreg2]
                              << "\n";
                }

                break;
            }

            case SLTI:
            {
                //TODO
                break;
            }

            case HLT:
            {
                std::cout << "--cpu-status (" << core_id << ") (execute HLT):\t"
                          << " reached program end\n";
                break;
            }

            case NOP:
            {
                std::cout << "--cpu-status (" << core_id << ") (execute NOP):\t"
                          << " doing nothing\n";
                break;
            }

            case JMP:
            {
                auto args = (j_args *) ((instr *) instruction)->args;
                std::cout << "--cpu-status (" << core_id << ") (execute JMP):\t"
                          << "jumped to addr 0x" << args->addr
                          << "\n";
                break;
            }

            case BEQ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] == reg[args->dreg])
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEQ):\t"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " == reg " << args->dreg << " = " << reg[args->dreg]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEQ):\t"
                              << " did not branch\n";
                }

                break;
            }

            case BNE:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] != reg[args->dreg])
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNE):\t"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " != reg " << args->dreg << " = " << reg[args->dreg]
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNE):\t"
                              << " did not branch\n";
                }

                break;
            }

            case BEZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] == 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEZ):\t"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " == 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BEZ):\t"
                              << " did not branch\n";
                }

                break;
            }

            case BNZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] != 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNZ):\t"
                              << " branched to addr 0x" << dec_to_hex(args->addr)
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " != 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BNZ):\t"
                              << " did not branch\n";
                }

                break;
            }

            case BGZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] > 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BGZ): "
                              << " branched to addr 0x" << args->addr
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " > 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BGZ):\t"
                              << " did not branch\n";
                }

                break;
            }

            case BLZ:
            {
                auto args = (i_args *) ((instr *) instruction)->args;
                if(reg[args->breg] < 0)
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BLZ):\t"
                              << " branched to addr 0x" << args->addr
                              << " since reg " << args->breg << " = " << reg[args->breg]
                              << " < 0"
                              << "\n";
                }
                else
                {
                    std::cout << "--cpu-status (" << core_id << ") (execute BLZ):\t"
                              << " did not branch\n";
                }

                break;
            }
        }

        print_lock->notify();
    }
}

void log_status::log_cpu_start(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_START)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (start): executing PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_stop(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_STOP)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (stop): stopping PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_set_pcb(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_SET_PCB)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (set_pcb): loading PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_save_pcb(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_SAVE_PCB)
    {
        print_lock->wait();

        std::cout << "--cpu-status (" << core_id << ") (save_pcb): saving PCB " << pcb_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_control_init(unsigned int num_cores)
{
    if(LOG_CPU_CONTROL_INIT)
    {
        print_lock->wait();

        std::cout << "--cpu_control-status (init): initialized " << num_cores << " cores\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_control_dispatch(unsigned int core_id, unsigned int pcb_id)
{
    if(LOG_CPU_CONTROL_DISPATCH)
    {
        print_lock->wait();

        std::cout << "--cpu_control-status (dispatch_to_core): dispatching PCB "
                  << pcb_id << " to core " << core_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_cpu_control_clear(unsigned int core_id)
{
    if(LOG_CPU_CONTROL_CLEAR)
    {
        print_lock->wait();

        std::cout << "--cpu_control-status (clear_finished_cores): clearing finished core "
                   << core_id << "\n";

        print_lock->notify();
    }
}

void log_status::log_disk_init(unsigned int num_words)
{
    if(LOG_DISK_INIT)
    {
        print_lock->wait();

        std::cout << "--disk-status (init): initalized disk with " << num_words << " words\n";

        print_lock->notify();
    }
}

void log_status::log_disk_write_word(unsigned int addr, const char val[8])
{
    if(LOG_DISK_WRITE_WORD)
    {
        print_lock->wait();

        std::cout << "--disk-status (write_word): wrote val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " to addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_disk_read_word(unsigned int addr, char val[8])
{
    if(LOG_DISK_READ_WORD)
    {
        print_lock->wait();

        std::cout << "--disk-status (read_word): read val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " from addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_ram_init(unsigned int num_words)
{
    if(LOG_RAM_INIT)
    {
        print_lock->wait();

        std::cout << "--ram-status (init): initalized ram with " << num_words << " words\n";

        print_lock->notify();
    }
}

void log_status::log_ram_write_word(unsigned int addr, char val[8])
{
    if(LOG_RAM_WRITE_WORD)
    {
        print_lock->wait();

        std::cout << "--ram-status (write_word): wrote val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " to addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_ram_read_word(unsigned int addr, char val[8])
{
    if(LOG_RAM_READ_WORD)
    {
        print_lock->wait();

        std::cout << "--ram-status (read_word): read val ";
        for(int i = 0; i < 8; i++)
        {
            std::cout << val[i];
        }
        std::cout << " from addr 0x" << dec_to_hex(addr) << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_create_pcb(unsigned int pcb_id, unsigned int base_disk_address)
{
    if(LOG_LONG_CREATE_PCB)
    {
        print_lock->wait();

        std::cout << "--longterm-status (create_pcb): created PCB " << pcb_id
                  << " at disk address 0x" << dec_to_hex(base_disk_address)
                  << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_schedule_fcfs(unsigned int pcb_id, unsigned int base_ram_address)
{
    if(LOG_LONG_SCHEDULE_FCFS)
    {
        print_lock->wait();

        std::cout << "--longterm-status (schedule_fcfs): loading PCB "
                  << pcb_id << " to RAM address 0x" << dec_to_hex(base_ram_address)
                  << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_schedule_priority(unsigned int pcb_id, unsigned int priority, unsigned int base_ram_address)
{
    if(LOG_LONG_SCHEDULE_PRIORITY)
    {
        print_lock->wait();

        std::cout << "--longterm-status (schedule_priority): loading PCB "
                  << pcb_id << " (priority " << priority
                  << ") to RAM address 0x" << dec_to_hex(base_ram_address)
                  << "\n";

        print_lock->notify();
    }
}

void log_status::log_long_writeback_pcb(unsigned int pcb_id)
{
    if(LOG_LONG_WRITEBACK_PCB)
    {
        print_lock->wait();

        std::cout << "--longterm-status (writeback_pcb): writing pcb "
                  << pcb_id << " back to disk\n";

        print_lock->notify();
    }
}