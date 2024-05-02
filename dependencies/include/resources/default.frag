#version 330 core

out vec4 color;

void main()
{
	vec3 normal;

	normal.xy = gl_PointCoord * 2.0 - vec2(1.0);

	float mag = dot(normal.xy, normal.xy);

	if (mag > 1.0)
	{
		discard;
	}

	normal.z = sqrt(1.0 - mag);

	color = vec4(0.0, 0.0, 0.5, 1.0);
}