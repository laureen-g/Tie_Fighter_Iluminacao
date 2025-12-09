#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

// === UNIFORMS ===
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float lightIntensity;
uniform int lightMode;
uniform vec3 lightColor;


uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // --- Normal ---
    vec3 norm = normalize(Normal);

    // --- Texturas ---
    vec3 color1 = texture(texture1, TexCoord).rgb;
    vec3 color2 = texture(texture2, TexCoord).rgb;

    // você pode mudar o fator aqui (0 = só tex1 / 1 = só tex2)
    float blendFactor = 0.5;
    vec3 baseColor = mix(color1, color2, blendFactor);

    // --- Ambiente ---
    vec3 ambient = 0.20 * baseColor * lightColor;

    // --- Difusa ---
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * baseColor * lightColor;

    // --- Especular ---
    vec3 viewDir    = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(0.4) * spec * lightColor;

    // resultado final
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0) * lightIntensity;
}
