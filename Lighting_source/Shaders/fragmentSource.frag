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

struct LightPoint {
    float constant;
	float linear;
	float quadratic;
};

struct LightSpot{
	float cosPhyInner;
	float cosPhyOutter;
};
uniform Material material;
uniform LightPoint lightP;
uniform LightSpot lightS;

uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

uniform float mixValue;

void main()
{
	//LightPoint coefficient
	float dist = length(lightPos-FragPos);
	float attenuation = 1.0 / (lightP.constant + lightP.linear * dist + lightP.quadratic * (dist * dist));
	
	//物体到光源的向量
	vec3 lightDir = normalize(lightPos - FragPos);
	//计算反射线（入射，法向）
	vec3 reflectVec = reflect(-lightDir, Normal);
	//物体到眼睛的向量
	vec3 cameraVec = normalize(cameraPos - FragPos);

	//漫反射
	vec3 diffuse = texture(material.diffuse,TexCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor;
	//vec3 diffuse = texture(material.diffuse,TexCoord).rgb;

	//镜面反射（高光）
	float specularAmount = pow(max(dot(cameraVec,reflectVec),0),material.shininess);
	vec3 specular = texture(material.specular,TexCoord).rgb *  specularAmount * lightColor;

	vec3 ambient = texture(material.diffuse,TexCoord).rgb * material.ambient * ambientColor;

	float cosTheta = dot(normalize(FragPos - lightPos), -1 * lightDirUniform);
	float spotRatio;
	if(cosTheta > lightS.cosPhyInner){
		//inside
		spotRatio = 1.0f;
	}
	else if(cosTheta > lightS.cosPhyOutter){
		//middle
		spotRatio = 1.0f - (cosTheta - lightS.cosPhyInner) /(lightS.cosPhyOutter - lightS.cosPhyInner) ;
	}
	else{
		//outside
		spotRatio = 0.0f;
	}
	FragColor = vec4(objectColor * (ambient+(diffuse+specular)*spotRatio),1.0f);

//	if(cosTheta > lightS.cosPhy){
//		//inside
//		FragColor = vec4(objectColor * (ambient+(diffuse+specular)),1.0f);
//	}
//	else{
//		//outside
//		FragColor = vec4(objectColor * (ambient),1.0f);
//	}

	



	

}