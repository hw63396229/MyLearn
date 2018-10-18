#pragma once
#include "Depend.h"

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
	//Model data
	std::vector<Texture>   m_vTextureLoad;
	std::vector<Mesh>      m_vMeshs;
	std::string            pathDir;
	bool                   gammaCorrection;

public:
	Model(const std::string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		LoadModel(path);
	}
	~Model() {}

	void Draw(Shader shader)
	{
		for (unsigned i = 0; i < m_vMeshs.size(); i++)
		{
			m_vMeshs[i].Draw(shader);
		}
	}

private:
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void LoadModel(const std::string const &path)
	{
		// read file via ASSIMP
		Assimp::Importer  m_importer;
		const aiScene* scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) //if is not zero
		{
			std::cout << "ERROR::ASSIMP:: " << m_importer.GetErrorString() << std::endl;
			return;
		}

		// retrieve the directory path of the filepath
		pathDir = path.substr(0, path.find_last_of('/'));

		// process ASSIMP's root node recursively
		ProcessNode(scene->mRootNode, scene);
	}

	void ProcessNode(aiNode* node, const aiScene* scene)
	{
		// process each mesh located at the current node
		for (unsigned i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_vMeshs.push_back(ProcessMesh(mesh, scene));
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex>   m_vVertices;
		std::vector<unsigned> m_vSurf;
		std::vector<Texture>  m_vTextures;

		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vert;
			vert.Position.x = mesh->mVertices[i].x;
			vert.Position.y = mesh->mVertices[i].y;
			vert.Position.z = mesh->mVertices[i].z;

			vert.Normal.x = mesh->mNormals[i].x;
			vert.Normal.y = mesh->mNormals[i].y;
			vert.Normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0])  //does the mesh contain texture coordinates?
			{
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vert.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vert.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
				vert.TexCoords = glm::vec2(0.f, 0.f);

			vert.Tangent.x = mesh->mTangents[i].x;
			vert.Tangent.y = mesh->mTangents[i].y;
			vert.Tangent.z = mesh->mTangents[i].z;

			vert.Bitangent.x = mesh->mBitangents[i].x;
			vert.Bitangent.y = mesh->mBitangents[i].y;
			vert.Bitangent.z = mesh->mBitangents[i].z;

			m_vVertices.push_back(vert);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				m_vSurf.push_back(face.mIndices[j]);
		}

		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN
		//1. diffuse maps
		std::vector<Texture>  m_vDiffuseMaps;
		loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", m_vDiffuseMaps);
		m_vTextures.insert(m_vTextures.end(), m_vDiffuseMaps.begin(), m_vDiffuseMaps.end());
		//2. specular maps
		std::vector<Texture>  m_vSpecularMaps;
		loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", m_vSpecularMaps);
		m_vTextures.insert(m_vTextures.end(), m_vSpecularMaps.begin(), m_vSpecularMaps.end());
		//3. normal maps
		std::vector<Texture>  m_vNormalMaps;
		loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", m_vNormalMaps);
		m_vTextures.insert(m_vTextures.end(), m_vNormalMaps.begin(), m_vNormalMaps.end());
		//4. height maps
		std::vector<Texture>  m_vHeightMaps;
		loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", m_vHeightMaps);
		m_vTextures.insert(m_vTextures.end(), m_vHeightMaps.begin(), m_vHeightMaps.end());

		return Mesh(m_vVertices, m_vSurf, m_vTextures);
	}

	void loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, std::vector<Texture> & textures)
	{
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (unsigned int j = 0; j < m_vTextureLoad.size(); j++)
			{
				if (std::strcmp(m_vTextureLoad[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(m_vTextureLoad[j]);
					skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->pathDir);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				m_vTextureLoad.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
			}
		}
	}
};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}