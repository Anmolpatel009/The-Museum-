# Agentic Workflows
## Building Intelligent AI Systems with State Machines and Multi-Agent Systems

### Introduction to Agentic AI
Agentic AI systems are autonomous entities that can:
- **Reason**: Make decisions based on goals
- **Act**: Perform actions in their environment
- **Learn**: Improve from experience
- **Communicate**: Interact with other agents and humans

### Agent Architecture Overview
```
┌─────────────────────────────────┐
│       Perception System         │
│ - Environment Observations      │
│ - Sensory Input Processing      │
│ - Context Extraction            │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│      Reasoning Engine           │
│ - Goal Recognition              │
│ - Plan Generation               │
│ - Decision Making               │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│      Execution System           │
│ - Action Selection              │
│ - Task Scheduling               │
│ - Resource Management           │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│       Communication System      │
│ - Natural Language Processing   │
│ - API Integration               │
│ - Multi-Agent Coordination      │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│       Learning System           │
│ - Experience Collection         │
│ - Model Fine-tuning             │
│ - Adaptation Mechanisms         │
└────────────────────┬────────────┘
                     │
                     ▼
┌─────────────────────────────────┐
│        Environment              │
│ - External APIs                 │
│ - Databases                     │
│ - Human Users                   │
└─────────────────────────────────┘
```

### Reasoning Mechanisms
#### Chain-of-Thought (CoT) Reasoning
```python
class ChainOfThoughtReasoner:
    def __init__(self, llm):
        self.llm = llm
    
    def reason(self, query, context):
        prompt = f"""
You are an expert problem solver. Please break down your reasoning step by step.

Context: {context}
Question: {query}

Reasoning Steps:
1. First, I will understand the question and context
2. Then, I will identify key information needed
3. Next, I will develop a plan to solve the problem
4. Then, I will execute the plan step by step
5. Finally, I will summarize the solution

Think through this carefully.
""".strip()
        
        response = self.llm.generate_response(prompt)
        return self.parse_reasoning_steps(response)
    
    def parse_reasoning_steps(self, response):
        steps = []
        lines = response.split('\n')
        for line in lines:
            line = line.strip()
            if line.startswith(('1.', '2.', '3.', '4.', '5.')):
                steps.append(line)
        return steps
```

#### ReAct Reasoning (Reason + Act)
```python
class ReActReasoner:
    def __init__(self, llm, tools):
        self.llm = llm
        self.tools = tools
    
    async def reason_and_act(self, query, context):
        history = [
            {
                "role": "system",
                "content": """
You are an AI assistant that can use tools. Use "THOUGHT:" to think, "ACT:" to use a tool, "OBSERVATION:" to record results.

Available tools:
{tool_list}

Your goal: {query}
Context: {context}
""".format(
    tool_list=self._format_tools(),
    query=query,
    context=context
                )
            }
        ]
        
        max_steps = 10
        
        for i in range(max_steps):
            response = await self.llm.generate_response(history)
            
            history.append({"role": "assistant", "content": response})
            
            if "FINISH:" in response:
                return self._parse_final_response(response)
            
            if "ACT:" in response:
                tool_call = self._parse_tool_call(response)
                if tool_call:
                    try:
                        observation = await self._execute_tool(tool_call)
                        history.append({"role": "system", "content": f"OBSERVATION: {observation}"})
                    except Exception as e:
                        history.append({"role": "system", "content": f"OBSERVATION: Error - {e}"})
        
        return {"status": "failed", "reason": "max_steps_exceeded"}
```

