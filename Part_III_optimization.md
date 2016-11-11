
Table of Contents:

- [Gradient Descent](#grad)


These are my personal notes about [course cs231n](http://cs231n.stanford.edu/) from Stanford university. 

<a name='grad'></a>

## Gradient Descent

Compute the gradient of the loss function with respect to the weights. Remember, on page 11, we have two different gradients for the correct and incorrect class, respectively.

Ok, emm, do we now take the gradient of the loss function, or do we take the weights (which ones??) And then update the weights.

Repeat the process.

Gradient Descent is currently by far the most common and established way of optimizing Neural Netwowrk loss functions.

### Mini-batch gradient descent
You would need a lot of iterations in order to compute the new weights for every training sample.
It is common to use just a batch of ca. 256 samples in order to update the weights. This works because the samples are correlate.

### Stochastic Gradient Descent
Theoretically, it uses only a single example to update the weights. In practise, however, it referes to mini-batch gradient descent??