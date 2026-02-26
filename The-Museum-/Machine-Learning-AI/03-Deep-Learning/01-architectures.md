# Deep Learning Architectures
## The Building Blocks of Modern AI

### Neural Networks Fundamentals
#### Perceptron
- **Basic Unit**: Single-layer perceptron (Rosenblatt, 1958)
- **Operation**: Takes inputs, computes weighted sum, applies activation
- **Limitations**: Can only solve linearly separable problems

#### Multi-Layer Perceptron (MLP)
- **Structure**: Input layer → Hidden layers → Output layer
- **Forward Pass**:
  - Each layer applies y = activation(Wx + b)
  - Weights (W) and biases (b) are learnable parameters

- **Activation Functions**:
  - **ReLU (Rectified Linear Unit)**: f(x) = max(0, x)
  - **GeLU (Gaussian Error Linear Unit)**: f(x) = xΦ(x)
  - **Softmax**: Converts logits to probabilities
  - **Tanh**: Hyperbolic tangent function
  - **Sigmoid**: S-shaped logistic function

### Computer Vision Architectures
#### Convolutional Neural Networks (CNNs)
- **Convolutional Layers**: Extract local features using filters
- **Pooling Layers**: Downsample feature maps
- **Key Operations**:
  - Convolution: Filter slides over input, computes dot product
  - Pooling: Max pooling, average pooling
  - Stride: Step size of filter movement

#### LeNet-5 (1998)
- **Classic Architecture**: LeCun et al.
- **Structure**: Conv → Pool → Conv → Pool → FC → FC
- **Applications**: Handwritten digit recognition (MNIST)

#### AlexNet (2012)
- **Breakthrough**: First deep CNN to win ImageNet
- **Key Innovations**:
  - ReLU activation
  - Dropout
  - GPU acceleration
  - Data augmentation

#### VGG Networks
- **Depth Matters**: VGG16 (16 layers), VGG19 (19 layers)
- **Uniform Architecture**: 3×3 convolution layers
- **Advantage**: Simple and consistent design

#### ResNet (Residual Networks)
- **Deep Residual Learning**: Skip connections
- **Structure**: Identity mappings that skip one or more layers
- **Key Insight**: Solves vanishing gradient problem in very deep networks
- **Versions**: ResNet-50, ResNet-101, ResNet-152

#### Inception Networks (GoogLeNet)
- **Inception Modules**: Parallel convolutional paths with different filter sizes
- **Key Innovations**: 1×1 convolutions for dimension reduction
- **Versions**: Inception v1, v2, v3, v4

#### MobileNet
- **Efficient CNNs**: Optimized for mobile devices
- **Depthwise Separable Convolutions**: Split convolution into depthwise and pointwise
- **Compression Techniques**: Quantization, pruning

### Sequence Models
#### Recurrent Neural Networks (RNNs)
- **Architecture**: Hidden state carries information from previous steps
- **Limitations**: Vanishing/exploding gradient problem
- **Applications**: Time series, natural language processing

#### Long Short-Term Memory (LSTM)
- **Memory Cells**: Maintain state over long sequences
- **Key Gates**:
  - Input gate: Controls information flow into cell
  - Forget gate: Controls what information to discard
  - Output gate: Controls what information to output
- **Applications**: Speech recognition, machine translation

#### Gated Recurrent Units (GRUs)
- **Simpler than LSTMs**: Combine input and forget gates into update gate
- **Key Components**:
  - Update gate: Decides how much old state to keep
  - Reset gate: Decides how much new information to use
- **Advantages**: Faster training, less computational cost

#### Bidirectional RNNs (BiRNN)
- **Forward + Backward**: Process sequence in both directions
- **Hidden States**: Concatenation of forward and backward states
- **Applications**: Sentiment analysis, named entity recognition

### Attention Mechanisms
#### Self-Attention
- **Key Insight**: Each position in sequence attends to all other positions
- **Queries, Keys, Values**: Three linear projections of input
- **Attention Scores**: Dot product of queries and keys, normalized

