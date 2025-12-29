# MultiplayerGamePrototype

Unreal Engine Game Developer – Technical Job Task

# UE5 Multiplayer Interaction Prototype

**A multiplayer prototype developed in Unreal Engine 5.5**

This project demonstrates a networked gameplay, focusing on **replicated interaction systems**, **clean interface-driven architecture**, and **network bandwidth optimization**. The implementation prioritizes correctness, scalability, and real-world multiplayer constraints over feature count.

---

## Project Overview

The objective of this prototype is to create a multiplayer environment where players can:

- Connect to a shared session (Listen Server)
- Move responsively using client-side prediction
- Interact with shared world objects in a secure, server-authoritative manner

The system is explicitly designed to be:

- **Cheat-resistant** through strict server authority
- **Modular and extensible** through interface-based interaction
- **Network-efficient** through state replication and event-driven updates

---

## Core Features

- **Networking**
  - Fully replicated movement and gameplay state
  - Listen Server architecture

- **Movement**
  - Networked sprinting with client-side prediction
  - Server reconciliation via authoritative movement component

- **Interaction**
  - Decoupled interaction system using `IInteractableInterface`
  - No hard casting to concrete item classes

---

##️ Technical Architecture

### 1. RPC & Network Logic

The project follows a strict **Server–Client trust model**:

- Clients handle **input and local prediction**
- The Server handles **all gameplay logic and state mutation**

---

### Interaction Flow — `Server_Interact`

1. **Input (Client)**
   - Player presses **E**

2. **RPC**
   - Client sends a **Reliable Server RPC**:  
     `Server_Interact()`

3. **Validation (Server-Side)**
   - Performs a **Capsule Sweep** from the camera forward vector (1200 units)
   - **Security Check**: Confirms the player is overlapping the target’s `OverlapSphere`
   - If either check fails, the interaction is rejected

4. **Execution**
   - Server calls `IInteractableInterface::Interact()`

5. **Replication**
   - State variables are replicated to all clients

6. **Visual Update**
   - Clients respond via `RepNotify` functions
   - Mesh, material, or attachment updates occur locally

---

### Movement Flow — `Server_SetSprinting`

1. **Client-Side Prediction**
   - Client immediately updates `MaxWalkSpeed` for responsiveness

2. **RPC**
   - Client sends `Server_SetSprinting(true)` to the Authority

3. **Server Validation**
   - Server applies its own authoritative movement change
   - If the client misrepresents speed, Unreal’s movement system naturally corrects the position (rubber-banding)

---

## Item Logic

All interactive objects:

- Inherit from `AItemBase`
- Implement `IInteractableInterface`

This allows the character to interact with any item **without casting or class awareness**.

---

### Base Class — `AItemBase`

**UI Detection Logic**

- Uses a **Timer-based Line Trace (10Hz)** to check if the local player is looking at the item
- Interaction widget appears only when:
  - Player is inside the item’s `OverlapSphere` *(range validation)*
  - Crosshair trace hits the item mesh *(visibility validation)*

This avoids unnecessary per-frame work and reduces network/UI overhead.

---

## Item Implementations

### Item A — Sphere (`AItem_Sphere`)

**Concept:** Networked State Machine

- **Replicated Variable**
  - `FLinearColor SphereColor`

- **Server**
  - Generates a random color on interaction

- **Client (`OnRep_SphereColor`)**
  - Creates or updates a Dynamic Material Instance

- **Optimization**
  - Lazy initialization of the material instance prevents memory leaks during repeated state changes

---

### Item B — Cone (`AItem_Cone`)

**Concept:** Ownership Transfer & Attachment

- **Server**
  - Identifies the interacting character

- **Physics Safety**
  - Explicitly disables physics simulation on the server before attachment

- **Attachment**
  - Mesh is attached to the character’s `S_Hat` socket
  - Attachment state replicates automatically to clients

---

### Item C — Cube (`AItem_Cube`)

**Concept:** Lifecycle Management

- **Server**
  - Calls `Destroy()` on interaction

- **Replication**
  - Actor destruction is automatically propagated to all connected clients
  - No additional RPCs required

---

## Controls

| Action     | Key Binding | Notes |
|-----------|------------|------|
| Move      | W, A, S, D | Standard movement
| Jump      | Spacebar   | Replicated jump
| Sprint    | Hold Shift | Increases speed to 1000 units
| Interact  | E          | Requires line-of-sight and overlap
| Look      | Mouse      | Camera control

---

## Setup & Installation

### Clone Repository
```bash
git clone https://github.com/Abir18r/MultiplayerGame.git

## Generate Project Files

 - Right-click the .uproject

 - Select Generate Visual Studio Project Files

 - Compile

 - Open the generated .sln

 - Build using Development Editor

 - Launch

 - Open the project in Unreal Engine 5.5+