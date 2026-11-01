#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &inds)
    : vertices(verts), indicies(inds)
{
    SetUp();
}

Mesh::~Mesh()
{
    DeleteMesh();
}

void Mesh::SetUp()
{
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Collega il VAO per primo e poi il VBO, in questo modo il VAO salverà le configurazioni del VBO
    glBindVertexArray(VAO);

    //Prende il buffer di vertici e lo passa alla GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // quasi usa GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);// quasi usa GL_ELEMENT_ARRAY_BUFFER

    //Configura il modo in cui OpenGL deve interpretare i dati del buffer
    // 0 -> è l'indice del attributo che deve equivalere alla location del vertex shader
    // 3 -> è il numero di componenti per vertice (x, y, z)
    // GL_FLOAT -> è il tipo di dato dei componenti
    // GL_FALSE -> indica se i dati devono essere normalizzati o meno
    // 3 * sizeof(float) -> è la distanza tra i vertici consecutivi nel buffer (stride)
    // (void*)0 -> è l'offset del primo componente del primo vertice nel buffer 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0 ); // (void*)0 è un puntatore vuoto nullo
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)) );
    glEnableVertexAttribArray(1);


    //unbind il VBO e il VAO per evitare modifiche accidentali
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::DeleteMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


