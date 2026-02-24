# Transformers & Attention

## What are Transformers?

Transformers are a neural network architecture introduced in the paper "Attention Is All You Need" (2017). They revolutionized Natural Language Processing and are now the backbone of modern AI including LLMs like GPT, BERT, and Llama.

```
┌─────────────────────────────────────────────────────────────┐
│              Transformer Architecture                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│                    INPUT EMBEDDINGS                          │
│                         │                                   │
│                         ▼                                   │
│              ┌─────────────────────┐                      │
│              │   Positional        │                      │
│              │   Encoding          │                      │
│              └──────────┬──────────┘                      │
│                         │                                   │
│                         ▼                                   │
│  ┌──────────────────────────────────────────────────────┐ │
│  │              ENCODER STACK (N layers)                │ │
│  │  ┌─────────────────────────────────────────────────┐  │ │
│  │  │  Multi-Head Self-Attention                     │  │ │
│  │  │         +                                       │  │ │
│  │  │  Add & Norm                                    │  │ │
│  │  │         +                                       │  │ │
│  │  │  Feed Forward Network                          │  │ │
│  │  │         +                                       │  │ │
│  │  │  Add & Norm                                    │  │ │
│  │  └─────────────────────────────────────────────────┘  │ │
│  └──────────────────────────────────────────────────────┘ │
│                         │                                   │
│                         ▼                                   │
│  ┌──────────────────────────────────────────────────────┐ │
│  │              DECODER STACK (N layers)                │ │
│  │  ┌─────────────────────────────────────────────────┐  │ │
│  │  │  Masked Multi-Head Self-Attention              │  │ │
│  │  │         +                                       │  │ │
│  │  │  Add & Norm                                    │  │ │
│  │  │         +                                       │  │ │
│  │  │  Encoder-Decoder Attention                      │  │ │
│  │  │         +                                       │  │ │
│  │  │  Add & Norm                                    │  │ │
│  │  │         +                                       │  │ │
│  │  │  Feed Forward Network                          │  │ │
│  │  │         +                                       │  │ │
│  │  │  Add & Norm                                    │  │ │
│  │  └─────────────────────────────────────────────────┘  │ │
│  └──────────────────────────────────────────────────────┘ │
│                         │                                   │
│                         ▼                                   │
│                    LINEAR + SOFTMAX                         │
│                         │                                   │
│                         ▼                                   │
│                    OUTPUT PROBABILITIES                     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## The Attention Mechanism

### What is Attention?

Attention allows the model to focus on relevant parts of the input when making predictions. It's like how humans focus on important information while ignoring the rest.

```
┌─────────────────────────────────────────────────────────────┐
│                   Self-Attention                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  For each word, the model "attends" to all other words     │
│                                                             │
│  Sentence: "The cat sat on the mat because it was tired"  │
│                                                             │
│  When processing "it":                                     │
│  ┌─────────────────────────────────────────────────────┐  │
│  │ The    cat    sat   on   the   mat  because  was │  │
│  │ 0.1    0.6    0.1   0.0   0.0   0.1   0.0    0.1│  │
│  │                       ↑                             │  │
│  │                      "cat" gets highest attention   │  │
│  └─────────────────────────────────────────────────────┘  │
│                                                             │
│  "it" attends most to "cat" because they're related       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Self-Attention Formula
```
Attention(Q, K, V) = softmax(QK^T / √d_k) × V

Where:
- Q (Query): What we're looking for
- K (Key): What we can look at
- V (Value): The actual content
- d_k: Dimension of keys (scaling factor)
```

### Multi-Head Attention
```
┌─────────────────────────────────────────────────────────────┐
│              Multi-Head Attention                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Instead of one attention function, use multiple:           │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                                                       │  │
│  │  Input X                                              │  │
│  │    │                                                  │  │
│  │    ├──────────────────┬──────────────────┐         │  │
│  │    ▼                  ▼                  ▼          │  │
│  │  Linear Linear Linear (create Q, K, V for each head)│  │
│  │    │                  │                  │          │  │
│  │    ▼                  ▼                  ▼          │  │
│  │  Attention Attention Attention (h heads)           │  │
│  │    │                  │                  │          │  │
│  │    └──────────────────┴──────────────────┘         │  │
│  │                    │                                  │  │
│  │                    ▼                                  │  │
│  │              Concatenate                              │  │
│  │                    │                                  │  │
│  │                    ▼                                  │  │
│  │              Linear (output)                          │  │
│  │                                                       │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                             │
│  Each head learns different aspects:                        │
│  - Head 1: Syntax/grammar                                  │
│  - Head 2: Word relationships                             │
│  - Head 3: Named entities                                 │
│  ...                                                     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Positional Encoding

Since transformers don't have recurrence or convolution, they need positional information to understand word order.

```
┌─────────────────────────────────────────────────────────────┐
│              Positional Encoding                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Formula:                                                   │
│  PE(pos, 2i) = sin(pos / 10000^(2i/d_model))              │
│  PE(pos, 2i+1) = cos(pos / 10000^(2i/d_model))           │
│                                                             │
│  Each position gets a unique encoding:                     │
│                                                             │
│  Position 1: [0.84, 0.54, 0.31, ...]                     │
│  Position 2: [0.90, 0.30, 0.96, ...]                     │
│  Position 3: [0.14, 0.65, 0.27, ...]                     │
│                                                             │
│  This allows the model to understand relative position    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Transformer Types

