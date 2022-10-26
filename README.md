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

## Usage
1. Print the initial board
2. Display the turn number and which player's turn
3. Enter the position of assigned chess in format:x y  //need to seperate wuth space
4. Enter the position for the assigned chess to go in format:x y
```
# Example
Turn 1
Player  x:
  Enter the initial position: 9 9   //need to seperate wuth space
  Enter the new position: 9 8
```
6. Enter desired output for each training example
```
# Example
Enter the Desired Outputs (Labels) for training example[0]:0
Enter the Desired Outputs (Labels) for training example[1]:1
Enter the Desired Outputs (Labels) for training example[2]:1
Enter the Desired Outputs (Labels) for training example[3]:0
```
7. Training the neural network 
   
   (You can decide whether to see the process by enter y or n)
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
