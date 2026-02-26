# MLOps & LLMOps
## The Difference Between a Demo and a Business

### Introduction to MLOps & LLMOps
MLOps is the practice of operationalizing machine learning models, while LLMOps is the specialization for large language models (LLMs). Both focus on:
- **Scalability**: Handling large workloads
- **Reliability**: Ensuring consistent performance
- **Efficiency**: Optimizing resource usage
- **Governance**: Compliance with regulations

### Production Engineering Architecture
```
┌─────────────────────────────────┐
│  Data Ops                       │
│  - Data Versioning (DVC)        │
│  - Feature Stores (Feast)       │
│  - Data Quality Monitoring      │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│  CI/CD for ML                   │
│  - Automated Testing            │
│  - Model Packaging              │
│  - Release Management           │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│  Model Serving                  │
│  - vLLM                         │
│  - TGI (Text Generation Inference) │
│  - NVIDIA Triton                │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│  Observability                  │
│  - Prompt Logging (LangSmith)   │
│  - Arize Phoenix                │
│  - Drift Detection              │
│  - Cost Tracking                │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│  Governance                     │
│  - AI Safety                    │
│  - Bias Mitigation              │
│  - Red Teaming                  │
└─────────────────────────────────┘
```

### Data Ops
#### Data Versioning with DVC
```python
import dvc
from dvc.api import read

class DataVersioning:
    def __init__(self, repo_path=".", remote_name="s3"):
        self.repo_path = repo_path
        self.remote_name = remote_name
    
    def add_data_version(self, file_path, commit_message="Add new data version"):
        """Add data to DVC tracking."""
        try:
            dvc.add(file_path)
            dvc.commit(file_path, message=commit_message)
            dvc.push(file_path, remote=self.remote_name)
            return True
        except Exception as e:
            print(f"Data versioning failed: {e}")
            return False
    
    def get_data_version(self, file_path, version="main"):
        """Get specific data version from DVC."""
        try:
            data = read(
                file_path,
                repo=self.repo_path,
                rev=version
            )
            return data
        except Exception as e:
            print(f"Failed to get data version: {e}")
            return None
    
    def list_versions(self, file_path):
        """List all available versions of a file."""
        try:
            history = dvc.history(file_path)
            versions = [
                {
                    'version': item['rev'],
                    'message': item['commit'],
                    'timestamp': item['date']
                }
                for item in history
            ]
            return versions
        except Exception as e:
            print(f"Failed to list versions: {e}")
            return []
```

#### Feature Stores with Feast
```python
import feast
from feast import FeatureStore, FeatureView, Field
from feast.infra.offline_stores.file_source import FileSource
from datetime import datetime

class FeatureStoreManager:
    def __init__(self, repo_path="./feature_repo"):
        self.store = FeatureStore(repo_path=repo_path)
    
    def create_feature_view(self, view_name, source_path):
        """Create and register a feature view."""
        
        source = FileSource(
            path=source_path,
            event_timestamp_column="event_timestamp"
        )
        
        feature_view = FeatureView(
            name=view_name,
            entities=["user_id"],
            features=[
                Field(name="feature1", dtype="float"),
                Field(name="feature2", dtype="int"),
                Field(name="feature3", dtype="string")
            ],
            source=source
        )
        
        self.store.apply([feature_view])
    
    def retrieve_features(self, entity_df, features):
        """Retrieve features for batch or real-time serving."""
        
        try:
            feature_df = self.store.get_historical_features(
                entity_df=entity_df,
                features=features
            ).to_df()
            
            return feature_df
        except Exception as e:
            print(f"Feature retrieval failed: {e}")
            return None
    
    def get_online_features(self, entity_keys, features):
        """Retrieve real-time features from online store."""
        
        try:
            features = self.store.get_online_features(
                entity_rows=[{"user_id": key} for key in entity_keys],
                features=features
            ).to_dict()
            
            return features
        except Exception as e:
            print(f"Online feature retrieval failed: {e}")
            return None
```

### CI/CD for ML
#### GitHub Actions Workflow
```yaml
name: ML CI/CD Pipeline

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    
    - name: Set up Python
      uses: actions/setup-python@v4
      with:
        python-version: '3.9'
    
    - name: Install dependencies
      run: |
        pip install -r requirements.txt
    
    - name: Run unit tests
      run: |
        python -m pytest tests/ -v
    
    - name: Run integration tests
      run: |
        python -m pytest tests/integration/ -v
    
  build:
    runs-on: ubuntu-latest
    needs: test
    steps:
    - uses: actions/checkout@v3
    
    - name: Build Docker image
      run: |
        docker build -t my-ml-model:${{ github.sha }} .
    
    - name: Push to Docker Hub
      run: |
        echo ${{ secrets.DOCKER_PASSWORD }} | docker login -u ${{ secrets.DOCKER_USERNAME }} --password-stdin
        docker tag my-ml-model:${{ github.sha }} ${{ secrets.DOCKER_USERNAME }}/my-ml-model:${{ github.sha }}
        docker tag my-ml-model:${{ github.sha }} ${{ secrets.DOCKER_USERNAME }}/my-ml-model:latest
        docker push ${{ secrets.DOCKER_USERNAME }}/my-ml-model:${{ github.sha }}
        docker push ${{ secrets.DOCKER_USERNAME }}/my-ml-model:latest
```