### Encoder-Only (BERT)
```
Purpose: Understanding / Representation
─────────────────────────────────────────────────────────────
BERT (Bidirectional Encoder Representations from Transformers)

Input → Encoder Stack → Output

- Processes text bidirectionally
- Pre-training: Masked Language Modeling
- Fine-tuning: Classification, NER, QA

Use cases:
- Text classification
- Named Entity Recognition
- Question Answering
```

### Decoder-Only (GPT)
```
Purpose: Generation
─────────────────────────────────────────────────────────────
GPT (Generative Pre-trained Transformer)

Input → Decoder Stack → Output

- Processes text left-to-right (autoregressive)
- Pre-training: Next Token Prediction
- Fine-tuning: Instruction tuning

Use cases:
- Text generation
- Code generation
- Conversation
```

### Encoder-Decoder (T5, BART)
```
Purpose: Seq2Seq / Translation
─────────────────────────────────────────────────────────────

Input → Encoder → Decoder → Output

- Encoder processes input
- Decoder generates output
- Cross-attention between them

Use cases:
- Machine translation
- Text summarization
- Question generation
```

## Large Language Models (LLMs)

### What are LLMs?

LLMs are large transformer models trained on massive amounts of text data. They can understand and generate human-like text.

```
┌─────────────────────────────────────────────────────────────┐
│                    LLM Scale                                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Model Size (Parameters):                                   │
│  ┌─────────────────────────────────────────────────────┐  │
│  │ Model          │ Parameters │ Training Tokens      │  │
│  ├───────────────┼────────────┼───────────────────────┤  │
│  │ GPT-2          │ 1.5B       │ 40GB                 │  │
│  │ GPT-3          │ 175B       │ 570GB                │  │
│  │ GPT-3.5       │ 175B       │ 570GB + RLHF         │  │
│  │ GPT-4         │ ~1.7T*     │ ~13T*                 │  │
│  │ LLaMA-2-70B   │ 70B        │ 2T                   │  │
│  │ Claude 3      │ Unknown    │ Unknown               │  │
│  └───────────────┴────────────┴───────────────────────┘  │
│                                                             │
│  * Estimates (not officially confirmed)                    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### How LLMs Work

```
┌─────────────────────────────────────────────────────────────┐
│              LLM Training Process                            │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Stage 1: Pre-training                                      │
│  ┌─────────────────────────────────────────────────────┐  │
│  │  Massive text corpus (Internet)                    │  │
│  │        │                                            │  │
│  │        ▼                                            │  │
│  │  Next Token Prediction (Language Modeling)         │  │
│  │        │                                            │  │
│  │        ▼                                            │  │
│  │  Learn general language patterns                   │  │
│  │  Knowledge, reasoning, grammar, facts               │  │
│  └─────────────────────────────────────────────────────┘  │
│                                                             │
│  Stage 2: Fine-tuning                                      │
│  ┌─────────────────────────────────────────────────────┐  │
│  │  Human feedback (RLHF)                             │  │
│  │        │                                            │  │
│  │        ▼                                            │  │
│  │  Align with human preferences                      │  │
│  │  Better instruction following                       │  │
│  │  Reduced harmful outputs                            │  │
│  └─────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Prompt Engineering
```
┌─────────────────────────────────────────────────────────────┐
│              Prompt Engineering Techniques                   │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Zero-shot:                                                 │
│  "Translate to French: Hello" → "Bonjour"                   │
│                                                             │
│  Few-shot:                                                  │
│  "Translate: cat → gato, dog → perro, hello → ?"           │
│                                                             │
│  Chain-of-Thought:                                          │
│  "Solve: 2 + 2 * 2 = ?"                                   │
│  "First multiply: 2 * 2 = 4"                              │
│  "Then add: 2 + 4 = 6"                                    │
│  "Answer: 6"                                              │
│                                                             │
│  ReAct (Reason + Act):                                     │
│  Combine reasoning with tool use                            │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Key Transformer Models

### BERT Variants
- BERT (base, large)
- RoBERTa (robustly optimized)
- ALBERT (lite)
- DistilBERT (distilled)

### GPT Family
- GPT-2, GPT-3, GPT-3.5, GPT-4
- GPT-Neo, GPT-J (open source)
- LLaMA (Meta)

### Open Source Models
- LLaMA 2
- Mistral
- Falcon
- BLOOM
- Falcon

## Interview Tips

1. **Know attention mechanism** - Q, K, V, how it works
2. **Understand multi-head attention** - Why multiple heads
3. **Know positional encoding** - Why it's needed
4. **Understand transformer architecture** - Encoder vs Decoder
5. **Know about LLMs** - Pre-training vs fine-tuning
6. **Be ready for prompt engineering questions**

## Summary

Transformers revolutionized NLP:
- **Self-attention** - Focus on relevant context
- **Parallel processing** - No recurrence, faster training
- **Scalability** - Bigger models = better performance
- **Transfer learning** - Pre-train then fine-tune

LLMs are:
- **Massive** - Billions of parameters
- **General-purpose** - Many capabilities
- **Autoregressive** - Generate token by token
- **Emergent abilities** - Few-shot learning, reasoning

The key to working with LLMs:
- **Prompt engineering** - How to get best outputs
- **Fine-tuning** - Adapt to specific tasks
- **RAG** - Combine with knowledge bases
- **Function calling** - Use external tools
