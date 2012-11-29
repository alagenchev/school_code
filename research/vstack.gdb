define vstack
	set $addtional = 2

	if $argc > 0
		set $addtional = $arg0
	end

	set $i = $rbp + 8 + 8 * $addtional

	while $i >= $rsp
		if $i == $rbp + 8
			printf "saved %crip\t", '%'
		else
			if $i == $rbp
				printf "    (%crbp)\t", '%'
			else
				if $i == $rsp
					printf "    (%crsp)\t", '%'
				else
					printf "%4d(%crbp)\t", $i - $rbp, '%'
				end
			end
		end
	
		printf "%08x %08x\t(%p -> %p)\n", *(int *)($i + 4), *(int *)$i, $i + 7, $i
	
		set $i -= 8
	end
end

document vstack
	View current stack.
	Syntax: vstack <additional>: view current stack, as well as additional quadwords from previous frame
	Notes: each entry is printed as two dword, high address is on the left
	Example:
	
	saved %rip	00000001 00000ee4	(0x7fff5fbfef8f -> 0x7fff5fbfef88)
	(%rbp)		00007fff 5fbfef98	(0x7fff5fbfef87 -> 0x7fff5fbfef80)
	-8(%rbp)	00000000 00000004	(0x7fff5fbfef7f -> 0x7fff5fbfef78)

	the saved %rip is 0x0000000100000ee4
	%rbp is 0x7fff5fbfef80, the qword addressed by (%rbp) (saved %rbp) is 0x00007fff5fbfef98
	the dword addressed by -8(%rbp) is 4
	the dword addressed by -4(%rbp) is 0
end
