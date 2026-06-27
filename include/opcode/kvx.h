/* Compatibility shim for MDS-generated code using kvx_ names. */
#include "lvx.h"

/* Struct-tag aliases: struct kvx_X → struct lvx_X */
#define kvx_register   lvx_register
#define kvx_reloc      lvx_reloc
#define kvx_opc        lvx_opc
#define kvx_operand    lvx_operand
#define kvx_core_info  lvx_core_info

/* Relocation kind aliases */
#define KVX_REL_ABS   LVX_REL_ABS
#define KVX_REL_PC    LVX_REL_PC
#define KVX_REL_GOT   LVX_REL_GOT
#define KVX_REL_BASE  LVX_REL_BASE
#define KVX_REL_TP    LVX_REL_TP

/* Opcode flag aliases */
#define KVX_OPERAND_SIGNED    LVX_OPERAND_SIGNED
#define KVX_OPERAND_WRAPPED   LVX_OPERAND_WRAPPED
#define KVX_OPCODE_FLAG_MODE64  LVX_OPCODE_FLAG_MODE64
#define KVX_OPCODE_FLAG_MODE32  LVX_OPCODE_FLAG_MODE32
#define KVX_OPCODE_FLAG_IMMX    LVX_OPCODE_FLAG_IMMX
#define KVX_OPCODE_FLAG_CALL    LVX_OPCODE_FLAG_CALL
#define KVX_OPCODE_FLAG_LOAD    LVX_OPCODE_FLAG_LOAD
#define KVX_OPCODE_FLAG_STORE   LVX_OPCODE_FLAG_STORE
#define KVX_OPCODE_FLAG_RISCV   LVX_OPCODE_FLAG_RISCV
#define KVX_OPCODE_FLAG_COND    LVX_OPCODE_FLAG_COND

/* ELF core ID aliases (KV3 IDs kept for MDS-generated tables) */
#define ELF_KVX_CORE_BIT_SHIFT   ELF_LVX_CORE_BIT_SHIFT
#define ELF_KVX_CORE_MINOR_SHIFT ELF_LVX_CORE_MINOR_SHIFT
#define ELF_KVX_CORE_KV3         (0x03 << ELF_LVX_CORE_BIT_SHIFT)
#define ELF_KVX_CORE_KV3_1      (ELF_KVX_CORE_KV3 | (1 << (ELF_LVX_CORE_MINOR_SHIFT)))
#define ELF_KVX_CORE_KV3_2      (ELF_KVX_CORE_KV3 | (2 << (ELF_LVX_CORE_MINOR_SHIFT)))
#define ELF_KVX_CORE_KV4_1      ELF_LVX_CORE_KV4_1

/* Forward declarations for kv3 opcode tables defined in lvx-opc.c */
extern struct lvx_opc kv3_v1_optab[];
extern struct lvx_opc kv3_v2_optab[];