#### Multi-Head Attention
- **Parallel Attention Heads**: Multiple attention mechanisms applied in parallel
- **Linear Projections**: Each head learns different attention patterns
- **Advantage**: Captures multiple types of relationships

#### Scaled Dot-Product Attention
- **Formula**: Attention(Q, K, V) = softmax(QK^T/√d_k)V
- **Scaling Factor**: √d_k prevents gradient vanishing
- **Stability**: Softmax ensures weights sum to 1

### Transformer Architecture
#### Encoder-Decoder Structure
- **Encoder**: Processes input sequence
- **Decoder**: Generates output sequence
- **Key Components**: Multi-head attention, feed-forward networks, layer normalization

#### Positional Encoding
- **Problem**: Transformers don't have inherent sequence information
- **Solution**: Add positional information to embeddings
- **Types**: Sinusoidal, learnable positional embeddings

#### Layer Normalization
- **Normalization Strategy**: Normalize across features, not samples
- **Position**: Applied before or after feed-forward layers
- **Advantage**: Faster training, better convergence

### Modern Architectures
#### BERT (Bidirectional Encoder Representations from Transformers)
- **Bidirectional Pre-training**: Trained on masked language modeling
- **Key Innovations**:
  - Masked Language Model (MLM)
  - Next Sentence Prediction (NSP)
- **Versions**: BERT-Base, BERT-Large, DistilBERT

#### GPT (Generative Pre-trained Transformer)
- **Autoregressive Language Model**: Generates text token by token
- **Unidirectional Attention**: Only attends to previous positions
- **Versions**: GPT-1, GPT-2, GPT-3, GPT-4

#### Vision Transformers (ViT)
- **Applying Transformers to Images**: Split image into patches, treat as sequence
- **Key Components**: Patch tokens, classification token, positional encoding
- **Advantages**: Handles long-range dependencies better than CNNs

### Training Dynamics
#### Optimizers
- **SGD (Stochastic Gradient Descent)**: Basic optimizer
- **Adam**: Adaptive moment estimation
- **AdamW**: Adam with weight decay
- **RMSProp**: Root mean square propagation

#### Regularization
- **Dropout**: Randomly drop neurons to prevent overfitting
- **Batch Normalization**: Normalize inputs to hidden layers
- **Layer Normalization**: Normalize across features in a layer

#### Loss Functions
- **Cross-Entropy**: Classification tasks
- **Huber Loss**: Regression tasks (robust to outliers)
- **Triplet Loss**: Contrastive learning

### Practice Exercises
#### CNNs
1. Implement LeNet-5 from scratch
2. Train a ResNet on CIFAR-10
3. Build a custom CNN for image classification

#### Sequence Models
1. Implement RNN for time series prediction
2. Build LSTM for sentiment analysis
3. Train GRU on text classification

#### Transformers
1. Implement a simple transformer
2. Fine-tune BERT for text classification
3. Train a small GPT-like model

### Resources
- **Books**:
  - "Deep Learning" by Goodfellow et al.
  - "Hands-On Machine Learning with Scikit-Learn, Keras, and TensorFlow" by Geron
- **Online Courses**:
  - Coursera: Deep Learning Specialization (Andrew Ng)
  - fast.ai: Practical Deep Learning for Coders
- **Tools**:
  - PyTorch: Deep learning framework
  - TensorFlow/Keras: High-level API
  - Hugging Face Transformers: Pre-trained models

### Real-World Applications
#### Computer Vision
- Image classification
- Object detection
- Image segmentation
- Face recognition

#### Natural Language Processing
- Machine translation
- Text generation
- Sentiment analysis
- Question answering

#### Sequence Analysis
- Time series forecasting
- Speech recognition
- Music generation
- Video understanding

Deep learning architectures continue to evolve rapidly, with transformers becoming the dominant architecture for most sequence-based tasks and showing promising results in computer vision.
