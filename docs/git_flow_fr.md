# Workflows de développement Git & GitHub

Un guide visuel des stratégies de branchement Git et workflows de développement les plus populaires.

---

## 1. Git Flow

Le modèle de branchement original introduit par Vincent Driessen en 2010. Il définit une structure de branches stricte conçue autour des releases du projet, idéal pour les logiciels avec des cycles de release planifiés.

**Branches principales :**
- `main` — Code prêt pour la production, tagué avec les numéros de version
- `develop` — Branche d'intégration pour les fonctionnalités
- `feature/*` — Nouvelles fonctionnalités, créées depuis develop
- `release/*` — Préparation d'une nouvelle release
- `hotfix/*` — Correctifs urgents pour la production

```mermaid
---
title: Git Flow - Modèle de branchement classique
---
gitGraph
    commit id: "Initial"
    branch develop
    checkout develop
    commit id: "Config dev"
    
    branch feature/login
    checkout feature/login
    commit id: "Ajout formulaire"
    commit id: "Ajout validation"
    checkout develop
    merge feature/login id: "Merge login" tag: "feature terminée"
    
    branch feature/dashboard
    checkout feature/dashboard
    commit id: "Création tableau de bord"
    commit id: "Ajout widgets"
    checkout develop
    merge feature/dashboard id: "Merge dashboard"
    
    branch release/1.0
    checkout release/1.0
    commit id: "Bump version"
    commit id: "Correction bug"
    checkout main
    merge release/1.0 id: "v1.0.0" tag: "v1.0.0"
    checkout develop
    merge release/1.0 id: "Back-merge"
    
    checkout main
    branch hotfix/securite
    commit id: "Patch sécurité"
    checkout main
    merge hotfix/securite id: "v1.0.1" tag: "v1.0.1"
    checkout develop
    merge hotfix/securite id: "Hotfix vers dev"
```

**Idéal pour :** Projets avec releases planifiées, plusieurs versions en production, ou équipes nécessitant une gestion stricte des releases.

---

## 2. GitHub Flow

Un workflow léger basé sur les branches qui convient aux équipes et projets déployant régulièrement. Il n'y a qu'une seule règle : tout ce qui est dans `main` est déployable.

**Principes :**
- `main` est toujours déployable
- Créer des branches descriptives pour chaque travail
- Ouvrir une Pull Request pour discussion et revue
- Déployer immédiatement après le merge

```mermaid
---
title: GitHub Flow - Workflow simple basé sur les PR
---
gitGraph
    commit id: "Production"
    commit id: "Stable"
    
    branch feature/nouvelle-api
    checkout feature/nouvelle-api
    commit id: "Création endpoint"
    commit id: "Ajout tests"
    commit id: "Corrections revue"
    checkout main
    merge feature/nouvelle-api id: "PR #42 mergée" tag: "déploiement"
    
    branch feature/maj-interface
    checkout feature/maj-interface
    commit id: "Mise à jour styles"
    commit id: "Design responsive"
    checkout main
    merge feature/maj-interface id: "PR #43 mergée" tag: "déploiement"
    
    branch bugfix/erreur-formulaire
    checkout bugfix/erreur-formulaire
    commit id: "Correction validation"
    checkout main
    merge bugfix/erreur-formulaire id: "PR #44 mergée" tag: "déploiement"
    
    commit id: "Prêt pour prod"
```

**Idéal pour :** Applications web, produits SaaS, et équipes pratiquant le déploiement continu.

---

## 3. Trunk-Based Development (Développement basé sur le tronc)

Un modèle de contrôle de source où les développeurs collaborent sur le code dans une seule branche appelée "trunk" (ou `main`), en évitant de créer des branches de fonctionnalités à longue durée de vie.

**Pratiques clés :**
- Branches de fonctionnalités à courte durée de vie (idéalement < 1 jour)
- Commits directs sur le trunk pour les petits changements
- Feature flags pour les fonctionnalités incomplètes
- Branches de release uniquement pour le cherry-picking de correctifs

