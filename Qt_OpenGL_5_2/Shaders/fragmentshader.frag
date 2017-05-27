#version 330

//Obsługuje teksturowanie
//Bez światła
//Partner: vertexshader

uniform sampler2D texture;

varying vec2 varyingTextureCoordinate;

out vec4 fragColor;

void main(void)
{
    gl_FragColor = texture2D(texture, varyingTextureCoordinate);
}
