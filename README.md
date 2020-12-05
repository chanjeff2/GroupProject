# GroupProject
COMP2012H group project - UST Students vs Assignments

# Project details
Project name: UST Students vs Assignments

Project type: Tower Defence game

# Project structure
```
.
├── build/                  # Compiled files (where our .a .o .exe located)
├── docs/                   # Documentations (Technical stuff are on Hackmd)
├── src/                    # Source files
│   ├── main/               # UI-related implementations
│   ├── enemy/              # enemy interface and implementations
│   ├── tower/              # tower interface and implementations
│   ├── map/                # game map and cell
│   └── utility/            # utilities and game values
├── res/                    # Resource file (graphics, demo map/wave data file)
├── group_project.pro       # The .pro file
├── LICENSE
└── README.md
```

# Docs
### Tower
https://hackmd.io/@G3xU2N67SF2fVm9Hqtva7g/H1efIRP_v
### Enemy
https://hackmd.io/@G3xU2N67SF2fVm9Hqtva7g/BJLXVCDdD
### Utilities
https://hackmd.io/@G3xU2N67SF2fVm9Hqtva7g/H1RxZBY_w
### Game Flow, UI, Game Map
https://hackmd.io/@G3xU2N67SF2fVm9Hqtva7g/r1GMGfu_D

# Possible Future Updates
* implement map editor and enemy wave editor
* multiple spawn points
* generate enemy by enemy (on die or periodically)
* implement MVC to increase expandability of tower and enemy (tower purchase button, Bestiary)
* re-design UI
* save & load feature
* make enemy animation sync with movement, or re-design movement logic
* ...

# Start working
1. **clone** this repo to your local machine (i.e. your PC)
2.  create a new **branch** with **semantic** name (never use branch1, branchA, etc) in your local project
3. work on your new local branch, make **commits** with **semantic** names
4. **push** your new **branch** to this repo
5. create a new **pull request** to dev branch
6. done

PS: whenever there is new update in this remote repo, you can do **pull** to your local copy in order to sync your project