```mermaid
---
title: Trunk-Based Development
---
gitGraph
    commit id: "Init"
    commit id: "Feature A"
    
    branch courte-duree/feature-b
    checkout courte-duree/feature-b
    commit id: "Changement rapide"
    checkout main
    merge courte-duree/feature-b id: "Merge (< 1 jour)"
    
    commit id: "Commit direct"
    commit id: "Petit correctif"
    
    branch courte-duree/feature-c
    checkout courte-duree/feature-c
    commit id: "Itération rapide"
    checkout main
    merge courte-duree/feature-c id: "Merge rapide"
    
    commit id: "Continu" tag: "v1.0"
    commit id: "Intégration"
    
    branch release/1.x
    checkout release/1.x
    commit id: "Cherry-pick correctif"
    checkout main
    
    commit id: "Nouvelle feature"
    commit id: "Trunk toujours vert" tag: "v1.1"
```

**Idéal pour :** Équipes performantes, environnements CI/CD, et organisations privilégiant l'itération rapide.

---

## 4. GitLab Flow (Branches d'environnement)

Combine le développement orienté fonctionnalités avec des branches d'environnement pour le déploiement. Il fournit un chemin clair du développement jusqu'à la production en passant par le staging.

**Branches d'environnement :**
- `main` — Dernier code de développement
- `pre-production` — Environnement de staging
- `production` — Environnement de production

```mermaid
---
title: GitLab Flow (Branches d'environnement)
---
gitGraph
    commit id: "Init"
    
    branch feature/auth
    checkout feature/auth
    commit id: "Ajout OAuth"
    commit id: "Ajout tests"
    checkout main
    merge feature/auth id: "MR mergée"
    
    commit id: "Plus de features"
    
    branch pre-production
    checkout pre-production
    commit id: "Déploiement staging" tag: "staging"
    
    checkout main
    branch feature/cache
    commit id: "Ajout Redis"
    checkout main
    merge feature/cache id: "MR #2"
    
    checkout pre-production
    merge main id: "MAJ staging"
    
    branch production
    checkout production
    commit id: "Déploiement prod" tag: "v1.0"
    
    checkout main
    commit id: "Nouvelle feature"
    checkout pre-production
    merge main id: "Vers staging"
    checkout production
    merge pre-production id: "Release" tag: "v1.1"
```

**Idéal pour :** Équipes nécessitant plusieurs environnements de déploiement avec promotion contrôlée entre les étapes.

---

## 5. Workflow de Fork

Le workflow standard pour les projets open source. Les contributeurs forkent le dépôt, font leurs modifications dans leur propre copie, et soumettent des pull requests au dépôt upstream.

```mermaid
---
title: Workflow de Fork (Contributions Open Source)
---
flowchart TB
    subgraph upstream["🏢 Dépôt Upstream (Projet original)"]
        um[branche main]
    end
    
    subgraph fork["🍴 Votre Fork (GitHub)"]
        fm[branche main]
        fb[branche feature]
    end
    
    subgraph local["💻 Machine locale"]
        lm[branche main]
        lb[branche feature]
    end
    
    um -->|"1. Fork sur GitHub"| fm
    fm -->|"2. git clone"| lm
    lm -->|"3. git checkout -b feature"| lb
    lb -->|"4. Modifications & commits"| lb
    lb -->|"5. git push origin feature"| fb
    fb -->|"6. Ouvrir Pull Request"| um
    um -->|"7. Mainteneur revoit & merge"| um
    um -->|"8. git fetch upstream"| lm
    lm -->|"9. git push origin main"| fm
    
    style upstream fill:#e1f5fe,stroke:#01579b
    style fork fill:#fff3e0,stroke:#e65100
    style local fill:#e8f5e9,stroke:#2e7d32
```

**Idéal pour :** Projets open source, contributions externes, et maintien d'un dépôt upstream propre.

---

## 6. Cycle de vie d'une Pull Request

Quelle que soit la stratégie de branchement, les pull requests suivent un cycle de vie similaire de la création au déploiement.

