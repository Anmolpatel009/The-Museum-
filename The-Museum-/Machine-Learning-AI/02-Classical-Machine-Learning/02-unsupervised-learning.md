# Unsupervised Learning
## Finding Patterns in Unlabeled Data

### What is Unsupervised Learning?
- **Definition**: Learning from unlabeled data to find inherent patterns
- **Goal**: Discover structure, clusters, or hidden patterns
- **Key Differences from Supervised Learning**:
  - No predefined labels
  - No target variable to predict
  - Focus on exploration and discovery

### Common Applications
- **Clustering**: Group similar data points together
- **Dimensionality Reduction**: Simplify data while preserving information
- **Anomaly Detection**: Identify unusual patterns
- **Association Rule Mining**: Find relationships between variables
- **Data Visualization**: Create 2D/3D representations of high-dimensional data

### Clustering Algorithms
#### K-Means Clustering
- **Basic Concept**: Partition data into K clusters
- **Algorithm Steps**:
  1. Initialize K cluster centroids
  2. Assign each point to nearest centroid
  3. Update centroids as mean of assigned points
  4. Repeat until convergence

- **Key Parameters**:
  - K: Number of clusters
  - Initialization method: Random, K-means++
  - Distance metric: Euclidean (default)

- **Pros and Cons**:
  - Pros: Simple, fast, scalable
  - Cons: Requires predefined K, sensitive to initialization

#### Hierarchical Clustering
- **Agglomerative (Bottom-Up)**:
  1. Start with each point as cluster
  2. Merge closest clusters iteratively
  3. Continue until single cluster

- **Divisive (Top-Down)**:
  1. Start with all points in one cluster
  2. Split cluster recursively
  3. Continue until single points

- **Linkage Methods**:
  - Single Linkage: Closest pair distance
  - Complete Linkage: Farthest pair distance
  - Average Linkage: Average pairwise distance
  - Centroid Linkage: Distance between centroids

#### DBSCAN (Density-Based Spatial Clustering)
- **Key Concepts**:
  - Core Points: Minimum number of neighbors within radius ε
  - Border Points: Reach core points but don't have enough neighbors
  - Noise Points: No core points nearby

- **Advantages**:
  - No need to specify K
  - Handles arbitrary shaped clusters
  - Robust to noise

- **Parameters**:
  - ε: Radius
  - min_samples: Minimum points for core status

#### Gaussian Mixture Models (GMM)
- **Probabilistic Clustering**: Points belong to multiple clusters with probabilities
- **Assumption**: Data comes from mixture of Gaussian distributions
- **Parameter Estimation**: Expectation-Maximization (EM) algorithm
- **Applications**: Soft clustering, density estimation

### Dimensionality Reduction
#### Principal Component Analysis (PCA)
- **Goal**: Find directions of maximum variance
- **Key Steps**:
  1. Standardize data
  2. Compute covariance matrix
  3. Compute eigenvalues and eigenvectors
  4. Sort and select top K components

- **Applications**:
  - Data compression
  - Noise reduction
  - Visualization
  - Feature engineering

#### t-SNE (t-Distributed Stochastic Neighbor Embedding)
- **Goal**: Visualize high-dimensional data in 2D/3D
- **Key Features**:
  - Preserves local structure
  - Non-linear dimensionality reduction
  - Perplexity parameter controls neighborhood size

- **Applications**:
  - Visualizing high-dimensional data
  - Cluster visualization
  - Data exploration

#### UMAP (Uniform Manifold Approximation and Projection)
- **Recent Advance**: Faster and more scalable than t-SNE
- **Key Advantages**:
  - Better preserves global structure
  - Linear time complexity
  - Parallelizable

### Association Rule Mining
#### Apriori Algorithm
- **Goal**: Find frequent itemsets and association rules
- **Key Concepts**:
  - Support: Fraction of transactions containing itemset
  - Confidence: P(B|A) = P(A∩B)/P(A)
  - Lift: P(B|A)/P(B) (measure of dependence)

- **Algorithm Steps**:
  1. Find all frequent itemsets with support ≥ minimum support
  2. Generate association rules from frequent itemsets
  3. Prune rules with confidence < minimum confidence

- **Applications**:
  - Market basket analysis
  - Recommendation systems
  - Web usage mining

### Anomaly Detection
#### Isolation Forest
- **Random Forest-based**: Isolate anomalies by creating random decision trees
- **Key Idea**: Anomalies are easier to isolate (fewer splits)
- **Advantages**:
  - Handles high-dimensional data
  - Fast and scalable
  - No distance calculations

#### Local Outlier Factor (LOF)
- **Density-Based**: Measures local deviation from neighbors
- **LOF Score**: >1 indicates anomaly, higher score = more anomalous
- **Advantages**:
  - Handles local density variations
  - No predefined thresholds

### Evaluation of Unsupervised Learning
#### Internal Evaluation Metrics
- **Silhouette Score**: Measures cluster tightness and separation
- **Davies-Bouldin Index**: Average similarity between clusters
- **Calinski-Harabasz Index**: Ratio of between-cluster to within-cluster dispersion

#### External Evaluation Metrics (If Labels Available)
- **Adjusted Rand Index**: Measures agreement with ground truth
- **Normalized Mutual Information**: Measures information shared between clusters
- **Fowlkes-Mallows Score**: Geometric mean of precision and recall

### Practice Exercises
#### Clustering
1. Implement K-means on synthetic data
2. Compare hierarchical clustering with DBSCAN
3. Apply GMM to real-world data

#### Dimensionality Reduction
1. Perform PCA on high-dimensional data
2. Visualize data with t-SNE and UMAP
3. Compare dimensionality reduction methods

#### Association Rule Mining
1. Apply Apriori algorithm to transaction data
2. Analyze frequent itemsets and association rules
3. Tune support and confidence thresholds

### Resources
- **Books**:
  - "Pattern Recognition and Machine Learning" by Christopher Bishop
  - "Data Mining: Concepts and Techniques" by Han et al.
- **Online Courses**:
  - Coursera: Unsupervised Learning (Andrew Ng)
  - edX: Machine Learning Fundamentals
- **Tools**:
  - Scikit-learn: Clustering, dimensionality reduction
  - scipy.cluster: Hierarchical clustering
  - mlxtend: Association rule mining

### Real-World Applications
#### Clustering
- **Customer Segmentation**: Group customers for targeted marketing
- **Image Segmentation**: Partition images into meaningful regions
- **Document Clustering**: Organize documents into topics

#### Dimensionality Reduction
- **Feature Selection**: Reduce dimensionality for classification
- **Visualization**: Explore high-dimensional datasets
- **Data Compression**: Reduce storage and computation requirements

#### Association Rule Mining
- **Retail**: Recommend complementary products (like Amazon's "Frequently Bought Together")
- **Healthcare**: Identify co-occurring medical conditions
- **Finance**: Detect fraud patterns

#### Anomaly Detection
- **Credit Card Fraud**: Identify unusual transactions
- **Network Intrusion**: Detect suspicious network activity
- **Manufacturing**: Predict equipment failure

Unsupervised learning is a powerful tool for exploratory data analysis and discovering hidden patterns in large datasets without requiring labeled data.
