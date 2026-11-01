#include <vector>

//-- Mesh Stuff
struct Vertex
{
    float position[3];
    float color[3];
};

class Mesh
{
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;

        unsigned int VBO{}, VAO{}, EBO{};   
    
    public:

        Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds);
        ~Mesh();
       
        void SetUp(); 

        unsigned int GetVBO() {return VBO;};
        unsigned int GetVAO() {return VAO;};
        unsigned int GetEBO() {return EBO;};

        void DeleteMesh();

};