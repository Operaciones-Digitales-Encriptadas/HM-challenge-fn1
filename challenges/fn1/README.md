# Code Challenge: Encrypt Function 1

### 1. Define a function we will call ‘BitLength(x)=L

This function takes one 32-bit integer x as input and returns the length L of the binary string representation.

- Example 1:
Input: x = 16 (which is 10000 in binary)
Output: L = 5

- Example 2:
Input: x = 333 (which is 101001101 in binary)
Output: L = 9


### 2. Define a function ‘GenRand(x)=K'
This function takes one integer x within the interval [1, 512] and returns a random integer K with bit length equal to x.

- Example 1:
Input: x = 5
Output: A random integer with a 5-bit length

- Example 2:
Input: x = 13
Output: A random integer with a 13-bit length

### 3. Define a function 'GenKey( Var1 , Var2 ) = ( K1, K2 , K3 )'
This function takes two 32-bit integers as inputs and returns three 64-bit integers, generated as follows:

- K1 = GenRand(64 - BitLength(Var1))
- K2 = GenRand(64)
- K3 = GenRand(64 - BitLength(SqrtInt(Var1^2 + Var2^2)))

The SqrtInt function is defined as rounding the square root of Var1^2 + Var2^2 to the nearest integer.

### 4. Define a function ‘EncryptVars( Var1, Var2 ) = ( EV1, EV2, EV3,EV4 )'
This function takes two 32-bit integers Var1 and Var2 and returns the result of each of the next operations:

Call GenKey(Var1, Var2) to get three keys: K1, K2, K3.
Define:
- EV1 = K1 * Var1 + K2
- EV2 = K3 * SqrtInt(Var1^2 + Var2^2)
- EV3 = K2 / EV2
- EV4 = K3 / K1

### 5. Finally define a function 'FinalCalculation( EV1, EV2, EV3, EV4 ) = R'
- R = EV4 * ((EV1 / EV2) - EV3)


### Examples for EncryptVars:
Input: Var1 = Var2 = 10
Output: R = 0.707106

Input: Var1 = Var2 = 100
Output: R = 0.707106

Input: Var1 = 1, Var2 = 2
Output: R = 0.894427

### Resource
You can use [Wolfram|Alpha](https://www.wolframalpha.com/) to verify your results. Example commands:

`Convert 265422 to binary`

Perform large arithmetic operations for validation.
