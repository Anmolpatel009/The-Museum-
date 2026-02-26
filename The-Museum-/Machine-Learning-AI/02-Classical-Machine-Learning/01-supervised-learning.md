# Supervised Learning
## Predictive Modeling with Labeled Data

### What is Supervised Learning?
- **Definition**: Learning from labeled examples (input-output pairs)
- **Goal**: Predict outputs for new, unseen inputs
- **Key Components**:
  - Training data: Labeled examples (X, y)
  - Model: Function mapping inputs to outputs
  - Loss function: Measures prediction error
  - Optimizer: Adjusts model parameters to minimize loss

### Types of Problems
#### Regression
- **Definition**: Predict continuous numerical values
- **Examples**:
  - House price prediction
  - Sales forecasting
  - Stock price prediction
  - Temperature forecasting

#### Classification
- **Definition**: Predict discrete categorical labels
- **Examples**:
  - Email spam detection
  - Image classification
  - Medical diagnosis
  - Customer churn prediction

### Linear Regression
#### Simple Linear Regression
- **Model**: y = β₀ + β₁x + ε
- **Least Squares Estimation**: Minimize sum of squared residuals
- **Assumptions**: Linearity, independence, homoscedasticity, normality

#### Multiple Linear Regression
- **Model**: y = β₀ + β₁x₁ + β₂x₂ + ... + βₙxₙ + ε
- **Feature Selection**: Choosing relevant features
- **Multicollinearity**: High correlation between predictors

### Polynomial Regression
- **Definition**: Extending linear regression to include polynomial terms
- **Model**: y = β₀ + β₁x + β₂x² + ... + βₙxⁿ + ε
- **Overfitting**: Risk of fitting noise instead of signal
- **Regularization**: Techniques to prevent overfitting

### Regularization Techniques
#### L1 Regularization (Lasso)
- **Objective**: Minimize sum of squared errors + λ|β|
- **Effect**: Encourages sparsity (sets some coefficients to zero)
- **Applications**: Feature selection

#### L2 Regularization (Ridge)
- **Objective**: Minimize sum of squared errors + λβ²
- **Effect**: Shrinks coefficients towards zero
- **Applications**: Reducing overfitting

#### Elastic Net
- **Objective**: Combination of L1 and L2 regularization
- **Effect**: Balances sparsity and shrinkage
- **Applications**: Handling collinear features

### Logistic Regression
- **Definition**: Classification algorithm for binary outcomes
- **Model**: p(y=1|x) = 1 / (1 + e^-(β₀ + β₁x))
- **Interpretation**: Probability of positive class
- **Decision Boundary**: Threshold for classification

### Support Vector Machines (SVM)
#### Basic Concept
- **Goal**: Find optimal hyperplane that maximizes margin between classes
- **Margin**: Distance from hyperplane to nearest data point

#### Kernel Trick
- **Definition**: Transform inputs into higher-dimensional space
- **Common Kernels**: Linear, Polynomial, RBF (Gaussian)
- **Advantages**: Handles non-linear relationships

#### Soft Margin Classification
- **C Parameter**: Controls trade-off between margin and misclassification
- **Effect**: Small C = larger margin, possibly more misclassifications

### Decision Trees
#### Structure
- **Root Node**: Entire dataset
- **Internal Nodes**: Feature splits
- **Leaf Nodes**: Class labels or regression values

#### Splitting Criteria
- **Gini Impurity**: Measures impurity of a node
- **Entropy**: Measure of randomness or uncertainty
- **Information Gain**: Reduction in impurity after split

#### Pruning
- **Pre-pruning**: Stop growing tree early
- **Post-pruning**: Remove branches from fully grown tree
- **Effect**: Prevents overfitting

### Random Forest
#### Ensemble Learning
- **Definition**: Combine multiple decision trees for better performance
- **Bagging**: Bootstrap aggregation - train on random subsets
- **Random Subspaces**: Feature randomness for diversity

#### Key Parameters
- **n_estimators**: Number of trees
- **max_depth**: Maximum depth of trees
- **min_samples_split**: Minimum samples to split node
- **max_features**: Number of features to consider for split

#### Advantages
- Robust to overfitting
- Handles non-linear relationships
- Feature importance scores

### Gradient Boosting Machines
#### Key Algorithms
- **XGBoost**: Extreme Gradient Boosting
- **LightGBM**: Microsoft's fast, distributed gradient boosting
- **CatBoost**: Yandex's implementation with categorical handling

#### Boosting Concept
- **Sequential Learning**: Add models to correct previous errors
- **Gradient Descent**: Minimize loss function using gradients
- **Shrinkage**: Learning rate to prevent overfitting

#### Hyperparameter Tuning
- **Learning Rate**: Step size for gradient descent
- **Number of Estimators**: Number of boosting rounds
- **Max Depth**: Maximum depth of trees
- **Subsample**: Fraction of samples per tree

### Model Evaluation
#### Regression Metrics
- **Mean Absolute Error (MAE)**: Average absolute difference
- **Mean Squared Error (MSE)**: Average squared difference
- **Root Mean Squared Error (RMSE)**: Square root of MSE
- **R-squared**: Proportion of variance explained

#### Classification Metrics
- **Accuracy**: Correct predictions / Total predictions
- **Precision**: True Positives / (True Positives + False Positives)
- **Recall**: True Positives / (True Positives + False Negatives)
- **F1 Score**: Harmonic mean of precision and recall
- **Confusion Matrix**: Visualization of classification performance

#### Cross-Validation
- **K-Fold Cross-Validation**: Split data into K parts, train on K-1, test on 1
- **Stratified K-Fold**: Preserves class distribution
- **Leave-One-Out Cross-Validation (LOOCV)**: K = n

### Feature Engineering
#### Feature Selection
- **Filter Methods**: Select features based on statistical tests
- **Wrapper Methods**: Evaluate subsets of features
- **Embedded Methods**: Select features during model training

#### Feature Transformation
- **Normalization**: Scale to [0, 1] range
- **Standardization**: Center to mean 0, standard deviation 1
- **Encoding Categorical Variables**: One-hot encoding, label encoding

### Practice Exercises
#### Linear Regression
1. Implement simple linear regression
2. Handle multiple regression with 3+ features
3. Apply polynomial regression to non-linear data

#### Classification
1. Implement logistic regression
2. Train SVM with different kernels
3. Compare random forest vs XGBoost

#### Evaluation
1. Calculate classification metrics
2. Perform cross-validation
3. Analyze confusion matrices

### Resources
- **Books**:
  - "Introduction to Statistical Learning" by James et al.
  - "Applied Predictive Modeling" by Kuhn and Johnson
- **Online Courses**:
  - Coursera: Machine Learning (Andrew Ng)
  - edX: Data Science Essentials
- **Tools**:
  - Scikit-learn: Classical ML algorithms
  - XGBoost: Gradient boosting
  - LightGBM: Fast training

### Real-World Applications
- **Healthcare**: Predict patient readmission
- **Finance**: Credit risk assessment
- **Retail**: Customer lifetime value prediction
- **Manufacturing**: Predictive maintenance

Supervised learning forms the foundation of practical machine learning and is widely used across industries for predictive modeling.
