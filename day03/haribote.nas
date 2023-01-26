ORG 0xc200

; 程序开始
    MOV     AL, 0x13        ; VGA显卡，320x200x8位彩色
    MOV     AH, 0x00 
    INT     0x10

fin:
    HLT
    JMP     fin