### Agent Frameworks
#### LangGraph (State Machines for AI)
```python
import langgraph
from langgraph.graph import StateGraph, END

class ResearchAgent:
    def __init__(self, llm):
        self.llm = llm
        self.graph = self._build_graph()
    
    def _build_graph(self):
        workflow = StateGraph(ResearchState)
        
        workflow.add_node("search_topics", self.search_topics)
        workflow.add_node("analyze_context", self.analyze_context)
        workflow.add_node("search_papers", self.search_papers)
        workflow.add_node("summarize_papers", self.summarize_papers)
        workflow.add_node("synthesize_report", self.synthesize_report)
        
        workflow.set_entry_point("search_topics")
        workflow.add_edge("search_topics", "analyze_context")
        workflow.add_edge("analyze_context", "search_papers")
        workflow.add_edge("search_papers", "summarize_papers")
        workflow.add_edge("summarize_papers", "synthesize_report")
        workflow.add_edge("synthesize_report", END)
        
        return workflow.compile()
    
    async def search_topics(self, state):
        search_result = await search_service.search(state['query'], n=5)
        return {"topics": search_result['suggestions']}
    
    async def analyze_context(self, state):
        analysis = await self.llm.analyze_context(state['query'], state['topics'])
        return {"context": analysis}
    
    async def search_papers(self, state):
        papers = await scholar_search.search(state['query'], n=10)
        return {"papers": papers}
    
    async def summarize_papers(self, state):
        summaries = []
        for paper in state['papers']:
            content = await arxiv_scraper.get_content(paper['id'])
            summary = await self.llm.summarize(content)
            summaries.append({
                "title": paper['title'],
                "summary": summary
            })
        return {"summaries": summaries}
    
    async def synthesize_report(self, state):
        report = await self.llm.synthesize_report(state['query'], state['summaries'])
        return {"final_report": report}
```

#### CrewAI (Multi-Agent Systems)
```python
from crewai import Agent, Task, Crew

class ProductDevelopmentCrew:
    def __init__(self, llm):
        self.llm = llm
        self.crew = self._build_crew()
    
    def _build_crew(self):
        # Define agents
        researcher = Agent(
            role="Market Research Specialist",
            goal="Identify customer needs and market opportunities",
            backstory="Expert in market analysis and user research",
            llm=self.llm
        )
        
        designer = Agent(
            role="Product Designer",
            goal="Create innovative product designs and user experiences",
            backstory="Award-winning UX/UI designer",
            llm=self.llm
        )
        
        developer = Agent(
            role="Software Developer",
            goal="Build scalable and efficient software solutions",
            backstory="Full-stack developer with 10+ years experience",
            llm=self.llm
        )
        
        tester = Agent(
            role="Quality Assurance Specialist",
            goal="Ensure product quality and reliability",
            backstory="Expert in software testing and quality assurance",
            llm=self.llm
        )
        
        # Define tasks
        research_task = Task(
            description="Conduct market research and user interviews",
            agent=researcher,
            expected_output="Comprehensive market analysis report"
        )
        
        design_task = Task(
            description="Create product wireframes and mockups",
            agent=designer,
            expected_output="Product design specifications"
        )
        
        develop_task = Task(
            description="Implement the product",
            agent=developer,
            expected_output="Working software prototype"
        )
        
        test_task = Task(
            description="Test and validate the product",
            agent=tester,
            expected_output="Test results and bug reports"
        )
        
        # Create crew
        crew = Crew(
            agents=[researcher, designer, developer, tester],
            tasks=[research_task, design_task, develop_task, test_task],
            verbose=2
        )
        
        return crew
    
    def run(self, product_idea):
        return self.crew.kickoff(inputs={"product_idea": product_idea})
```

### Memory Systems
#### Short-Term (Buffer) Memory
```python
class ShortTermMemory:
    def __init__(self, max_tokens=4096):
        self.buffer = []
        self.max_tokens = max_tokens
    
    def add_message(self, role, content):
        """Add message to short-term memory."""
        message = {"role": role, "content": content}
        self.buffer.append(message)
        
        while len(self.buffer) > self.max_tokens:
            self.buffer.pop(0)
    
    def get_recent_context(self, max_messages=10):
        """Get most recent messages as context."""
        return self.buffer[-max_messages:]
    
    def clear(self):
        """Clear short-term memory."""
        self.buffer.clear()
```

