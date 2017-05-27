#version 330
//Shader do kolorowania figur przy użyciu koloru
//Bez tekstury bez światła
//Partner: coloringvertexshader

in vec4 varyingColor;

out vec4 fragColor;

void main(void)
{
    fragColor = varyingColor;
}
