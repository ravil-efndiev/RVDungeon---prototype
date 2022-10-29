varying vec4 vert_pos;

uniform sampler2D texture[2];
uniform bool hasTexture;
uniform vec2 lightPos[2];

float lightCount = 2.0;

void main()
{
	//Ambient light
	vec4 ambient = vec4(0.05, 0.05, 0.1, 1.0);

	//Convert light to view coords
	vec2 lightPosTmp[2]; 
	float vecLength[2];
	vec2 lightToFrag[2];
	vec4 pixels[2];


	lightPosTmp[0] = (gl_ModelViewProjectionMatrix * vec4(lightPos[0], 0, 1)).xy;
	lightPosTmp[1] = (gl_ModelViewProjectionMatrix * vec4(lightPos[1], 0, 1)).xy;

	//Calculate the vector from light to pixel (Make circular)
	lightToFrag[0] = lightPosTmp[0] - vert_pos.xy;
	lightToFrag[0].y = lightToFrag[0].y / 1.7;
	lightToFrag[1] = lightPosTmp[1] - vert_pos.xy;
	lightToFrag[1].y = lightToFrag[1].y / 1.7;


	//Length of the vector (distance)
	vecLength[0] = clamp(length(lightToFrag[0]) * 1.5, 0.2, 1.0);
	vecLength[1] = clamp(length(lightToFrag[1]) * 3.0, 0.2, 1.0);

	// lookup the pixel in the texture
	pixels[0] = texture2D(texture[0], gl_TexCoord[0].xy);
	pixels[1] = texture2D(texture[1], gl_TexCoord[0].xy);

	
	vec4 a;
	/*
	if (abs(
        sqrt(
            ((lightPosTmp[0].x - lightPosTmp[1].x) * (lightPosTmp[0].x - lightPosTmp[1].x))
            + ((lightPosTmp[0].y - lightPosTmp[1].y) * (lightPosTmp[0].y - lightPosTmp[1].y))
        )
    ) >= 1.0)
	{*/
	a = gl_Color * ((pixels[0]* (clamp(ambient/(lightCount*1.5) + vec4(1.0-vecLength[0], 1.0-vecLength[0], 1.0-vecLength[0], 1.0) / 1.5, 0.0, 1.0))) + (pixels[1] * (clamp(ambient/(lightCount*1.5) + vec4(1.0-vecLength[1], 1.0-vecLength[1], 1.0-vecLength[1], 1.0) / 1.3, 0.0, 1.0))));
	/*}
	else
		a = gl_Color * ((pixels[0] * (clamp(ambient/lightCount + vec4(1.0-vecLength[0], 1.0-vecLength[0], 1.0-vecLength[0], 1.0) / 1.9, 0.0, 1.0))) + (pixels[1] * (clamp(ambient/lightCount + vec4(1.0-vecLength[1], 1.0-vecLength[1], 1.0-vecLength[1], 1.0) / 1.9, 0.0, 1.0))));
	*/

	// multiply it by the color and lighting
	if(hasTexture == true)
	{
		gl_FragColor = a;
	}
	else
	{
		gl_FragColor = gl_Color;
	}
}
