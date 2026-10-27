#version 330 core

in vec4 vertexSCO;
in vec3 normalSCO;
in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

out vec4 FragColor;

// Valors per als components que necessitem dels focus de llum
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 colFocus = vec3(1, 1, 1);

uniform vec3 posFocus;
uniform vec3 posFocus1;
uniform vec3 posFocus2;
uniform vec3 posFocus3;
uniform bool focusCamera;

vec3 Ambient()
{
  return llumAmbient * fmatamb;
}

vec3 Difus(vec3 NormSCO, vec3 L, vec3 colorFocus)
{
  // Fixeu-vos que SOLS es retorna el terme difús
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  // Càlcul component difusa, si n'hi ha
  if (dot(L, NormSCO) > 0)
    colRes = colorFocus * fmatdiff * dot(L, NormSCO);
  return (colRes);
}

vec3 Especular(vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colorFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3(0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO, L) < 0) || (fmatshin == 0))
    return colRes; // no hi ha component especular

  // Calculem R i V
  vec3 R = reflect(-L, NormSCO);    // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes; // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (fmatspec * colorFocus * shine);
}

void main()
{
    
  vec3 normalAux = normalize(normalSCO);

  
  
    vec3 L1 = normalize(posFocus1 - vertexSCO.xyz); // vermell
    vec3 L2 = normalize(posFocus2 - vertexSCO.xyz); // verd
    vec3 L3 = normalize(posFocus3 - vertexSCO.xyz); // blau

    vec3 color = Ambient() + Difus(normalAux, L1, vec3(1, 0, 0)) + Especular(normalAux, L1, vertexSCO, vec3(1, 0, 0));
    color += Difus(normalAux, L2, vec3(0, 1, 0)) + Especular(normalAux, L2, vertexSCO, vec3(0, 1, 0));
    color += Difus(normalAux, L3, vec3(0, 0, 1)) + Especular(normalAux, L3, vertexSCO, vec3(0, 0, 1));
    FragColor = vec4(color, 1);    
    
}
