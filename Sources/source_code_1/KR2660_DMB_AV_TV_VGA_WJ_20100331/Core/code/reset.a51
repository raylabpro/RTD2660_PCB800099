PUBLIC   Reset_MCU
$LIST

SoftwareIIC     SEGMENT CODE
                RSEG    SoftwareIIC
;;***********************************************************************
;;    Function : Reset_CPU                                              ;
;; Description : CPU reset                                              ;
;;       Input : none                                                   ;
;;      Output : none                                                   ;
;;***********************************************************************
Reset_MCU:
                LJMP    00000H                  ; jump to BIOS start
                MOV     ACC,#0
                PUSH    ACC
                PUSH    ACC
                RET

                END
