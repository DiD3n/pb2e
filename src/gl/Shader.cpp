#include "Shader.hpp"

#include <fstream>

static bool compileShader(int type, unsigned int& shader,const std::string& source) {
    if (source == "") {
        logError("gl::compileShader() - source is empty!");
        return false;
    }
    
    GLCall(shader = glCreateShader(type));

    const char* tmp = source.c_str();
    GLCall(glShaderSource(shader,1, &tmp, NULL));
 
    GLCall(glCompileShader(shader));
    
    int compileStatus;
    GLCall(glGetShaderiv(shader,GL_COMPILE_STATUS,&compileStatus));

    if (compileStatus != GL_TRUE) {
        
        int length = 0;
        GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

        char msg[length];
        GLCall(glGetShaderInfoLog(shader, length, &length, msg));

        logError("gl::compileShader(",type,",",source,") - compile error: \n", (const char*)msg,'\n');
        GLCall(glDeleteShader(shader));
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
        GLCall(programID = glCreateProgram()); 
        if (this->compile(programID)) {
            legit = true;
        }  
        use();
    }


    bool Shader::compile(const unsigned int& program) const {
        bool good = false;
        std::string fragmentSource, vertexSource, tmp;

        std::ifstream fragFile(fragmentSourcePath, std::ifstream::binary);
        if (fragFile.good()) {
            while (std::getline(fragFile,tmp)) {
                fragmentSource += tmp + "\n";
            }
        }
        else
            logError("gl::Shader::compile() - Problem with source file:\"",fragmentSourcePath,"\"");

        std::ifstream verFile(vertexSourcePath, std::ifstream::binary);
        if (verFile.good()) {
            while (std::getline(verFile,tmp)) {
                vertexSource += tmp + "\n";
            }
        }  
        else
            logError("gl::Shader::compile() - Problem with source file:\"",vertexSourcePath,"\"");

        unsigned int fragmentShader, vertexShader;
        if (compileShader(GL_FRAGMENT_SHADER, fragmentShader, fragmentSource) && compileShader(GL_VERTEX_SHADER, vertexShader, vertexSource)) {

            GLCall(glAttachShader(program,fragmentShader));
            GLCall(glAttachShader(program,vertexShader));
            GLCall(glLinkProgram(program));

            good = true;   
        }

        GLCall(glDeleteShader(fragmentShader));
        GLCall(glDeleteShader(vertexShader));

        return good;
    }

    void Shader::recompile() {
        GLCall(unsigned int program = glCreateProgram());
        if (compile(program)) {

            //replacing program
            unsigned int oldProgram = programID;
            programID = program;
            
            use();

            bool legit = true;
            for (UniformData& i : uniformList) {
                GLCall(int id = glGetUniformLocation(this->programID,i.name.c_str()));
                if (id > -1)
                    i.id = id;
                else {
                    legit = false;
                    logError("gl::Shader::recompile() - can not find \"",i.name,"\" Uniform in the shader... did you change something?"); 
                }
                   
            }

            if (legit) {

                //Restoring the last valid uniforms
                for (const UniformData& i : uniformList)
                    updateShaderUniform(i);

                GLCall(glDeleteProgram(programID));

                logInfo("gl::Shader::recompile() - done!");

                return;

            }
            programID = oldProgram;
                
        }
        
        
        GLCall(glDeleteProgram(program)); //in case of a failed compilation
        logError("gl::Shader::recompile() - failed!");
            
    }

    void Shader::updateShaderUniform(const UniformData& data) const {
        use();
        switch (data.uniform->type) {
            /*   vec1   */

            case vec1f:   
            GLCall(glUniform1f(data.id,*(float*)data.uniform->data));            break;
            case vec1ui:  
            GLCall(glUniform1ui(data.id,*(unsigned int*)data.uniform->data));    break;
            case vec1i:   
            GLCall(glUniform1i(data.id,*(int*)data.uniform->data));              break;
			case vec1d:   
            GLCall(glUniform1d(data.id,*(double*)data.uniform->data));              break;
            /*   vec2   */

            case vec2f:   
            GLCall(glUniform2f(data.id,((float*)data.uniform->data)[0],((float*)data.uniform->data)[1]));                   break;
            case vec2ui:  
            GLCall(glUniform2ui(data.id,((unsigned int*)data.uniform->data)[0],((unsigned int*)data.uniform->data)[1]));    break;
            case vec2i:   
            GLCall(glUniform2i(data.id,((int*)data.uniform->data)[0],((int*)data.uniform->data)[1]));                       break;
			case vec2d:   
            GLCall(glUniform2d(data.id,((double*)data.uniform->data)[0],((double*)data.uniform->data)[1]));                 break;
            /*   vec3   */

            case vec3f:
            GLCall(glUniform3f(data.id,((float*)data.uniform->data)[0],((float*)data.uniform->data)[1],((float*)data.uniform->data)[2]));                          break;
            case vec3ui:
            GLCall(glUniform3ui(data.id,((unsigned int*)data.uniform->data)[0],((unsigned int*)data.uniform->data)[1],((unsigned int*)data.uniform->data)[2]));    break;
            case vec3i:
            GLCall(glUniform3i(data.id,((int*)data.uniform->data)[0],((int*)data.uniform->data)[1],((int*)data.uniform->data)[2]));                                break;
			case vec3d:
            GLCall(glUniform3d(data.id,((double*)data.uniform->data)[0],((double*)data.uniform->data)[1],((double*)data.uniform->data)[2]));                       break;

            case mat2:
            GLCall(glUniformMatrix2fv(data.id,1,GL_FALSE,(float*)&((glm::mat2*)data.uniform->data)[0][0]));   break;
            case mat3:
            GLCall(glUniformMatrix3fv(data.id,1,GL_FALSE,(float*)&((glm::mat3*)data.uniform->data)[0][0]));   break;
            case mat4:
            GLCall(glUniformMatrix4fv(data.id,1,GL_FALSE,(float*)&((glm::mat4*)data.uniform->data)[0][0]));   break;
            default:
            logError("gl::Shader::updateShaderUniform(uniformType:",data.uniform->type,") - Unknown type... skipping!");
        }
    }

    void Shader::use(bool bind) const {
        static unsigned int lastID;
        if (legit) {
            if (bind) {
                if (lastID != programID) {
                    lastID = programID;
                    GLCall(glUseProgram(programID));
                }
                return;
            }
        }
            
        if (lastID != 0) {
            lastID = 0;
            GLCall(glUseProgram(0));
        }
    }

    
    /* update */

    void Shader::update() const {
        for (const UniformData& i : uniformList) {
            if (!i.uniform->pointable)
                continue;
            else
                updateShaderUniform(i);
        }
    }

    void Shader::update(const std::string& name) const{
        for (const UniformData& i : uniformList) {
            if (i.name != name)
                continue;
            if (i.uniform->pointable) {
                updateShaderUniform(i);
            } else {
                logError("gl::Shader::update(",name,") - Uniform isn't pointable. Use update(name,data) instead of update(name)... skipping!");
            }
            return; 
        }
    }

    void Shader::update(const std::string& name, const Uniform& uniform) {
        for (UniformData& i : uniformList) {
            if (i.name != name)
                continue;
            i.replaceUniform(uniform);
            return;
        }
        logError("gl::Shader::pushUniform() - can not find \"",name,"\" Uniform in the shader... skipping!");
    }

    /* misc */

    bool Shader::pushUniform(const std::string& name, const Uniform& uniform) {  

        GLCall(int id = glGetUniformLocation(this->programID,name.c_str()));

        if (id != -1) {
            //testing whether there is any duplication
            for (UniformData& i : uniformList) {
                if (i.name != name)
                    continue;
                i.replaceUniform(uniform);
                return true;
            }

            //adding uniform to the list
            this->uniformList.emplace_back(name,id,uniform);
        }
        else {
            logError("gl::Shader::pushUniform() - can not find \"",name,"\" Uniform in the shader... skipping!");
            return false;
        }
        return true;
    }

};
