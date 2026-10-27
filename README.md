# IDI - Interacció i Disseny d'Interfícies (FIB - UPC)

Aquest repositori conté les pràctiques, exercicis i codi desenvolupat per a l'assignatura **Interacció i Disseny d'Interfícies (IDI)** del Grau en Enginyeria Informàtica de la [Facultat d'Informàtica de Barcelona (FIB)](https://www.fib.upc.edu/ca/graus/grau-en-enginyeria-informatica/pla-destudis/assignatures/IDI), Universitat Politècnica de Catalunya (UPC).

---

> [!WARNING]
> **Avís d'ús acadèmic (Disclaimer):**  
> Aquest repositori té una finalitat purament il·lustrativa i de consulta. Si ets estudiant d'IDI, et recomano fortament **intentar resoldre els exercicis i la prova pràctica de laboratori pel teu compte** abans de mirar les solucions. Copiar codi directament no et prepararà correctament per a l'avaluació ni per al disseny d'aplicacions interactives.

---

## 🛠️ Tecnologies i Eines

* **Llenguatge:** C++
* **Gràfics 3D:** OpenGL (Shaders GLSL: Vertex & Fragment Shader)
* **Interfície Gràfica & GUI:** Qt (Qt Creator / Qt Designer)
* **Modelat i Geometria:** Càrrega i manipulació de malles de triangles (.obj)

---

## 📁 Estructura del Repositori

El contingut de l'assignatura està dividit principalment en dos grans blocs pràctics:

* **`Bloc-1-OpenGL`**: Introducció als gràfics per computador 3D.
  * Primitives gràfiques, transformacions geomètriques (traslació, rotació, escala).
  * Gestió de la càmera (projecció ortogonal i perspectiva), navegació 3D i selecció d'objectes.
  * Model d'il·luminació (ambient, difusa, especular) i Shading (Phong / Blinn-Phong).
* **`Bloc-2-Qt`**: Disseny d'interfícies d'usuari (GUI) i esdeveniments.
  * Ús de Qt Designer, disseny de layouts i widgets.
  * Mecanismes de Signals & Slots.
  * Integració de visualització OpenGL dins d'interfícies de Qt (`QOpenGLWidget`).
  * Gestió d'esdeveniments de teclat i ratolí.
* **`Examens-Lab`**: Resolució de pràctiques de control i exàmens de laboratori d'anys anteriors.

---

## 🚀 Com Executar el Codi

### Requisits previs
Certifica't de tenir instal·lat:
* Compilador C++ (g++ / clang)
* **Qt Creator** (amb el mòdul OpenGL / `QOpenGLWidget`)
* Biblioteques de desenvolupament d'OpenGL (p. ex., `libgl1-mesa-dev` en Linux)

### Instruccions
1. Obre el fitxer del projecte `.pro` correnponent a la sessió amb **Qt Creator**.
2. Configura el *kit* de compilació (Desktop C++).
3. Compila i executa des de l'entorn de Qt Creator (`Ctrl + R`).

---

## ✒️ Autor

* **El teu nom / Usuari de GitHub** ([@el-teu-usuari](https://github.com/))
