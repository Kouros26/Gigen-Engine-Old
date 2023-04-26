#include <vector>
#include <string>

class Mesh;
class Material;
struct aiNode;
struct aiScene;
struct aiMesh;

constexpr unsigned int VERTEX_SIZE = 8;
constexpr unsigned int FACE_SIZE = 3;

class ModelLoader
{
public:

    void LoadModel(std::vector<Mesh*>& meshes, std::vector<Material*>& materials, std::string const& pFilePath);
private:
    void ProcessNode(const aiNode* pNode, const aiScene* pScene, std::vector<Mesh*>& meshes, std::vector<Material*>& materials);
    void ProcessMesh(const aiMesh* pMesh, const aiScene* pScene, std::vector<Mesh*>& meshes);
    void ProcessMaterial(const aiScene* pScene, std::vector<Material*>& materials);
};