### Model Serving
#### vLLM (High Throughput Inference)
```python
import vllm
from vllm import LLM, SamplingParams

class vLLMServer:
    def __init__(self, model_name="lmsys/vicuna-7b-v1.5"):
        self.model_name = model_name
        self.llm = LLM(
            model=model_name,
            tensor_parallel_size=2,
            gpu_memory_utilization=0.9
        )
    
    async def generate_batch(self, prompts, max_tokens=256, temperature=0.7):
        """Generate text for multiple prompts in parallel."""
        
        sampling_params = SamplingParams(
            temperature=temperature,
            max_tokens=max_tokens
        )
        
        try:
            outputs = await self.llm.generate(prompts, sampling_params)
            return [output.outputs[0].text for output in outputs]
        except Exception as e:
            print(f"Generation failed: {e}")
            return None
    
    def serve_rest_api(self, host="0.0.0.0", port=8000):
        """Start REST API server."""
        from vllm.entrypoints.openai.api_server import OpenAIServer
        server = OpenAIServer(
            llm=self.llm,
            host=host,
            port=port
        )
        server.run()
```

#### TGI (Text Generation Inference)
```python
import requests
import json

class TGIServer:
    def __init__(self, base_url="http://localhost:3000"):
        self.base_url = base_url
    
    async def generate_text(self, prompt, max_tokens=256, temperature=0.7):
        """Generate text using TGI API."""
        
        headers = {"Content-Type": "application/json"}
        payload = {
            "inputs": prompt,
            "parameters": {
                "max_new_tokens": max_tokens,
                "temperature": temperature,
                "return_full_text": False
            }
        }
        
        try:
            response = requests.post(
                f"{self.base_url}/generate",
                headers=headers,
                json=payload
            )
            
            if response.status_code == 200:
                return response.json()['generated_text']
            else:
                return None
        except Exception as e:
            print(f"Generation failed: {e}")
            return None
    
    async def generate_stream(self, prompt, max_tokens=256):
        """Stream generation response."""
        
        headers = {"Content-Type": "application/json"}
        payload = {
            "inputs": prompt,
            "parameters": {
                "max_new_tokens": max_tokens,
                "stream": True
            }
        }
        
        try:
            with requests.post(
                f"{self.base_url}/generate_stream",
                headers=headers,
                json=payload,
                stream=True
            ) as response:
                for line in response.iter_lines():
                    if line:
                        chunk = json.loads(line.decode('utf-8'))
                        yield chunk['generated_text']
        except Exception as e:
            print(f"Stream generation failed: {e}")
```

### Observability
#### LangSmith Monitoring
```python
import langsmith
from langsmith import Client

class LangSmithMonitor:
    def __init__(self, api_key):
        self.client = Client(api_key=api_key)
    
    def log_prompt(self, prompt, response, metadata=None):
        """Log prompt-response pair."""
        
        try:
            run = self.client.create_run(
                inputs={"prompt": prompt},
                outputs={"response": response},
                metadata=metadata
            )
            return run.id
        except Exception as e:
            print(f"Logging failed: {e}")
            return None
    
    def get_metrics(self, project_name):
        """Get performance metrics for a project."""
        
        try:
            runs = self.client.list_runs(
                project_name=project_name,
                order="desc",
                limit=1000
            )
            
            metrics = {
                "total_runs": 0,
                "average_latency": 0,
                "success_rate": 0
            }
            
            for run in runs:
                metrics["total_runs"] += 1
                if run.outputs:
                    metrics["success_rate"] += 1
            
            if metrics["total_runs"] > 0:
                metrics["success_rate"] /= metrics["total_runs"]
            
            return metrics
        except Exception as e:
            print(f"Metrics retrieval failed: {e}")
            return None
```

