	#.abicalls
	.option	pic0
	#.section .mdebug.abi32
	#.previous
	#.file	"test.ll"
	.text
	.globl	main
	.align	2
	#.type	main,@function
	.set	nomips16                # @main
	.ent	main
main:
	#.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# BB#0:                                 # %entryBlock
	addiu	$sp, $sp, -24
$tmp2:
	#.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)            # 4-byte Folded Spill
$tmp3:
	#.cfi_offset 31, -4
	# lui	$1, %hi($.str)
	# addiu	$4, $1, %lo($.str)
	jal	printf
	# addiu	$5, $zero, 10
	lw	$ra, 20($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	main
$tmp4:
	# .size	main, ($tmp4)-main
	#.cfi_endproc

	#.type	$.str,@object           # @.str
	#.section	.rodata,"a",@progbits
$.str:
	#.asciz	"%d"
	#.size	$.str, 3


