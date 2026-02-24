# Introduction to Machine Learning & AI

## What is Artificial Intelligence?

Artificial Intelligence is the simulation of human intelligence in machines. It encompasses systems that can:
- **Learn** from experience
- **Reason** through problems
- **Perceive** and understand environment
- **Make decisions**

```
┌─────────────────────────────────────────────────────────────┐
│                   AI Spectrum                                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────────────────────────────────────────────┐  │
│  │                  ARTIFICIAL INTELLIGENCE             │  │
│  │  ┌───────────────────────────────────────────────┐  │  │
│  │  │              MACHINE LEARNING                  │  │  │
│  │  │  ┌─────────────────────────────────────────┐  │  │  │
│  │  │  │           DEEP LEARNING                 │  │  │  │
│  │  │  │                                       │  │  │  │
│  │  │  │  Neural Networks with many layers     │  │  │  │
│  │  │  │                                       │  │  │  │
│  │  │  └─────────────────────────────────────────┘  │  │  │
│  │  │                                               │  │  │
│  │  │  Learning from data to make predictions      │  │  │
│  │  │                                               │  │  │
│  │  └───────────────────────────────────────────────┘  │  │
│  │                                                       │  │
│  │  Systems that can learn from data                   │  │
│  └─────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## What is Machine Learning?

Machine Learning is a subset of AI where computers learn from data without being explicitly programmed. Instead of rules written by humans, ML algorithms find patterns in data.

```
Traditional Programming vs Machine Learning:
─────────────────────────────────────────────────────────────

TRADITIONAL:
─────────────────────────────────────────────────────────────
    Rules (Code)           Data
         │                   │
         └─────────┬─────────┘
                   ▼
              Output/Predictions

MACHINE LEARNING:
─────────────────────────────────────────────────────────────
    Data            +         Output/Predictions
         │                   │
         └─────────┬─────────┘
                   ▼
              Model (Learned Rules)
```

## Types of Machine Learning

### 1. Supervised Learning
```
Learning with labeled data:
─────────────────────────────────────────────────────────────
    ┌─────────────────────────────────────────────────────┐
    │  TRAINING DATA                                      │
    │                                                     │
    │  Input (X)          Label (Y)                      │
    │  ┌─────────┐        ┌─────────┐                  │
    │  │ Email   │   →    │ Spam    │                  │
    │  │ Subject │        │ Not Spam│                  │
    │  └─────────┘        └─────────┘                  │
    │                                                     │
    │  The algorithm learns the mapping: X → Y          │
    │                                                     │
    └─────────────────────────────────────────────────────┘

Examples:
- Email spam detection
- Image classification
- Price prediction
- Medical diagnosis
```

### 2. Unsupervised Learning
```
Learning without labels:
─────────────────────────────────────────────────────────────
    ┌─────────────────────────────────────────────────────┐
    │  TRAINING DATA                                      │
    │                                                     │
    │  Input (X)          (No labels)                    │
    │  ┌─────────┐                                    │
    │  │ Customer│                                    │
    │  │ Data    │   →   Find hidden patterns/groups  │
    │  └─────────┘                                    │
    │                                                     │
    └─────────────────────────────────────────────────────┘

Examples:
- Customer segmentation
- Anomaly detection
- Dimensionality reduction
- Market basket analysis
```

### 3. Reinforcement Learning
```
Learning through trial and error:
─────────────────────────────────────────────────────────────
    ┌─────────────────────────────────────────────────────┐
    │                                                      │
    │  Agent → Action → Environment → Reward             │
    │    ↑                                    │           │
    │    │____________Feedback_______________│           │
    │                                                      │
    │  Goal: Maximize total reward                        │
    │                                                      │
    └─────────────────────────────────────────────────────┘

Examples:
- Game playing (Chess, Go)
- Robotics
- Autonomous vehicles
- Resource management
```

## Machine Learning Workflow

```
┌─────────────────────────────────────────────────────────────┐
│              ML Pipeline Overview                            │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. PROBLEM DEFINITION                                     │
│     - What are we trying to predict?                       │
│     - Classification? Regression?                          │
│     - What data do we need?                                │
│                                                             │
│  2. DATA COLLECTION                                        │
│     - Gather relevant data                                │
│     - API calls, web scraping, databases                   │
│                                                             │
│  3. DATA PREPROCESSING                                     │
│     - Clean data                                          │
│     - Handle missing values                               │
│     - Feature engineering                                │
│                                                             │
│  4. DATA SPLITTING                                         │
│     - Training set (70-80%)                               │
│     - Validation set (10-15%)                            │
│     - Test set (10-15%)                                  │
│                                                             │
│  5. MODEL SELECTION                                        │
│     - Try multiple algorithms                             │
│     - Start simple, increase complexity                   │
│                                                             │
│  6. TRAINING                                              │
│     - Fit model to training data                         │
│     - Tune hyperparameters                                │
│                                                             │
│  7. EVALUATION                                            │
│     - Test on held-out data                              │
│     - Use appropriate metrics                             │
│                                                             │
│  8. DEPLOYMENT                                            │
│     - Put model in production                             │
│     - Monitor performance                                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Common ML Algorithms

