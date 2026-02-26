# Retrieval Augmented Generation (RAG)
## Enhancing LLMs with External Knowledge

### What is RAG?
Retrieval Augmented Generation (RAG) is an architecture that combines the strengths of:
- **Retrieval Systems**: Access external knowledge bases
- **LLMs**: Generate human-like text responses

### RAG Architecture Overview
```
┌─────────────────────────┐
│   User Query            │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Query Rewriting        │
│  (Optional)             │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Vector Search          │
│  (Similarity Matching)  │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Retrieve Context       │
│  (Top-K relevant chunks)│
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Context Compression    │
│  (Optional)             │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Prompt Construction    │
│  (Query + Context)      │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  LLM Generation         │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Response               │
└─────────────────────────┘
```

### RAG Components in Detail
#### 1. Document Preprocessing Pipeline
```
┌─────────────────────────┐
│   Raw Documents         │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Document Splitting     │
│  (Chunking)             │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Metadata Extraction    │
│  (Title, Author, Date)  │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Text Cleaning          │
│  (Noise Reduction)      │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Embedding Generation   │
│  (Vectorization)        │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│  Vector Database        │
│  (Storage & Indexing)   │
└─────────────────────────┘
```

### Chunking Strategies
#### 1. Fixed-Size Chunking
```python
def fixed_size_chunker(text, chunk_size=1000, overlap=100):
    """Split text into fixed-size chunks with overlap."""
    chunks = []
    start = 0
    while start < len(text):
        end = min(start + chunk_size, len(text))
        chunks.append(text[start:end])
        start += chunk_size - overlap
    return chunks
```

#### 2. Semantic Chunking
```python
def semantic_chunker(text, embedding_model, threshold=0.8):
    """Split text by semantic similarity between sentences."""
    sentences = split_into_sentences(text)
    sentence_embeddings = [
        embedding_model.embed(sentence) for sentence in sentences
    ]
    chunks = []
    current_chunk = [sentences[0]]
    
    for i in range(1, len(sentences)):
        sim = cosine_similarity(
            sentence_embeddings[i-1], 
            sentence_embeddings[i]
        )
        if sim < threshold:
            chunks.append(' '.join(current_chunk))
            current_chunk = []
        current_chunk.append(sentences[i])
    
    if current_chunk:
        chunks.append(' '.join(current_chunk))
    
    return chunks
```

#### 3. Hierarchical Chunking
```python
def hierarchical_chunker(text, max_levels=3):
    """Create hierarchical chunk structure with different granularities."""
    hierarchy = []
    # Level 1: Paragraphs
    hierarchy.append(text.split('\n\n'))
    # Level 2: Sentences within paragraphs
    sentence_level = []
    for paragraph in hierarchy[0]:
        sentences = split_into_sentences(paragraph)
        sentence_level.append(sentences)
    hierarchy.append(sentence_level)
    return hierarchy
```

### Embeddings and Vectorization
#### Choosing Embedding Models
```python
from sentence_transformers import SentenceTransformer
from openai.embeddings import get_embedding

def get_embedding(text, model="text-embedding-ada-002"):
    """Generate embeddings using OpenAI API."""
    text = text.replace("\n", " ")
    return get_embedding(text, model=model)

# Local model alternative
local_model = SentenceTransformer('all-MiniLM-L6-v2')

def get_local_embedding(text):
    """Generate embeddings using local model."""
    return local_model.encode(text)
```

#### Embedding Best Practices
```python
def optimize_embedding(text):
    """Optimize text for better embedding quality."""
    text = text.strip()
    text = re.sub(r'\s+', ' ', text)
    # Remove noisy patterns
    text = re.sub(r'\[.*?\]', '', text)  # Remove references
    text = re.sub(r'\(.*?\)', '', text)  # Remove parenthetical
    return text

def batch_embeddings(texts, model, batch_size=32):
    """Process embeddings in batches."""
    all_embeddings = []
    for i in range(0, len(texts), batch_size):
        batch = texts[i:i+batch_size]
        optimized = [optimize_embedding(t) for t in batch]
        batch_embeddings = model.encode(optimized)
        all_embeddings.extend(batch_embeddings)
    return all_embeddings
```

