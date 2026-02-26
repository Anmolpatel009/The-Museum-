# Probability & Statistics
## The Science of Uncertainty in AI/ML

### Probability Basics
#### Definition and Axioms
- **Probability**: Numerical measure of the likelihood of an event occurring
- **Axioms of Probability**:
  1. Non-negativity: P(A) ≥ 0 for all events A
  2. Normalization: P(Ω) = 1 (total probability)
  3. Additivity: If events A and B are mutually exclusive, P(A ∪ B) = P(A) + P(B)

#### Key Concepts
- **Random Variable**: Variable that takes random values from a probability distribution
- **Probability Distribution**: Function describing probabilities of possible outcomes
- **PDF/PMF**: Probability Density Function (continuous) / Probability Mass Function (discrete)
- **CDF**: Cumulative Distribution Function - P(X ≤ x)

### Common Probability Distributions
#### Gaussian (Normal) Distribution
- **Properties**: Bell-shaped curve, symmetric around mean
- **Parameters**: Mean (μ) and standard deviation (σ)
- **Applications**: Error terms, height/weight measurements, central limit theorem

#### Bernoulli and Binomial Distributions
- **Bernoulli**: Single trial with two outcomes (success/failure)
- **Binomial**: Number of successes in n independent Bernoulli trials
- **Applications**: Classification problems, binary outcomes

#### Poisson Distribution
- **Properties**: Models count data over fixed interval
- **Parameter**: λ (rate parameter)
- **Applications**: Event occurrences, count-based features

#### Power Law Distribution
- **Properties**: Heavy-tailed distribution
- **Parameter**: α (exponent)
- **Applications**: Social networks, wealth distribution, natural language

### Hypothesis Testing
#### Basic Concepts
- **Null Hypothesis (H₀)**: Assumed to be true unless proven otherwise
- **Alternative Hypothesis (H₁)**: What we're trying to prove
- **Test Statistic**: Calculated value to test hypothesis
- **p-value**: Probability of observing test statistic under null hypothesis

#### Common Tests
- **t-test**: Compare means of two groups
- **Chi-Square Test**: Test independence of categorical variables
- **ANOVA**: Compare means of three or more groups
- **F-test**: Compare variances of two groups

#### Errors in Hypothesis Testing
- **Type I Error (False Positive)**: Rejecting H₀ when it's true (α)
- **Type II Error (False Negative)**: Accepting H₀ when it's false (β)
- **Power**: Probability of correctly rejecting H₀ (1 - β)

### Confidence Intervals
#### Definition
- **Confidence Level**: Probability that interval contains true parameter
- **Margin of Error**: Range around point estimate
- **Calculation**: Based on sample mean, standard error, and confidence level

#### Interpretation
- 95% confidence interval: 95% of random samples will contain true parameter
- Not a statement about specific interval
- Narrower with larger sample size or lower confidence level

### Estimation Theory
#### Maximum Likelihood Estimation (MLE)
- **Principle**: Choose parameters that maximize likelihood of observed data
- **Likelihood Function**: P(data | parameters)
- **Log-likelihood**: Natural log of likelihood for computational efficiency
- **Applications**: Logistic regression, linear regression

#### Bayesian Inference
- **Bayes' Theorem**: P(θ | data) = P(data | θ)P(θ)/P(data)
- **Prior Distribution**: Belief about parameters before seeing data
- **Posterior Distribution**: Updated belief after seeing data
- **Likelihood**: Probability of data given parameters
- **Applications**: Bayesian networks, posterior predictive distribution

### Bayesian vs. Frequentist Approaches
#### Frequentist Statistics
- **Interpretation**: Probabilities as long-run frequencies
- **Estimation**: Point estimates (mean, median)
- **Uncertainty**: Confidence intervals
- **Examples**: Classic statistical methods

#### Bayesian Statistics
- **Interpretation**: Probabilities as degrees of belief
- **Estimation**: Posterior distributions
- **Uncertainty**: Credible intervals
- **Examples**: Bayesian networks, probabilistic programming

### Probabilistic Graphical Models
#### Bayesian Networks
- **Directed Graph**: Nodes represent variables, edges represent dependencies
- **Conditional Probability Tables**: Quantify relationships between variables
- **Inference**: Calculate posterior probabilities given evidence
- **Applications**: Medical diagnosis, fault detection

#### Markov Random Fields
- **Undirected Graph**: Nodes connected by edges representing dependencies
- **Potential Functions**: Quantify compatibility between variables
- **Applications**: Image segmentation, computer vision

### Information Theory
#### Entropy
- **Definition**: Measure of uncertainty or randomness in a probability distribution
- **Formula**: H(X) = -ΣP(x)logP(x)
- **Properties**: Higher entropy = more uncertainty

#### Kullback-Leibler Divergence
- **Definition**: Measure of difference between two probability distributions
- **Formula**: D_KL(P || Q) = ΣP(x)log(P(x)/Q(x))
- **Properties**: Non-negative, zero if distributions are identical

#### Cross-Entropy
- **Definition**: Average number of bits needed to encode data from P using Q
- **Formula**: H(P, Q) = -ΣP(x)logQ(x)
- **Applications**: Loss function in classification

### Practice Exercises
#### Probability Calculations
1. Calculate probabilities for standard distributions
2. Compute conditional probabilities
3. Apply Bayes' theorem

#### Hypothesis Testing
1. Perform t-tests on sample data
2. Calculate p-values and confidence intervals
3. Interpret results of statistical tests

#### Estimation
1. Implement MLE for simple distributions
2. Perform Bayesian inference
3. Compare different estimation methods

### Resources
- **Books**:
  - "Probability Theory: The Logic of Science" by E.T. Jaynes
  - "Statistics Done Wrong" by Alex Reinhart
- **Online Courses**:
  - Coursera: Probability and Statistics for Data Science
  - Khan Academy: Probability
- **Tools**:
  - Scipy: Statistical functions
  - Stan: Probabilistic programming
  - PyMC3: Bayesian modeling

### Importance in AI/ML
- **Model Evaluation**: p-values, confidence intervals
- **Probabilistic Modeling**: Bayesian networks, Gaussian processes
- **Uncertainty Quantification**: Reliable predictions
- **Decision Making**: Incorporating uncertainty in AI systems

Probability and statistics are essential for:
- Understanding and interpreting AI models
- Evaluating model performance
- Designing experiments
- Making informed decisions based on data
