#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

void qsplat(vec4 position)
{    
    fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0); // 3:top-left
    EmitVertex();
    //gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0); // 4:top-right
    //EmitVertex();
    EndPrimitive();
}

void main() {    
    qsplat(gl_in[0].gl_Position);
}