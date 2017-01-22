#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 fragTexCoord;

out vec2 texCoord;
out vec3 vertPos; //Vertex position in eye coords
out vec3 N; //Transformed normal
out vec3 lightPos; //Light position in eye coords



uniform vec3 LightPosition; // Light position 
uniform mat3 NormalMatrix;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{

   vertPos = vec3(V * M * vec4(VertexPosition,1.0)); 
     
   lightPos = vec3(V * vec4(LightPosition,1.0));  

   texCoord = fragTexCoord;

   N = normalize( NormalMatrix * VertexNormal);
      
   gl_Position = P * V * M * vec4(VertexPosition,1.0);
}
