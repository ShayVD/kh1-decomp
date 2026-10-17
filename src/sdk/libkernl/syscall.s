/* EE kernel syscall stubs (libkernl), sdk segment. These were assembly in
 * the original too: li $v1,N; syscall; jr $ra; nop (docs/sdk.md). */
	.set	noreorder
	.set	noat

	.section	.text.func_00257d40,"ax",@progbits
	.globl	func_00257d40
	.ent	func_00257d40
func_00257d40:  /* 0x00257D40 */
	li	$3,0
	syscall
	jr	$31
	nop
	.end	func_00257d40

	.section	.text.ResetEE,"ax",@progbits
	.globl	ResetEE
	.ent	ResetEE
ResetEE:  /* 0x00257D50 */
	li	$3,1
	syscall
	jr	$31
	nop
	.end	ResetEE

	.section	.text.SetGsCrt,"ax",@progbits
	.globl	SetGsCrt
	.ent	SetGsCrt
SetGsCrt:  /* 0x00257D60 */
	li	$3,2
	syscall
	jr	$31
	nop
	.end	SetGsCrt

	.section	.text.func_00257d70,"ax",@progbits
	.globl	func_00257d70
	.ent	func_00257d70
func_00257d70:  /* 0x00257D70 */
	li	$3,3
	syscall
	jr	$31
	nop
	.end	func_00257d70

	.section	.text.Exit,"ax",@progbits
	.globl	Exit
	.ent	Exit
Exit:  /* 0x00257D80 */
	li	$3,4
	syscall
	jr	$31
	nop
	.end	Exit

	.section	.text.func_00257d90,"ax",@progbits
	.globl	func_00257d90
	.ent	func_00257d90
func_00257d90:  /* 0x00257D90 */
	li	$3,5
	syscall
	jr	$31
	nop
	.end	func_00257d90

	.section	.text.LoadExecPS2,"ax",@progbits
	.globl	LoadExecPS2
	.ent	LoadExecPS2
LoadExecPS2:  /* 0x00257DA0 */
	li	$3,6
	syscall
	jr	$31
	nop
	.end	LoadExecPS2

	.section	.text.ExecPS2,"ax",@progbits
	.globl	ExecPS2
	.ent	ExecPS2
ExecPS2:  /* 0x00257DB0 */
	li	$3,7
	syscall
	jr	$31
	nop
	.end	ExecPS2

	.section	.text.func_00257dc0,"ax",@progbits
	.globl	func_00257dc0
	.ent	func_00257dc0
func_00257dc0:  /* 0x00257DC0 */
	li	$3,8
	syscall
	jr	$31
	nop
	.end	func_00257dc0

	.section	.text.func_00257dd0,"ax",@progbits
	.globl	func_00257dd0
	.ent	func_00257dd0
func_00257dd0:  /* 0x00257DD0 */
	li	$3,9
	syscall
	jr	$31
	nop
	.end	func_00257dd0

	.section	.text.func_00257de0,"ax",@progbits
	.globl	func_00257de0
	.ent	func_00257de0
func_00257de0:  /* 0x00257DE0 */
	li	$3,10
	syscall
	jr	$31
	nop
	.end	func_00257de0

	.section	.text.func_00257df0,"ax",@progbits
	.globl	func_00257df0
	.ent	func_00257df0
func_00257df0:  /* 0x00257DF0 */
	li	$3,11
	syscall
	jr	$31
	nop
	.end	func_00257df0

	.section	.text.func_00257e00,"ax",@progbits
	.globl	func_00257e00
	.ent	func_00257e00
func_00257e00:  /* 0x00257E00 */
	li	$3,12
	syscall
	jr	$31
	nop
	.end	func_00257e00

	.section	.text.func_00257e10,"ax",@progbits
	.globl	func_00257e10
	.ent	func_00257e10
func_00257e10:  /* 0x00257E10 */
	li	$3,13
	syscall
	jr	$31
	nop
	.end	func_00257e10

	.section	.text.func_00257e20,"ax",@progbits
	.globl	func_00257e20
	.ent	func_00257e20
func_00257e20:  /* 0x00257E20 */
	li	$3,14
	syscall
	jr	$31
	nop
	.end	func_00257e20

	.section	.text.func_00257e30,"ax",@progbits
	.globl	func_00257e30
	.ent	func_00257e30
func_00257e30:  /* 0x00257E30 */
	li	$3,15
	syscall
	jr	$31
	nop
	.end	func_00257e30

	.section	.text.AddIntcHandler,"ax",@progbits
	.globl	AddIntcHandler
	.ent	AddIntcHandler
AddIntcHandler:  /* 0x00257E40 */
	li	$3,16
	syscall
	jr	$31
	nop
	.end	AddIntcHandler

	.section	.text.AddIntcHandler2,"ax",@progbits
	.globl	AddIntcHandler2
	.ent	AddIntcHandler2
AddIntcHandler2:  /* 0x00257E50 */
	li	$3,16
	syscall
	jr	$31
	nop
	.end	AddIntcHandler2

	.section	.text.RemoveIntcHandler,"ax",@progbits
	.globl	RemoveIntcHandler
	.ent	RemoveIntcHandler
RemoveIntcHandler:  /* 0x00257E60 */
	li	$3,17
	syscall
	jr	$31
	nop
	.end	RemoveIntcHandler

	.section	.text.AddDmacHandler,"ax",@progbits
	.globl	AddDmacHandler
	.ent	AddDmacHandler
