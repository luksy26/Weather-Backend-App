# Weather Subscription App - C++ Design Patterns Project

## Overview

This project is a C++ application that emulates a weather subscription service using a client-server communication architecture. The purpose is to evaluate the effectiveness of different design patterns and architectural styles in creating scalable, maintainable, and efficient software.

The app notifies clients of specific weather conditions for locations they follow and allows clients to query weather reports for arbitrary locations. This project is structured to compare the implementation of various design patterns (such as Observer, Command, and Proxy) and architectural styles (client-server vs. publish-subscribe) and measure their impact on several key metrics.

## Objectives

- **Simulate a Weather Subscription System**: Clients subscribe to weather updates for specific locations and receive notifications based on pre-set weather conditions. They can also request on-demand weather reports for any location.
- **Compare Design Pattern Implementations**: Demonstrate and compare the effectiveness of various design patterns to understand their impact on system efficiency, scalability, and maintainability.
- **Measure Key Metrics**: Quantitatively evaluate latency, throughput, resource usage, modularity, and fault tolerance for different design approaches.

## Design Patterns and Architectural Styles Used

1. **Observer Pattern**
   - Used for the notification mechanism where clients subscribe to specific weather updates.
   - Helps decouple the weather server from the clients, allowing the server to notify all subscribed clients without direct coupling.
2. **Command Pattern**
    - Handles client requests for on-demand weather reports.
Each request is encapsulated as a command, making it easier to manage, log, or queue requests.
3. **Proxy Pattern**
    - Provides a local interface for clients, simulating interactions with the server behind the scenes.
    - This pattern improves modularity and potentially reduces redundant network calls.
4. **Factory Method / Abstract Factory Pattern**
    - Creates different types of notifications, such as general weather updates or severe weather alerts.
    - Ensures scalability and flexibility in adding new notification types.
5. **Architectural Styles**
    - Client-Server Model: Standard model where the server manages all data and handles client requests.
    - Publish-Subscribe Model: Decouples the sender and receiver, where clients subscribe to weather channels and receive updates as notifications.

## Metrics for Comparison

To assess the impact of using design patterns and different architectures, the following metrics are measured:
- **Latency and Throughput**: Time taken for clients to receive updates and respond to queries.
- **Code Modularity and Maintainability**: Code complexity, readability, and ease of extension.
- **Resource Usage**: Memory and CPU usage under various load conditions.
- **Scalability**: System performance under a high volume of clients and frequent weather updates.
- **Error Handling and Fault Tolerance**: System response to communication failures and other unexpected errors.

## Project Structure

The project is divided into the following components:
- **Server**: Manages weather data updates, processes client requests, and notifies subscribed clients.
- **Client**: Allows users to subscribe to specific weather conditions, request weather reports, and receive updates.
- **Communication Layer**: Manages client-server communication.

## Implementation Variations

To illustrate the impact of using design patterns, the following implementations are created:
1. **Without Design Patterns**: Basic implementation where the server directly manages notifications and client requests without abstraction.
2. **With Design Patterns**: Implements the Observer, Command, and Proxy patterns.
3. **Architectural Comparison**: Implements a client-server model and a publish-subscribe model to demonstrate scalability and fault tolerance differences.

## Testing and Experimentation

### Scalability Testing
Simulate a large number of clients subscribing to weather updates and observe how each implementation manages notifications.

### Condition-Based Testing
Simulate various weather conditions to test the responsiveness of the Observer pattern in notifying subscribed clients.

### Failure and Fault Tolerance Testing
Introduce communication failures or interruptions to evaluate how gracefully each implementation recovers.

## Results and Analysis

TODO
