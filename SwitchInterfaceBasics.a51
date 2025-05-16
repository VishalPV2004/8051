; A switch is connected at P1.1 and an output LED is connected at P2.0, write logic keeping the Pull down configuration of the switch

ORG 00h
	MOV P1, #00H
	AGAIN : JNB P1.1, OVER
	        SETB P2.0
			SJMP AGAIN
	OVER :  CLR P2.0
	        SJMP AGAIN
END
