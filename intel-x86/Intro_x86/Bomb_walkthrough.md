	Public speaking is very easy. is pushed on to the stack with our input to string_not_equal funciton

	push eax

	edx = our input
	eax = ebp - 24

	push eax
	push edx

	ecx = 0x34333231(our input)
	edx = 0xffffd0e0

	cmp first number, 1
	bypass bomb call

	mov ebx, 1
	ebx = 1
	esi = first number address
	eax = ebx+1 = 2

	imul eax,DWORD PTR [esi+ebx*4-0x4] => 
	eax = eax * take the second number = 4

	   1 2 6 24 120 720

	arr = [1,2,6,24,120,720]

	ebx =1 
	eax = ebx + 1 = 2
	eax = eax * arr[0]
	cmp arr[1] == eax
	info
	ebx + 1 = 2

	ebx =2
	eax = [ebx + 1] = 3 address
	eax = eax * 2
	cmp 3 == eax

	no of input should be greater than 2

	cmp eax, 0x2

	3 k 8

	first input should be less than or equal to 7

	cmp    DWORD PTR [ebp-0xc],0x7

	mov eax,DWORD PTR [ebp-0xc]

	eax = our first input value = 3

	7 switch cases
	our input is mutiplied with 4

	0x80497e8+(input*4)


	mov    bl,0x6b // checks with a char
	cmp    DWORD PTR [ebp-0x4],0xfb // very case checks with a number

	0 q 777
	1 b 214
	2 k 251
	4 o 160

	input = 2

	cmp    eax,0x1 // one input check

	cmp    DWORD PTR [ebp-0x4],0x0 // input should be greater than zero

	ebx = [ebp + 0x8] = 2

	lea    eax,[ebx-0x1] //decrement ebx - 1
	push   eax

	in final recuresion when

	ebx = 1

	it jump down

	eax = 0x1
	esp = ebp-0x18

	esi = eax = 1

	end of first rec returns 1
	another return 1

					eax = 2
					1 func call

			ebx = 2
			cmp less than 1
			eax = 1
			2 func returned 1
			esi = eax = 1
			eax = 0
			3 func returned 1
			eax = 1
			eax = esi + eax = 2
			return  2

	2 func call	
	cmp less than 1
	eax = 1
	return 1

	3 func call
	cmp less than 1
	eax = 1
	return 1


	cmp     eax, 37h
	if eax == 55
	we pass the check

	recurssion example so with 9 as input we can get 55 as ouput