#### Long-Term (Vector) Memory
```python
import chromadb
from langchain.embeddings import OpenAIEmbeddings
from langchain.vectorstores import Chroma

class LongTermMemory:
    def __init__(self, persist_directory="./memory_db"):
        self.embeddings = OpenAIEmbeddings()
        self.vectorstore = Chroma(
            persist_directory=persist_directory,
            embedding_function=self.embeddings
        )
    
    def add_experience(self, content, metadata):
        """Add experience to long-term memory."""
        self.vectorstore.add_texts(
            texts=[content],
            metadatas=[metadata],
            ids=[str(time.time())]
        )
    
    def retrieve_relevant_context(self, query, n_results=3):
        """Retrieve relevant context from memory."""
        docs = self.vectorstore.similarity_search(
            query,
            k=n_results
        )
        
        return [doc.page_content for doc in docs]
    
    def get_statistics(self):
        """Get memory statistics."""
        return {
            "total_records": self.vectorstore._collection.count(),
            "memory_size": len(self.vectorstore._collection.get()['ids'])
        }
```

#### Entity Memory
```python
class EntityMemory:
    def __init__(self):
        self.entities = {}
    
    def add_entity(self, entity_name, attributes):
        """Add or update entity in memory."""
        self.entities[entity_name.lower()] = attributes
    
    def update_entity_attribute(self, entity_name, attribute, value):
        """Update entity attribute."""
        entity_name = entity_name.lower()
        if entity_name in self.entities:
            self.entities[entity_name][attribute] = value
    
    def get_entity(self, entity_name):
        """Retrieve entity information."""
        return self.entities.get(entity_name.lower(), {})
    
    def search_entities(self, query):
        """Search entities by query."""
        matches = []
        
        for entity, attributes in self.entities.items():
            if query.lower() in entity:
                matches.append((entity, attributes))
            else:
                for attr, value in attributes.items():
                    if query.lower() in str(value):
                        matches.append((entity, attributes))
        
        return matches
```

### Agentic Workflow Example
```python
class ComplexWorkflowAgent:
    def __init__(self, llm, tools):
        self.llm = llm
        self.tools = tools
        self.graph = self._build_workflow()
    
    def _build_workflow(self):
        workflow = StateGraph(WorkflowState)
        
        workflow.add_node("receive_input", self.receive_input)
        workflow.add_node("route_request", self.route_request)
        workflow.add_node("handle_simple_query", self.handle_simple_query)
        workflow.add_node("handle_research_query", self.handle_research_query)
        workflow.add_node("handle_complex_query", self.handle_complex_query)
        workflow.add_node("finalize_response", self.finalize_response)
        
        workflow.set_entry_point("receive_input")
        workflow.add_edge("receive_input", "route_request")
        workflow.add_conditional_edges(
            "route_request",
            self.route_request_decision,
            {
                "simple": "handle_simple_query",
                "research": "handle_research_query",
                "complex": "handle_complex_query"
            }
        )
        workflow.add_edge("handle_simple_query", "finalize_response")
        workflow.add_edge("handle_research_query", "finalize_response")
        workflow.add_edge("handle_complex_query", "finalize_response")
        workflow.add_edge("finalize_response", END)
        
        return workflow.compile()
    
    async def receive_input(self, state):
        return {"query": state['query']}
    
    async def route_request(self, state):
        classification = await self.llm.classify_query(state['query'])
        return {"classification": classification}
    
    async def route_request_decision(self, state):
        return state['classification']
    
    async def handle_simple_query(self, state):
        answer = await self.llm.answer_question(state['query'])
        return {"response": answer}
    
    async def handle_research_query(self, state):
        research_agent = ResearchAgent(self.llm)
        result = await research_agent.research(state['query'])
        return {"response": result['final_report']}
    
    async def handle_complex_query(self, state):
        analysis = await self.react_agent.reason_and_act(
            state['query'], 
            state['context']
        )
        return {"response": analysis}
    
    async def finalize_response(self, state):
        return {"final_response": state['response']}
```

