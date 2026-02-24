# Neural Networks Basics

## What are Neural Networks?

Neural networks are computing systems inspired by biological neural networks in the brain. They consist of interconnected nodes (neurons) that process information using connectionist approaches.

```
┌─────────────────────────────────────────────────────────────┐
│                Biological vs Artificial Neuron                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Biological Neuron:          Artificial Neuron:              │
│                                                             │
│     Dendrites                  Input (x1, x2, x3...)      │
│        │                            │                       │
│        ▼                            ▼                       │
│   ┌─────────┐              ┌─────────────────┐            │
│   │  Cell   │              │  Weighted Sum   │            │
│   │  Body   │     →        │  Σ(wi * xi) + b│            │
│   │         │              └────────┬────────┘            │
│   └────┬────┘                       │                      │
│        │                            ▼                      │
│        ▼                   ┌─────────────────┐            │
│      Axon                  │  Activation     │            │
│        │                   │  Function       │            │
│        ▼                   └────────┬────────┘            │
│     Synapse                       │                       │
│                                    ▼                       │
│                           ┌─────────────────┐            │
│                           │    Output (y)   │            │
│                           └─────────────────┘            │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Perceptron - The Simplest Neural Network

### Single Perceptron
```
┌─────────────────────────────────────────────────────────────┐
│                    Perceptron Model                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  x1 ──► [w1] ──┐                                           │
│                │                                            │
│  x2 ──► [w2] ──┼──► Σ ──► Activation ──► Output         │
│                │                                            │
│  x3 ──► [w3] ──┘                                           │
│                                                             │
│  Equation:                                                  │
│  y = f(w1*x1 + w2*x2 + w3*x3 + b)                        │
│                                                             │
│  Where:                                                     │
│  - w = weights                                              │
│  - b = bias                                                 │
│  - f = activation function                                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Perceptron Learning Algorithm
```
1. Initialize weights randomly
2. For each training example:
   a. Calculate output: ŷ = f(w·x + b)
   b. Calculate error: error = y - ŷ
   c. Update weights: w = w + learning_rate * error * x
   d. Update bias: b = b + learning_rate * error
3. Repeat until convergence
```

## Multi-Layer Perceptron (MLP)

```
┌─────────────────────────────────────────────────────────────┐
│              Multi-Layer Perceptron                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  INPUT          HIDDEN              OUTPUT                  │
│  LAYER          LAYERS               LAYER                   │
│                                                             │
│    ○─────────►  ○ ──►  ○ ──►  ○                          │
│    │           │     │     │                              │
│    ○─────────►  ○ ──►  ○ ──►  ○ ──►  ○                  │
│    │           │     │     │     │                        │
│    ○─────────►  ○ ──►  ○ ──►  ○ ──►  ○                  │
│    │           │     │     │     │                        │
│    ○─────────►  ○ ──►  ○ ──►  ○                          │
│                │     │     │                              │
│                │     │     │                              │
│    x1           h1    h2    h3           y               │
│    x2                                    y               │
│    x3                                    ...              │
│                                                             │
│  Input → Hidden → Output                                    │
│  (features) → (learned representations) → (predictions)   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Forward Propagation
```
Step-by-step:
─────────────────────────────────────────────────────────────
Input (x) → Multiply by weights (W) → Add bias (b)
                     │
                     ▼
              Linear combination: z = Wx + b
                     │
                     ▼
              Apply activation: a = f(z)
                     │
                     ▼
              Pass to next layer

For each layer:
  z⁽ˡ⁾ = W⁽ˡ⁾ a⁽ˡ⁻¹⁾ + b⁽ˡ⁾
  a⁽ˣ⁾ = f(z⁽ˡ⁾)
```

### Backpropagation
```
How the network learns:
─────────────────────────────────────────────────────────────
1. Forward pass: Compute predictions
2. Calculate loss: Compare prediction to actual
3. Backward pass: Compute gradients
4. Update weights: Move in direction that reduces loss

The Chain Rule:
─────────────────────────────────────────────────────────────
∂L/∂w = ∂L/∂a × ∂a/∂z × ∂z/∂w

