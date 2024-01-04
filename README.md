# coin_wanderer
**About the project:**

This is a quick C++ demo using a linked-list coin system.

All of the original source code is located within src, these files were all compiled together to create "coin_wanderer.exe"

**Running the program:**

To execute the program on a windows machine; Double click "coin_wanderer.exe" | Within a terminal you might run .\coin_wanderer.exe

**Usage / Instructions:**

•	Upon execution, an input for the board's column dimension will present itself (Input must be a whole number greater than zero).

•	Having entered a valid integer for both the column and row dimensions; the 'game' will commence.

•	Instructions are provided by entering 'h' in the '-- Enter move' field, but should display automatically upon successful board generation.

•	Move around the board with w a s d and make use of the coin system by continuously dropping coins and then moving.

•	When using the 'r' command to drop coins; You will observe that the coins are being removed from the board in the order that they were placed. E.g. dropping a coin in squares 1, 2, 3, 3, 1. The coins will be removed in that order (left to right). 

**Proposed improvements / revisions:**

The print function uses a temporary array to display the data and iterates through all coins to update it, this could be changed/improved by permanently holding an array in memory and updating it in parallel to the creation of coins, or by removing the array all together and printing square by square and iterating through each coin, depending on computational and/or memory limitations in real world scenarios.

The board also doesn't keep track of a lastCoin, middleCoin etc. pointer. These could be ways to speed up finding specific items (in this case Coins) in a linked list if we knew roughly where the target item was. E.g. similar to a binary search if the items were ordered and inserted according to some variable. In this scenario however there is no need to search for specific coins as we always destroy the first coin placed, a lastCoin variable would speed up coin creation by avoiding iterating through the entire list each time.

The print function does not handle large coin stacks well (e.g. 10+ starts throwing the columns out of alignment). This could be improved with padding/formatting the columns dynamically. Although in real-world scenarios it is likely that such things would be displayed outside of a terminal-based-environment.

**Note:**

If you have any advice on how I might have approached this differently or improved the design please feel free to reach out, I welcome constructive criticism.
