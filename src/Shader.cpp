#include "Shader.hpp"

Shader::Shader(std::string vPath, std::string fPath)
{
    vertSrc = get_file_content(vPath.c_str());
    fragSrc = get_file_content(fPath.c_str());

    Gen();
}

std::string Shader::get_file_content(const char* path)
{
    std::ifstream in(path);
    if(!in)
    {
        std::cerr << "Can't open the shader file!" << std::endl;
        std::exit(-1);
    }
    std::string line, content;
    while(getline(in, line))
    {
        content += line + "\n";
        line = "";
    }

    in.close();

    return content;
}

void Shader::Gen()
{
    const char* vSrc = vertSrc.c_str();
    const char* fSrc = fragSrc.c_str();
    // std::cout << vSrc << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    // std::cout << fSrc << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    int success;
    GLchar log[512];

    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vSrc, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, log);
        std::cout << "ERROR in VERTEX SHADER :- " << log << std::endl;
        std::exit(-1);
    }

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fSrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, log);
        std::cout << "ERROR in FRAGMENT SHADER :- " << log << std::endl;
        std::exit(-1);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void Shader::Bind()
{
    glUseProgram(ID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::PutMat4(glm::mat4 mat, const char *name)
{
    this->Bind();
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::PutTex(int slot, const char *name)
{
    this->Bind();
    glUniform1i(glGetUniformLocation(ID, name), slot);
}

void Shader::PutInt(int val, const char *name)
{
    this->Bind();
    glUniform1i(glGetUniformLocation(ID, name), val);
}

void Shader::PutFloat(float val, const char *name)
{
    this->Bind();
    glUniform1f(glGetUniformLocation(ID, name), val);
}

void Shader::PutVec3(glm::vec3 vec, const char *name)
{
    this->Bind();
    glUniform3f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z);
}

void Shader::Cleanup()
{
    glDeleteProgram(ID);
}