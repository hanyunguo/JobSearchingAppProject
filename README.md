# Job Searching App

## Description

The **Job Searching App** is designed to help job seekers stay organized during their job hunt. In a competitive job market, keeping track of job applications, deadlines, and tasks can be overwhelming. This app offers a simple and effective way to manage everything in one place.

### Key Features:
- **Job Applications Tracker**: Keep all your job applications organized with details like job title, company name, application links, and job descriptions. Never lose track of an opportunity again.
- **Task and Deadline Organizer**: Stay on top of important dates like application deadlines, interview schedules, and follow-up reminders. You can easily organize tasks to make sure nothing slips through the cracks.
- **Daily Planner**: Plan your day with a built-in daily planner that helps you stay productive and focused on your job search goals.
- **Data Storage**: All your data is saved locally in **XML format**, so you won’t lose any information when you close the app.
- **Simple and Clean Interface**: The app’s user-friendly design makes it easy to add, edit, or remove job applications and tasks. Everything is right at your fingertips.

### Why Use This App?
- **Stay Organized**: Keep all your job applications and tasks in one place to make it easier to track everything without feeling overwhelmed.
- **Save Time**: The app helps you quickly find and manage your job search details, so you can spend less time organizing and more time applying.
- **Flexible & Customizable**: Whether you’re applying for several jobs at once or focusing on a specific role, the app lets you prioritize tasks and set reminders based on your needs.

### Additional Features:
- **Customizable Task Management**: Prioritize your tasks and track deadlines based on urgency.
- **macOS ARM64 Compatible**: The app runs smoothly on macOS ARM64 for a reliable experience.
- **Efficient Performance**: It’s lightweight and designed to handle multiple job applications without slowing down.

---

<img width="749" alt="Screenshot 2024-12-21 at 23 00 26" src="https://github.com/user-attachments/assets/1038902c-d20c-43ab-9e3b-e764771a2a3c" />

<img width="751" alt="Screenshot 2024-12-21 at 23 00 59" src="https://github.com/user-attachments/assets/511e000d-8dc2-41d0-a108-ff53106a8cf4" />

<img width="742" alt="Screenshot 2024-12-21 at 23 01 55" src="https://github.com/user-attachments/assets/1c1cfa79-dbf9-4ea0-a878-fd1c48467242" />

<img width="750" alt="Screenshot 2024-12-21 at 23 02 17" src="https://github.com/user-attachments/assets/e292d70c-4ea4-44d5-a9ca-87e236f38d34" />

## Dependencies

- **Qt Creator**: The project is developed and built using Qt Creator, which is compatible with **macOS ARM64** architecture.
- **Google Test (gtest)**: Used for writing and running unit tests in the project.

## Setup Procedure for Google Test (gtest)

Follow these steps to set up Google Test for your project:

1. **Clone the Google Test Repository:**

   Run the following command to clone the Google Test repository:
   ```bash
   git clone https://github.com/google/googletest.git
   ```

2. **Verify Google Test Build:**
    
- **MacOs**: Confirm that the libraries (libgmock.a, libgtest.a) exist in /path/to/googletest/install/lib. If not, rebuild the project with the following steps:

    ```bash
    cd /path/to/googletest
    mkdir build
    cd build
    cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
    cmake --build .
    ```

- Confirm the existence of the libraries using:

    ```bash
    find . -name "libgtest.a"
    find . -name "libgmock.a"
    ```

- Verify that the libraries are built for arm64:

    ```bash
    lipo -info /path/to/libgtest.a
    lipo -info /path/to/libgmock.a
    ```
3. Update the .pro File:

    Ensure that the paths to the Google Test include and library directories are correctly set in your .pro file:

    ```bash
    INCLUDEPATH += /path/to/googletest/include
    INCLUDEPATH += /path/to/googletest/googlemock/include
    LIBS += -L/path/to/googletest/build/lib -lgmock -lgtest
     ```
4. Debug Build Errors:
    
    If you encounter build errors, check the following:
    - Ensure INCLUDEPATH and LIBS are accurate.
    - If both gmock and gtest are used, ensure the linking order is correct (i.e., -lgmock should come before -lgtest).
    - Clean the build cache in Qt Creator and rebuild.



## Compiling and Running the Project

1. **Clone the Project Repository:** Clone the repository containing the project code:

    ```bash
    git clone git@github.com:UWO-CS-3307/project-deliverable-3-hanyun-doris-s-team.git
    ```

2. **Open the Project in Qt Creator:** Launch Qt Creator, and open the .pro file located in the project directory.
3. **Build the Project:** Click on the green run button in Qt Creator to build and run the project.
4. **Run Test Cases:** The test cases can also be executed by clicking the green run button in Qt Creator. This will run the project along with the test cases.



