#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;
struct Tri{
    vec3 v[3];
    Tri(vec3 v0, vec3 v1, vec3 v2) {
        v[0] = v0; v[1] = v1; v[2] = v2;
    }
};

bool intersecta(Tri &t1, Tri &t2);
bool intersecta(Tri &t1, vec3 &a, vec3 &b);
int main() {
    Tri t1(vec3(0), vec3(1,0,0), vec3(0,1,0));
    Tri t2(vec3(0,0,1), vec3(1),vec3(0.5, 0.5,-0.5));
    cout << intersecta(t1, t2);
    return 0;
}
bool intersecta(Tri &t1, Tri &t2) {
    return  intersecta(t1, t2.v[0], t2.v[1]) or
            intersecta(t1, t2.v[0], t2.v[1]) or
            intersecta(t1, t2.v[0], t2.v[1]);
}
bool intersecta(Tri &t1, vec3 &a, vec3 &b) {

}