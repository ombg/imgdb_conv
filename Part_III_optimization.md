
Table of Contents:
- [Computing the gradient analytically with calculus](#SVMlossgrad)
- [Gradient Descent](#graddescent)

These are my personal notes about [course cs231n](http://cs231n.stanford.edu/) from Stanford university. 

<a name='SVMlossgrad'></a>
# Computing the gradient analytically with calculus

The SVM loss function calculates a loss. The more consistent the predictions, based on training samples $x_i$, are with their ground truth labels $y_i$, the lower is the SVM loss. The SVM loss is a function of the weights $W$, which we need to minimize. We do this by computing the gradient of the loss function with respect to the weights. Remember, on page 11, we have two different gradients for the correct and incorrect class, respectively.
It computes the difference of the score function and the actual score with the help of the SVM loss.

Insert equations here:

In the equations shown here, we have $\nabla_{w_{y_i}} L_{i}$ which denotes the gradient vector of the loss $L$ with respect to $w_{y_i}$. However, I am still unsure how the gradients, derivatives, etc. look like. Which of the variables is a vector, which is a matrix, what is the dimension of $\nabla_{w_{y_i}} L_{i}$ eventually? You should understand this with the help of this: 

[Derivations in ML](http://cs231n.stanford.edu/vecDerivs.pdf)

If you got it then write it down in the thesis. Maybe here as a first version.

### Gradient check
The analytically computed gradients should be checked using a numerical method. The numerical and the analytical result should contain the same gradient matrix $\nabla_{w} L$. The results can be compared using the Frobenius norm.





<a name='graddescent'></a>

# Gradient Descent


Gradient Descent is currently by far the most common and established way of optimizing Neural Network loss functions.

### Mini-batch gradient descent
You would need a lot of iterations in order to compute the new weights for every training sample.
It is common to use just a batch of ca. 256 samples in order to update the weights. This works because the samples are correlate.

### Stochastic Gradient Descent
Theoretically, it uses only a single example to update the weights. In practise, however, it refers to mini-batch gradient descent??

### Tuning the hyperparameters

<dl>
  <dt>Learning rate or step size</dt>
    <dd> The gradient matrix of the weights is multiplied by this factor. Every time, or every iteration, when a new gradient has been computed it is multiplied by this factor. If it is set too small, it might take a long time until the loss function converges. If it is set too large it might not converge at all or even diverge. (Correct?) Typical range: </dd>
  <dt>Number of iterations</dt>
    <dd></dd>
  <dt>Batch size</dt>
    <dd>The batch size determines the number of training samples which are used to update the weights in one iteration. The weights are updated with weights += - learning_rate * weights_grad. Th</dd>
  <dt>Regularization strength</dt>
    <dd></dd>

</dl>

In conclusion, the patches shown at the bottom of svm.ipynb show the actual weights and not the vectors $x_i$ , right? How is is it possible that the weights actually show the form of a car in the car picture? It must have sth to do with the score function.
