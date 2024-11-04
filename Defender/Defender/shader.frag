uniform float iTime;


//void main()
//{
//	float r = cos(iTime * 10.f) *0.5 + 0.5;
//	float g = cos(iTime * 20.f) * 0.5 + 0.5;
//	float b = cos(iTime * 30.f) * 0.5 + 0.5;
//	
//	gl_FragColor = vec4(r,g,b,1.0);
//}
//
void main()
{
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
}

// float r = (cos(iTime * 10.0) + 1.0) * 0.5;
// float g = (cos(iTime * 20.0) + 1.0) * 0.5;
// float b = (cos(iTime * 30.0) + 1.0) * 0.5;