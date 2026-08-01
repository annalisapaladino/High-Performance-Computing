# High Performance Computing

This repository contains the projects developed for the **High Performance Computing** course of the Master's Degree in **Data Science & Artificial Intelligence** at the **University of Trieste**.

The repository focuses on parallel programming techniques, performance evaluation, and scalability analysis using **MPI**, **OpenMP**, and hybrid programming models.

---

## Project Overview

The repository consists of two main projects.

### Exercise 1 – MPI Collective Communication Benchmarking

The first project evaluates the performance of different **MPI collective communication algorithms** using the **OSU Micro-Benchmarks**.

The analysis includes:

- Broadcast benchmarking
- Scatter benchmarking
- Comparison of different OpenMPI collective algorithms
- Latency measurements
- Strong scalability analysis
- Performance comparison across different hardware configurations (cores, sockets, and nodes)

The collected experimental data were analyzed using Python notebooks and statistical models developed in R.

---

### Exercise 2 – Hybrid MPI + OpenMP Mandelbrot

The second project implements a hybrid parallel application for generating the **Mandelbrot Set**.

The implementation combines:

- MPI for distributed-memory parallelism
- OpenMP for shared-memory parallelism

The project investigates:

- Work distribution across MPI processes
- Thread-level parallelism with OpenMP
- Hybrid parallel programming
- Strong scalability
- Weak scalability
- Overall execution performance

---

## Repository Structure

```
Exercise 1/
    Benchmark analysis
    OSU Micro-Benchmarks
    Statistical models
    Performance evaluation

Exercise 2/
    Hybrid MPI + OpenMP implementation
    Mandelbrot Set generator
    Scalability experiments

README.md
```

---
