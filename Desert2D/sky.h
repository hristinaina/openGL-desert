#pragma once

void createSun(float centerX, float centerY, float width, float height);

void renderSun(unsigned int shaderProgram);

void createMoon(float centerX, float centerY, float width, float height);

void renderMoon(unsigned int shaderProgram);

void DeleteSkyVariables();