### Vector Databases
#### Pinecone (Cloud)
```python
from pinecone import Pinecone, ServerlessSpec

def initialize_pinecone(api_key, index_name="my-rag-index"):
    """Initialize Pinecone vector database."""
    pc = Pinecone(api_key=api_key)
    
    if index_name not in pc.list_indexes().names():
        pc.create_index(
            name=index_name,
            dimension=1536,
            metric="cosine",
            spec=ServerlessSpec(
                cloud="aws",
                region="us-east-1"
            )
        )
    
    return pc.Index(index_name)

def query_pinecone(index, query_vector, top_k=3):
    """Query Pinecone vector database."""
    try:
        results = index.query(
            vector=query_vector,
            top_k=top_k,
            include_metadata=True,
            include_values=False
        )
        return parse_pinecone_results(results)
    except Exception as e:
        print(f"Pinecone query failed: {e}")
        return []
```

#### ChromaDB (Local)
```python
import chromadb
from chromadb.utils import embedding_functions

def initialize_chromadb(path="./chroma_db", collection_name="rag-docs"):
    """Initialize ChromaDB locally."""
    client = chromadb.PersistentClient(path=path)
    collection = client.get_or_create_collection(
        name=collection_name,
        embedding_function=embedding_functions.SentenceTransformerEmbeddingFunction()
    )
    return client, collection

def query_chromadb(collection, query_text, top_k=3):
    """Query ChromaDB vector database."""
    try:
        results = collection.query(
            query_texts=[query_text],
            n_results=top_k
        )
        return parse_chroma_results(results)
    except Exception as e:
        print(f"ChromaDB query failed: {e}")
        return []
```

### Advanced RAG Retrieval Techniques
#### Hybrid Search
```python
from rank_bm25 import BM25Okapi
import numpy as np

class HybridRetriever:
    def __init__(self, corpus, corpus_embeddings, embedding_model):
        self.corpus = corpus
        self.corpus_embeddings = corpus_embeddings
        self.embedding_model = embedding_model
        
        tokenized_corpus = [doc.split() for doc in corpus]
        self.bm25 = BM25Okapi(tokenized_corpus)
    
    def retrieve(self, query, top_k=3, weight=0.5):
        query_embedding = self.embedding_model.encode(query)
        
        # Semantic search scores
        sim_scores = cosine_similarity(
            query_embedding, 
            self.corpus_embeddings
        )[0]
        
        # BM25 scores
        tokenized_query = query.split()
        bm25_scores = self.bm25.get_scores(tokenized_query)
        
        # Combine scores
        normalized_sim = sim_scores / np.max(sim_scores)
        normalized_bm25 = bm25_scores / np.max(bm25_scores)
        combined = (weight * normalized_sim) + ((1-weight) * normalized_bm25)
        
        # Get top results
        top_indices = np.argsort(combined)[::-1][:top_k]
        
        return [self.corpus[i] for i in top_indices]
```

#### Re-ranking
```python
from sentence_transformers import CrossEncoder

class Reranker:
    def __init__(self, model_name="cross-encoder/ms-marco-MiniLM-L-6-v2"):
        self.model = CrossEncoder(model_name, max_length=512)
    
    def rerank(self, query, documents, top_k=3):
        """Re-rank retrieved documents based on query-document relevance."""
        pairs = [(query, doc) for doc in documents]
        scores = self.model.predict(pairs)
        
        # Sort by score descending
        ranked = sorted(
            zip(documents, scores), 
            key=lambda x: x[1], 
            reverse=True
        )
        
        return [doc for doc, score in ranked[:top_k]]
```

