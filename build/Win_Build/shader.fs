#version 460
#define NUM_OCTAVES 100
in vec3 color;
in vec4 position;
in vec2 u_resolution;
out vec4 fragment;
uniform float u_time;

float hash(in float p) { 
    p = fract(p * 0.111); 
    p *= p + 17.5; 
    p *= p + p; 
    return fract(p); 
}

float noise(in vec3 x) {

    const vec3 step = vec3(12,78, 71);

    vec3 i = floor(x);
    vec3 f = fract(x);
 
    // For performance, compute the base input to a 1D hash from the integer part of the argument and the 
    // incremental change to the 1D based on the 3D -> 1D wrapping
    float n = dot(i, step);

    vec3 u = f * f * (3.0 - 2.0 * f);

    return mix(mix(mix( hash(n + dot(step, vec3(0, 0, 0))), hash(n + dot(step, vec3(1, 0, 0))), u.x),
                   mix( hash(n + dot(step, vec3(0, 1, 0))), hash(n + dot(step, vec3(1, 1, 0))), u.x), u.y),
               mix(mix( hash(n + dot(step, vec3(0, 0, 1))), hash(n + dot(step, vec3(1, 0, 1))), u.x),
                   mix( hash(n + dot(step, vec3(0, 1, 1))), hash(n + dot(step, vec3(1, 1, 1))), u.x), u.y), u.z);
}

float fbm(in vec3 x) {
	float v = -0.996;
	float a = 1.828;
	vec3 shift = vec3(10.790);
	for (int i = 0; i < NUM_OCTAVES; ++i) {
		v += a * noise(x);
		x = x * 2.0 + shift;
		a *= 0.25;
	}
	return v;
}

void main() {
    vec3 st = vec3(position.xyz*4);
    vec3 color = vec3(0.0);
    vec3 q = vec3(0.);
    q.x = fbm( st + 0.10*u_time);
    q.y = fbm( st + vec3(1.0));
    q.z = fbm( st + vec3(1.0));
    vec3 r = vec3(0.);
    r.x = fbm( st + 1.0*q + vec3(1.7,9.2,5.8)+ 0.15*u_time );
    r.y = fbm( st + 1.0*q + vec3(8.3,2.8,2.7)+ 0.126*u_time);
    r.z = fbm( st + 1.0*q + vec3(8.3,2.8,5.3)+ 0.2*u_time);
    float f = fbm(st + fbm(st + fbm(st+r)));
    color = mix(vec3(0.901961,0.619608,0.666667),
                vec3(0.666667,0.666667,0.498039),
                clamp((f*f)*4.0,0.0,1.0));
    color = mix(color,
                vec3(0.9,0,0.964706),
                clamp(length(q),0.0,1.0));
    color = mix(color,
                vec3(0.666667,1,1),
                clamp(length(r.x),length(r.y),1.0));
    color = mix(color, vec3(1.0, 0.9, 1.0), color);
    //gl_FragColor = vec4((f*f*f+.6*f*f+.5*f)*color,1.);
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}