```mermaid
---
title: Cycle de vie d'une Pull Request
---
flowchart LR
    subgraph Developpement["Développement"]
        A[📝 Créer branche] --> B[💻 Écrire code]
        B --> C[✅ Tests en local]
        C --> D[📤 Push vers remote]
    end
    
    subgraph Revue["Revue de code"]
        D --> E[🔀 Ouvrir PR]
        E --> F{Vérifications CI/CD}
        F -->|Réussite| G[👀 Demander revue]
        F -->|Échec| B
        G --> H{Retour reviewer}
        H -->|Modifications demandées| B
        H -->|Approuvé| I[✅ Approuvé]
    end
    
    subgraph Fusion["Merge"]
        I --> J{Stratégie de merge}
        J -->|Squash| K[Squash & Merge]
        J -->|Rebase| L[Rebase & Merge]
        J -->|Merge Commit| M[Créer Merge Commit]
        K --> N[🗑️ Supprimer branche]
        L --> N
        M --> N
        N --> O[🚀 Déployer]
    end
    
    style A fill:#bbdefb
    style E fill:#fff9c4
    style I fill:#c8e6c9
    style O fill:#ffccbc
```

---

## 7. Choisir le bon workflow

Utilisez cet arbre de décision pour sélectionner le workflow qui correspond le mieux à votre équipe et votre projet.

```mermaid
---
title: Guide de sélection de workflow Git
---
flowchart TD
    START([🤔 Choisir un workflow Git]) --> Q1{Taille de l'équipe ?}
    
    Q1 -->|Solo / Petite| Q2{Fréquence des releases ?}
    Q1 -->|Grande / Entreprise| Q3{Open Source ?}
    
    Q2 -->|Continue| GHF[✅ GitHub Flow]
    Q2 -->|Planifiée| Q4{Releases complexes ?}
    
    Q3 -->|Oui| FORK[✅ Workflow de Fork]
    Q3 -->|Non| Q5{Plusieurs environnements ?}
    
    Q4 -->|Oui| GF[✅ Git Flow]
    Q4 -->|Non| TBD[✅ Trunk-Based]
    
    Q5 -->|Oui| GLF[✅ GitLab Flow]
    Q5 -->|Non| GF
    
    style GHF fill:#c8e6c9,stroke:#2e7d32
    style GF fill:#bbdefb,stroke:#1565c0
    style TBD fill:#fff9c4,stroke:#f9a825
    style GLF fill:#ffccbc,stroke:#d84315
    style FORK fill:#e1bee7,stroke:#7b1fa2
    style START fill:#f5f5f5,stroke:#424242
```

---

## Comparaison rapide

| Workflow | Complexité | Idéal pour | Style de release |
|----------|------------|------------|------------------|
| **GitHub Flow** | Faible | Apps web, SaaS | Continue |
| **Git Flow** | Élevée | Logiciels versionnés | Planifiée |
| **Trunk-Based** | Faible | Équipes haute vélocité | Continue |
| **GitLab Flow** | Moyenne | Multi-environnement | Par étapes |
| **Fork** | Moyenne | Open source | Guidée par contributeurs |

---

## Commandes Git essentielles par workflow

### GitHub Flow
```bash
git checkout -b feature/ma-feature
# ... faire les modifications ...
git add . && git commit -m "Ajout fonctionnalité"
git push -u origin feature/ma-feature
# Ouvrir PR sur GitHub, merger, puis :
git checkout main && git pull
git branch -d feature/ma-feature
```

### Git Flow
```bash
# Démarrer une feature
git checkout develop
git checkout -b feature/ma-feature

# Terminer une feature
git checkout develop
git merge feature/ma-feature

# Créer une release
git checkout -b release/1.0 develop
# ... bump version, corriger bugs ...
git checkout main && git merge release/1.0
git tag -a v1.0.0 -m "Release 1.0.0"
git checkout develop && git merge release/1.0
```

### Workflow de Fork
```bash
# Configuration initiale
git clone https://github.com/VOTRE-USERNAME/repo.git
git remote add upstream https://github.com/ORIGINAL/repo.git

# Rester à jour
git fetch upstream
git checkout main
git merge upstream/main

# Contribuer
git checkout -b feature/contribution
# ... faire les modifications ...
git push origin feature/contribution
# Ouvrir PR vers upstream
```

---

*Généré avec des diagrammes Mermaid. Visualisable sur GitHub, GitLab, VS Code, ou tout viewer compatible Mermaid.*