AddDmacHandler:  /* 0x00257E70 */
	li	$3,18
	syscall
	jr	$31
	nop
	.end	AddDmacHandler

	.section	.text.AddDmacHandler2,"ax",@progbits
	.globl	AddDmacHandler2
	.ent	AddDmacHandler2
AddDmacHandler2:  /* 0x00257E80 */
	li	$3,18
	syscall
	jr	$31
	nop
	.end	AddDmacHandler2

	.section	.text.RemoveDmacHandler,"ax",@progbits
	.globl	RemoveDmacHandler
	.ent	RemoveDmacHandler
RemoveDmacHandler:  /* 0x00257E90 */
	li	$3,19
	syscall
	jr	$31
	nop
	.end	RemoveDmacHandler

	.section	.text._EnableIntc,"ax",@progbits
	.globl	_EnableIntc
	.ent	_EnableIntc
_EnableIntc:  /* 0x00257EA0 */
	li	$3,20
	syscall
	jr	$31
	nop
	.end	_EnableIntc

	.section	.text._DisableIntc,"ax",@progbits
	.globl	_DisableIntc
	.ent	_DisableIntc
_DisableIntc:  /* 0x00257EB0 */
	li	$3,21
	syscall
	jr	$31
	nop
	.end	_DisableIntc

	.section	.text._EnableDmac,"ax",@progbits
	.globl	_EnableDmac
	.ent	_EnableDmac
_EnableDmac:  /* 0x00257EC0 */
	li	$3,22
	syscall
	jr	$31
	nop
	.end	_EnableDmac

	.section	.text._DisableDmac,"ax",@progbits
	.globl	_DisableDmac
	.ent	_DisableDmac
_DisableDmac:  /* 0x00257ED0 */
	li	$3,23
	syscall
	jr	$31
	nop
	.end	_DisableDmac

	.section	.text.func_00257ee0,"ax",@progbits
	.globl	func_00257ee0
	.ent	func_00257ee0
func_00257ee0:  /* 0x00257EE0 */
	li	$3,252
	syscall
	jr	$31
	nop
	.end	func_00257ee0

	.section	.text.func_00257ef0,"ax",@progbits
	.globl	func_00257ef0
	.ent	func_00257ef0
func_00257ef0:  /* 0x00257EF0 */
	li	$3,253
	syscall
	jr	$31
	nop
	.end	func_00257ef0

	.section	.text._iEnableIntc,"ax",@progbits
	.globl	_iEnableIntc
	.ent	_iEnableIntc
_iEnableIntc:  /* 0x00257F00 */
	li	$3,-26
	syscall
	jr	$31
	nop
	.end	_iEnableIntc

	.section	.text._iDisableIntc,"ax",@progbits
	.globl	_iDisableIntc
	.ent	_iDisableIntc
_iDisableIntc:  /* 0x00257F10 */
	li	$3,-27
	syscall
	jr	$31
	nop
	.end	_iDisableIntc

	.section	.text._iEnableDmac,"ax",@progbits
	.globl	_iEnableDmac
	.ent	_iEnableDmac
_iEnableDmac:  /* 0x00257F20 */
	li	$3,-28
	syscall
	jr	$31
	nop
	.end	_iEnableDmac

	.section	.text._iDisableDmac,"ax",@progbits
	.globl	_iDisableDmac
	.ent	_iDisableDmac
_iDisableDmac:  /* 0x00257F30 */
	li	$3,-29
	syscall
	jr	$31
	nop
	.end	_iDisableDmac

	.section	.text.func_00257f40,"ax",@progbits
	.globl	func_00257f40
	.ent	func_00257f40
func_00257f40:  /* 0x00257F40 */
	li	$3,-254
	syscall
	jr	$31
	nop
	.end	func_00257f40

	.section	.text.func_00257f50,"ax",@progbits
	.globl	func_00257f50
	.ent	func_00257f50
func_00257f50:  /* 0x00257F50 */
	li	$3,-255
	syscall
	jr	$31
	nop
	.end	func_00257f50

	.section	.text.CreateThread,"ax",@progbits
	.globl	CreateThread
	.ent	CreateThread
CreateThread:  /* 0x00257F60 */
	li	$3,32
	syscall
	jr	$31
	nop
	.end	CreateThread

	.section	.text.DeleteThread,"ax",@progbits
	.globl	DeleteThread
	.ent	DeleteThread
DeleteThread:  /* 0x00257F70 */
	li	$3,33
	syscall
	jr	$31
	nop
	.end	DeleteThread

	.section	.text.StartThread,"ax",@progbits
	.globl	StartThread
	.ent	StartThread
StartThread:  /* 0x00257F80 */
	li	$3,34
	syscall
	jr	$31
	nop
	.end	StartThread

	.section	.text.ExitThread,"ax",@progbits
	.globl	ExitThread
	.ent	ExitThread
ExitThread:  /* 0x00257F90 */
	li	$3,35
	syscall
	jr	$31
	nop
	.end	ExitThread

	.section	.text.ExitDeleteThread,"ax",@progbits
	.globl	ExitDeleteThread
	.ent	ExitDeleteThread
ExitDeleteThread:  /* 0x00257FA0 */
	li	$3,36
	syscall
	jr	$31
	nop
	.end	ExitDeleteThread

	.section	.text.TerminateThread,"ax",@progbits
	.globl	TerminateThread
	.ent	TerminateThread
