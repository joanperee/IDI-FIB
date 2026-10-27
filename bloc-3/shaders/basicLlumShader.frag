#version 330 core

in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

in vec3 normSCO;
in vec4 vertexSCO;

out vec4 FragColor;

uniform mat4 view; 
uniform mat4 TG;
uniform vec3 posFocus;
uniform vec3 colorFocus;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient()
{
	return llumAmbient * fmatamb;
}

vec3 Difus(vec3 NormSCO, vec3 L, vec3 colFocus)
{
	vec3 colRes = vec3(0.0);
	float d = dot(L, NormSCO);
	if (d > 0)
		colRes = colFocus * fmatdiff * d;
	return colRes;
}

vec3 Especular(vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
	if (dot(NormSCO, L) < 0 || fmatshin == 0)
		return vec3(0.0);

	vec3 R = reflect(-L, NormSCO);
	vec3 V = normalize(-vertSCO.xyz);

	float rv = dot(R, V);
	if (rv < 0)
		return vec3(0.0);

	float shine = pow(rv, fmatshin);
	return fmatspec * colFocus * shine;
}

void main()
{
	vec4 focusSCO = view * vec4(posFocus, 1.0);
	vec3 LSCO = normalize(focusSCO.xyz - vertexSCO.xyz);

	vec3 color =
		Ambient() +
		Difus(normSCO, LSCO, colorFocus) +
		Especular(normSCO, LSCO, vertexSCO, colorFocus);

	FragColor = vec4(color, 1.0);
}
