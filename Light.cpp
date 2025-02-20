#include "Light.h"

// GL
#if   defined(OSX) 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glx.h>
#endif

#include <string.h>
#include <iostream>
#include <glm/glm.hpp>

// Default Constructor
Light::
Light() {
  position = glm::vec4(0.f, 0.f, 100.f, 0.f); // Directional default behind camera
}

Light::
Light(string input, unsigned int lightNumber) {
  char* data = (char*)input.c_str();
  parseInput(data);
  lightNum = lightNumber;
}

void
Light::
draw() {
  glEnable(GL_LIGHT0 + getLight()); // Enables light i
  glLightfv(GL_LIGHT0 + getLight(), GL_AMBIENT, getAmbient());
  glLightfv(GL_LIGHT0 + getLight(), GL_DIFFUSE, getDiffuse());
  glLightfv(GL_LIGHT0 + getLight(), GL_SPECULAR, getSpecular());
  glLightfv(GL_LIGHT0 + getLight(), GL_POSITION, getPosition());

  if(getType() == 1) { // Spotlight/Pointlight exclusive
    glLightfv(GL_LIGHT0+getLight(), GL_SPOT_DIRECTION, getDirection());
    glLightfv(GL_LIGHT0+getLight(), GL_SPOT_CUTOFF, getAngularLimit());
    glLightfv(GL_LIGHT0+getLight(), GL_CONSTANT_ATTENUATION, getCAtten());
    glLightfv(GL_LIGHT0+getLight(), GL_LINEAR_ATTENUATION, getLAtten());
    glLightfv(GL_LIGHT0+getLight(), GL_QUADRATIC_ATTENUATION, getQAtten());
    if(*getAngularLimit() < 180.f) { // Pointlight exclusive
      glLightfv(GL_LIGHT0+getLight(), GL_SPOT_EXPONENT, getAAtten());
    }
  }
}

void 
Light::
print() {
  printf("light#: %u\t type: %f\tposition: (%f, %f, %f)\tdirection: (%f, %f, %f)\n", lightNum, position[3], position[0], position[1], position[2], direction[0], direction[1], direction[2]);
}


char*
Light::
parseInput(char* input) {
  char* filename = strtok(input, " ");
  char* tmp;
  float x, y, z, t;
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  position = glm::vec4(x, y, z, t); // Sets position
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if(t > 0) // spot/point
    direction = glm::vec3(x, y, z); // Sets direction
  else if(t <= 0)
    direction = glm::normalize(glm::vec3(x, y, z)); // Sets direction
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  ambient = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  diffuse = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  specular = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL) // The following only happen for spot/point lights
    constantAttenuation = atof(tmp); // Sets constant Attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    linearAttenuation = atof(tmp);  // Sets linear attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    quadraticAttenuation = atof(tmp);// sets quadratic attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    angularAttenuation = atof(tmp);  // sets angular attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    angularLimit = atof(tmp);       // sets angular Limit
  return filename;
}

