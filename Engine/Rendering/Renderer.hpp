#pragma once

#include <iostream>
#include <vector>
#include "../Scene/IntersectionInfo.hpp"
#include "../Scene/Sphere.hpp"
#include "../Scene/Plane.hpp"
#include "../Scene/Triangle.hpp"
#include "../Scene/ALight.hpp"
#include "../Scene/Scene.hpp"
#include "../Scene/Camera.hpp"
#include "../Tools/Tools.hpp"

namespace Tricible
{
	class Renderer
	{
	public:
		int *image;
		int _resX;
		int _resY;
		Scene::Scene *Scene;
		/*	std::vector<AIntersectable *>	_objects;
			std::vector<ALight *>	_lights;
			Camera _camera;*/
	public:
		Renderer(int resX, int resY, int bpp, Scene::Scene *scene) :Scene(scene)
		{
			_resX = resX;
			_resY = resY;
			image = new int[resX * resY];
		}

		void Render()
		{
			auto& camera = *Scene->CurrentCamera;
			for (int y = 0; y < _resY; ++y)
			{
				for (int x = 0; x < _resX; ++x)
				{
					Point3 vec;
					camera.GetRay(x - (_resX * .5f), y - (_resY * .5f), vec);
					vec.Normalize();
					Color::RGB finalColor = Color::RGB();
					float nearestDist = -1.f;
					// IntersectionInfo *retainedInter;
					IntersectionInfo interInfo = IntersectionInfo();

					if (Scene->IntersectsRay(camera.getPosition() + vec, vec, &interInfo, camera.NearClip, camera.FarClip))
					{
						Color::RGB diffuseColor;
						if (interInfo.Object->Material != nullptr)
						{
							diffuseColor = interInfo.Object->Material->DiffuseColor;
						}

						Point3 normal;
						interInfo.Object->ComputeNormal(interInfo, normal);

						{ // Displays normal
							//Point3 vecToVisualizeAsCol = normal;
							//finalColor = Color::RGB((vecToVisualizeAsCol._x * 0.5f + 0.5f) * 255.0f, (vecToVisualizeAsCol._y * 0.5f + 0.5f) * 255.0f, (vecToVisualizeAsCol._z * 0.5f + 0.5f) * 255.0f);
						}

						{ // Displays if distance is less than
							//finalColor = Color::RGB((interInfo.Distance < 20.0f ? 255U : 0U), 0U, 0U);
						}

						// displays depth
						//float distMax = 50.0f;
						//uint8_t colDist = Clamp((int)(255 * (1.0f - Clamp01(interInfo.Distance / distMax))), 0, 255);
						//finalColor = Color::RGB(colDist, colDist, colDist);

						for (ALight *l : Scene->Lights)
						{
							Point3 tmp = (l->getPosition() - interInfo.Intersection);
							tmp.Normalize();
							const float mult = Clamp01(tmp.Dot(normal));
							if (true)//mult > 0.f)
							{
								Color::RGB currentColor = diffuseColor;// *mult * l->intensity;
								finalColor += currentColor;
							}
						}
					}
					else
					{
						if (Scene->Skymap != nullptr)
						{
							Point3 normVec = vec;
							float radius = sqrtf(POW2(vec._x) + POW2(vec._y) + POW2(vec._z));
							normVec.Normalize();
							float pitch = asinf(-(normVec._y));
							float yaw = atan2f(normVec._x, normVec._z);
							
							//finalColor = Scene->Skymap->Get360PixelBilinearInterpolation(pitch, yaw);
							finalColor = Scene->Skymap->Get360Pixel(pitch, yaw);
						}
						else
						{
							finalColor = Color::RGB();
						}
					}
					image[x + y * _resX] = finalColor.ToInt();
				}
			}
		}
	};
}