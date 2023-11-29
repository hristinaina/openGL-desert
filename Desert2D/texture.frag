#version 330 core

in vec2 chTex; //koordinate teksture
out vec4 outCol;

uniform sampler2D uTex; //teksturna jedinica
uniform float alphaCh;

void main()
{
	vec4 texColor = texture(uTex, chTex);

    // Check if the alpha value of the texture at this pixel is greater than a threshold
    float alphaThreshold = 0.1;
    if (texColor.a > alphaThreshold) {
        // There is texture at this pixel
        texColor.a = alphaCh;
        outCol = texColor;
    } else {
        // No texture at this pixel, make it transparent
        outCol = vec4(0.0, 0.0, 0.0, 0.0);
    }
}