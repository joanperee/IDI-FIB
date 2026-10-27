#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

uniform vec3 posFocus1;
uniform vec3 posFocus2;
uniform vec3 posFocus3;
uniform vec3 posFocus4;
uniform vec3 colorFocus;
uniform vec3 posFocusModel;
uniform vec3 colorFocusModel;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
  // 1. Normalitzar normSCO (comú per tots)
  vec3 normSCO = normalize(fnormal);

  // 2. Trobar la LSCO de cada focus
  vec3 L1 = normalize(posFocus1 - fvertex);
  vec3 L2 = normalize(posFocus2 - fvertex);
  vec3 L3 = normalize(posFocus3 - fvertex);
  vec3 L4 = normalize(posFocus4 - fvertex);
  vec3 Lm = normalize(posFocusModel - fvertex);
  
  // 3. Calcular el color sumant tots els focus
  vec3 color = Ambient();
  color += Difus(normSCO, L1, colorFocus);
  color += Difus(normSCO, L2, colorFocus);
  color += Difus(normSCO, L3, colorFocus);
  color += Difus(normSCO, L4, colorFocus);
  color += Difus(normSCO, Lm, colorFocusModel);
  color += Especular(normSCO, L1, fvertex, colorFocus);
  color += Especular(normSCO, L2, fvertex, colorFocus);
  color += Especular(normSCO, L3, fvertex, colorFocus);
  color += Especular(normSCO, L4, fvertex, colorFocus);
  color += Especular(normSCO, Lm, fvertex, colorFocusModel);

  FragColor = vec4(color, 1);
}
