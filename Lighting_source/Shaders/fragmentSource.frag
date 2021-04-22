#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;


in vec2 TexCoord;
struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 





struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
};
struct LightSpot{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
	float cosPhyInner;
	float cosPhyOutter;
};

uniform Material material;
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;


uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

uniform float mixValue;
//平行光
vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirTocamera){
	//diffuse max(0,dot(L,N))
	float diffIntensity = max(dot(light.dirToLight,uNormal),0);
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular pow(max(dot(R,Cam),0),shininess)
	vec3 R = normalize(reflect(-light.dirToLight,uNormal));
	float specIntensity = pow(max(dot(R,dirTocamera),0),material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular,TexCoord).rgb;


	vec3 result = diffColor + specColor;

	return result;
}

//点光源
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirTocamera){
	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation  = 1 / (light.constant + light.linear * dist + light.quadratic * (dist*dist));


	//diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos),uNormal),0) * attenuation;
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos),uNormal));
	float specIntensity = pow(max(dot(R,dirTocamera),0),material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular,TexCoord).rgb;

	 vec3 result = diffColor+specColor;
	 return result;
}


vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirTocamera){
	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation  = 1 / (light.constant + light.linear * dist + light.quadratic * (dist*dist));
	float spotRatio;
	float CosThta = dot(normalize(FragPos - light.pos),-light.dirToLight);
	if(CosThta > light.cosPhyInner){
		spotRatio = 1.0f;
	}
	else if(CosThta > light.cosPhyOutter){
		spotRatio = (CosThta - light.cosPhyOutter) / (light.cosPhyInner - light.cosPhyOutter);
	}
	else {
		spotRatio = 0.0f;
	}

	//diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos),uNormal),0) * attenuation * spotRatio;
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos),uNormal));
	float specIntensity = pow(max(dot(R,dirTocamera),0),material.shininess) * attenuation * spotRatio;
	vec3 specColor = specIntensity * light.color * texture(material.specular,TexCoord).rgb;


	 vec3 result = diffColor + specColor;
	 return result;
}
void main()
{
	vec3 finalResult = vec3(0.0f,0.0f,0.0f);
	vec3 uNormal = normalize(Normal);
	vec3 dirTocamera = normalize(cameraPos - FragPos);

	finalResult += CalcLightDirectional(lightD,uNormal,dirTocamera);

	finalResult += CalcLightPoint(lightP0,uNormal,dirTocamera);
	finalResult += CalcLightPoint(lightP1,uNormal,dirTocamera);
	finalResult += CalcLightPoint(lightP2,uNormal,dirTocamera);
	finalResult += CalcLightPoint(lightP3,uNormal,dirTocamera);

	finalResult += CalcLightSpot(lightS,uNormal,dirTocamera);



	FragColor = vec4(finalResult,1.0f);
}