TerminateThread:  /* 0x00257FB0 */
	li	$3,37
	syscall
	jr	$31
	nop
	.end	TerminateThread

	.section	.text.iTerminateThread,"ax",@progbits
	.globl	iTerminateThread
	.ent	iTerminateThread
iTerminateThread:  /* 0x00257FC0 */
	li	$3,-38
	syscall
	jr	$31
	nop
	.end	iTerminateThread

	.section	.text.DisableDispatchThread,"ax",@progbits
	.globl	DisableDispatchThread
	.ent	DisableDispatchThread
DisableDispatchThread:  /* 0x00257FD0 */
	li	$3,39
	syscall
	jr	$31
	nop
	.end	DisableDispatchThread

	.section	.text.EnableDispatchThread,"ax",@progbits
	.globl	EnableDispatchThread
	.ent	EnableDispatchThread
EnableDispatchThread:  /* 0x00257FE0 */
	li	$3,40
	syscall
	jr	$31
	nop
	.end	EnableDispatchThread

	.section	.text.ChangeThreadPriority,"ax",@progbits
	.globl	ChangeThreadPriority
	.ent	ChangeThreadPriority
ChangeThreadPriority:  /* 0x00257FF0 */
	li	$3,41
	syscall
	jr	$31
	nop
	.end	ChangeThreadPriority

	.section	.text.iChangeThreadPriority,"ax",@progbits
	.globl	iChangeThreadPriority
	.ent	iChangeThreadPriority
iChangeThreadPriority:  /* 0x00258000 */
	li	$3,-42
	syscall
	jr	$31
	nop
	.end	iChangeThreadPriority

	.section	.text.RotateThreadReadyQueue,"ax",@progbits
	.globl	RotateThreadReadyQueue
	.ent	RotateThreadReadyQueue
RotateThreadReadyQueue:  /* 0x00258010 */
	li	$3,43
	syscall
	jr	$31
	nop
	.end	RotateThreadReadyQueue

	.section	.text.iRotateThreadReadyQueue,"ax",@progbits
	.globl	iRotateThreadReadyQueue
	.ent	iRotateThreadReadyQueue
iRotateThreadReadyQueue:  /* 0x00258020 */
	li	$3,-44
	syscall
	jr	$31
	nop
	.end	iRotateThreadReadyQueue

	.section	.text.ReleaseWaitThread,"ax",@progbits
	.globl	ReleaseWaitThread
	.ent	ReleaseWaitThread
ReleaseWaitThread:  /* 0x00258030 */
	li	$3,45
	syscall
	jr	$31
	nop
	.end	ReleaseWaitThread

	.section	.text.iReleaseWaitThread,"ax",@progbits
	.globl	iReleaseWaitThread
	.ent	iReleaseWaitThread
iReleaseWaitThread:  /* 0x00258040 */
	li	$3,-46
	syscall
	jr	$31
	nop
	.end	iReleaseWaitThread

	.section	.text.GetThreadId,"ax",@progbits
	.globl	GetThreadId
	.ent	GetThreadId
GetThreadId:  /* 0x00258050 */
	li	$3,47
	syscall
	jr	$31
	nop
	.end	GetThreadId

	.section	.text.ReferThreadStatus,"ax",@progbits
	.globl	ReferThreadStatus
	.ent	ReferThreadStatus
ReferThreadStatus:  /* 0x00258060 */
	li	$3,48
	syscall
	jr	$31
	nop
	.end	ReferThreadStatus

	.section	.text.iReferThreadStatus,"ax",@progbits
	.globl	iReferThreadStatus
	.ent	iReferThreadStatus
iReferThreadStatus:  /* 0x00258070 */
	li	$3,-49
	syscall
	jr	$31
	nop
	.end	iReferThreadStatus

	.section	.text.SleepThread,"ax",@progbits
	.globl	SleepThread
	.ent	SleepThread
SleepThread:  /* 0x00258080 */
	li	$3,50
	syscall
	jr	$31
	nop
	.end	SleepThread

	.section	.text.WakeupThread,"ax",@progbits
	.globl	WakeupThread
	.ent	WakeupThread
WakeupThread:  /* 0x00258090 */
	li	$3,51
	syscall
	jr	$31
	nop
	.end	WakeupThread

	.section	.text.iWakeupThread,"ax",@progbits
	.globl	iWakeupThread
	.ent	iWakeupThread
iWakeupThread:  /* 0x002580A0 */
	li	$3,-52
	syscall
	jr	$31
	nop
	.end	iWakeupThread

	.section	.text.CancelWakeupThread,"ax",@progbits
	.globl	CancelWakeupThread
	.ent	CancelWakeupThread
CancelWakeupThread:  /* 0x002580B0 */
	li	$3,53
	syscall
	jr	$31
	nop
	.end	CancelWakeupThread

	.section	.text.iCancelWakeupThread,"ax",@progbits
	.globl	iCancelWakeupThread
	.ent	iCancelWakeupThread
iCancelWakeupThread:  /* 0x002580C0 */
	li	$3,-54
	syscall
	jr	$31
	nop
	.end	iCancelWakeupThread

	.section	.text.SuspendThread,"ax",@progbits
	.globl	SuspendThread
	.ent	SuspendThread
