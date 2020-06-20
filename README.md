# UdacityCPP
Udacity C++ Nanodegree Program: **Projects**.

## A* Search Algorithm
* Contained in the folder `A_star`
* Implemented an A* grid-based search algorithm. 
    * The searching behavior a *BFS like algorithm* to visit priority of neighbor nodes w/ higher ```int f``` value, which is a dynamic value relate to its current node during the search process, that equals to the sum of ```int h (Heuristic)``` and ```int g``` value, i.e., ```f(n) = g(n) + h(n)```.
    * A set of tests is provided by Udacity and have been passed using such implementation.`
* In this project, the A* algorithm is utilized to implement a path planning algorithm
    * It is within the *OpenStreetMap* frame
    * It searches a path from givin *start* and *end* position

## Introduction to Object-Oriented-Pogramming (OOP)
* This topic includes a series of introduction, examples and exercise scripts about OOP in C++:
    * **Abstraction**: class declaration/definition, access modifiers.
    * **Inheritance**: basics, multiple inheritance, multi-level inheritance, friend class.
    * **Polymorphism**: overload operator/function, virtual functions.
    * **Generic Programming**: class/function template, deduction and multiple generic types.
others / etc.

## System Monitor Project
* Contained in the folder `System Monitor`
* In this project, a Linux System Monitor is built using C++ OOP topics, including *abstraction*, *inheritance*, *polymorphism*, and etc.
    * It implements similar functionalities as `htop`
    * The basic idea is to read and parse system file contents in `/proc`
