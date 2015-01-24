	.abicalls
	.section .mdebug.abi32
	.previous
	.file	"test1.ll"
	.section	.text.test,"axG",@progbits,test,comdat
	.weak	test
	.align	2
	.type	test,@function
	.set	nomips16                # @test
	.ent	test
test:
	.cfi_startproc
	.frame	$sp,8,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# BB#0:                                 # %methodBlock
	addiu	$sp, $sp, -8
$tmp1:
	.cfi_def_cfa_offset 8
	sw	$4, 4($sp)
	sw	$5, 0($sp)
	move	 $2, $5
	jr	$ra
	addiu	$sp, $sp, 8
	.set	at
	.set	macro
	.set	reorder
	.end	test
$tmp2:
	.size	test, ($tmp2)-test
	.cfi_endproc

	.section	.text.temp,"axG",@progbits,temp,comdat
	.weak	temp
	.align	2
	.type	temp,@function
	.set	nomips16                # @temp
	.ent	temp
temp:
	.cfi_startproc
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# BB#0:                                 # %methodBlock
	jr	$ra
	addiu	$2, $zero, 4
	.set	at
	.set	macro
	.set	reorder
	.end	temp
$tmp3:
	.size	temp, ($tmp3)-temp
	.cfi_endproc

	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomips16                # @main
	.ent	main
main:
	.cfi_startproc
	.frame	$sp,32,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# BB#0:                                 # %entryBlock
	lui	$2, %hi(_gp_disp)
	addiu	$2, $2, %lo(_gp_disp)
	addiu	$sp, $sp, -32
$tmp6:
	.cfi_def_cfa_offset 32
	sw	$ra, 28($sp)            # 4-byte Folded Spill
	sw	$16, 24($sp)            # 4-byte Folded Spill
$tmp7:
	.cfi_offset 31, -4
$tmp8:
	.cfi_offset 16, -8
	addu	$16, $2, $25
	lw	$25, %call16(test)($16)
	addiu	$4, $sp, 16
	addiu	$5, $zero, 1000
	jalr	$25
	move	 $gp, $16
	lw	$1, %got($.str)($16)
	addiu	$4, $1, %lo($.str)
	lw	$25, %call16(printf)($16)
	move	 $5, $2
	jalr	$25
	move	 $gp, $16
	lw	$16, 24($sp)            # 4-byte Folded Reload
	lw	$ra, 28($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 32
	.set	at
	.set	macro
	.set	reorder
	.end	main
$tmp9:
	.size	main, ($tmp9)-main
	.cfi_endproc

	.type	$.str,@object           # @.str
	.section	.rodata,"a",@progbits
$.str:
	.asciz	"%d"
	.size	$.str, 3