SuspendThread:  /* 0x002580D0 */
	li	$3,55
	syscall
	jr	$31
	nop
	.end	SuspendThread

	.section	.text.iSuspendThread,"ax",@progbits
	.globl	iSuspendThread
	.ent	iSuspendThread
iSuspendThread:  /* 0x002580E0 */
	li	$3,-56
	syscall
	jr	$31
	nop
	.end	iSuspendThread

	.section	.text.ResumeThread,"ax",@progbits
	.globl	ResumeThread
	.ent	ResumeThread
ResumeThread:  /* 0x002580F0 */
	li	$3,57
	syscall
	jr	$31
	nop
	.end	ResumeThread

	.section	.text.iResumeThread,"ax",@progbits
	.globl	iResumeThread
	.ent	iResumeThread
iResumeThread:  /* 0x00258100 */
	li	$3,-58
	syscall
	jr	$31
	nop
	.end	iResumeThread

	.section	.text.func_00258110,"ax",@progbits
	.globl	func_00258110
	.ent	func_00258110
func_00258110:  /* 0x00258110 */
	li	$3,59
	syscall
	jr	$31
	nop
	.end	func_00258110

	.section	.text.SetupThread,"ax",@progbits
	.globl	SetupThread
	.ent	SetupThread
SetupThread:  /* 0x00258120 */
	li	$3,60
	syscall
	jr	$31
	nop
	.end	SetupThread

	.section	.text.SetupHeap,"ax",@progbits
	.globl	SetupHeap
	.ent	SetupHeap
SetupHeap:  /* 0x00258130 */
	li	$3,61
	syscall
	jr	$31
	nop
	.end	SetupHeap

	.section	.text.EndOfHeap,"ax",@progbits
	.globl	EndOfHeap
	.ent	EndOfHeap
EndOfHeap:  /* 0x00258140 */
	li	$3,62
	syscall
	jr	$31
	nop
	.end	EndOfHeap

	.section	.text.func_00258150,"ax",@progbits
	.globl	func_00258150
	.ent	func_00258150
func_00258150:  /* 0x00258150 */
	li	$3,63
	syscall
	jr	$31
	nop
	.end	func_00258150

	.section	.text.CreateSema,"ax",@progbits
	.globl	CreateSema
	.ent	CreateSema
CreateSema:  /* 0x00258160 */
	li	$3,64
	syscall
	jr	$31
	nop
	.end	CreateSema

	.section	.text.DeleteSema,"ax",@progbits
	.globl	DeleteSema
	.ent	DeleteSema
DeleteSema:  /* 0x00258170 */
	li	$3,65
	syscall
	jr	$31
	nop
	.end	DeleteSema

	.section	.text.SignalSema,"ax",@progbits
	.globl	SignalSema
	.ent	SignalSema
SignalSema:  /* 0x00258180 */
	li	$3,66
	syscall
	jr	$31
	nop
	.end	SignalSema

	.section	.text.iSignalSema,"ax",@progbits
	.globl	iSignalSema
	.ent	iSignalSema
iSignalSema:  /* 0x00258190 */
	li	$3,-67
	syscall
	jr	$31
	nop
	.end	iSignalSema

	.section	.text.WaitSema,"ax",@progbits
	.globl	WaitSema
	.ent	WaitSema
WaitSema:  /* 0x002581A0 */
	li	$3,68
	syscall
	jr	$31
	nop
	.end	WaitSema

	.section	.text.PollSema,"ax",@progbits
	.globl	PollSema
	.ent	PollSema
PollSema:  /* 0x002581B0 */
	li	$3,69
	syscall
	jr	$31
	nop
	.end	PollSema

	.section	.text.iPollSema,"ax",@progbits
	.globl	iPollSema
	.ent	iPollSema
iPollSema:  /* 0x002581C0 */
	li	$3,-70
	syscall
	jr	$31
	nop
	.end	iPollSema

	.section	.text.ReferSemaStatus,"ax",@progbits
	.globl	ReferSemaStatus
	.ent	ReferSemaStatus
ReferSemaStatus:  /* 0x002581D0 */
	li	$3,71
	syscall
	jr	$31
	nop
	.end	ReferSemaStatus

	.section	.text.iReferSemaStatus,"ax",@progbits
	.globl	iReferSemaStatus
	.ent	iReferSemaStatus
iReferSemaStatus:  /* 0x002581E0 */
	li	$3,-72
	syscall
	jr	$31
	nop
	.end	iReferSemaStatus

	.section	.text.func_002581f0,"ax",@progbits
	.globl	func_002581f0
	.ent	func_002581f0
func_002581f0:  /* 0x002581F0 */
	li	$3,73
	syscall
	jr	$31
	nop
	.end	func_002581f0

	.section	.text.SetOsdConfigParam,"ax",@progbits
	.globl	SetOsdConfigParam
	.ent	SetOsdConfigParam
SetOsdConfigParam:  /* 0x00258200 */
	li	$3,74
	syscall
	jr	$31
	nop
	.end	SetOsdConfigParam

	.section	.text.GetOsdConfigParam,"ax",@progbits
	.globl	GetOsdConfigParam
	.ent	GetOsdConfigParam
GetOsdConfigParam:  /* 0x00258210 */
	li	$3,75
	syscall
	jr	$31
	nop
	.end	GetOsdConfigParam

	.section	.text.GetGsHParam,"ax",@progbits
	.globl	GetGsHParam
	.ent	GetGsHParam
