
# Task:

Task is to create a simple spreadsheet editor. A table consists of cells in which values or other expressions are stored, and these cells can then be used in other cells.

The table editor must implement the following functionality:

1) Work with numbers and strings (op. other types at your discretion).
2) Basic numerical operations: addition, subtraction, multiplication, division.
3) Basic operations on strings: joining two strings, repeating a string.
4) At least 3 simple functions (e.g. sin, abs, pad, regex,...).
5) List the table and its values and formulas.
6) Saving the table (that is, its cells) into a file in a readable form. It is also possible to restore this state from the file. (And this includes defined formulas.)
7) Cells can have a value or a formula stored in them; in the case of a formula, it must update its contents based on changes in the referenced cells. Similarly, the program must detect cycles and must not allow the creation of an expression that would cause a cycle.

In addition, the application must process expressions according to one of the following principles:

1) Basic operations (at least addition, subtraction, multiplication, division, joining Strings, and repeating strings) must be nested using parentheses (e.g. ("w" * A3). ".cvut.cz") brackets can be arbitrarily nested.
2) For writing expressions, use prefix (or postfix) notation, they have the advantage that they do not require parentheses and are easier to process. In this case, however, all operations and functions must be written in one expression(e.g. A2 = CONCAT REPEAT "w" A1 REPLACE ".cvut.cz " / (. cz)$/".en").

Where can polymorphism be used? (suggested)

- cell representation: number, string, formula, …
- operations: addition, subtraction, multiplication, …
- export formats: text, binary, …
- user interface: console, ncurses, SDL, OpenGL (various variants), …

## Specification

When the program starts, the user can already start working with the table (create, edit, use various formulas),
or if the user does not know which functions are available for use, the "/help" command will display all available functions with a detailed description.

"/help" command will show following formulas:
- FORMULA [CELL : CELL]: print table from A1 to D10
- CELL = VALUE: assigns a value to the cell
- CELL = CELL: assigning other cell's value to the cell is available as well
- PRINT CELL: prints value of particular cell
- SUM(CELL, CELL): calculates the sum of a range of cells
- SIN(CELL): calculates the sine of a given angle in radians
- COS(CELL): calculates the cosine of a given angle in radians
- ABS(CELL): returns the absolute value of a number
- Basic numerical operations: counting, subtracting, multiplying, dividing

### Polymorfismus

Polymorphism is applied within the "CCell" class hierarchy, which has descendant "CInput".
The CInput class, which is a child of CCell, has a specialized behavior of accepting input.
Its child classes, CInteger and CString, inherit this behavior from their parent class.
By utilizing polymorphism, we can use the same methods for objects of different classes and easily adapt to different input values.
This makes the code more flexible and maintainable in the future.