[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/_YxQha_I)
# Final Project Template - CS 3307
A sample template for the final project of CS 3307


## Table of Contents
[CS3307A Project Instructions - Fall 2024](#cs3307a-project-instructions---fall-2024)  
[Team Structure & Collaboration](#team-structure--collaboration)  
[Project Overview](#project-overview)  
[Key Deliverables](#key-deliverables)  
[Nature of the Project](#nature-of-the-project)  
[Evaluation Criteria](#evaluation-criteria)  
[Submission Guidelines](#submission-guidelines)  


## CS3307A Project Instructions - Fall 2024
The final project for CS3307A is preferred to be completed individually, but students
have the option to work in teams of two maximum. Each individual or team will be
responsible for designing, modeling, and implementing a real-world software system using
Object-Oriented Design and Analysis (OODA) principles in C++. This project offers the
opportunity to apply the concepts learned in class and demonstrate mastery of object-oriented
principles. Students who choose to work in pairs must submit a team contract detailing each
member’s responsibilities, roles, and deadlines to ensure accountability and clarity throughout
the project.

## Team Structure & Collaboration
Individual (preferred) or Group Work: Students have the flexibility to choose to work
individually or in teams of two maximum. Those choosing to work in pairs must submit a team
contract outlining each member’s roles, responsibilities, deadlines, and communication. This
contract must be submitted with the project proposal and will help ensure clarity and
accountability throughout the project.
Collaborative Domain: While multiple individuals or groups may work on different aspects
of a larger, domain-related solution (such as contributing to various components of the same
system or problem space), each team or individual must submit their own unique solution.
Collaboration is limited to discussions about the broader domain, and no code or deliverables
may be shared between groups or individuals. This approach allows for parallel work in a
shared context but ensures that each submission is distinct and independently developed.
Therefore, this is not considered group work but rather independent contributions to a
common problem space.

## Project Overview
Each student will develop a software system that solves a moderately complex problem using
the core concepts of Object-Oriented Design (OOD). This includes:  
• Requirements Gathering and Analysis: Understanding the problem you are solving
and collecting relevant requirements to inform the design of the system.  
• UML System Modeling: Using UML diagrams (Class Diagrams, Sequence Diagrams,
Use Case Diagrams) to represent the design and behavior of your system.  
• Applying Design Patterns: Leveraging at least two creational design patterns
(e.g., Singleton, Factory Method, Abstract Factory) and one structural or behavioral
pattern (e.g., Adapter, Observer, Strategy) to ensure flexibility, scalability, and
maintainability.  
• Full System Implementation in C++: Writing clean, efficient, and functional C++
code to bring your design to life, demonstrating a solid understanding of OOD
principles such as encapsulation, inheritance, polymorphism, and abstraction.
Project Scope:  
• The project must address a non-trivial, real-world problem. Simple systems like
calculators or basic to-do lists will not meet the complexity requirements.  
• You are expected to demonstrate the ability to design a system that is scalable (can be
easily expanded), maintainable (easy to update and refactor), and efficient (handles
operations with optimal use of resources).  
• Your system should implement essential object-oriented concepts and demonstrate best
practices, such as error handling, input validation, and proper use of inheritance and
polymorphism.  

## Key Deliverables
The project will be delivered in three phases, each building upon the previous:  
### 1. Project Proposal (20%)  
* Due: Oct 22, 2024  
* The proposal is a critical first step to outline your understanding of the problem
and your approach to solving it. It must include:  
      - Problem Statement: A clear and concise description of the problem
      your system is solving, including why it is important or relevant.  
      - System Features: A list of key features that your software will include.
      For example, if you're developing an inventory system, features might
      include stock tracking, order processing, and report generation.  
      - Design Approach: An overview of your high-level design. This should
      include a discussion on how you plan to apply object-oriented principles
      and which design patterns you think are relevant to the system. Mention
      key classes and their roles within the system.  
      - Initial UML Class Diagram: A draft class diagram showing the key
      classes, their attributes, methods, and relationships. This diagram should
      highlight key object-oriented concepts such as inheritance and
      encapsulation.


### 2. Intermediate Design and Partial Implementation (30%)  
* Due: Nov 19, 2024  
* This phase involves submitting a detailed system design and a partially
implemented system. The submission must include:  
    - Complete UML Diagrams: You should submit refined versions of
    your UML Class Diagrams and Sequence Diagrams, along with a Use
    Case Diagram. These diagrams must clearly represent the relationships
    between classes, the interactions between objects, and the flow of
    operations.  
    - Use Case Descriptions: For each use case in your diagram, provide
    detailed descriptions that explain the actors, scenarios, and expected
    outcomes.  
    - Partial Implementation in C++: At least 50% of the system should be
    implemented by this stage. Key features should be functional, and you
    should have implemented some of the critical design patterns. The
    implementation should demonstrate the correct use of object-oriented
    principles, such as inheritance, polymorphism, and encapsulation.  
    - Design Rationale Document: A detailed document explaining the
    choices made during the design phase. This includes a justification for the
    design patterns used and how they help address specific challenges in
    your system. For instance, if you’re using a Factory Pattern, explain why
    object creation needed to be abstracted.  


### 3. Final Submission (30%)  
* Due: Dec 17, 2024  
* This is the final submission, where you will deliver a fully implemented system,
including detailed documentation and diagrams. The submission must include:  
    - Complete System Implementation: The final working software
    system implemented in C++. This should include all features outlined in
    the proposal, with careful attention to error handling, user input
    validation, and system performance. Make sure the code is wellstructured, easy to read, and follows best practices for object-oriented
    programming.  
    - Final UML Diagrams: Submit the complete set of UML Class
    Diagrams, Sequence Diagrams, and Use Case Diagrams. These diagrams
    should fully reflect the final design of your system, including all classes,
    relationships, and interactions.  
    - Comprehensive Documentation: This document should provide a
    thorough explanation of:  
        - The overall design and how object-oriented principles (such as
        inheritance, polymorphism, and encapsulation) were applied.  
        - The design patterns used, including why each pattern was chosen
        and how it improves the system’s design.  
        - An analysis of how the system addresses key quality attributes
        such as scalability, performance, and maintainability.  
        - Reflection on challenges faced during the development process
        and how they were overcome.  
        - Test cases or a testing report, including how you validated the
        system’s correctness and performance.  

        
## Nature of the Project  
Your project must involve a system that solves a moderately complex real-world problem. The
complexity of the system should be sufficient to demonstrate the application of multiple objectoriented concepts and design patterns. Below are a few detailed example projects to give you an idea of the scope and expectations:  
* Inventory Management System: A software application that tracks inventory levels,
processes orders, and generates reports. The system should support multiple users with
different access levels (e.g., managers vs. regular employees). You could implement the
Factory Method pattern to manage the creation of different product categories and the
Observer pattern to notify users when stock levels are low.  
* Online Ticket Booking System: A system that allows users to search for events,
book tickets, and manage their bookings. The system must handle concurrent bookings
and ensure ticket availability is updated in real-time. You could use the Singleton pattern
to manage a single instance of the booking system and the Strategy pattern to handle
different payment methods.  
* Task Scheduling Application: An app that allows users to schedule and manage
tasks, with priority levels, reminders, and integration with a calendar system. The system
should allow for dynamic task filtering and sorting. The Command pattern could be used
to implement an undo/redo feature, and the Factory Method pattern to create different
task categories.  
* Student Course Registration System: A system where students can register for
courses, track prerequisites, and check seat availability. You could use the Adapter
pattern to interface with a university’s external system for course prerequisites and the
Singleton pattern to manage course registration across multiple users.  


## Evaluation Criteria  
Your project will be evaluated based on the following:  
* System Design (30%):  
    - UML Diagrams: How clear, accurate, and detailed your UML diagrams are.
    This includes class diagrams, sequence diagrams, and use case diagrams. You will
    be assessed on how well your diagrams capture the system’s structure and
    behavior.  
    - Design Patterns: The correct use and justification of design patterns to
    address specific system challenges.  
    - Object-Oriented Principles: How well you applied encapsulation, inheritance,
polymorphism, and abstraction in the design of your system.  
* Implementation (50%):  
    - Correctness: Whether your system works as intended, with all features
    implemented and functioning correctly.  
    - Object-Oriented Programming: Proper use of object-oriented features,
    such as inheritance and polymorphism, in your code.  
    - Design Patterns: Implementation of design patterns and how effectively they
    improve system flexibility and maintainability.  
    - Code Quality: Well-structured, readable, and commented code that adheres to
    best practices in C++.  
* Documentation (20%):  
    - Clarity: How well you explain your design decisions and the reasoning behind
    them.  
    - Design Rationale: A detailed and thoughtful analysis of how you applied OOD
    principles and design patterns, and how they contribute to the system’s quality.  
    - Testing and Validation: Evidence that the system has been thoroughly tested,
    with a discussion of how potential issues were handled (e.g., error handling,
    input validation).  

    
## Submission Guidelines
* All deliverables (code, diagrams, and documentation) must be submitted through
Brightspace.
* Source code should be well-commented and submitted as a zip file.
* UML diagrams must be submitted in PDF format.
* Ensure that your documentation is clear and concise, covering all required aspects of
the project.