GetGsHParam:  /* 0x00258220 */
	li	$3,76
	syscall
	jr	$31
	nop
	.end	GetGsHParam

	.section	.text.GetGsVParam,"ax",@progbits
	.globl	GetGsVParam
	.ent	GetGsVParam
GetGsVParam:  /* 0x00258230 */
	li	$3,77
	syscall
	jr	$31
	nop
	.end	GetGsVParam

	.section	.text.SetGsHParam,"ax",@progbits
	.globl	SetGsHParam
	.ent	SetGsHParam
SetGsHParam:  /* 0x00258240 */
	li	$3,78
	syscall
	jr	$31
	nop
	.end	SetGsHParam

	.section	.text.SetGsVParam,"ax",@progbits
	.globl	SetGsVParam
	.ent	SetGsVParam
SetGsVParam:  /* 0x00258250 */
	li	$3,79
	syscall
	jr	$31
	nop
	.end	SetGsVParam

	.section	.text.func_00258260,"ax",@progbits
	.globl	func_00258260
	.ent	func_00258260
func_00258260:  /* 0x00258260 */
	li	$3,80
	syscall
	jr	$31
	nop
	.end	func_00258260

	.section	.text.func_00258270,"ax",@progbits
	.globl	func_00258270
	.ent	func_00258270
func_00258270:  /* 0x00258270 */
	li	$3,81
	syscall
	jr	$31
	nop
	.end	func_00258270

	.section	.text.func_00258280,"ax",@progbits
	.globl	func_00258280
	.ent	func_00258280
func_00258280:  /* 0x00258280 */
	li	$3,82
	syscall
	jr	$31
	nop
	.end	func_00258280

	.section	.text.func_00258290,"ax",@progbits
	.globl	func_00258290
	.ent	func_00258290
func_00258290:  /* 0x00258290 */
	li	$3,-83
	syscall
	jr	$31
	nop
	.end	func_00258290

	.section	.text.func_002582a0,"ax",@progbits
	.globl	func_002582a0
	.ent	func_002582a0
func_002582a0:  /* 0x002582A0 */
	li	$3,84
	syscall
	jr	$31
	nop
	.end	func_002582a0

	.section	.text.func_002582b0,"ax",@progbits
	.globl	func_002582b0
	.ent	func_002582b0
func_002582b0:  /* 0x002582B0 */
	li	$3,-85
	syscall
	jr	$31
	nop
	.end	func_002582b0

	.section	.text.func_002582c0,"ax",@progbits
	.globl	func_002582c0
	.ent	func_002582c0
func_002582c0:  /* 0x002582C0 */
	li	$3,86
	syscall
	jr	$31
	nop
	.end	func_002582c0

	.section	.text.func_002582d0,"ax",@progbits
	.globl	func_002582d0
	.ent	func_002582d0
func_002582d0:  /* 0x002582D0 */
	li	$3,87
	syscall
	jr	$31
	nop
	.end	func_002582d0

	.section	.text.func_002582e0,"ax",@progbits
	.globl	func_002582e0
	.ent	func_002582e0
func_002582e0:  /* 0x002582E0 */
	li	$3,-88
	syscall
	jr	$31
	nop
	.end	func_002582e0

	.section	.text.func_002582f0,"ax",@progbits
	.globl	func_002582f0
	.ent	func_002582f0
func_002582f0:  /* 0x002582F0 */
	li	$3,89
	syscall
	jr	$31
	nop
	.end	func_002582f0

	.section	.text.func_00258300,"ax",@progbits
	.globl	func_00258300
	.ent	func_00258300
func_00258300:  /* 0x00258300 */
	li	$3,-90
	syscall
	jr	$31
	nop
	.end	func_00258300

	.section	.text.func_00258310,"ax",@progbits
	.globl	func_00258310
	.ent	func_00258310
func_00258310:  /* 0x00258310 */
	li	$3,91
	syscall
	jr	$31
	nop
	.end	func_00258310

	.section	.text.func_00258320,"ax",@progbits
	.globl	func_00258320
	.ent	func_00258320
func_00258320:  /* 0x00258320 */
	li	$3,92
	syscall
	jr	$31
	nop
	.end	func_00258320

	.section	.text.func_00258330,"ax",@progbits
	.globl	func_00258330
	.ent	func_00258330
func_00258330:  /* 0x00258330 */
	li	$3,-92
	syscall
	jr	$31
	nop
	.end	func_00258330

	.section	.text.func_00258340,"ax",@progbits
	.globl	func_00258340
	.ent	func_00258340
func_00258340:  /* 0x00258340 */
	li	$3,93
	syscall
	jr	$31
	nop
	.end	func_00258340

	.section	.text.func_00258350,"ax",@progbits
	.globl	func_00258350
	.ent	func_00258350
func_00258350:  /* 0x00258350 */
	li	$3,-93
	syscall
	jr	$31
	nop
	.end	func_00258350

	.section	.text.func_00258360,"ax",@progbits
	.globl	func_00258360
	.ent	func_00258360
func_00258360:  /* 0x00258360 */
	li	$3,94
	syscall
	jr	$31
	nop
	.end	func_00258360

	.section	.text.func_00258370,"ax",@progbits
	.globl	func_00258370
	.ent	func_00258370
func_00258370:  /* 0x00258370 */
	li	$3,-94
	syscall
	jr	$31
	nop
	.end	func_00258370

	.section	.text.func_00258380,"ax",@progbits
	.globl	func_00258380
	.ent	func_00258380
