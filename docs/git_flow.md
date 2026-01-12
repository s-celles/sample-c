# Git & GitHub Development Workflows

A visual guide to the most popular Git branching strategies and development workflows.

---

## 1. Git Flow

The original branching model introduced by Vincent Driessen in 2010. It defines a strict branching structure designed around project releases, making it ideal for software with scheduled release cycles.

**Key branches:**
- `main` — Production-ready code, tagged with version numbers
- `develop` — Integration branch for features
- `feature/*` — New features, branched from develop
- `release/*` — Preparation for a new release
- `hotfix/*` — Emergency fixes for production

```mermaid
---
title: Git Flow - Classic Branching Model
---
gitGraph
    commit id: "Initial"
    branch develop
    checkout develop
    commit id: "Dev setup"
    
    branch feature/login
    checkout feature/login
    commit id: "Add login form"
    commit id: "Add validation"
    checkout develop
    merge feature/login id: "Merge login" tag: "feature complete"
    
    branch feature/dashboard
    checkout feature/dashboard
    commit id: "Create dashboard"
    commit id: "Add widgets"
    checkout develop
    merge feature/dashboard id: "Merge dashboard"
    
    branch release/1.0
    checkout release/1.0
    commit id: "Bump version"
    commit id: "Fix bug"
    checkout main
    merge release/1.0 id: "v1.0.0" tag: "v1.0.0"
    checkout develop
    merge release/1.0 id: "Back-merge"
    
    checkout main
    branch hotfix/security
    commit id: "Security patch"
    checkout main
    merge hotfix/security id: "v1.0.1" tag: "v1.0.1"
    checkout develop
    merge hotfix/security id: "Hotfix to dev"
```

**Best for:** Projects with scheduled releases, multiple versions in production, or teams requiring strict release management.

---

## 2. GitHub Flow

A lightweight, branch-based workflow that supports teams and projects deploying regularly. There's only one rule: anything in `main` is deployable.

**Principles:**
- `main` is always deployable
- Create descriptive branches for new work
- Open a Pull Request for discussion and review
- Deploy immediately after merging

```mermaid
---
title: GitHub Flow - Simple PR-Based Workflow
---
gitGraph
    commit id: "Production"
    commit id: "Stable"
    
    branch feature/new-api
    checkout feature/new-api
    commit id: "Create endpoint"
    commit id: "Add tests"
    commit id: "Code review fixes"
    checkout main
    merge feature/new-api id: "PR #42 merged" tag: "deploy"
    
    branch feature/ui-update
    checkout feature/ui-update
    commit id: "Update styles"
    commit id: "Responsive design"
    checkout main
    merge feature/ui-update id: "PR #43 merged" tag: "deploy"
    
    branch bugfix/form-error
    checkout bugfix/form-error
    commit id: "Fix validation"
    checkout main
    merge bugfix/form-error id: "PR #44 merged" tag: "deploy"
    
    commit id: "Production ready"
```

**Best for:** Web applications, SaaS products, and teams practicing continuous deployment.

---

## 3. Trunk-Based Development

A source-control branching model where developers collaborate on code in a single branch called "trunk" (or `main`), resisting the urge to create long-lived feature branches.

**Key practices:**
- Short-lived feature branches (ideally < 1 day)
- Direct commits to trunk for small changes
- Feature flags for incomplete features
- Release branches only for cherry-picking fixes

```mermaid
---
title: Trunk-Based Development
---
gitGraph
    commit id: "Init"
    commit id: "Feature A"
    
    branch short-lived/feature-b
    checkout short-lived/feature-b
    commit id: "Quick change"
    checkout main
    merge short-lived/feature-b id: "Merge (< 1 day)"
    
    commit id: "Direct commit"
    commit id: "Small fix"
    
    branch short-lived/feature-c
    checkout short-lived/feature-c
    commit id: "Fast iteration"
    checkout main
    merge short-lived/feature-c id: "Merge quickly"
    
    commit id: "Continuous" tag: "v1.0"
    commit id: "Integration"
    
    branch release/1.x
    checkout release/1.x
    commit id: "Cherry-pick fix"
    checkout main
    
    commit id: "New feature"
    commit id: "Keep trunk green" tag: "v1.1"
```

**Best for:** High-performing teams, CI/CD environments, and organizations prioritizing rapid iteration.

---

## 4. GitLab Flow (Environment Branches)

Combines feature-driven development with environment branches for deployment. It provides a clear path from development through staging to production.

**Environment branches:**
- `main` — Latest development code
- `pre-production` — Staging environment
- `production` — Live environment

```mermaid
---
title: GitLab Flow (Environment Branches)
---
gitGraph
    commit id: "Init"
    
    branch feature/auth
    checkout feature/auth
    commit id: "Add OAuth"
    commit id: "Add tests"
    checkout main
    merge feature/auth id: "MR merged"
    
    commit id: "More features"
    
    branch pre-production
    checkout pre-production
    commit id: "Staging deploy" tag: "staging"
    
    checkout main
    branch feature/cache
    commit id: "Add Redis"
    checkout main
    merge feature/cache id: "MR #2"
    
    checkout pre-production
    merge main id: "Update staging"
    
    branch production
    checkout production
    commit id: "Production deploy" tag: "v1.0"
    
    checkout main
    commit id: "New feature"
    checkout pre-production
    merge main id: "To staging"
    checkout production
    merge pre-production id: "Release" tag: "v1.1"
```

**Best for:** Teams needing multiple deployment environments with controlled promotion between stages.

---

