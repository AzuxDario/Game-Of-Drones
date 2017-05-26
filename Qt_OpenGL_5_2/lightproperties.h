#ifndef LIGHTPROPERTIES_H
#define LIGHTPROPERTIES_H

#include <QColor>

using GLFloat = float; //Nie wiem w jakim pliku nagłówkowym to jest więc sam stoworzyłem

class LightProperties
{
private:

    QColor ambientColor;
    QColor diffuseColor;
    QColor specularColor;
    GLFloat ambientReflection;
    GLFloat diffuseReflection;
    GLFloat specularReflection;
    GLFloat shininess;

public:

    LightProperties();
    QColor getAmbientColor() noexcept {return ambientColor;}
    QColor getDiffuseColor() noexcept {return diffuseColor;}
    QColor getSpecularColor() noexcept {return specularColor;}
    GLFloat getAmbientReflection() noexcept {return ambientReflection;}
    GLFloat getDiffuseReflection() noexcept {return diffuseReflection;}
    GLFloat getSpecularReflection() noexcept {return specularReflection;}
    GLFloat getShininess() noexcept {return shininess;}
    void setAmbientColor(QColor color) noexcept {ambientColor = color;}
    void setAmbientColor(int r, int g, int b, int a = 255) noexcept {ambientColor = QColor(r, g, b, a);}
    void setDiffuseColor(QColor color) noexcept {diffuseColor = color;}
    void setDiffuseColor(int r, int g, int b, int a = 255) noexcept {diffuseColor = QColor(r, g, b, a);}
    void setSpecularColor(QColor color) noexcept {specularColor = color;}
    void setSpecularColor(int r, int g, int b, int a = 255) noexcept {specularColor = QColor(r, g, b, a);}
    void setAmbientReflection(GLFloat value) noexcept {ambientReflection = value;}
    void setDiffuseReflection(GLFloat value) noexcept {diffuseReflection = value;}
    void setSpecularReflection(GLFloat value) noexcept {specularReflection = value;}
    void setShininess(GLFloat value) noexcept {shininess = value;}
};

#endif // LIGHTPROPERTIES_H
