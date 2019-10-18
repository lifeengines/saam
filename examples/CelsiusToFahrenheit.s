; --- INSTRUCTION MEMORY ---
        AREA main, CODE, READONLY
        EXPORT __main
        ENTRY

__main  PROC
        LDR r0,=Temp
        LDR r0,[r0, #0x00]
        LDR r1,=Temp
        MOV r2,#0x09
        MUL r0,r0,r2
        MOV r2,#0x05
        SDIV r0,r0,r3

        MOV r2,#0x20
        ADD r0,r0,r2
        STR r0,[r1, #0x00]
        NOP
        Self B Self
        ENDP

; --- DATA MEMORY ---

        AREA data, DATA, READWRITE

Temp    DCD 100
        END
