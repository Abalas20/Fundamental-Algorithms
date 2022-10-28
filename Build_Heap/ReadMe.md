## Heap construction algorithms:

 ## 1. Bottom-up approach 
 ### Construction complexity: O(n)
 <img src="Images\BT.png">

 ## 2. Top-down approach
 ### Construction complexity: O(n*log(n))
 <img src="Images\TD.png">

 ## 3. Top-down VS Bottom-up:
### TD_op = Top-down construction operations
### BT_op = Bottom-up construction operations

 ### Average case
 <img src="Images\AVG.png"> 

 ### Worst case
 <img src="Images\Worst.png">

 ## Conclusion:
 ### - Bottom-up has a better complexity (O(n)) than the Top-down approach (O(n*log(n)))
 ### - Bottom-up is faster, but Top-down can handle variable dimension
 ### - Usage: Bottom-up is used for sorting, while Top-down is used for priority queues.