### Regression (Predict Continuous Values)
```
┌─────────────────────────────────────────────────────────────┐
│  Linear Regression          │  Predict house prices       │
│  Polynomial Regression     │  Complex patterns            │
│  Ridge/Lasso Regression    │  Regularization             │
│  Decision Tree Regression   │  Non-linear                 │
│  Random Forest Regression   │  Ensemble                   │
└─────────────────────────────────────────────────────────────┘
```

### Classification (Predict Categories)
```
┌─────────────────────────────────────────────────────────────┐
│  Logistic Regression       │  Binary classification        │
│  Decision Tree             │  Interpretable               │
│  Random Forest             │  Robust                      │
│  Support Vector Machine   │  High-dimensional            │
│  Naive Bayes               │  Fast, probabilistic         │
│  K-Nearest Neighbors       │  Simple, instance-based     │
│  Neural Networks            │  Complex patterns            │
└─────────────────────────────────────────────────────────────┘
```

### Clustering (Group Data)
```
┌─────────────────────────────────────────────────────────────┐
│  K-Means                  │  Centroid-based               │
│  Hierarchical Clustering │  Dendrogram-based            │
│  DBSCAN                   │  Density-based               │
│  Gaussian Mixture         │  Probabilistic               │
└─────────────────────────────────────────────────────────────┘
```

## Key Concepts

### Overfitting vs Underfitting
```
┌─────────────────────────────────────────────────────────────┐
│                   Model Complexity                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Error                                                     │
│    │                                                       │
│    │       ╲                                             │
│    │        ╲   Overfitting                              │
│    │         ╲  (High variance)                          │
│    │          ╲                                          │
│    │           ╲__                                        │
│    │        ___╲                                         │
│    │    ___╲     ╲  Optimal                              │
│    │___╱          ╲__                                    │
│    │                  ╲___ Underfitting                  │
│    │                       ╲   (High bias)              │
│    │                        ╲__                          │
│    │                                                   │
│    └───────────────────────────────────────────────►      │
│                      Model Complexity                       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Bias-Variance Tradeoff
```
Bias: Error from oversimplified assumptions
- High bias → Underfitting
- Model too simple

Variance: Error from sensitivity to training data
- High variance → Overfitting  
- Model too complex

Goal: Find optimal complexity that minimizes total error
```

## Essential Math for ML

### Linear Algebra
- Vectors and matrices
- Matrix operations
- Eigenvalues and eigenvectors
- Dimensionality reduction

### Calculus
- Derivatives and gradients
- Chain rule
- Partial derivatives
- Gradient descent

### Probability & Statistics
- Distributions (normal, binomial, etc.)
- Bayes' theorem
- Maximum likelihood estimation
- Hypothesis testing

## Tools and Frameworks

```
┌─────────────────────────────────────────────────────────────┐
│                    ML Tools                                  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Languages:                                                 │
│  - Python (most popular)                                   │
│  - R (statistics)                                         │
│  - Julia (performance)                                     │
│                                                             │
│  Data Processing:                                          │
│  - NumPy (numerical computing)                           │
│  - Pandas (data manipulation)                            │
│  - SciPy (scientific computing)                          │
│                                                             │
│  ML Libraries:                                             │
│  - Scikit-learn (traditional ML)                         │
│  - PyTorch (deep learning)                                │
│  - TensorFlow (deep learning)                             │
│  - Keras (high-level TensorFlow)                         │
│  - XGBoost (gradient boosting)                           │
│                                                             │
│  Visualization:                                            │
│  - Matplotlib                                             │
│  - Seaborn                                                 │
│  - Plotly                                                 │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Interview Tips

1. **Know the difference** between AI, ML, and DL
2. **Understand types of ML** - Supervised, unsupervised, reinforcement
3. **Know the ML pipeline** - End to end process
4. **Understand overfitting/underfitting** - Bias-variance tradeoff
5. **Be ready for practical questions** - Data preprocessing, model selection

## Summary

Machine Learning is:
- **Subset of AI** - Systems that learn from data
- **Data-driven** - Learns patterns from examples
- **Divided into types** - Supervised, unsupervised, reinforcement

The workflow:
1. Define problem
2. Collect data
3. Preprocess data
4. Train model
5. Evaluate
6. Deploy

Key challenges:
- **Data quality** - Garbage in, garbage out
- **Overfitting** - Model memorizes, doesn't generalize
- **Bias** - Models can perpetuate biases
- **Interpretability** - Complex models are "black boxes"
