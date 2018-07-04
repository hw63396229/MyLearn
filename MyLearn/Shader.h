#pragma once

#include <glad\glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//class Shader
//{
//public:
//	unsigned ID;
//
//	//construct generates the shader on	the fly
//	Shader(const char * vertexPath, const char * fragmentPath)
//	{
//		//1. retrieve the vertex/fragment source code from filePath
//		std::string vertexCode;
//		std::string fragmentCode;
//		std::ifstream vShaderFile;
//		std::ifstream fShaderFile;
//
//		//ensure ifstream objects can throw exceptions
//		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//		try
//		{
//			vShaderFile.open(vertexPath);
//			fShaderFile.open(fragmentPath);
//			std::stringstream   vShaderStream, fShaderStream;
//
//			//read file's buffer contents into streams
//			vShaderStream << vShaderFile.rdbuf();
//			fShaderStream << fShaderFile.rdbuf();
//
//			//close file handlers
//			vShaderFile.close();
//			fShaderFile.close();
//
//			//convert stream to string
//			vertexCode = vShaderStream.str();
//			fragmentCode = fShaderStream.str();
//		}
//		catch (const std::exception& e)
//		{
//			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESS_READ" << std::endl;
//		}
//
//		const char * vShaderCode = vertexCode.c_str();
//		const char * fShaderCode = fragmentCode.c_str();
//
//		//compile shaders
//		unsigned vertex, fragment;
//		int success;
//		char infoLog[512];
//		//vertex shader
//		vertex = glCreateShader(GL_VERTEX_SHADER);
//		glShaderSource(vertex, 1, &vShaderCode, NULL);
//		glCompileShader(vertex);
//		ckeckCompileErrors(vertex, "VERTEX");
//		//fragment shader
//		fragment = glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(fragment, 1, &fShaderCode, NULL);
//		glCompileShader(fragment);
//		ckeckCompileErrors(fragment, "FRAGMENT");
//		//shader program
//		ID = glCreateProgram();
//		glAttachShader(ID, vertex);
//		glAttachShader(ID, fragment);
//		glLinkProgram(ID);
//		ckeckCompileErrors(ID, "PROGRAM");
//		//delete the shaders as they're linked into our program now and no longer necessary
//		glDeleteShader(vertex);
//		glDeleteShader(fragment);
//	}
//	//active the shader
//	void use()
//	{
//		glUseProgram(ID);
//	}
//
//	//utility uniform functions
//	void setBool(const std::string & name, bool value) const
//	{
//		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//	}
//	void setInt(const std::string & name, int value)  const
//	{
//		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//	}
//	void setFloat(const std::string & name, float value) const
//	{
//		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//	}
//	~Shader() {}
//
//private:
//	//utility function for check compilation/linked errors
//	void ckeckCompileErrors(unsigned shader, std::string type)
//	{
//		int success;
//		char infoLog[1024];
//		if (type != "PROGRAM")
//		{
//			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//			if (!success)
//			{
//				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n---------------------------" << std::endl;
//			}
//		}
//		else
//		{
//			glGetProgramiv(shader, GL_LINK_STATUS, &success);
//			if (!success)
//			{
//				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------- " << std::endl;
//			}
//		}
//	}
//};