func_00258380:  /* 0x00258380 */
	li	$3,95
	syscall
	jr	$31
	nop
	.end	func_00258380

	.section	.text.func_00258390,"ax",@progbits
	.globl	func_00258390
	.ent	func_00258390
func_00258390:  /* 0x00258390 */
	li	$3,-95
	syscall
	jr	$31
	nop
	.end	func_00258390

	.section	.text.func_002583a0,"ax",@progbits
	.globl	func_002583a0
	.ent	func_002583a0
func_002583a0:  /* 0x002583A0 */
	li	$3,96
	syscall
	jr	$31
	nop
	.end	func_002583a0

	.section	.text.func_002583b0,"ax",@progbits
	.globl	func_002583b0
	.ent	func_002583b0
func_002583b0:  /* 0x002583B0 */
	li	$3,97
	syscall
	jr	$31
	nop
	.end	func_002583b0

	.section	.text.func_002583c0,"ax",@progbits
	.globl	func_002583c0
	.ent	func_002583c0
func_002583c0:  /* 0x002583C0 */
	li	$3,98
	syscall
	jr	$31
	nop
	.end	func_002583c0

	.section	.text.func_002583d0,"ax",@progbits
	.globl	func_002583d0
	.ent	func_002583d0
func_002583d0:  /* 0x002583D0 */
	li	$3,99
	syscall
	jr	$31
	nop
	.end	func_002583d0

	.section	.text.FlushCache,"ax",@progbits
	.globl	FlushCache
	.ent	FlushCache
FlushCache:  /* 0x002583E0 */
	li	$3,100
	syscall
	jr	$31
	nop
	.end	FlushCache

	.section	.text.func_002583f0,"ax",@progbits
	.globl	func_002583f0
	.ent	func_002583f0
func_002583f0:  /* 0x002583F0 */
	li	$3,102
	syscall
	jr	$31
	nop
	.end	func_002583f0

	.section	.text.func_00258400,"ax",@progbits
	.globl	func_00258400
	.ent	func_00258400
func_00258400:  /* 0x00258400 */
	li	$3,-103
	syscall
	jr	$31
	nop
	.end	func_00258400

	.section	.text.iFlushCache,"ax",@progbits
	.globl	iFlushCache
	.ent	iFlushCache
iFlushCache:  /* 0x00258410 */
	li	$3,-104
	syscall
	jr	$31
	nop
	.end	iFlushCache

	.section	.text.func_00258420,"ax",@progbits
	.globl	func_00258420
	.ent	func_00258420
func_00258420:  /* 0x00258420 */
	li	$3,-106
	syscall
	jr	$31
	nop
	.end	func_00258420

	.section	.text.func_00258430,"ax",@progbits
	.globl	func_00258430
	.ent	func_00258430
func_00258430:  /* 0x00258430 */
	li	$3,107
	syscall
	jr	$31
	nop
	.end	func_00258430

	.section	.text.func_00258440,"ax",@progbits
	.globl	func_00258440
	.ent	func_00258440
func_00258440:  /* 0x00258440 */
	li	$3,108
	syscall
	jr	$31
	nop
	.end	func_00258440

	.section	.text.func_00258450,"ax",@progbits
	.globl	func_00258450
	.ent	func_00258450
func_00258450:  /* 0x00258450 */
	li	$3,109
	syscall
	jr	$31
	nop
	.end	func_00258450

	.section	.text.func_00258460,"ax",@progbits
	.globl	func_00258460
	.ent	func_00258460
func_00258460:  /* 0x00258460 */
	li	$3,110
	syscall
	jr	$31
	nop
	.end	func_00258460

	.section	.text.func_00258470,"ax",@progbits
	.globl	func_00258470
	.ent	func_00258470
func_00258470:  /* 0x00258470 */
	li	$3,111
	syscall
	jr	$31
	nop
	.end	func_00258470

	.section	.text.GsGetIMR,"ax",@progbits
	.globl	GsGetIMR
	.ent	GsGetIMR
GsGetIMR:  /* 0x00258480 */
	li	$3,112
	syscall
	jr	$31
	nop
	.end	GsGetIMR

	.section	.text.iGsGetIMR,"ax",@progbits
	.globl	iGsGetIMR
	.ent	iGsGetIMR
iGsGetIMR:  /* 0x00258490 */
	li	$3,-112
	syscall
	jr	$31
	nop
	.end	iGsGetIMR

	.section	.text.GsPutIMR,"ax",@progbits
	.globl	GsPutIMR
	.ent	GsPutIMR
GsPutIMR:  /* 0x002584A0 */
	li	$3,113
	syscall
	jr	$31
	nop
	.end	GsPutIMR

	.section	.text.iGsPutIMR,"ax",@progbits
	.globl	iGsPutIMR
	.ent	iGsPutIMR
iGsPutIMR:  /* 0x002584B0 */
	li	$3,-113
	syscall
	jr	$31
	nop
	.end	iGsPutIMR

	.section	.text.SetPgifHandler,"ax",@progbits
	.globl	SetPgifHandler
	.ent	SetPgifHandler
SetPgifHandler:  /* 0x002584C0 */
	li	$3,114
	syscall
	jr	$31
	nop
	.end	SetPgifHandler

	.section	.text.SetVSyncFlag,"ax",@progbits
	.globl	SetVSyncFlag
	.ent	SetVSyncFlag
