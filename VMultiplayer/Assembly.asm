IFDEF RAX
; 64 bit assembly section
.DATA           
.CODE   

GetCaller PROC 
   mov RAX, [RSP+RCX]
   ret 
GetCaller ENDP 

GetTEB PROC 
	MOV RAX, gs:[58h]
	MOV RAX, [RAX + RCX * 8]
   ret 
GetTEB ENDP 

SHUFPS_55 PROC 
	SHUFPS XMM0, XMM1, 85
   ret 
SHUFPS_55 ENDP 

SHUFPS_AA PROC 
	SHUFPS XMM0, XMM1, 170
   ret 
SHUFPS_AA ENDP 

SHUFPS_FF PROC 
	SHUFPS XMM0, XMM1, 255
   ret 
SHUFPS_FF ENDP 
 
ENDIF
 
END