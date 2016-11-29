
Table of Contents:

- [Quick Intro without brain analogies](#intro)
- [Modeling one neuron](#neuron)
- [Activation Functions](#activation-functions)
- [Neural Network Architectures](#architectures)

These are my personal notes about [course cs231n](http://cs231n.stanford.edu/) from Stanford university. 

<a name='intro'></a>

# Quick Intro without brain analogies

When using linear classification the score function looks something like $s=Wx$.
When using neural networks (let's say with two layers) the score function could look something like this: 

$$
s = W_2 max(0,W_1 x)
$$
$W_1$ and $W_2$ are matrices of a shape that they will result into a 10-dimensional vector $s$. The non-linear $max(0,-)$ function is crucial. Without it, the two $W_{1,2}$ matrices would merge to one big matrix - and we would have a linear function again. 
*We don't want that, we need non-linearity, this is where we get the wiggle.* (??)
Wiggle in this respect means, we have an additional thing to tweak with. Every neuron has the ability to fire or not to fire, depending on the learned weights. I am not sure if you can do this with pure matrix multiplications. Of course one could set weights to zero, in a linear function... But here these functions are non-linear! Surely, this is an additional feature, isn't it.

<a name='neuron'></a>

# Modeling one neuron
We should not try to mix the biological model of a neuron and the Machine-Learning neuron.

## Biological motivations and connections

Nevertheless, the ML-neuron as we implement it, is inspired and based on the biological neuron. 
It can be seen as an activation device with a certain threshold. When the threshold is met by the neuron's input signals then the neuron fires with a specific frequency. OK, let's leave it with that.

## Single neuron as a linear classifier
A linear classifier $Wx+b$ can be modeled by one neuron. It has the additional feature of being active or not on certain rows $w_i$ of $W$. This can be expressed mathematically with the sigmoid function. As soon as its output is greater than 0.5 the neuron will fire.
**With these features a neuron could model a binary SVM or binary Softmax (aka logistic regression).**

<a name='activation-functions'></a>

## Activation functions

- Activation function seems to be called a non-linearity and vice versa.
- It takes a single number as input and performs a fixed mathematical operation on it.
- This single number is the computed score of the neuron's input: $\sigma(W x + b)$ This means that the linear equation's output (the score) is used as input to the activation function (e.g. Sigmoid or ReLU) 

### Sigmoid function
Rarely ever used due to one major, and one minor reasons:
- Sigmoids kill gradients. As soon as x is very small or very large, the sigmoid gets saturated to either 0 or 1, causing a gradient of zero. A small gradient means, no signal will flow through the neuron (major reason). The argument x of this function is normally the result of the score function f.
- Sigmoids outputs are not zero centered which could cause undesirable zig-zagging in the gradient updates (minor reason).

### Tanh
- Same problem as with the sigmoid function: The activations saturate.
- However, it is zero-centered and therefore it should be always preferred to the sigmoid nonlinearity.
- Aside: The tanh neuron is simply a scaled sigmoid neuron: $tanh(x)=2\sigma(2x)-1$


### ReLU

Definition:
$$
f(x)= max(0,x)
$$
Very popular, because
- it greatly accelerates the convergence of stochastic gradient descent.
- it is simple to implement

However, a disadvantage is its fragile behavior during training. A large gradient flowing through a ReLU neuron can cause death of this neuron. It will permanently be zero from that point on.

### Leaky ReLU
Leaky ReLU tries to fix the "dying ReLU" problem. Its consistency is presently unclear.
Definition:
$$
f(x)= \mathbb{1}( x < 0 )(\alpha x) + \mathbb{1}(x \geq 0)(x),  \alpha \rightarrow 0
$$
Core idea: With $\alpha$ being very small, the gradient of f(x) is never(?) zero.

###Maxout

Definition:
$$
f(x) = max(w^T_1 x + b_1, w^T_2 x + b_2)
$$

- ReLU and leaky ReLU are special versions of it.
- It doesn't die like ReLU (good)
- It has high total number of parameters (bad)



- Normally, one sticks to one activation function per Neural Network architecture.
- *Try out different activation functions with your favorite CNN library.*
- ***But use ReLU eventually.*** See course notes for details.

### TLDR
Use ReLU, be careful with learning rate and possibly monitor the fraction of dead units.

<a name='architectures'></a>


# Neural Network Architectures

##Layer-wise organization
- Neurons are connected in an acyclic graph, no loops allowed.
- Neurons can become input to other neurons.
- NNs are organized into distinct layers.
- Simplest layer type: Full-connected layer where neurons between two adjacent layers are fully pairwise connected. 
- There are no connections between neurons within a single layer.
- We do not count the input layer when we say N-layer Neural Network.
- It seems to be that "Multilayer Perceptron" (MLP) is just another word for NN.
- The output layer does not have an activation function. This layer represents the class scores or regression results.
I think you use the loss function's output as the final result which you compare with your target or labels (by using either cross entropy or hinge loss).
- Size of a NN: 
    - Number of neurons (without input layer)
    - Number of learnable parameters (weights plus biases.) These are basically all edges in the graph.

## Example feed-forward computation

- The organization of a NN into layers makes it easy to work with NN using matrix vector operations.
- To trigger all activations of one neuron, you multiply the input layer of that neuron with one row of the weight matrix for that layer. One row of this weight matrix holds all the weights for the input edges of that neuron.

The full forward pass is just a concatenation of matrix multiplications, interwoven with the activation functions.
**One forward pass in a fully connected layer corresponds to one matrix multiplication plus a bias offset and an activation function.**

## Representational Power

- A Neural Network can approximate any continuous function with just one hidden layer.
- Why go deeper then? It is quite complicated to model everything with just one hidden layer/ two layer in total. In practice it is much easier to use more layers and the representational power is equal anyway.

- NN with 4,5, or 6 layers don't perform really better than three-layer NNs. 
- BUT, Convolutional Neural Networks need the depth! This is in stark contrast to the points above. CNNs deal with images, which have a hierarchical structure, so several layers make intuitive sense for this domain.

## Setting number of layers and their sizes

How do we decide on the architecture?
More neurons can model more complicated functions, which is good.
However, more neurons tend to overfit the model to the training data.
Nevertheless, one should not cheap out on neurons due to that reason.
There are other ways to deal with that (L2 regularization, dropout, ...).

Small networks with few neurons can have an equally high prediction accuracy than large networks. However, it is hard learn these NNs with gradient descent. Often you are just trapped in one of the local minima, which have a high loss, when you have a small net. A large network has many more local minima, but these are much easier to avoid and you and the finally achieved loss is much smaller. **In other words, a large network is less dependent on a good (random) initialization of the weights.**