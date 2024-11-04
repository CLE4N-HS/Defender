uniform float iTime;


void main()
{
	float r = cos(iTime * 10.f);
	float g = cos(iTime * 20.f);
	float b = cos(iTime * 30.f);
	
	gl_FragColor = vec4(r,g,b,1.0);
}