#version 330 core

out vec4 fColor;

void main()
{
	if(dot(gl_PointCoord-0.5,gl_PointCoord-0.5)>0.25)
	{
		discard;
	}
	else
	{
		fColor = vec4(0.25, 0.5, 0.75, 1.0);
	}
}