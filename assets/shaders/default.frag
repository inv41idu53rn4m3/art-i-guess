#version 330 core
#define iterations 1000 // Easy way to change max iterations
out vec4 colour; // Here we define our output
in vec2 vertpos;

void main () {
    float x = vertpos.x;
    float y = vertpos.y;
    float rc = (-y + 0.2) * 3; // Real constant
    float ic = (x - 0.5) * 3; // Imaginary constant
    float r = 0; // Real
    float i = 0; // Imaginary
    float n = 0; // Iteration counter
    while (n < iterations) {
        if (r * r + i * i > 4) { // If the number escapes, stop the loop
            break;
        }
        float newr = r * r - i * i + rc; // Calculate new values for the real
        float newi = 2 * r * i + ic; // and the imaginary component
        r = newr;
        i = newi;
        n++;
    }
    n = pow(max(n, 0.0f) / iterations, 0.2); // Take the 5th root to change the curve of the gradient
    colour = vec4(x, y, 1.0f - x, n); // Set the output colour and alpha based on the coordinates and iterations
    //colour = vec4(vertpos.x, vertpos.y, vertpos.y, 1.0f);
    //colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