Gradient flows backward through network
```

## Activation Functions

### Why Activation Functions?
```
Without activation: Neural network is just linear combination
With activation: Can learn non-linear patterns
```

### Common Activation Functions
```
┌─────────────────────────────────────────────────────────────┐
│           Activation Functions Comparison                    │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Sigmoid: σ(x) = 1 / (1 + e^-x)                           │
│  ─────────────────────────                                  │
│  Output: (0, 1)                                            │
│  Used in: Output layer for binary classification            │
│  Problem: Vanishing gradients                              │
│                                                             │
│  Tanh: tanh(x)                                             │
│  ─────────────────────                                      │
│  Output: (-1, 1)                                           │
│  Used in: Hidden layers                                    │
│  Better than sigmoid (zero-centered)                      │
│                                                             │
│  ReLU: max(0, x)                                           │
│  ─────────────────                                          │
│  Output: [0, ∞)                                            │
│  Used in: Almost all modern networks                       │
│  Pros: Fast, reduces vanishing gradient                    │
│  Cons: Dying ReLU problem                                  │
│                                                             │
│  Leaky ReLU: max(0.01x, x)                                │
│  ────────────────────────────                              │
│  Pros: Allows gradient flow for negative inputs            │
│                                                             │
│  Softmax: e^x / Σe^x                                       │
│  ─────────────────────────                                  │
│  Output: Probability distribution                         │
│  Used in: Output layer for multi-class                    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Loss Functions

### Regression Losses
```
Mean Squared Error (MSE):
─────────────────────────────────────────────────────────────
L = (1/n) Σ(y - ŷ)²

Good for: Regression tasks
```

### Classification Losses
```
Cross-Entropy Loss:
─────────────────────────────────────────────────────────────
L = -Σ y × log(ŷ)

Good for: Classification tasks

Binary Cross-Entropy:
L = -[y × log(ŷ) + (1-y) × log(1-ŷ)]
```

## Gradient Descent

### How Gradient Descent Works
```
┌─────────────────────────────────────────────────────────────┐
│                  Gradient Descent                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Goal: Find minimum of loss function                        │
│                                                             │
│  Process:                                                   │
│  1. Start at random point                                  │
│  2. Calculate gradient (direction of steepest ascent)     │
│  3. Move in opposite direction (descent)                  │
│  4. Repeat until convergence                              │
│                                                             │
│  Update Rule:                                               │
│  w = w - learning_rate × ∂L/∂w                           │
│                                                             │
│  Visual:                                                    │
│                    ╱                                        │
│                  ╱  ○ Start                                │
│                ╱                                            │
│              ╱                                              │
│            ╱   Minimum                                      │
│          ╱                                                  │
│        ╱                                                    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Types of Gradient Descent
```
┌─────────────────────────────────────────────────────────────┐
│              Types of Gradient Descent                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. Batch Gradient Descent                                  │
│     - Use ALL training data per update                     │
│     - Slow but accurate                                     │
│                                                             │
│  2. Stochastic Gradient Descent (SGD)                      │
│     - Use ONE sample per update                             │
│     - Fast but noisy                                        │
│                                                             │
│  3. Mini-Batch Gradient Descent                             │
│     - Use BATCH of samples (32, 64, 128)                   │
│     - Best of both worlds (popular)                        │
│                                                             │
│  Modern Optimizers:                                         │
│  - Adam (Adaptive Moment Estimation)                       │
│  - RMSprop (Root Mean Square Propagation)                  │
│  - Momentum                                                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Building a Neural Network in PyTorch

```python
import torch
import torch.nn as nn
import torch.optim as optim

# Define the network
class NeuralNetwork(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(NeuralNetwork, self).__init__()
        self.layer1 = nn.Linear(input_size, hidden_size)
        self.relu = nn.ReLU()
        self.layer2 = nn.Linear(hidden_size, hidden_size)
        self.output = nn.Linear(hidden_size, output_size)
    
    def forward(self, x):
        x = self.layer1(x)
        x = self.relu(x)
        x = self.layer2(x)
        x = self.relu(x)
        x = self.output(x)
        return x

# Create model
model = NeuralNetwork(784, 256, 10)

# Loss function
criterion = nn.CrossEntropyLoss()

# Optimizer
optimizer = optim.Adam(model.parameters(), lr=0.001)

# Training loop
for epoch in range(num_epochs):
    for batch in train_loader:
        # Forward pass
        outputs = model(batch.x)
        loss = criterion(outputs, batch.y)
        
        # Backward pass
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
```

## Interview Tips

1. **Know the architecture** - Input, hidden, output layers
2. **Understand forward propagation** - How data flows through network
3. **Know backpropagation** - Chain rule, gradient computation
4. **Understand activation functions** - ReLU, sigmoid, tanh, softmax
5. **Know loss functions** - MSE, cross-entropy
6. **Understand optimizers** - SGD, Adam, momentum

## Summary

Neural networks are:
- **Universal function approximators** - Can learn any pattern
- **Layered** - Input, hidden, output
- **Trainable** - Via backpropagation
- **Non-linear** - Through activation functions

Key components:
- **Weights and biases** - Learnable parameters
- **Activation functions** - Add non-linearity
- **Loss function** - Measures error
- **Optimizer** - Updates weights

Modern deep learning builds on these basics with:
- **CNNs** - For images
- **RNNs** - For sequences
- **Transformers** - For text
