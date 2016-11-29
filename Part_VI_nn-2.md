
Table of Contents:

- [Setting up the data and the model](#setup)


These are my personal notes about [course cs231n](http://cs231n.stanford.edu/) from Stanford university. 

<a name='setup'></a>

# Setting up the Data and the Model

Neural networks perform a sequence of linear mappings with interwoven non-linearities to compute the final score function.

## Data Preprocessing: How to prepare $X$

This is on how to ste up the weight matrices $W$ and how to preprocess the input data before we can start running the net. There are three common preprocessing steps for the data matrix $X$:

### 1. Mean substraction
You substract the mean of every feature point. This results in centering the data around the origin.

### 2. Feature Scaling or Normalization
Each dimension of a feature is scaled by its standard deviation. This gives equal importance to every feature if the have initialy different scales.

### ((3. Principal Component Analysis))
Rough idea: Compute the covariance matrix. It tells us how the data elements are correlated to each other. Then with the help of Singular Value Decomposition (SVD) we can compute eigenvectors and eventually get a covariance matrix which is diagonal. This matrix and the eigenvectors can be used to perform a dimensionality reduction.

#### Covariance Matrix 
The covariance matrix stores a covariance at each matrix position. It is the covariance between the $i^{th}$ and $j^{th}$ element of random vector $\vec{x}$. A random vector is one random variable with multiple dimensions.
The diagonal of the covariance matrix holds the variance values since the indices of the vector elements of the random vector(s?) are the same.

But I think you could also create the covariance matrix of two random vectors...
See 
[https://en.wikipedia.org/wiki/Covariance_matrix]
and google a bit.

### TLDR
In CNNs PCA/Whitening *is not used*. Why? However, zero-centering and normalization is very important.

## Weight initializations: How to prepare $W$ and $b$
aka Symmetry breaking

### Pitfall: All zero initialization: 
This is not good. One might think it is good, because eventually - after training the network - half of the weights should be positive, half of the weights should be negative due to a good data normalization. Their mean value (or our mean expectation) would be zero. So why not initialize all with zero? All parameters $w$ in the network would compute the same output and hence would have the same gradient. The parameter update would be the same for every weight. There wouldn't be any source of asymmetry. OK, got it. But why is this bad?

### Small random numbers:
Initialize the weights with small random numbers. This could be done with a random gaussian distribution, then every input vector points into a random direction.

### Calibrate the weights with $1/ \sqrt(n)$
The variance of the outputs would grow with above initialization. We can normalize this output to 1 by scaling the weight vector with $1/ \sqrt(n)$. $n$ is the number of inputs (which inputs?)
Rest unclear.

### Sparse Initialization
This was covered very briefly. Relevant?

### Initializing the bias
They can be initialized to zero. Asymmetry breaking is provided by the weights

###TLDR: 
Use ReLU units and normalize the initialization variance with $\sqrt(\frac{2}{n})$.
Or use batch normalization? No details have been shown, they just refer to the original paper about batch normalization which seems to be THE way to go?:
[https://arxiv.org/pdf/1502.03167v3.pdf] 

## Regularization