### Prompt Engineering for RAG
#### Context-aware Prompt Templates
```python
def build_rag_prompt(query, context_chunks):
    """Construct effective prompt with retrieved context."""
    
    prompt_template = """
You are an AI assistant with access to the following information:

{context}

Please answer the question based only on the information provided above. 
If you don't know the answer from the given information, 
please say "I don't know based on the provided information".

Question: {query}
Answer:
""".strip()
    
    context_str = "\n\n---\n\n".join(
        f"[Document chunk {i+1}]: {chunk}" 
        for i, chunk in enumerate(context_chunks)
    )
    
    return prompt_template.format(
        context=context_str,
        query=query
    )

def optimize_context_chunks(chunks, max_tokens=4000):
    """Optimize context by token count and relevance."""
    tokenizer = GPT2Tokenizer.from_pretrained("gpt2")
    optimized = []
    total_tokens = 0
    
    for chunk in chunks:
        chunk_tokens = len(tokenizer.encode(chunk))
        
        if total_tokens + chunk_tokens <= max_tokens:
            optimized.append(chunk)
            total_tokens += chunk_tokens
        else:
            break
    
    return optimized
```

### RAG Evaluation Metrics
```python
def evaluate_rag_response(
    response, 
    ground_truth, 
    query, 
    context_chunks
):
    """Comprehensive RAG response evaluation."""
    
    metrics = {}
    
    # Context Relevance
    context_relevance_scores = []
    cross_encoder = CrossEncoder('cross-encoder/ms-marco-MiniLM-L-6-v2')
    for chunk in context_chunks:
        score = cross_encoder.predict([(query, chunk)])[0]
        context_relevance_scores.append(float(score))
    
    metrics['context_relevance'] = float(np.mean(context_relevance_scores))
    
    # Factuality
    factuality_score = factcheck_response(response, context_chunks)
    metrics['factuality'] = float(factuality_score)
    
    # Answer Precision
    precision = calculate_precision(response, ground_truth)
    metrics['precision'] = float(precision)
    
    # Answer Recall
    recall = calculate_recall(response, ground_truth)
    metrics['recall'] = float(recall)
    
    # Answer F1 Score
    f1 = 2 * (precision * recall) / (precision + recall)
    metrics['f1'] = float(f1)
    
    # Answer Conciseness
    conciseness_score = calculate_conciseness(response, ground_truth)
    metrics['conciseness'] = float(conciseness_score)
    
    # Hallucination Check
    hallucination_score = check_hallucinations(response, context_chunks)
    metrics['no_hallucination'] = float(hallucination_score)
    
    return metrics
```

### Example RAG Pipeline Implementation
```python
class RAGSystem:
    def __init__(self, config):
        """Initialize complete RAG system with all components."""
        
        # Load configuration
        self.config = config
        
        # Initialize document storage
        self.document_store = DocumentStore(config)
        
        # Initialize retriever
        self.retriever = Retriever(config, self.document_store)
        
        # Initialize reranker
        self.reranker = Reranker(config)
        
        # Initialize LLM
        self.llm = LLM(config)
        
        # Initialize response evaluator
        self.evaluator = ResponseEvaluator(config)
    
    async def process_query(self, query, user_id=None, conversation_history=None):
        """Process user query through RAG pipeline."""
        
        try:
            # 1. Preprocess query
            processed_query = self.preprocess_query(query)
            
            # 2. Retrieve relevant contexts
            retrieved_chunks = self.retriever.retrieve(
                processed_query, 
                conversation_history
            )
            
            # 3. Re-rank contexts
            reranked_chunks = self.reranker.rerank(
                processed_query, 
                retrieved_chunks
            )
            
            # 4. Generate response
            prompt = self.build_prompt(processed_query, reranked_chunks)
            response = self.llm.generate_response(prompt)
            
            # 5. Evaluate response
            evaluation = self.evaluator.evaluate(
                query, 
                response, 
                reranked_chunks
            )
            
            return {
                'response': response,
                'contexts': reranked_chunks,
                'evaluation': evaluation
            }
            
        except Exception as e:
            return {
                'response': "I'm sorry, I encountered an error processing your request.",
                'contexts': [],
                'evaluation': {'error': str(e)},
                'error': True
            }
```

