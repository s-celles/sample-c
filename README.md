# sample-c

C Sample for various isolation methods (containers, VMs).

## Overview

This project demonstrates how to set up a C development environment using different isolation methods:
- **Dev Containers** (Docker) - lightweight containerized development
- **Vagrant** (VirtualBox VM) - full virtual machine isolation

### Isolation Levels

| Environment | Isolation Level | Details |
|-------------|-----------------|---------|
| **DevContainer** | Medium | Runs in a Docker container, shares the host kernel, file system is isolated but mounts your project folder |
| **Vagrant/VirtualBox** | High | Full VM with its own kernel, hardware virtualization, stronger isolation from the host |

> **Note:** Both setups mount/sync your project directory into the guest environment for convenience. For true isolation (e.g., running untrusted code), you would need to remove the volume mount / synced folder and copy files instead.

## Prerequisites

### For Dev Containers
- [Docker](https://www.docker.com/get-started) installed and running
- [VS Code](https://code.visualstudio.com/) with the [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### For Vagrant
- [VirtualBox](https://www.virtualbox.org/)
- [Vagrant](https://www.vagrantup.com/)

## Project Structure

```
.
├── .devcontainer/
│   ├── devcontainer.json    # Dev container configuration
│   └── Dockerfile           # Ubuntu 24.04 based image
├── .vscode/                 # VS Code settings
├── CMakeLists.txt           # CMake build configuration
├── main.c                   # Main source file
├── hello.h.in               # Header template for version info
├── Vagrantfile              # Vagrant VM configuration
└── README.md
```

## Running the project

Clone the repository and open it in VS Code:

```sh
git clone https://github.com/s-celles/sample-c-devcontainer-vagrant.git
cd sample-c-devcontainer-vagrant
code .
```

### Dev Container (Docker)

![VS Code reopen in container](assets/vscode_reopen_in_container.png)

1. Open the project in VS Code
2. When prompted, click "Reopen in Container" or use the command palette (`Ctrl+Shift+P`) and select "Dev Containers: Reopen in Container"
3. Wait for the container to build (first time may take a few minutes)

The container automatically runs cmake and builds the project on startup.

#### Manual build

Open the terminal in VS Code (inside container) via `Terminal > New Terminal` (`Ctrl+Shift+``):

**Using CMake (recommended):**
```sh
cmake -B build -S .
cmake --build build
./build/HelloWorld
```

**Using GCC directly:**
```sh
gcc main.c -o HelloWorld
./HelloWorld
```

Or just press the *Run Code* button found in the top right of the editor panel.

#### Dev Container Features

- **Base image:** Ubuntu 24.04 LTS (Noble Numbat)
- **Installed tools:** gcc, g++, cmake, git, curl
- **VS Code extensions:** C/C++ Extension Pack, CMake Tools

#### Container Lifecycle

The following diagram shows all possible container states and how to transition between them:

```mermaid
stateDiagram-v2
    [*] --> NoContainer: Project opened

    NoContainer --> Building: Reopen in Container
    Building --> Running: Build successful
    Building --> NoContainer: Build failed

    Running --> Stopped: Close VS Code / Stop Container
    Running --> Running: Rebuild Container
    Running --> NoContainer: Dev Containers Clean Up

    Stopped --> Running: Reopen in Container
    Stopped --> NoContainer: Dev Containers Clean Up

    note right of NoContainer
        No container exists
        .devcontainer/ config present
    end note

    note right of Building
        Docker builds image
        from Dockerfile
    end note

    note right of Running
        Container active
        VS Code connected
    end note

    note right of Stopped
        Container exists
        but not running
    end note
```

#### Dev Container Startup Sequence

What happens when you select "Reopen in Container":

```mermaid
sequenceDiagram
    participant User
    participant VSCode as VS Code
    participant Extension as Dev Containers Extension
    participant Docker
    participant Container

    User->>VSCode: Open project folder
    VSCode->>Extension: Detect .devcontainer/
    Extension-->>User: Prompt "Reopen in Container"

    User->>Extension: Click "Reopen in Container"
    Extension->>Extension: Parse devcontainer.json

    Extension->>Docker: Check for existing image
    alt Image not built or outdated
        Extension->>Docker: Build image from Dockerfile
        Docker->>Docker: Pull base image (ubuntu:24.04)
        Docker->>Docker: Run apt-get install commands
        Docker-->>Extension: Image built
    end

    Extension->>Docker: Create container
    Docker->>Container: Start container
    Docker->>Container: Mount workspace folder
    Container-->>Docker: Container running
    Docker-->>Extension: Container ready

    Extension->>Container: Install VS Code Server
    Container-->>Extension: Server running

    Extension->>Container: Install extensions (C/C++, CMake)
    Container-->>Extension: Extensions ready

    alt postCreateCommand defined
        Extension->>Container: Run postCreateCommand
        Container->>Container: cmake -B build && cmake --build build
        Container-->>Extension: Build complete
    end

    Extension-->>VSCode: Connect to container
    VSCode-->>User: Ready to develop
```

#### Dev Container Development Workflow

Decision tree for common Dev Container operations:

```mermaid
flowchart TD
    A[Open Project in VS Code] --> B{.devcontainer/ exists?}
    B -->|No| C[Create .devcontainer/]
    C --> D[Add devcontainer.json]
    D --> E[Add Dockerfile]
    B -->|Yes| F{Container running?}

    F -->|No| G[Reopen in Container]
    F -->|Yes| H[Work in Container]

    G --> I{Build successful?}
    I -->|Yes| H
    I -->|No| J[Check Dockerfile / logs]
    J --> K[Fix configuration]
    K --> G

    H --> L{Need config change?}

    L -->|Yes| M[Edit devcontainer.json / Dockerfile]
    M --> N[Rebuild Container]
    N --> H

    L -->|No| O{Done for now?}

    O -->|Switch to local| P[Reopen Folder Locally]
    O -->|Clean up| Q[Dev Containers: Clean Up]
    O -->|Keep working| H

    P --> R[Container stops]
    Q --> S[Container removed]
```

#### Docker Commands Reference

| Command | Description |
|---------|-------------|
| `docker ps` | List running containers |
| `docker ps -a` | List all containers (including stopped) |
| `docker images` | List Docker images |
| `docker system prune` | Remove unused containers, networks, images |
| `docker logs <container>` | View container logs |

### Vagrant (VirtualBox VM)

1. Start the virtual machine:
```sh
vagrant up
```

2. SSH into the VM:
```sh
vagrant ssh
```

3. Navigate to the project and run the executable:
```sh
cd /home/vagrant/project
./build/HelloWorld
```

The VM automatically builds the project during provisioning.

#### Manual build (inside VM)

```sh
cd /home/vagrant/project
cmake -B build -S .
cmake --build build
./build/HelloWorld
```

#### Vagrant Commands

| Command | Description |
|---------|-------------|
| `vagrant up` | Start and provision the VM |
| `vagrant ssh` | Connect to the VM via SSH |
| `vagrant halt` | Stop the VM |
| `vagrant destroy` | Delete the VM |
| `vagrant reload` | Restart the VM |
| `vagrant provision` | Re-run provisioning scripts |

#### VM Lifecycle

The following diagram shows all possible VM states and the commands to transition between them:

```mermaid
stateDiagram-v2
    [*] --> NotCreated: vagrant init

    NotCreated --> Running: vagrant up
    Running --> Suspended: vagrant suspend
    Running --> PowerOff: vagrant halt
    Running --> NotCreated: vagrant destroy

    Suspended --> Running: vagrant resume
    Suspended --> NotCreated: vagrant destroy

    PowerOff --> Running: vagrant up
    PowerOff --> NotCreated: vagrant destroy

    Running --> Running: vagrant reload
    Running --> Running: vagrant provision

    note right of NotCreated
        No VM exists yet
        Only Vagrantfile present
    end note

    note right of Running
        VM is active
        Can SSH, run commands
    end note

    note right of Suspended
        RAM saved to disk
        Fast resume
    end note

    note right of PowerOff
        Clean shutdown
        Disk preserved
    end note
```

#### Vagrant Up Sequence

What happens when you run `vagrant up`:

```mermaid
sequenceDiagram
    participant User
    participant Vagrant
    participant VirtualBox
    participant VM
    participant Provisioner

    User->>Vagrant: vagrant up
    Vagrant->>Vagrant: Parse Vagrantfile

    alt Box not downloaded
        Vagrant->>Vagrant: Download box image
    end

    Vagrant->>VirtualBox: Create VM (name, memory, cpus)
    VirtualBox-->>Vagrant: VM created

    Vagrant->>VirtualBox: Configure synced folders
    Vagrant->>VirtualBox: Configure network

    Vagrant->>VirtualBox: Start VM
    VirtualBox->>VM: Boot OS
    VM-->>VirtualBox: OS running
    VirtualBox-->>Vagrant: VM started

    Vagrant->>VM: Wait for SSH ready
    VM-->>Vagrant: SSH available

    Vagrant->>VM: Mount synced folders
    VM-->>Vagrant: Folders mounted

    alt First boot or --provision flag
        Vagrant->>Provisioner: Run shell provisioner
        Provisioner->>VM: apt-get update && install packages
        VM-->>Provisioner: Packages installed
        Provisioner->>VM: cmake build commands
        VM-->>Provisioner: Build complete
        Provisioner-->>Vagrant: Provisioning done
    end

    Vagrant-->>User: Machine ready
```

#### Development Workflow

Decision tree for common Vagrant operations:

```mermaid
flowchart TD
    A[Start] --> B{Vagrantfile exists?}
    B -->|No| C[vagrant init]
    C --> D[Edit Vagrantfile]
    B -->|Yes| E{VM exists?}

    E -->|No| F[vagrant up]
    E -->|Yes| G{VM running?}

    G -->|No| H[vagrant up / resume]
    G -->|Yes| I[vagrant ssh]

    F --> I
    H --> I

    I --> J[Work in VM]
    J --> K{Need config change?}

    K -->|Yes| L[Edit Vagrantfile]
    L --> M[vagrant reload]
    M --> I

    K -->|No| N{Done for now?}

    N -->|Pause work| O[vagrant suspend]
    N -->|End session| P[vagrant halt]
    N -->|Delete everything| Q[vagrant destroy]

    O --> R[Fast resume later]
    P --> S[Clean shutdown]
    Q --> T[Start fresh]

    T --> F
```

#### Vagrant Features

- **Base box:** Ubuntu 24.04 LTS (Noble Numbat)
- **Memory:** 2 GB RAM
- **CPUs:** 2 cores
- **Synced folder:** Project mounted at `/home/vagrant/project`
- **Installed tools:** gcc, g++, cmake, git, curl

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Want to contribute?

Feel free to open a PR with any suggestions for this test project!
