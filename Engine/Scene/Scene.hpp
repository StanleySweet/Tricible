#pragma once

#include <vector>
#include "AObject.hpp"
#include "AIntersectable.hpp"
#include "ALight.hpp"
#include "../Scene/Camera.hpp"

namespace Tricible
{
	namespace Scene
	{
		class Scene : public AObject, public AIntersectable
		{
		public:
			Texture *Skymap;

			std::vector<AIntersectable *>	Objects;
			std::vector<ALight *>	Lights;
			Camera *CurrentCamera;
			Camera DefaultCamera;

			Scene() :
				AIntersectable()
			{
				CurrentCamera = &DefaultCamera;
			}

			static Scene *LoadFromObj(const std::string& filePath);

			// Inherited via AIntersectable
			virtual bool IntersectsRay(const Point3 & origin, const Point3 & vec, IntersectionInfo *interInfo, float nearClip, float farClip) override;
			virtual void ComputeNormal(const IntersectionInfo & interInfo, Point3 & normal) override;
		};
	}
}
