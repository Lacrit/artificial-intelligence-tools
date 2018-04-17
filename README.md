# Artificial Intelligence Tools
Implementing basic ML algorithms in C++.

* K Nearest Neighbours <br/>
   - Let m be the number of training data samples (iris data set). Let p be an unknown point.

   - Store the training samples in an array of data points arr[]. This means each element of this array represents a tuple (x, y).
   ```
   for i=0 to m:
   Calculate Euclidean distance d(arr[i], p).
   ```
  - Make set S of K smallest distances obtained. Each of these distances correspond to an already classified data point.
  Return the majority label among S.
  
  - [ ] Implement my own sorting function (quickselect)
  - [ ] Provide functionality to manualy input test example
  - [ ] Plot percentage

* Perceptron <br/> 
  Learning algorithm: <br/> 
  - set all weights and threshold to relatively small numbers.
  - for each case in training data: <br/>
    Calculate output of perceptron <br/>
   <img src="http://computing.dcu.ie/~humphrys/Notes/Neural/Bitmaps/rule.gif"><br/>
   Update Weights and threshold <br/>
   <img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/836eee7f6aad76f42937de5490281f6ee89e80f0" height= 35 weight=35><br/>
  - repeat step 1 until specified number of iterations is completed
  - calculate accuracy on the test set 
* One Layer Neural Network 
