# LearningOpenGL

Progetto personale di studio su OpenGL (C++) con l’obiettivo di costruire un piccolo engine grafico per realizzare giochi semplici.

> Questo repository non è solo un insieme di esercizi, ma il percorso verso un mini-engine leggero e comprensibile, sufficiente per fare piccoli giochi 2D/3D semplici.

Seguo un percorso ispirato a [LearnOpenGL](https://learnopengl.com/).

## Stato attuale (aggiornato al 3 nov 2026)

- [x] Setup finestra (GLFW + GLAD)
- [x] Primo triangolo
- [x] Più triangoli + wireframe / fill mode
- [x] Classe `Mesh`
- [x] Shader caricati da file (`.vs` / `.fs`)
- [x] Uniforms
- [x] Movimento base del triangolo
- [ ] Texture
- [ ] Trasformazioni (matrici)
- [ ] Camera
- [ ] Lighting

## Roadmap (verso un mini-engine per giochi semplici)

### Fase 1 – Fondamenta (in corso)
- [x] Finestra + input base
- [x] Rendering di mesh semplici
- [x] Sistema shader
- [ ] Texture (2D)
- [ ] Trasformazioni (model / view / projection)
- [ ] Camera base (FPS o free look)

### Fase 2 – Rendering più solido
- [ ] Lighting base (Phong o Blinn-Phong)
- [ ] Materiali semplici
- [ ] Depth testing e face culling
- [ ] Batching o gestione multi-mesh efficiente

### Fase 3 – Struttura engine
- [ ] Scene / GameObject base
- [ ] Component system minimale (Transform, MeshRenderer, ecc.)
- [ ] Gestione risorse (shader, texture, mesh)
- [ ] Input manager più completo
- [ ] Delta time e game loop più robusto

### Fase 4 – Per giochi semplici
- [ ] Collider base (AABB o sfera)
- [ ] Sistema di entità semplice o ECS leggero
- [ ] Audio base (opzionale, es. OpenAL o miniaudio)
- [ ] UI minima (testo o sprite)
- [ ] Serializzazione scena o livello semplice (JSON/XML)

### Fase 5 – Polish
- [ ] Framebuffer e post-processing base
- [ ] Skybox / cubemap
- [ ] Debug drawing (linee, gizmo)
- [ ] Build cross-platform più pulito (CMake)

## Dipendenze

- C++17
- OpenGL 3.3+
- GLFW3
- GLAD (già incluso)
- `pkg-config` (per il Makefile)

### Installazione dipendenze

**Ubuntu / Debian**
```bash
sudo apt install build-essential libglfw3-dev pkg-config
```

**Fedora**
```bash
sudo apt install build-essential libglfw3-dev pkg-config
```

## Struttura

src/
├── main.cpp
└── Core/
    ├── Application.cpp/h   # Loop principale e finestra
    ├── Mesh.cpp/h          # Gestione geometria
    └── Shader.cpp/h        # Caricamento e compilazione shader