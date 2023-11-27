#pragma once

void createSun(float centerX, float centerY, float width, float height);

void renderSun(unsigned int shaderProgram, float paused, float restared);

void createMoon(float centerX, float centerY, float width, float height);

void renderMoon(unsigned int shaderProgram);

void DeleteSkyVariables();