# Linear Algebra & Matrix Calculus
## The Mathematical Foundation of AI/ML

### Vector Spaces
#### Basic Concepts
- **Vector**: An ordered list of numbers representing a point in n-dimensional space
- **Scalar**: A single numerical value (magnitude without direction)
- **Basis Vectors**: A set of linearly independent vectors that span a vector space
- **Span**: All possible vectors that can be formed by linear combinations of basis vectors

#### Key Properties
- **Linearity**: If v and w are vectors, and a and b are scalars, then a(v + w) = av + bw
- **Dimensions**: The number of basis vectors in a space
- **Orthogonality**: Vectors whose dot product is zero
- **Normalization**: Rescaling a vector to have unit length

### Matrix Operations
#### Basic Operations
- **Addition**: Element-wise addition of matrices of the same size
- **Subtraction**: Element-wise subtraction
- **Scalar Multiplication**: Multiplication by a single scalar
- **Matrix Multiplication**: Dot product of row vectors with column vectors

#### Special Matrices
- **Identity Matrix**: Square matrix with 1s on diagonal, 0s elsewhere
- **Diagonal Matrix**: Matrix with non-zero elements only on the diagonal
- **Symmetric Matrix**: Matrix equal to its transpose
- **Sparse Matrix**: Matrix with mostly zero elements

#### Important Operations
- **Transpose**: Flipping a matrix over its diagonal
- **Determinant**: Scalar value representing the "volume" of the matrix
- **Inverse**: Matrix that when multiplied by the original gives the identity

### Matrix Decompositions
#### Eigenvalue/Eigenvector
- **Eigenvector**: A vector that only changes in scale when multiplied by a matrix
- **Eigenvalue**: The scalar factor by which the eigenvector is scaled
- **Applications**: Dimensionality reduction, stability analysis

#### Singular Value Decomposition (SVD)
- **Factorization**: Breaking a matrix into three component matrices
- **Form**: A = UΣV^T where U and V are orthogonal, Σ is diagonal
- **Applications**: Data compression, image processing, recommender systems

#### Other Decompositions
- **QR Decomposition**: Factorization into orthogonal and upper triangular matrices
- **LU Decomposition**: Factorization into lower and upper triangular matrices
- **Cholesky Decomposition**: Special case for positive definite matrices

### Calculus Concepts
#### Partial Derivatives
- **Definition**: Rate of change with respect to one variable while keeping others constant
- **Notation**: ∂f/∂x
- **Applications**: Optimization, gradient descent

#### Chain Rule
- **Definition**: Derivative of a composite function
- **Form**: d/dx [f(g(x))] = f'(g(x)) * g'(x)
- **Importance**: Critical for backpropagation in neural networks

#### Gradients
- **Definition**: Vector of partial derivatives of a scalar function
- **Direction**: Points towards maximum increase of the function
- **Magnitude**: Rate of increase in that direction

#### Jacobians and Hessians
- **Jacobian**: Matrix of first-order partial derivatives of a vector-valued function
- **Hessian**: Square matrix of second-order partial derivatives
- **Applications**: Optimization, curvature analysis

### Practical Applications in AI/ML
#### Neural Networks
- **Weights and Biases**: Stored as matrices and vectors
- **Forward Pass**: Matrix multiplication operations
- **Backpropagation**: Calculation of gradients using chain rule
- **Optimization**: Gradient descent using partial derivatives

#### Computer Vision
- **Images**: Represented as 3D tensors (width × height × channels)
- **Convolutions**: Special matrix operations for feature extraction
- **Transformations**: Rotation, scaling represented as matrices

#### Natural Language Processing
- **Word Embeddings**: Vectors representing word meanings
- **Attention Mechanisms**: Weighted sum operations using matrices
- **Transformers**: Complex matrix operations for sequence processing

### Numerical Computation
#### Floating Point Precision
- **Single Precision (float32)**: 32-bit floating point numbers
- **Double Precision (float64)**: 64-bit floating point numbers
- **Overflow and Underflow**: Common numerical issues

#### Efficient Implementations
- **BLAS/LAPACK**: Optimized linear algebra libraries
- **NumPy**: Python library for efficient numerical operations
- **TensorFlow/PyTorch**: Automatic differentiation frameworks

### Practice Exercises
#### Vector Operations
1. Compute the dot product of two vectors
2. Normalize a vector to unit length
3. Calculate the Euclidean distance between two points

#### Matrix Operations
1. Multiply two matrices
2. Compute the determinant of a matrix
3. Find the inverse of a matrix

#### Calculus Practice
1. Calculate partial derivatives of multi-variable functions
2. Compute gradients of simple functions
3. Implement the chain rule for composite functions

### Resources
- **Books**:
  - "Linear Algebra and Its Applications" by Gilbert Strang
  - "Calculus: Early Transcendentals" by James Stewart
- **Online Courses**:
  - Coursera: Linear Algebra for Machine Learning
  - Khan Academy: Linear Algebra and Calculus
- **Tools**:
  - NumPy for numerical computation
  - SymPy for symbolic computation

Understanding linear algebra and matrix calculus is essential for:
- Debugging failing model convergence
- Optimizing gradient descent
- Interpreting model outputs
- Understanding the inner workings of neural networks
