#version 430

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;
in vec2 texCoord;


uniform vec3 La;			// Ambient light intensity
uniform vec3 Lp;			// Point light intensity

uniform sampler2D tex;

uniform float constantAtt;
uniform float linearAtt;
uniform float quadraticAtt;

uniform vec3 Ka;			// Ambient light reflectivity
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ks;			// Specular light reflectivity


layout( location = 0 ) out vec4 FragColour;

void main() {

   //Calculate the light vector
   vec3 L = normalize(lightPos - vertPos);
   vec3 V = normalize(0.0 + vertPos);	//Camera Distance vector

   float attenuation;

   float distance = length(lightPos - vertPos);

   attenuation = 1.0 / (constantAtt + linearAtt * distance + quadraticAtt * distance * distance);
    
   //calculate Diffuse Light Intensity making sure it is not negative 
   vec4 Id = vec4(Kd,1.0) * max(dot(N,L), 0.0);	//
   //Calculating Ambient Light
   vec4 Ia = vec4(La,1.0) * max(vec4(Ka, 1.0), 0.0);

   //Calculating Specular Lighting
   vec3 R = reflect(L, N);	//calculating reflection vector
   vec4 Is = vec4(Ks,1.0) * max(pow(dot(R, V), 20.0), 0.0);	//Specular reflection coefficient times dot product of RV to the power of specular reflection exponent

   //clamping lights 0 to 1  
   Id = clamp(Id, 0.0, 1.0);     
   Ia = clamp(Ia, 0.0, 1.0);   
   Is = clamp(Is, 0.0, 1.0);

   Id *= attenuation;
   Ia *= attenuation;
   Is *= attenuation;

   vec4 lights = (Ia + vec4(Lp,1.0) * (Id +Is));

   //Combining all lighting elements and textures together

   FragColour = lights * texture(tex,texCoord);

}