### Optimization Strategies
#### Caching for Performance
```python
from functools import lru_cache
from cachetools import TTLCache
import hashlib

class QueryCache:
    def __init__(self, maxsize=1000, ttl=3600):
        self.cache = TTLCache(maxsize=maxsize, ttl=ttl)
    
    def get_cache_key(self, query, model="text-embedding-ada-002"):
        return hashlib.md5(f"{query}:{model}".encode()).hexdigest()
    
    def cache_result(self, query, results):
        key = self.get_cache_key(query)
        self.cache[key] = results
        return results
    
    def get_cached_result(self, query):
        key = self.get_cache_key(query)
        return self.cache.get(key)
```

#### Index Optimization
```python
class DocumentCollection:
    def __init__(self, embeddings_dim=1536, metric='cosine'):
        self.embeddings_dim = embeddings_dim
        self.metric = metric
        self.documents = []
        self.embeddings = []
        self.metadata = []
    
    def add_document(self, text, metadata):
        embedding = get_embedding(text)
        self.documents.append(text)
        self.embeddings.append(embedding)
        self.metadata.append(metadata)
    
    def optimize_index(self):
        # Compress embeddings using principal component analysis
        from sklearn.decomposition import PCA
        
        if len(self.embeddings) < 1000:
            return  # Skip for small collections
        
        pca = PCA(n_components=0.95)
        compressed_embeddings = pca.fit_transform(self.embeddings)
        
        print(f"Compressed from {self.embeddings_dim} to {compressed_embeddings.shape[1]} dimensions")
        
        self.embeddings_dim = compressed_embeddings.shape[1]
        self.embeddings = compressed_embeddings
    
    def cluster_documents(self, n_clusters=100):
        from sklearn.cluster import KMeans
        
        if len(self.embeddings) < n_clusters * 2:
            return
        
        kmeans = KMeans(n_clusters=n_clusters)
        labels = kmeans.fit_predict(self.embeddings)
        
        self.metadata = [
            {**meta, 'cluster': int(label)} 
            for meta, label in zip(self.metadata, labels)
        ]
        
        self.kmeans_model = kmeans
```

### Deployment Architecture
```python
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import asyncio
import logging

app = FastAPI(title="RAG API")
rag_system = None

@app.on_event("startup")
async def startup_event():
    """Initialize RAG system on server startup."""
    global rag_system
    try:
        config = load_config()
        rag_system = RAGSystem(config)
        await rag_system.initialize()
        logging.info("RAG system initialized successfully")
    except Exception as e:
        logging.error(f"Failed to initialize RAG system: {e}")
        raise

class QueryRequest(BaseModel):
    query: str
    user_id: Optional[str] = None
    history: Optional[List[Dict[str, str]]] = None

class QueryResponse(BaseModel):
    response: str
    contexts: List[str]
    evaluation: Dict[str, float]
    response_time: float

@app.post("/query", response_model=QueryResponse)
async def process_query(request: QueryRequest):
    """Process RAG query."""
    try:
        start_time = time.time()
        
        result = await rag_system.process_query(
            request.query,
            request.user_id,
            request.history
        )
        
        response_time = time.time() - start_time
        
        if result.get('error'):
            raise HTTPException(status_code=500, detail=result['response'])
        
        return QueryResponse(
            response=result['response'],
            contexts=result['contexts'],
            evaluation=result['evaluation'],
            response_time=response_time
        )
        
    except Exception as e:
        logging.error(f"Error processing query: {e}")
        raise HTTPException(status_code=500, detail=str(e))
```

