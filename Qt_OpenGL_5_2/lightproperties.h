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
    QColor getAmbientColor() {return ambientColor;}
    QColor getDiffuseColor() {return diffuseColor;}
    QColor getSpecularColor() {return specularColor;}
    GLFloat getAmbientReflection() {return ambientReflection;}
    GLFloat getDiffuseReflection() {return diffuseReflection;}
    GLFloat getSpecularReflection() {return specularReflection;}
    GLFloat getShininess() {return shininess;}
    void setAmbientColor(QColor color) {ambientColor = color;}
    void setAmbientColor(int r, int g, int b, int a = 255) {ambientColor = QColor(r, g, b, a);}
    void setDiffuseColor(QColor color) {diffuseColor = color;}
    void setDiffuseColor(int r, int g, int b, int a = 255) {diffuseColor = QColor(r, g, b, a);}
    void setSpecularColor(QColor color) {specularColor = color;}
    void setSpecularColor(int r, int g, int b, int a = 255) {specularColor = QColor(r, g, b, a);}
    void setAmbientReflection(GLFloat value) {ambientReflection = value;}
    void setDiffuseReflection(GLFloat value) {diffuseReflection = value;}
    void setSpecularReflection(GLFloat value) {specularReflection = value;}
    void setShininess(GLFloat value) {shininess = value;}
};

#endif // LIGHTPROPERTIES_H