SetVSyncFlag:  /* 0x002584D0 */
	li	$3,115
	syscall
	jr	$31
	nop
	.end	SetVSyncFlag

	.section	.text.SetSyscall,"ax",@progbits
	.globl	SetSyscall
	.ent	SetSyscall
SetSyscall:  /* 0x002584E0 */
	li	$3,116
	syscall
	jr	$31
	nop
	.end	SetSyscall

	.section	.text.func_002584f0,"ax",@progbits
	.globl	func_002584f0
	.ent	func_002584f0
func_002584f0:  /* 0x002584F0 */
	li	$3,117
	syscall
	jr	$31
	nop
	.end	func_002584f0

	.section	.text.sceSifDmaStat,"ax",@progbits
	.globl	sceSifDmaStat
	.ent	sceSifDmaStat
sceSifDmaStat:  /* 0x00258500 */
	li	$3,118
	syscall
	jr	$31
	nop
	.end	sceSifDmaStat

	.section	.text.isceSifDmaStat,"ax",@progbits
	.globl	isceSifDmaStat
	.ent	isceSifDmaStat
isceSifDmaStat:  /* 0x00258510 */
	li	$3,-118
	syscall
	jr	$31
	nop
	.end	isceSifDmaStat

	.section	.text.sceSifSetDma,"ax",@progbits
	.globl	sceSifSetDma
	.ent	sceSifSetDma
sceSifSetDma:  /* 0x00258520 */
	li	$3,119
	syscall
	jr	$31
	nop
	.end	sceSifSetDma

	.section	.text.isceSifSetDma,"ax",@progbits
	.globl	isceSifSetDma
	.ent	isceSifSetDma
isceSifSetDma:  /* 0x00258530 */
	li	$3,-119
	syscall
	jr	$31
	nop
	.end	isceSifSetDma

	.section	.text.sceSifSetDChain,"ax",@progbits
	.globl	sceSifSetDChain
	.ent	sceSifSetDChain
sceSifSetDChain:  /* 0x00258540 */
	li	$3,120
	syscall
	jr	$31
	nop
	.end	sceSifSetDChain

	.section	.text.isceSifSetDChain,"ax",@progbits
	.globl	isceSifSetDChain
	.ent	isceSifSetDChain
isceSifSetDChain:  /* 0x00258550 */
	li	$3,-120
	syscall
	jr	$31
	nop
	.end	isceSifSetDChain

	.section	.text.sceSifSetReg,"ax",@progbits
	.globl	sceSifSetReg
	.ent	sceSifSetReg
sceSifSetReg:  /* 0x00258560 */
	li	$3,121
	syscall
	jr	$31
	nop
	.end	sceSifSetReg

	.section	.text.sceSifGetReg,"ax",@progbits
	.globl	sceSifGetReg
	.ent	sceSifGetReg
sceSifGetReg:  /* 0x00258570 */
	li	$3,122
	syscall
	jr	$31
	nop
	.end	sceSifGetReg

	.section	.text.ExecOSD,"ax",@progbits
	.globl	ExecOSD
	.ent	ExecOSD
ExecOSD:  /* 0x00258580 */
	li	$3,123
	syscall
	jr	$31
	nop
	.end	ExecOSD

	.section	.text.Deci2Call,"ax",@progbits
	.globl	Deci2Call
	.ent	Deci2Call
Deci2Call:  /* 0x00258590 */
	li	$3,124
	syscall
	jr	$31
	nop
	.end	Deci2Call

	.section	.text.PSMode,"ax",@progbits
	.globl	PSMode
	.ent	PSMode
PSMode:  /* 0x002585A0 */
	li	$3,125
	syscall
	jr	$31
	nop
	.end	PSMode

	.section	.text.MachineType,"ax",@progbits
	.globl	MachineType
	.ent	MachineType
MachineType:  /* 0x002585B0 */
	li	$3,126
	syscall
	jr	$31
	nop
	.end	MachineType

	.section	.text.GetMemorySize,"ax",@progbits
	.globl	GetMemorySize
	.ent	GetMemorySize
GetMemorySize:  /* 0x002585C0 */
	li	$3,127
	syscall
	jr	$31
	nop
	.end	GetMemorySize

	.section	.text.func_002585d0,"ax",@progbits
	.globl	func_002585d0
	.ent	func_002585d0
func_002585d0:  /* 0x002585D0 */
	li	$3,130
	syscall
	jr	$31
	nop
	.end	func_002585d0

	.section	.text.func_0025f3e0,"ax",@progbits
	.globl	func_0025f3e0
	.ent	func_0025f3e0
func_0025f3e0:  /* 0x0025F3E0 */
	li	$3,90
	syscall
	jr	$31
	nop
	.end	func_0025f3e0

	.section	.text.func_0025f468,"ax",@progbits
	.globl	func_0025f468
	.ent	func_0025f468
func_0025f468:  /* 0x0025F468 */
	li	$3,131
	syscall
	jr	$31
	nop
	.end	func_0025f468

	.section	.text.func_0025f5b0,"ax",@progbits
	.globl	func_0025f5b0
	.ent	func_0025f5b0
func_0025f5b0:  /* 0x0025F5B0 */
	li	$3,116
	syscall
	jr	$31
	nop
	.end	func_0025f5b0

	.section	.text.func_0025f600,"ax",@progbits
	.globl	func_0025f600
	.ent	func_0025f600
