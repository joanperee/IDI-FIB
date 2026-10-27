#version 330 core

out vec4 FragColor;
in vec3 fcolor;

void main() {
    
    FragColor = vec4(fcolor, 1);

    // // PINTA PER QUADRANTS
    // if (gl_FragCoord.x <= 354 && gl_FragCoord.y > 354)
    // {
    //     FragColor = vec4(1, 0, 0, 1);    // vermell
    // }
    // else if (gl_FragCoord.x <= 354 && gl_FragCoord.y <= 354)
    // {
    //     FragColor = vec4(1, 1, 0, 1);    // groc
    // }
    // else if (gl_FragCoord.x > 354 && gl_FragCoord.y > 354)
    // {
    //     FragColor = vec4(0, 0, 1, 1);    // blau
    // }
    // else 
    // {
    //     FragColor = vec4(0, 1, 0, 1); // verd   
    // }
}
