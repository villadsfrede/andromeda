#include "ShaderClass.h"

//Read Shader files
std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}


Shader::Shader(const char* VertexFile, const char* FragFile) {

    //Get the file, by using "get_file_contents" function
    std::string VertexCode = get_file_contents(VertexFile);
    std::string FragCode = get_file_contents(FragFile);

    //convert to C_str
    const char* vertexSource = VertexCode.c_str();
    const char* FragSource = FragCode.c_str();


    //create VertexShader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, NULL);

    glCompileShader(vertexShader);

    //Create FragmentShader
    GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(FragShader, 1, &FragSource, NULL);

    glCompileShader(FragShader);

    //Create Shader Program
    ID = glCreateProgram();

    //Attach both shaders to ShaderProgram
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, FragShader);

    glLinkProgram(ID);


    //Delete Shaders:
    glDeleteShader(vertexShader);
    glDeleteShader(FragShader);



}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    
    glDeleteProgram(ID);
}
