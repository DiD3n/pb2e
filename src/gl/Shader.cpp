#include "Shader.hpp"

#include <fstream>

static bool compileShader(int type, unsigned int& shader,const std::string& source) {
    if (source == "") {
        logError("gl::compileShader() - source is empty!");
        return false;
    }
    
    shader = glCreateShader(type);

    const char* tmp = source.c_str();
    glShaderSource(shader,1, &tmp, NULL);
 
    glCompileShader(shader);
    
    int compileStatus;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileStatus);

    if (compileStatus != GL_TRUE) {
        
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char msg[length];
        glGetShaderInfoLog(shader, length, &length, msg);

        logError("gl::compileShader(",type,",",source,") - compile error: \n", (const char*)msg,'\n');
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}


namespace gl {

    Shader::Shader(const Shader& other) {
        Shader(other.vertexSourcePath,other.fragmentSourcePath);
    }

    Shader::Shader(const std::string& vertexSourcePath, const std::string& fragmentSourcePath) 
    : vertexSourcePath(vertexSourcePath) , fragmentSourcePath(fragmentSourcePath) {
        programID = glCreateProgram(); 
        if (this->compile(programID)) {
            legit = true;
        }  
        this->bind();
    }


    bool Shader::compile(const unsigned int& program) {
        bool good = false;
        std::string fragmentSource, vertexSource, tmp;

        std::ifstream fragFile(fragmentSourcePath, std::ifstream::binary);
        if (fragFile.good())
            while (std::getline(fragFile,tmp)) {
                fragmentSource += tmp + "\n";
            }
        else
            logError("gl::Shader::compile() - Problem with source file:\"",fragmentSourcePath,"\"");

        std::ifstream verFile(vertexSourcePath, std::ifstream::binary);
        if (verFile.good())
            while (std::getline(verFile,tmp)) {
                vertexSource += tmp + "\n";
            }
        else
            logError("gl::Shader::compile() - Problem with source file:\"",vertexSourcePath,"\"");

        unsigned int fragmentShader, vertexShader;
        if (compileShader(GL_FRAGMENT_SHADER, fragmentShader, fragmentSource) && compileShader(GL_VERTEX_SHADER, vertexShader, vertexSource)) {

            glAttachShader(program,fragmentShader);
            glAttachShader(program,vertexShader);
            glLinkProgram(program);

            good = true;   
        }

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        return good;
    }

    void Shader::recompile() {
        unsigned int program = glCreateProgram();
        if (compile(program)) {
            //replacing program
            glDeleteProgram(programID);
            programID = program;
            this->bind();
        } else
            glDeleteProgram(program); //in case of a failed compilation
    }

    void Shader::updateShaderUniform(const UniformData& data) {
        this->bind();
        switch (data.uniform.type) {
            /*   vec1   */

            case vec1f:   
            glUniform1f(data.id,*(float*)data.uniform.data);            break;
            case vec1ui:  
            glUniform1ui(data.id,*(unsigned int*)data.uniform.data);    break;
            case vec1i:   
            glUniform1i(data.id,*(int*)data.uniform.data);              break;
            /*   vec2   */

            case vec2f:   
            glUniform2f(data.id,((float*)data.uniform.data)[0],((float*)data.uniform.data)[1]);                   break;
            case vec2ui:  
            glUniform2ui(data.id,((unsigned int*)data.uniform.data)[0],((unsigned int*)data.uniform.data)[1]);    break;
            case vec2i:   
            glUniform2i(data.id,((int*)data.uniform.data)[0],((int*)data.uniform.data)[1]);                       break;
            /*   vec3   */

            case vec3f:
            glUniform3f(data.id,((float*)data.uniform.data)[0],((float*)data.uniform.data)[1],((float*)data.uniform.data)[2]);                          break;
            case vec3ui:
            glUniform3ui(data.id,((unsigned int*)data.uniform.data)[0],((unsigned int*)data.uniform.data)[1],((unsigned int*)data.uniform.data)[2]);    break;
            case vec3i:
            glUniform3i(data.id,((int*)data.uniform.data)[0],((int*)data.uniform.data)[1],((int*)data.uniform.data)[2]);                                break;

            //TODO: matrix
        }
    }
    
    /* update */

    void Shader::update() {
        for (UniformData& i : uniformList) {
            if (!i.uniform.pointable)
                continue;
            else
                updateShaderUniform(i);
        }
    }

    void Shader::update(const std::string& name) {
        for (UniformData& i : uniformList) {
            if (i.name != name)
                continue;
            if (i.uniform.pointable) {
                updateShaderUniform(i);
            } else {
                logError("gl::Shader::update(",name,") - Uniform isn't pointable. Use update(name,data) instead of update(name)... skiping");
            }
            return;
        }
    }

    void Shader::update(const std::string& name, Uniform& data) {
        for (UniformData& i : uniformList) {
            if (i.name != name)
                continue;
            i.uniform = data;
            return;
        }
    }

    /* misc */

    bool Shader::pushUniform(const std::string& name, Uniform& uniform) {  

        int id = glGetUniformLocation(this->programID,name.c_str());

        if (id != -1) {
            //testing whether there is any duplication
            for (UniformData& i : uniformList) {
                if (i.name != name)
                    continue;
                i.uniform = uniform;
                return true;
            }

            //adding uniform to the list
            this->uniformList.push_back({name,id,uniform});
        }
        else {
            logError("gl::Shader::pushUniform() - can not find \"",name,"\" Uniform in the shader... skiping");
            return false;
        }
        return true;
    }

};
