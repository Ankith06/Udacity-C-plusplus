# UdacityCPP
Course materials of Udacity C++ Nanodegree Program: **Knowledge** and **Projects**.

## A* Search Algorithm
* Contained in the folder `A_star`
* Implemented an A* grid-based search algorithm. 
    * The searching behavior a *BFS like algorithm* to visit priority of neighbor nodes w/ higher ```int f``` value, which is a dynamic value relate to its current node during the search process, that equals to the sum of ```int h (Heuristic)``` and ```int g``` value, i.e., ```f(n) = g(n) + h(n)```.
    * A set of tests is provided by Udacity and have been passed using such implementation.

## Path Planning Project
* Contained in the folder `Path_Planning_OpenStreetMap`
* In this project, an A* algorithm is utilized to implement a path planning algorithm
    * it is within the *OpenStreetMap* frame
    * it searches a path from givin *start* and *end* position

## Introduction to Object-Oriented-Pogramming (OOP)
* Contained in the folder `Intro_to_OOP`
* The materials/topics include a series of introduction, examples and exercise scripts about how C++ handles memory management, such as allocation and deleting without memory leak. Such topics include:
    * **Basic Data Type**: `Stack`, `Heap`, `Pointer`, `Reference`, etc.
    * **Memory Process**: `new`, `delete`, `malloc`, `memset`, etc.
    * **Smart Pointer**: `unique_ptr`, `shared_ptr`, etc.
    * others / etc.

## System Monitor Project
* Contained in the folder `System_Monitor`
* In this project, a Linux System Monitor is built using C++ OOP topics, including *abstraction*, *inheritance*, *polymorphism*, and etc.
    * it implements similar functionalities as `htop`
    * the basic idea is to read and parse system file contents in `/proc`
    * (TODO) refine the UI by utilizing Ncurses package
