//Shader do pozycjonowania obiektów, obsługujący tekstury poprzez fragmentshader
//Partner: fragmentshader
uniform mat4 mvpMatrix;

in vec4 vertex;
in vec2 textureCoordinate;

varying vec2 varyingTextureCoordinate;

void main(void)
{
    varyingTextureCoordinate = textureCoordinate;
    gl_Position = mvpMatrix * vertex;
}