### Performance Monitoring Dashboard
```python
import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objects as go
import pandas as pd

app = dash.Dash(__name__)

app.layout = html.Div([
    html.H1("RAG System Performance Dashboard"),
    
    dcc.Interval(
        id='interval-component',
        interval=60000,  # Refresh every minute
        n_intervals=0
    ),
    
    html.Div([
        dcc.Graph(id='response-time-graph'),
        dcc.Graph(id='context-relevance-graph'),
        dcc.Graph(id='factuality-graph'),
        dcc.Graph(id='throughput-graph'),
        dcc.Graph(id='error-rate-graph')
    ])
])

@app.callback(
    [Output('response-time-graph', 'figure'),
     Output('context-relevance-graph', 'figure'),
     Output('factuality-graph', 'figure'),
     Output('throughput-graph', 'figure'),
     Output('error-rate-graph', 'figure')],
    [Input('interval-component', 'n_intervals')]
)
def update_metrics(n):
    metrics = fetch_recent_metrics()
    
    figures = []
    metrics_to_plot = ['response_time', 'context_relevance', 'factuality', 'throughput', 'error_rate']
    
    for metric in metrics_to_plot:
        fig = go.Figure()
        fig.add_trace(go.Scatter(
            x=metrics['timestamps'],
            y=metrics[metric],
            mode='lines+markers',
            name=metric.replace('_', ' ').title()
        ))
        fig.update_layout(title=metric.replace('_', ' ').title())
        figures.append(fig)
    
    return figures

if __name__ == '__main__':
    app.run_server(debug=True, host='0.0.0.0', port=8050)
```

### Security and Compliance
```python
class SecurityHandler:
    def __init__(self, config):
        self.config = config
        self.jwt_validator = JWTValidator(config)
        self.harm_detector = HarmDetection(config)
    
    def validate_request(self, request: Request):
        """Validate incoming request."""
        
        # Validate API key if required
        api_key = request.headers.get('X-API-Key')
        if api_key and api_key != self.config['API_KEY']:
            raise HTTPException(
                status_code=401, 
                detail="Invalid API key"
            )
        
        # Validate user credentials
        user_id = request.headers.get('X-User-ID')
        if user_id:
            if not self.validate_user(user_id):
                raise HTTPException(
                    status_code=403, 
                    detail="User not authorized"
                )
        
        return True
    
    async def filter_content(self, text):
        """Filter harmful content."""
        harm_scores = await self.harm_detector.analyze(text)
        
        if any(score > self.config['HARM_THRESHOLD'] for score in harm_scores):
            raise HTTPException(
                status_code=400, 
                detail="Content violates usage policy"
            )
        
        return text
```

### Usage Analytics
```python
class UsageAnalytics:
    def __init__(self, config):
        self.config = config
        self.metrics = []
    
    def record_request(self, request, response, evaluation):
        """Record detailed request metrics."""
        
        record = {
            'timestamp': time.time(),
            'request_id': request.request_id,
            'user_id': request.user_id,
            'query_length': len(request.query),
            'response_length': len(response['response']),
            'context_count': len(response['contexts']),
            **evaluation,
            'model_type': 'rag',
            'processed': True
        }
        
        self.metrics.append(record)
    
    def get_performance_report(self, time_window='24h'):
        """Generate detailed performance report."""
        
        relevant_records = self._filter_records(time_window)
        
        report = {
            'total_requests': len(relevant_records),
            'avg_response_time': np.mean([r['response_time'] for r in relevant_records]),
            'avg_context_relevance': np.mean([r['context_relevance'] for r in relevant_records]),
            'avg_factuality': np.mean([r['factuality'] for r in relevant_records]),
            'avg_f1_score': np.mean([r['f1'] for r in relevant_records]),
            'error_rate': np.mean([1 if r.get('error') else 0 for r in relevant_records]),
            'model_usage': {
                'avg_response_tokens': np.mean([
                    calculate_tokens(r['response']) for r in relevant_records
                ]),
                'avg_context_tokens': np.mean([
                    sum(calculate_tokens(c) for c in r['contexts']) for r in relevant_records
                ])
            },
            'throughput': len(relevant_records) / self._window_seconds(time_window)
        }
        
        return report
```

### Summary
The modern RAG architecture is a sophisticated system combining:
1. **Document Management**: Efficient processing and storage
2. **Retrieval**: Advanced similarity search with multiple techniques
3. **LLM Integration**: Powerful generation based on retrieved context
4. **Evaluation**: Comprehensive quality assessment
5. **Monitoring**: Real-time performance tracking
6. **Scalability**: Optimized infrastructure for production

By implementing these components, you can build RAG systems that provide accurate, factual responses based on your specific knowledge base.
