# AISD_PROJECTS
Projects made during studies within a subject "Algorithms and data structures"


Project 1:
Stack Processor
The Gedanum state has decided to conquer space. In the first stage, it plans to send a number of probes that will search for planets suitable for colonization. 
The probes must be intelligent and energy-efficient, so a new processor is needed to control them. The commission of Experts Technology Interstellar was commissioned to design it. 
After many hours of hard work and numerous flashes of genius, the Stack Translator Of Symbols, model AaD5, was created. It still requires a lot of work to start mass production, 
but in order not to waste time, you were commissioned to write an emulator of this processor. Thanks to it, the creation of probe control systems can begin much faster.

The processor has a program memory, an instruction pointer, and a stack. Program memory stores the program. A program is a sequence of instructions, and each instruction is one character. 
The instruction pointer stores the number of the instruction that will be executed next, and increments by one after each execution (for most instructions). 
The processor terminates when the instruction pointer points beyond the last instruction in the program. The first instruction is numbered 0.

The stack stores data for calculations. The stack elements are lists containing zero or more characters (digits, letters, and other symbols). 
If the list contains only digits and at most one '-' (minus) character at the end, we say that such a list contains a number. 
The youngest digit of the number is stored in the first position of the list, so the number -1234 is stored as a list 4321-.

It can be assumed that all programs will be correct, i.e. there will be no situations not foreseen in the instruction list.

The list of processor instructions is as follows:

'	apostrophe            	push an empty list on the stack
,	comma                  	pop a list from the stack
:	colon                  	put a copy of the list on the top of the stack
;	semicolon              	swap the places of the list on the top of the stack and the list directly below it
@	at	                    pop the number A off the stack, then put a copy of the list on the A-th position on the stack (0 is the top of the stack, 1 is the list directly below it etc.); program '0@ is equivalent to the instruction :
.	dot	                    read a character from standard input and append it to the beginning of the list on the top of the stack
>	greater than	          write the first character from the list on the top of the stack to standard output and pop the list off the top of the stack
!	exclamation mark	      logical negation: if the top of the stack is an empty list or a list containing a single character '0', replace it with a list containing the character '1'; 
                          otherwise replace the list on the top of the stack with a list containing the character '0'
<	less than	              pop number A off the stack, pop number B off the stack, if B < A put number 1 on the stack, otherwise put number 0 on the stack
=	equal	pop               number A off the stack, pop number B off the stack, if B = A put number 1 on the stack, otherwise put number 0 on the stack
~	tilde	                  put a number equal to the number of this instruction (the value of the instruction pointer) on the stack
?	question mark	          conditional jump: pop number T off the stack pop list W off the stack if W is not empty and does not contain only the character '0' put number T into the instruction pointer and do not increment the instruction pointer;
-	minus	negation:         if the last character of the top list is '-' (minus) remove it from the list; otherwise append '-' to the end of the list at the top of the stack
^	caret	absolute value:   if the last character of the top list is '-' (minus) remove it from the list
$	dollar	split:          detach the first character from the top list and push it onto the stack
#	hash	                  pop list A off the stack; append A to the end of the list at the top of the stack
+	plus	                  pop number A off the stack; pop number B off the stack; put number A + B on the stack
&	ampersand	              print the contents of the stack to the standard output in the format:
]	Right square bracket    pop number A off the stack; put the character with the ASCII number A on the stack
[	Left square bracket	    pop list A off the stack; put the number equal to the ASCII number of the first character from list A on the stack
remaining characters	    append this character to the top of the list at the top of the stack




Project 2:

The goal of the task is to find the shortest route through a given terrain. The terrain is divided into fields. Each field has a certain height, expressed as a non-negative integer. 
Moving to a field of height A from a field of height B takes:
A - B + 1 minutes, if A > B,
1 minute, if A ≤ B.
We can move only to fields adjacent by side, so from a given field we can move to at most four neighboring fields. We cannot leave the area described by the map.

There may be a number of lifts in the area. A lift allows you to travel from its starting point to its destination point (it is one-way). Using the lift takes a certain number of minutes. 
Additionally, lifts operate at specific times — if we are at the lift’s starting field at minute 8 and we know the lift's destination is (12, 12), it runs every 5 minutes, and the ride takes 3 minutes, 
then we will arrive at (12, 12) at minute 13 (13 = 8 + 2 + 3; 2 minutes waiting plus 3 minutes travel).

Solving the task does not require using numbers exceeding the range of the int type.




Procjet 3:

To store values indexed by sparse keys from a certain universe N, hash tables seem to be a good solution. A downside of using them may be poor access time in the pessimistic case. 
Another way to handle this task is to use a trie tree, which offers a better pessimistic time estimate.

In our task, the trie is described by two parameters: n and k. It is built in the following way: the root has n child nodes, and each of those has k more child nodes. 
To insert a key x, we start from the root. If the root is free (each node holds at most one key and possibly a value — in our case only the key), we store the value and finish the operation. 
If the root is already occupied, we search for a place by selecting the next child node using div = x mod n, and then div = div mod k, repeating until we find a free spot. 
Searching is done similarly — starting from the root and following nodes with indices mod n and then mod k until we find the value x or reach an empty child node (meaning the key is not in the tree). 
Deleting is a bit harder and requires finding the node p with the given key. If it's an internal node, a deletion candidate must be selected. 
The candidate q can be searched for in different ways but must always be a leaf node (one with no children). We use a simple strategy of always searching to the left. 
If a candidate is found, its value is copied to the node p (where key x was stored), and then node q is deleted.