### Evaluation Framework
```python
class AgentEvaluator:
    def __init__(self, llm):
        self.llm = llm
    
    async def evaluate_task_completion(self, task, response):
        """Evaluate how well the agent completed the task."""
        
        evaluation_prompt = f"""
Please evaluate how well the following task was completed.

Task: {task}
Response: {response}

Criteria:
1. Completeness - Did the response address all aspects of the task?
2. Accuracy - Is the information accurate and correct?
3. Relevance - Is the response relevant to the task?
4. Clarity - Is the response clear and easy to understand?

Rating Scale:
- 5: Excellent (complete, accurate, relevant, clear)
- 4: Good (mostly complete, accurate, relevant, clear)
- 3: Average (somewhat complete, may contain minor errors)
- 2: Poor (incomplete, contains errors, not very relevant)
- 1: Very Poor (not relevant, incorrect)

Please provide a rating from 1-5 and brief explanation.
""".strip()
        
        result = await self.llm.generate_response(evaluation_prompt)
        
        try:
            match = re.search(r'(\d+)\s*:', result)
            rating = int(match.group(1))
            explanation = result.split(':', 1)[1].strip()
        except:
            return {"rating": 0, "explanation": "Could not parse rating"}
        
        return {
            "task": task,
            "response": response,
            "rating": rating,
            "explanation": explanation,
            "timestamp": time.time()
        }
```

### Monitoring & Debugging
```python
from prometheus_client import Counter, Gauge, Histogram

class AgentMonitor:
    def __init__(self):
        self.request_counter = Counter(
            'agent_requests_total', 
            'Total number of agent requests',
            ['agent_type', 'status']
        )
        
        self.response_time = Histogram(
            'agent_response_time_seconds', 
            'Response time distribution',
            ['agent_type']
        )
        
        self.error_counter = Counter(
            'agent_errors_total', 
            'Total errors by agent',
            ['agent_type', 'error_type']
        )
    
    def record_request(self, agent_type, status, duration):
        self.request_counter.labels(agent_type, status).inc()
        self.response_time.labels(agent_type).observe(duration)
    
    def record_error(self, agent_type, error_type):
        self.error_counter.labels(agent_type, error_type).inc()
    
    def get_health_report(self):
        """Generate health report."""
        return {
            'total_requests': self.request_counter._value.get(),
            'total_errors': self.error_counter._value.get(),
            'avg_response_time': self.calculate_avg_response_time()
        }
```

### Security & Compliance
```python
class AgentSecurity:
    def __init__(self, config):
        self.config = config
    
    def validate_request(self, request):
        """Validate incoming request security."""
        
        if not request.get('api_key') or request['api_key'] != self.config['API_KEY']:
            return False, {"error": "Invalid API key"}
        
        user_id = request.get('user_id')
        if user_id and not self._validate_user_id(user_id):
            return False, {"error": "Invalid user ID"}
        
        return True, {}
    
    def sanitize_input(self, text):
        """Sanitize user input to prevent injection attacks."""
        # Remove potentially malicious content
        forbidden_patterns = [
            r'<script[^>]*?>.*?</script>',
            r'javascript:',
            r'vbscript:',
            r'data:',
        ]
        
        for pattern in forbidden_patterns:
            text = re.sub(pattern, '', text, flags=re.IGNORECASE)
        
        return text
    
    def rate_limit(self, user_id):
        """Check rate limits."""
        # Implement simple token bucket or sliding window
        key = f"rate_limit:{user_id}"
        count = self.redis.incr(key)
        
        if count == 1:
            self.redis.expire(key, 60)  # Reset every minute
        
        return count <= self.config['RATE_LIMIT']
```

### Performance Optimization
```python
class AgentOptimizer:
    def __init__(self):
        self.performance_data = {}
    
    def optimize_prompt(self, prompt, query, response):
        """Optimize prompts based on performance."""
        
        response_quality = self._evaluate_response_quality(query, response)
        token_usage = self._count_tokens(response)
        
        optimization_suggestions = []
        
        if response_quality < 3 and token_usage > 1000:
            optimization_suggestions.append("Consider more focused prompts")
        elif response_quality < 2:
            optimization_suggestions.append("Completely rewrite prompt with more context")
        elif token_usage > 2000:
            optimization_suggestions.append("Reduce prompt length to save costs")
        
        return {
            'prompt': prompt,
            'response_quality': response_quality,
            'token_usage': token_usage,
            'suggestions': optimization_suggestions
        }
    
    def optimize_workflow(self, workflow_data):
        """Optimize workflow execution."""
        
        bottlenecks = self._identify_bottlenecks(workflow_data)
        
        optimizations = []
        
        for node, duration in bottlenecks.items():
            if duration > 10 and node == "api_call":
                optimizations.append("Consider caching API responses")
            elif duration > 5 and node == "model_call":
                optimizations.append("Consider using smaller model")
        
        return {
            'workflow_data': workflow_data,
            'bottlenecks': bottlenecks,
            'optimizations': optimizations
        }
```

