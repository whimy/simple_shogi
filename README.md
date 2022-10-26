# Simple_Shogi

## Mini shogi game program

* Shogi
* Usage of data store methods
 
-------------------------------------
# Mini Shogi game in C

This is assignment 2 of Data Structure.

> There are some instrucion that the user need to enter them manually 
> 
> Which will be display by code block above

## About board display
include:
* A 9x9 board, row(段) 1-9 from right to left, and column(筋) 1-9 from upward to downward
* 20 chess for both user:
** King 

## Usage
1. Print the initial board(Blue for playerx, and red for player y)
2. Display the turn number and which player's turn
3. Start from player x, and take turns enter above data:
4. Enter the position of assigned chess in format:x y  //need to seperate wuth space
5. Enter the position for the assigned chess to go in format:x y
```
# Example
Turn 1
Player  x:
  Enter the initial position: 9 9   //need to seperate with space
  Enter the new position: 9 8
```
6. The program will show user whether the movement is available
7. If movement available, then program will execute.If not, it would ask user to enter again
```
# Example of Error message
  You can not move to here.
  Error: 步 can only move forward one step.
  Please try again.
```
8. If the movement include eating others chess, the chess will be place in eater's 'mochigoma bag'
```
#Example
Would you like to see the detailed process?[y/n]:y
Input: 1.000000
Input: 1.000000
Output: 0
MAE: 0.000000
MSE: 0.000000
...
```

   (It usually takes some time)

8. Write each training data into a csv file named "train.csv"
9. Start Testing (Exit the test by entering 0):
        
   * Enter how much bits is your testing input: n

   * Enter the n-bits-input
```
# Example
Enter input's number of bits(Enter 0 to exit the test):4
Enter the input:0011
Output:0
```  
# Compile & Run

```sh
# Compile
cd xor_in_nn/
gcc -o main.c -lm layer.c neuron.c

# Run
./a.out
```
# Reference
[Code reference](https://medium.com/analytics-vidhya/building-neural-network-framework-in-c-using-backpropagation-8ad589a0752d) 

> Building-neural-network-framework-in-c-using-backpropagation

[Concept of Neural Network](https://towardsdatascience.com/simple-neural-network-implementation-in-c-663f51447547)

> Simple neural network implementation in C

[Concept of Neural Network](https://medium.com/datathings/neural-networks-and-backpropagation-explained-in-a-simple-way-f540a3611f5e)

> Neural networks and back-propagation explained in a simple way

[Concept of Neural Network](https://towardsdatascience.com/activation-functions-neural-networks-1cbd9f8d91d6?gi=2041018f7b46)

> Activation Functions in Neural Networks
