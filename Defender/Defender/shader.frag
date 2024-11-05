uniform float iTime;


void main()
{
	float r = cos(sin(iTime) * 10.f) * 0.5 + 0.5;
	float g = cos(sin(iTime) * 20.f) * 0.5 + 0.5;
	float b = cos(sin(iTime) * 30.f) * 0.5 + 0.5;
	
	gl_FragColor = vec4(r,g,b,1.0);
}
