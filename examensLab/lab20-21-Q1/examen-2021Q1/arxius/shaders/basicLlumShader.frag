#version 330 core

in vec4 vertexSCO;
in vec3 normalSCO;
in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

out vec4 FragColor;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocus = vec3(0, 0, 0);

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 colFocus;

vec3 Ambient()
{
  return llumAmbient * fmatamb;
}

vec3 Difus(vec3 NormSCO, vec3 L, vec3 colFocus)
{
  vec3 colRes = vec3(0);
  if (dot(L, NormSCO) > 0.0)
    colRes = colFocus * fmatdiff * dot(L, NormSCO);
  return colRes;
}

vec3 Especular(vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
  vec3 colRes = vec3(0);
  if ((dot(NormSCO, L) < 0.0) || (fmatshin == 0.0))
    return colRes;

  vec3 R = reflect(-L, NormSCO);
  vec3 V = normalize(-vertSCO.xyz);

  if (dot(R, V) < 0.0)
    return colRes;

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return fmatspec * colFocus * shine;
}

void main()
{
  vec4 focusSCO = vec4(posFocus, 1.0);
  vec3 LSCO = normalize(focusSCO.xyz - vertexSCO.xyz);

  vec3 color =
      Ambient() +
      Difus(normalSCO, LSCO, colFocus) +
      Especular(normalSCO, LSCO, vertexSCO, colFocus);

  FragColor = vec4(color, 1.0);
}
