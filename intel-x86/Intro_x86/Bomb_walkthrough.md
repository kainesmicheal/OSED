Public speaking is very easy.

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

123456

our input should be 6 chars or len
cmp    eax,0x6

ebx = our input location = 0x0804b7c0
edx = 0
ecx = 0xffffd090
esi = 0x804b220 => point to this isrveawhobpnutfg
until edx is less than  or equal to 5, which is six iteration
cmp    edx,0x5

0th time:
al = edx+ebx*1 = 0+char string location*1 = 31
and al, 0xf = 1
movsx eax, al // our char to eax
mov al,BYTE PTR [eax+esi*1] // 0+randomcharloca*1
mov [edx+ecx*1],al = our string in to stack location
inc edx 

1st time:
al = edx+ebx*1 = 1+char string location*1 = 32
and al, 0xf = 2
movsx eax, al // our char to eax
mov al,BYTE PTR [eax+esi*1] // 1+randomcharloca*1
mov [edx+ecx*1],al = our string in to stack location
inc edx

so on till 5

push    offset aGiants  ; "giants"
lea     eax, [ebp+var_8] // our indexed input in the stack
push    eax
call    strings_not_equal
add     esp, 10h
test    eax, eax


push 0x804980b => srveaw

105 'i' 0
115 's' 1
114 'r' 2
118 'v' 3
101 'e' 4
97 'a'  5
119 'w' 6      
104 'h'7
111 'o' 8
98 'b'  9
112 'p' 10
110 'n' 11
117 'u' 12
116 't' 13
102 'f'     14  
103 'g'15

ord('m') & 0xf // find the char that and with 0xf will produce the correct index values for arr

o05km1

1 2 3 4 5 6

edx = our input string
ebp-0x34 = 0xffffd064 = 0x804b26c

linked list with 6 node, every node has two value, index and a hex value

(gdb) x/x 0x804b26c
0x804b26c <node1>:      0x000000fd
(gdb) x/x 0x804b26c+8
0x804b274 <node1+8>:    0x0804b260
(gdb) x/x 0x0804b260
0x804b260 <node2>:      0x000002d5
(gdb) x/x 0x0804b260+4
0x804b264 <node2+4>:    0x00000002
(gdb) x/x 0x0804b260+0
0x804b260 <node2>:      0x000002d5


eax = ebp-0x18 = 0xffffd080

call read_six_numbers

eax = 6

seems like a nested for loop

edi = 0
esi = esi + 0
eax = ebp-0x18 = 0xffffd0b0

eax = eax+edi*4 = start of our input in stack address * [index] * 4

(gdb) x/x 0xffffd0b0+0*4
0xffffd0b0:     0x00000001
(gdb) x/x 0xffffd0b0+1*4
0xffffd0b4:     0x00000002
(gdb) x/x 0xffffd0b0+2*4
0xffffd0b8:     0x00000003
(gdb) x/x 0xffffd0b0+3*4
0xffffd0bc:     0x00000004
(gdb) x/x 0xffffd0b0+4*4
0xffffd0c0:     0x00000005
(gdb) x/x 0xffffd0b0+5*4
0xffffd0c4:     0x00000006

dec eax

eax = eax - 1 = 0

cmp eax, 5

if less than or equal to 5 get into the next loop

checks if current index + 1 is less than 5

ebx = edi + 1 (j)

cmp ebx, 5

eax = edi * 4 + 0 = 0

mov    DWORD PTR [ebp-56],eax

esi = ebp-0x18 = 0xffffd0b0
edx = ebp-0x38 = 0 (i)
eax = edx+esi*1 = 0 + our stack input arr loc * 1

eax,DWORD PTR [esi+ebx*4] = if (i == j) 

if not equal increment j (ebx)

ebx = edx +1

this for loop goes through every value one by and one and checks wiht the rest of value 
to see if they are equal

edi = 0

ecx  = ebp - 0x18 =  0xffffd0b0
eax  = ebp - 0x30 =  0xffffd098          

ebp - 0x3c = eax

esi = [ebp-0x34] = 0x804b26c

ebx = 1

eax = edi * 4+0
edx = eax

cmp ebx,DWORD PTR [eax+ecx*1] = (1 >= 1)

if greater than or equal to 

edx = [ebp-0x3c] = 0xffffd098

edx+edi*4 = 0xffffd098 = esi

edi = edi + 1 = 1

cmp edi, 5

if less than get back agin to the same inner loop

esi = [ebp-0x34] = 0x804b26c //first node

ebx = 1

eax = edi * 4+0 = 4
edx = eax = 4

cmp    ebx, [eax+ecx*1]

(1 >= 4)

eax = edx+ecx*1 = 4+our input in stack location*1 = 2

esi = esi + 8 //take the pointer to next node current + 8

ebx = ebx + 1 = 2

cmp ebx, eax

if less than go back and inc ebx

edx = 0xffffd098

[edx+edi*4] = 0xffffd09c = 0x0804b260

edi = edi + 1 = 1 + 1 = 2

(gdb) x/3x $esi
0x804b26c <node1>:      0x000000fd      0x00000001      0x0804b260
(gdb) x/3x *($esi+8)
0x804b260 <node2>:      0x000002d5      0x00000002      0x0804b254
(gdb) x/3x *(*($esi+8)+8)
0x804b254 <node3>:      0x0000012d      0x00000003      0x0804b248
(gdb) x/3x *(*(*($esi+8)+8)+8)
0x804b248 <node4>:      0x000003e5      0x00000004      0x0804b23c
(gdb) x/3x *(*(*(*($esi+8)+8)+8)+8)
0x804b23c <node5>:      0x000000d4      0x00000005      0x0804b230
(gdb) x/3x *(*(*(*(*($esi+8)+8)+8)+8)+8)
0x804b230 <node6>:      0x000001b0      0x00000006      0x00000000

i = 0
j = 1
cn = 1
in[0] = 5
1 < 5
cn = 2
j =2
j < 5
cn = 3
j = 3
j < 5
cn = 4
j = 4
j < 5
cn = 5
j = 5
j < 5

tn = cn

this way it take the value our input as index and create a new arr of nodes with order as our input

so if our input is 1 2 3 4 5 6

i create a temp arr with n1,n2,n3,n4,n5,n6

as very node has a hex value in it, we are finally checking if the hex value is are in high to low order

i = 1
cn = tarr[0] = n1

tn = tarr[1] = n2

cn.next = tn

i = i + 1 = 2

cn = tn

i < 6

tn = tarr[2] = n3

cn.next = tn

i = i + 3 = 3

cn = tn


this loop is itreate thoru temp arr of nodes and assign very node next pointer to next nodes pointer
so that every node will have pointer to the next node.



























