### Case Study: AI Research Assistant
```python
class AIResearchAssistant:
    def __init__(self, llm, api_keys):
        self.llm = llm
        self.api_keys = api_keys
        self.research_agent = ResearchAgent(llm)
        self.writing_agent = AcademicWritingAgent(llm)
        self.reference_manager = ReferenceManager()
    
    async def conduct_research(self, research_topic):
        """Complete research workflow."""
        
        # Phase 1: Literature Review
        print("1. Conducting literature review...")
        research_result = await self.research_agent.research(research_topic)
        
        # Phase 2: Analysis
        print("2. Analyzing findings...")
        analysis = await self.analyze_research(research_result)
        
        # Phase 3: Writing
        print("3. Writing research paper...")
        paper = await self.writing_agent.write_paper(research_topic, analysis)
        
        # Phase 4: Reference Management
        print("4. Managing references...")
        paper = await self.reference_manager.format_references(paper)
        
        print("Research complete!")
        return paper
    
    async def analyze_research(self, research_result):
        """Analyze research findings."""
        
        analysis_prompt = f"""
Please analyze the following research findings and identify key patterns,
trends, and conclusions. Focus on identifying important insights and
implications for further research.

Research Topic: {research_result['query']}

Findings:
{self._format_research_findings(research_result['summaries'])}

Please provide a comprehensive analysis including:
1. Key Findings
2. Patterns and Trends
3. Gaps in Current Research
4. Implications for Future Work
""".strip()
        
        analysis = await self.llm.generate_response(analysis_prompt)
        
        return {
            'analysis': analysis,
            'findings': research_result['summaries'],
            'timestamp': research_result['timestamp']
        }
```

### Future Directions
```python
class AdvancedAgentFeatures:
    def __init__(self):
        self.feature_flags = {
            'meta_reasoning': False,
            'adaptive_learning': False,
            'self_reflection': False,
            'multi_modal': False
        }
    
    async def enable_meta_reasoning(self):
        """Enable self-reflection and meta-reasoning."""
        self.feature_flags['meta_reasoning'] = True
        await self._retrain_meta_reasoning()
    
    async def enable_adaptive_learning(self):
        """Enable continuous learning from user interactions."""
        self.feature_flags['adaptive_learning'] = True
        await self._setup_learning_pipeline()
    
    async def enable_multi_modal(self):
        """Add support for images and multimedia inputs."""
        self.feature_flags['multi_modal'] = True
        await self._integrate_vision_models()
    
    async def meta_reasoning(self, task, previous_steps):
        """Reflect on previous actions and decide future steps."""
        
        reflection = await self.llm.reflect_on_performance(
            task, 
            previous_steps
        )
        
        if reflection['suggestion'] == 'continue':
            return await self.continue_task()
        elif reflection['suggestion'] == 'backtrack':
            return await self.backtrack_task(reflection['reason'])
        else:
            return await self.abandon_task(reflection['reason'])
```

### Summary
Agentic AI systems represent the future of intelligent computing, with capabilities including:
1. **Advanced Reasoning**: Chain-of-Thought and ReAct mechanisms
2. **Multi-Agent Systems**: CrewAI for collaborative workflows
3. **State Machine Architectures**: LangGraph for complex process control
4. **Memory Systems**: Short-term, long-term, and entity memory
5. **Performance Optimization**: Prompt engineering and workflow tuning
6. **Security & Compliance**: Enterprise-grade security controls
7. **Continuous Learning**: Adaptive systems that improve over time

By implementing these components, organizations can build intelligent agents that handle complex tasks, collaborate with humans and other agents, and continuously improve through experience.
