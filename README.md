# ccprog2-shuttle-service
My final machine project for my Programming with Structured Data Types class of A.Y. 2023-2024.

## Test Script
Teacher said to make a Google Docs with the test conditions:
https://docs.google.com/document/d/1lX5aKAMuXOuK5AH3mLpbo6t9NDI8_qPdFUDwmcx5Epo/edit?usp=sharing

## Coding Conventions
Make missing stuff up as you go ig but tell me before doing so, this stuff isn't set in stone obviously. Just serves as a guide.
- Tabs are 4 spaces
- Ideally stick to 80 chars per line

### Variables
Descriptive, please, even if the name is kinda long, with obvious exceptions like *i* for counters.

### Functions
```C
/*
 * functionName does this and that.
 * Precondition: assumptions made when running the function.
 * @param1: parameter description.
 * @param2: parameter description.
 * @return type what does this function return?
 */
int functionName(int param1, int* param2)
{
	int type = 0;
	return type;
}
```
Also don't be scared to create functions if stuff looks like it's geting too complicated. On the flipside don't try fancy tricks to make the code shorter if it makes it less readable. **Readability > short length**.

Comment stuff when needed too, but don't overdo it.

### Conditionals and Loops
I prefer using the braces even if there's one statement inside.
```C
if (condition) {
	// do stuff
}

while (condition) {
	// do stuff
	// do more stuff
}

int i;

for (i = 0; i < smth idk; i++) {
	// do stuff
}
```

### Structs
Tag should be defined with capital 1st letter, with no global variable. A typedef of the same name should immediately follow so we don't have to type `struct` everytime we want to reference it.
```C
struct Tag {
	// variables go here.
};

typedef struct Tag Tag;
```