func_0025f600:  /* 0x0025F600 */
	li	$3,116
	syscall
	jr	$31
	nop
	.end	func_0025f600

	.section	.text.func_0025f610,"ax",@progbits
	.globl	func_0025f610
	.ent	func_0025f610
func_0025f610:  /* 0x0025F610 */
	li	$3,90
	syscall
	jr	$31
	nop
	.end	func_0025f610

	.section	.text.func_0025f658,"ax",@progbits
	.globl	func_0025f658
	.ent	func_0025f658
func_0025f658:  /* 0x0025F658 */
	li	$3,91
	syscall
	jr	$31
	nop
	.end	func_0025f658

	.section	.text.func_0025f780,"ax",@progbits
	.globl	func_0025f780
	.ent	func_0025f780
func_0025f780:  /* 0x0025F780 */
	li	$3,90
	syscall
	jr	$31
	nop
	.end	func_0025f780

	.section	.text.func_0025f7c0,"ax",@progbits
	.globl	func_0025f7c0
	.ent	func_0025f7c0
func_0025f7c0:  /* 0x0025F7C0 */
	li	$3,116
	syscall
	jr	$31
	nop
	.end	func_0025f7c0

	.section	.text.func_0025fa20,"ax",@progbits
	.globl	func_0025fa20
	.ent	func_0025fa20
func_0025fa20:  /* 0x0025FA20 */
	li	$3,116
	syscall
	jr	$31
	nop
	.end	func_0025fa20

	.section	.text.func_0025fa30,"ax",@progbits
	.globl	func_0025fa30
	.ent	func_0025fa30
func_0025fa30:  /* 0x0025FA30 */
	li	$3,90
	syscall
	jr	$31
	nop
	.end	func_0025fa30

	.section	.text.func_0025fa78,"ax",@progbits
	.globl	func_0025fa78
	.ent	func_0025fa78
func_0025fa78:  /* 0x0025FA78 */
	li	$3,91
	syscall
	jr	$31
	nop
	.end	func_0025fa78

	.section	.text.func_002608d0,"ax",@progbits
	.globl	func_002608d0
	.ent	func_002608d0
func_002608d0:  /* 0x002608D0 */
	li	$3,90
	syscall
	jr	$31
	nop
	.end	func_002608d0

	.section	.text.func_00260918,"ax",@progbits
	.globl	func_00260918
	.ent	func_00260918
func_00260918:  /* 0x00260918 */
	li	$3,91
	syscall
	jr	$31
	nop
	.end	func_00260918

	.section	.text.func_00260928,"ax",@progbits
	.globl	func_00260928
	.ent	func_00260928
func_00260928:  /* 0x00260928 */
	li	$3,116
	syscall
	jr	$31
	nop
	.end	func_00260928

	.section	.text.func_00260a00,"ax",@progbits
	.globl	func_00260a00
	.ent	func_00260a00
func_00260a00:  /* 0x00260A00 */
	li	$3,85
	syscall
	jr	$31
	nop
	.end	func_00260a00

	.section	.text.func_00260a10,"ax",@progbits
	.globl	func_00260a10
	.ent	func_00260a10
func_00260a10:  /* 0x00260A10 */
	li	$3,-85
	syscall
	jr	$31
	nop
	.end	func_00260a10

	.section	.text.func_00260a20,"ax",@progbits
	.globl	func_00260a20
	.ent	func_00260a20
func_00260a20:  /* 0x00260A20 */
	li	$3,86
	syscall
	jr	$31
	nop
	.end	func_00260a20

	.section	.text.func_00260a60,"ax",@progbits
	.globl	func_00260a60
	.ent	func_00260a60
func_00260a60:  /* 0x00260A60 */
	li	$3,-86
	syscall
	jr	$31
	nop
	.end	func_00260a60

	.section	.text.func_00260a70,"ax",@progbits
	.globl	func_00260a70
	.ent	func_00260a70
func_00260a70:  /* 0x00260A70 */
	li	$3,87
	syscall
	jr	$31
	nop
	.end	func_00260a70

	.section	.text.func_00260a80,"ax",@progbits
	.globl	func_00260a80
	.ent	func_00260a80
func_00260a80:  /* 0x00260A80 */
	li	$3,-87
	syscall
	jr	$31
	nop
	.end	func_00260a80

	.section	.text.func_00260a90,"ax",@progbits
	.globl	func_00260a90
	.ent	func_00260a90
func_00260a90:  /* 0x00260A90 */
	li	$3,88
	syscall
	jr	$31
	nop
	.end	func_00260a90

	.section	.text.func_00260aa0,"ax",@progbits
	.globl	func_00260aa0
	.ent	func_00260aa0
func_00260aa0:  /* 0x00260AA0 */
	li	$3,-88
	syscall
	jr	$31
	nop
	.end	func_00260aa0

	.section	.text.func_00260ab0,"ax",@progbits
	.globl	func_00260ab0
	.ent	func_00260ab0
func_00260ab0:  /* 0x00260AB0 */
	li	$3,89
	syscall
	jr	$31
	nop
	.end	func_00260ab0

	.section	.text.func_002655f8,"ax",@progbits
	.globl	func_002655f8
	.ent	func_002655f8
func_002655f8:  /* 0x002655F8 */
	li	$3,128
	syscall
	jr	$31
	nop
	.end	func_002655f8
