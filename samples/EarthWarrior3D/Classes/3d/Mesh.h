
#ifndef __CCMESH_H_
#define __CCMESH_H_

#include <string>
#include <vector>

#include "Vector.h"
#include "ccTypes.h"

struct Face
{
    ivec3 face;
    ivec3 texi;
};

struct FaceVertex
{
    FaceVertex(int vIndex, int uvIndex, int normIndex)
    : _vIndex(vIndex)
    , _uvIndex(uvIndex)
    , _normIndex(normIndex)
    {
    }
    int _vIndex;
    int _uvIndex;
    int _normIndex;
};

struct RenderMesh
{
    struct RenderVertex
    {
        vec3 vertex;
        vec3 normal;
        vec2 uv;
    };
    
    std::vector<RenderVertex> _vertexs;
    std::vector<unsigned short> _indices;
};

struct ObjMeshData
{
    //mesh data
    std::vector<vec3> _vertexLists;
    std::vector<vec2> _uvVertexLists;
    std::vector<vec3> _normalVertexLists;
    std::vector<std::vector<FaceVertex>> _faceLists;
    
public:
    bool checkBound() const;
    bool isTriangeMesh() const;
    void triangular();
    void trianglarAndGenerateNormals();
    void convertToRenderMesh(RenderMesh& renderMesh);
};

class Mesh
{
public:
    Mesh(const std::string& name);
    ~Mesh();
    
    bool loadFromFile(const std::string& name);

    inline GLuint getVertexBuffer() const { return _vertexBuffer; }
    inline GLuint getIndexBuffer() const { return _indexBuffer; }
    inline ssize_t getIndexCount() const { return _indexCount; }

    //void readTexels(std::vector<vec2>& ) const;

protected:
    void generateVertices();
    void generateTriangleIndices();
    void buildBuffer();

    void generateLineIndices(std::vector<unsigned short>& indices) const {}
    int getVertexCount(/*int &texInCount*/) const;
    int getTexelCount() const;
    
    int getLineIndexCount() const { return 0; }
    int getTriangleIndexCount() const;

    void freeBuffers();

protected:
    void countVertexData() const;
    std::string _name;
    //vector<ivec3> m_faces;
    //std::vector<Face> _faces;
    //std::vector<vec2> _texels;
    mutable int _faceCount;
    mutable int _vertexCount;
    mutable int _texelCount;
    static const int MAX_LINE_SIZE = 128;

    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    ssize_t _indexCount;

    std::vector<GLfloat> _vertices;
    std::vector<GLushort> _indices;

private:
    RenderMesh _renderableMesh;
    
};

#endif // __CCMESH_H_