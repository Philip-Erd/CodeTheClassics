#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
varying vec2 fragTexCoord;
varying vec4 fragColor;
varying vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec3 sunColor;
uniform vec3 sunDir;            //sun direction not position

const float ambientStrength = 0.2;



void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord);
    vec3 normal = normalize(fragNormal);

    // ambient
    vec3 ambient = ambientStrength * sunColor;

  	
    // diffuse 
    float diff = max(dot(normal, -normalize(sunDir)), 0.0);
    vec3 diffuse = diff * sunColor;
            
    vec3 result = (ambient + diffuse) * vec3(texelColor);
    //result = fragNormal;
    
    
    gl_FragColor = vec4(result, 1.0);
}