#### Arize Phoenix
```python
import phoenix
from phoenix import trace

class ArizePhoenixMonitor:
    def __init__(self, endpoint="http://localhost:6006"):
        self.endpoint = endpoint
    
    def start_tracing(self):
        """Start tracing requests."""
        trace(
            url=self.endpoint,
            project_name="my-llm-project"
        )
    
    def log_request(self, prompt, response, metadata=None):
        """Log request with Arize."""
        
        from phoenix.trace import Span
        from phoenix.trace import SpanStatusCode
        
        with Span(name="llm_request") as span:
            span.set_attributes({
                "prompt": prompt,
                "response": response,
                "metadata": metadata
            })
            span.set_status(SpanStatusCode.OK)
    
    def get_data_drift(self):
        """Get data drift metrics."""
        
        import phoenix as px
        
        try:
            drift_results = px.analyze_dataset_drift(
                baseline_dataset="baseline",
                current_dataset="current"
            )
            
            return {
                "drift_score": drift_results['drift_score'],
                "affected_features": drift_results['drifted_features']
            }
        except Exception as e:
            print(f"Drift detection failed: {e}")
            return None
```

### Governance & Compliance
#### Bias Mitigation
```python
class BiasDetection:
    def __init__(self, evaluation_metrics):
        self.evaluation_metrics = evaluation_metrics
    
    async def detect_bias(self, model, dataset):
        """Detect bias in model predictions."""
        
        results = await model.evaluate(dataset)
        
        bias_metrics = {}
        
        for group in ['gender', 'race', 'age']:
            group_performance = await self._calculate_group_performance(
                model,
                dataset.filter_group(group)
            )
            
            bias_metrics[group] = {
                'overall': results['accuracy'],
                'group_performance': group_performance,
                'disparity': self._calculate_disparity(
                    results['accuracy'],
                    group_performance
                )
            }
        
        return bias_metrics
    
    async def _calculate_group_performance(self, model, dataset):
        """Calculate performance for a specific group."""
        
        predictions = await model.predict(dataset)
        labels = dataset.get_labels()
        
        correct = sum(
            1 for pred, actual in zip(predictions, labels) 
            if pred == actual
        )
        
        return correct / len(dataset)
    
    def _calculate_disparity(self, overall, group_performance):
        """Calculate performance disparity for a group."""
        
        return abs((group_performance / overall) - 1)
```

#### Red Teaming
```python
class RedTeaming:
    def __init__(self, model, prompt_templates):
        self.model = model
        self.prompt_templates = prompt_templates
    
    async def test_adversarial_attacks(self, severity_level='medium'):
        """Test model against adversarial attacks."""
        
        test_results = []
        
        for template_name, template in self.prompt_templates.items():
            if template['severity'] <= severity_level:
                result = await self._run_adversarial_test(template)
                test_results.append(result)
        
        return self._analyze_test_results(test_results)
    
    async def _run_adversarial_test(self, template):
        """Run a single adversarial test."""
        
        try:
            response = await self.model.generate_response(
                template['prompt']
            )
            
            return {
                'template': template['name'],
                'prompt': template['prompt'],
                'response': response,
                'violation': self._detect_violation(response),
                'severity': template['severity']
            }
        except Exception as e:
            return {
                'template': template['name'],
                'prompt': template['prompt'],
                'response': str(e),
                'violation': True,
                'severity': 'critical'
            }
```

### Security & Vulnerability Management
```python
class SecurityMonitor:
    def __init__(self, endpoint):
        self.endpoint = endpoint
    
    def scan_for_vulnerabilities(self, model_path):
        """Scan model for security vulnerabilities."""
        
        from mlsec.scan import ModelScanner
        
        scanner = ModelScanner()
        vulnerabilities = scanner.scan(model_path)
        
        return {
            "critical": sum(1 for v in vulnerabilities if v['severity'] == 'critical'),
            "high": sum(1 for v in vulnerabilities if v['severity'] == 'high'),
            "medium": sum(1 for v in vulnerabilities if v['severity'] == 'medium'),
            "low": sum(1 for v in vulnerabilities if v['severity'] == 'low')
        }
    
    async def monitor_api_security(self):
        """Monitor API for security issues."""
        
        security_events = await self._collect_security_events()
        
        return {
            "total_events": len(security_events),
            "suspicious_requests": self._count_suspicious_requests(security_events),
            "blocked_requests": self._count_blocked_requests(security_events)
        }
```

### Cost Optimization
```python
class CostOptimizer:
    def __init__(self, cloud_provider="aws"):
        self.cloud_provider = cloud_provider
    
    async def optimize_model_deployment(self, current_config):
        """Optimize model deployment for cost efficiency."""
        
        cost_analysis = await self._analyze_current_costs()
        
        optimization_suggestions = []
        
        if cost_analysis['avg_gpu_utilization'] < 0.3:
            optimization_suggestions.append("Consider scaling down GPU resources")
        
        if cost_analysis['api_cost'] > 10000:
            optimization_suggestions.append("Consider model quantization")
        
        if cost_analysis['storage_cost'] > 1000:
            optimization_suggestions.append("Consider deleting old checkpoints")
        
        return {
            "current_cost": cost_analysis['total_cost'],
            "optimization_suggestions": optimization_suggestions,
            "expected_savings": self._calculate_expected_savings(
                optimization_suggestions,
                cost_analysis['total_cost']
            )
        }
```