## 5. Forking Workflow

The standard workflow for open source projects. Contributors fork the repository, make changes in their own copy, and submit pull requests to the upstream repository.

```mermaid
---
title: Forking Workflow (Open Source Contributions)
---
flowchart TB
    subgraph upstream["🏢 Upstream Repository (Original Project)"]
        um[main branch]
    end
    
    subgraph fork["🍴 Your Fork (GitHub)"]
        fm[main branch]
        fb[feature branch]
    end
    
    subgraph local["💻 Local Machine"]
        lm[main branch]
        lb[feature branch]
    end
    
    um -->|"1. Fork on GitHub"| fm
    fm -->|"2. git clone"| lm
    lm -->|"3. git checkout -b feature"| lb
    lb -->|"4. Make changes & commit"| lb
    lb -->|"5. git push origin feature"| fb
    fb -->|"6. Open Pull Request"| um
    um -->|"7. Maintainer reviews & merges"| um
    um -->|"8. git fetch upstream"| lm
    lm -->|"9. git push origin main"| fm
    
    style upstream fill:#e1f5fe,stroke:#01579b
    style fork fill:#fff3e0,stroke:#e65100
    style local fill:#e8f5e9,stroke:#2e7d32
```

**Best for:** Open source projects, external contributions, and maintaining a clean upstream repository.

---

## 6. Pull Request Lifecycle

Regardless of the branching strategy, pull requests follow a similar lifecycle from creation to deployment.

```mermaid
---
title: Pull Request Lifecycle
---
flowchart LR
    subgraph Development
        A[📝 Create Branch] --> B[💻 Write Code]
        B --> C[✅ Run Tests Locally]
        C --> D[📤 Push to Remote]
    end
    
    subgraph Review["Code Review"]
        D --> E[🔀 Open PR]
        E --> F{CI/CD Checks}
        F -->|Pass| G[👀 Request Review]
        F -->|Fail| B
        G --> H{Reviewer Feedback}
        H -->|Changes Requested| B
        H -->|Approved| I[✅ Approved]
    end
    
    subgraph Merge
        I --> J{Merge Strategy}
        J -->|Squash| K[Squash & Merge]
        J -->|Rebase| L[Rebase & Merge]
        J -->|Merge Commit| M[Create Merge Commit]
        K --> N[🗑️ Delete Branch]
        L --> N
        M --> N
        N --> O[🚀 Deploy]
    end
    
    style A fill:#bbdefb
    style E fill:#fff9c4
    style I fill:#c8e6c9
    style O fill:#ffccbc
```

---

## 7. Choosing the Right Workflow

Use this decision tree to select the workflow that best fits your team and project.

```mermaid
---
title: Git Workflow Selection Guide
---
flowchart TD
    START([🤔 Choose a Git Workflow]) --> Q1{Team Size?}
    
    Q1 -->|Solo / Small| Q2{Release Cadence?}
    Q1 -->|Large / Enterprise| Q3{Open Source?}
    
    Q2 -->|Continuous| GHF[✅ GitHub Flow]
    Q2 -->|Scheduled| Q4{Complex Releases?}
    
    Q3 -->|Yes| FORK[✅ Forking Workflow]
    Q3 -->|No| Q5{Multiple Environments?}
    
    Q4 -->|Yes| GF[✅ Git Flow]
    Q4 -->|No| TBD[✅ Trunk-Based]
    
    Q5 -->|Yes| GLF[✅ GitLab Flow]
    Q5 -->|No| GF
    
    style GHF fill:#c8e6c9,stroke:#2e7d32
    style GF fill:#bbdefb,stroke:#1565c0
    style TBD fill:#fff9c4,stroke:#f9a825
    style GLF fill:#ffccbc,stroke:#d84315
    style FORK fill:#e1bee7,stroke:#7b1fa2
    style START fill:#f5f5f5,stroke:#424242
```

---

## Quick Comparison

| Workflow | Complexity | Best For | Release Style |
|----------|------------|----------|---------------|
| **GitHub Flow** | Low | Web apps, SaaS | Continuous |
| **Git Flow** | High | Versioned software | Scheduled |
| **Trunk-Based** | Low | High-velocity teams | Continuous |
| **GitLab Flow** | Medium | Multi-environment | Staged |
| **Forking** | Medium | Open source | Contributor-driven |

---

## Essential Git Commands by Workflow

### GitHub Flow
```bash
git checkout -b feature/my-feature
# ... make changes ...
git add . && git commit -m "Add feature"
git push -u origin feature/my-feature
# Open PR on GitHub, merge, then:
git checkout main && git pull
git branch -d feature/my-feature
```

### Git Flow
```bash
# Start a feature
git checkout develop
git checkout -b feature/my-feature

# Finish a feature
git checkout develop
git merge feature/my-feature

# Create a release
git checkout -b release/1.0 develop
# ... bump version, fix bugs ...
git checkout main && git merge release/1.0
git tag -a v1.0.0 -m "Release 1.0.0"
git checkout develop && git merge release/1.0
```

### Forking Workflow
```bash
# Setup
git clone https://github.com/YOUR-USERNAME/repo.git
git remote add upstream https://github.com/ORIGINAL/repo.git

# Stay updated
git fetch upstream
git checkout main
git merge upstream/main

# Contribute
git checkout -b feature/contribution
# ... make changes ...
git push origin feature/contribution
# Open PR to upstream
```

---

*Generated with Mermaid diagrams. Render in GitHub, GitLab, VS Code, or any Mermaid-compatible viewer.*
