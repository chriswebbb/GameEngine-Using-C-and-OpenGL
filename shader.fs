#version 460
in vec3 color;
in vec4 position;
in vec2 u_resolution;
out vec4 fragment;
uniform float u_time;

float random (in vec3 _st) {
    return fract(sin(dot(_st.xyz,
                         vec3(12.9898,78.233,0.0)))*
        43758.5453123);
}
float noise (in vec3 _st) {
    vec3 i = floor(_st);
    vec3 f = fract(_st);

    float a = random(i);
    float b = random(i + vec3(1.0, 0.0, 0.0));
    float c = random(i + vec3(0.0, 1.0, 0.0));
    float d = random(i + vec3(1.0, 1.0, 1.0));

    vec3 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

#define NUM_OCTAVES 100

float fbm ( in vec3 _st) {
    float v = -0.296;
    float a = 0.828;
    vec3 shift = vec3(0.790);
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(_st);
        _st = _st * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}

void main() {
    vec3 st = vec3(position.xy/u_resolution.xy*3., position.z);
    vec3 color = vec3(0.0);
    vec3 q = vec3(0.);
    q.x = fbm( st + 0.00*u_time);
    q.y = fbm( st + vec3(1.0));
    q.z = fbm( st + vec3(1.0));
    vec3 r = vec3(0.);
    r.x = fbm( st + 1.0*q + vec3(1.7,9.2,0.0)+ 0.15*u_time );
    r.y = fbm( st + 1.0*q + vec3(8.3,2.8,0.0)+ 0.126*u_time);
    r.z = fbm( st + 1.0*q + vec3(8.3,2.8,0.0)+ 0.126*u_time);
    float f = fbm(st + fbm(st + fbm(st+r)));
    color = mix(vec3(0.101961,0.619608,0.666667),
                vec3(0.666667,0.666667,0.498039),
                clamp((f*f)*4.0,0.0,1.0));
    color = mix(color,
                vec3(0,0,0.164706),
                clamp(length(q),0.0,1.0));
    color = mix(color,
                vec3(0.666667,1,1),
                clamp(length(r.x),0.0,1.0));
    //gl_FragColor = vec4((f*f*f+.6*f*f+.5*f)*color,1.);
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}