### Case Study: Production LLM System
```python
class ProductionLLMSystem:
    def __init__(self, config):
        self.config = config
        self.monitors = self._init_monitors()
        self.optimizers = self._init_optimizers()
        self.security = self._init_security()
    
    def _init_monitors(self):
        return {
            "langsmith": LangSmithMonitor(self.config['LANGSMITH_API_KEY']),
            "phoenix": ArizePhoenixMonitor(),
            "prometheus": PrometheusMonitor()
        }
    
    def _init_optimizers(self):
        return {
            "cost": CostOptimizer(),
            "performance": PerformanceOptimizer(),
            "resource": ResourceOptimizer()
        }
    
    def _init_security(self):
        return {
            "bias": BiasDetection(),
            "redteam": RedTeaming(),
            "vulnerability": SecurityMonitor()
        }
    
    async def run_health_check(self):
        """Run comprehensive health check on production system."""
        
        health_report = {
            "timestamp": time.time(),
            "services": {},
            "monitors": {},
            "security": {},
            "cost": {},
            "performance": {}
        }
        
        # Check services
        health_report['services']['api'] = await self._check_api_service()
        health_report['services']['database'] = await self._check_database()
        
        # Run monitors
        health_report['monitors']['langsmith'] = await self.monitors['langsmith'].get_metrics()
        health_report['monitors']['phoenix'] = await self.monitors['phoenix'].get_data_drift()
        
        # Run security checks
        health_report['security']['bias'] = await self.security['bias'].detect_bias()
        health_report['security']['vulnerabilities'] = await self.security['vulnerability'].scan_for_vulnerabilities()
        
        # Calculate costs
        health_report['cost'] = await self.optimizers['cost'].optimize_model_deployment()
        
        return health_report
    
    async def auto_optimize(self):
        """Automatically optimize system based on health report."""
        
        health_report = await self.run_health_check()
        
        actions = []
        
        if health_report['monitors']['phoenix']['drift_score'] > 0.3:
            actions.append("Trigger retraining pipeline")
        
        if health_report['security']['vulnerabilities']['critical'] > 0:
            actions.append("Deploy emergency security patch")
        
        if health_report['cost']['expected_savings'] > 0.2:
            actions.append("Apply cost optimization suggestions")
        
        return {
            "health_report": health_report,
            "suggested_actions": actions
        }
```

### Infrastructure as Code
```yaml
# Terraform configuration for LLM infrastructure
resource "aws_ecs_cluster" "llm_cluster" {
  name = "llm-inference-cluster"
}

resource "aws_ecs_service" "llm_service" {
  name            = "llm-inference-service"
  cluster         = aws_ecs_cluster.llm_cluster.id
  task_definition = aws_ecs_task_definition.llm_task.arn
  desired_count   = 2
  
  network_configuration {
    subnets         = aws_subnet.private_subnets.ids
    security_groups = [aws_security_group.llm_sg.id]
  }
  
  load_balancer {
    target_group_arn = aws_lb_target_group.llm_target_group.arn
    container_name   = "llm-inference-container"
    container_port   = 8000
  }
}

resource "aws_ecs_task_definition" "llm_task" {
  family                   = "llm-inference"
  network_mode             = "awsvpc"
  requires_compatibilities = ["FARGATE"]
  cpu                     = "4096"
  memory                  = "16384"
  
  container_definitions = jsonencode([
    {
      name      = "llm-inference-container"
      image     = "ghcr.io/huggingface/text-generation-inference:latest"
      portMappings = [
        {
          containerPort = 8000
          hostPort      = 8000
        }
      ]
      environment = [
        {
          name  = "MODEL_ID"
          value = "lmsys/vicuna-7b-v1.5"
        },
        {
          name  = "GPU_MEMORY_UTILIZATION"
          value = "0.9"
        }
      ]
      logConfiguration {
        logDriver = "awslogs"
        options = {
          "awslogs-group"         = "/ecs/llm-inference"
          "awslogs-region"        = "us-east-1"
          "awslogs-stream-prefix" = "ecs"
        }
      }
    }
  ])
}
```

### Summary
Production engineering for LLMs involves:
1. **Robust Infrastructure**: Scalable serving with vLLM and TGI
2. **Comprehensive Monitoring**: LangSmith, Arize Phoenix, Prometheus
3. **Automated CI/CD**: GitHub Actions for seamless deployment
4. **Strong Security**: Bias detection and red team testing
5. **Cost Optimization**: Resource allocation and quantization
6. **Data Management**: DVC for versioning, Feast for feature stores
7. **Governance**: Compliance with regulations and ethical guidelines

By implementing these practices, organizations can transition from prototypes to production-grade LLM systems that are reliable, scalable, and cost-effective.
