#include "Raytracer.h"
#include "Sphere.h"
#include <cmath>

struct RayHit 
{
    Vector3 Point;
    Vector3 Normal;
    const Sphere* Object;
};


static bool RaySphereIntersection(const Ray& InRay, const Sphere& InSphere, RayHit& Hit) 
{
    Vector3 L = InSphere.Center - InRay.Origin;
    float Tca = L.Dot(InRay.Direction);

    float MagnL2 = L.MagnetudeSquared();

    float D2 = MagnL2 - Tca * Tca;
    float Radius2 = InSphere.Radius * InSphere.Radius;
    if (D2 > Radius2) return false;

    float Thc = sqrtf(Radius2 - D2);

    float T0 = Tca - Thc; //
    float T1 = Tca + Thc;

    if (T1 < T0)  //In T0 we will keep the smallest value
    {
        float Temp = T0;
        T0 = T1;
        T1 = Temp;
    }

    if (T0 < 0) 
    {
        T0 = T1; //Case: where T1 > T0
        if (T0 < 0) return false;
    }

    Hit.Point = InRay.Origin + InRay.Direction * T0;
    Hit.Normal = (Hit.Point - InSphere.Center).Normalized();
    Hit.Object = &InSphere;
    return true;
}

static bool RayCast(const Ray& InRay, const Scene& InScene, RayHit& Hit) 
{
    for(auto& EachSphere : InScene.Spheres) 
    {   
        //TODO: Improve taking best hit 
        if (RaySphereIntersection(InRay, EachSphere, Hit)) 
        {
            return true;
        }
    }
    return false;
}


XColor Raytracer::RayTrace(const Ray& InRay, Scene& InScene)
{
    //Primary Result
    RayHit Hit;
    bool HasHit = RayCast(InRay, InScene, Hit);
    if (!HasHit) return {0, 0, 0};

    //Secondary Ray (Shadow ray)
    Vector3 InvertedLightDirection = InScene.Light.Direction * -1.f;


    float bias = 1e-4;
    Ray ShadowRay;
    ShadowRay.Origin = Hit.Point + (Hit.Normal * bias);
    ShadowRay.Direction = InvertedLightDirection;

    RayHit ShadowHit;
    bool ShadowHasHit = RayCast(ShadowRay, InScene, ShadowHit);
    //if (ShadowHasHit) return {0, 0, 0};

    XColor SphereColor = Hit.Object->Material.Albedo;

    //PHONG
    //1. Ambient
    float AmbientFactor = 0.1f;
    XColor Ambient = SphereColor * AmbientFactor;

    //2. Diffuse
    float Lambert = fmaxf(0, InvertedLightDirection.Dot(Hit.Normal));
    XColor Diffuse = SphereColor * Lambert;

    //3. Specular
    Vector3 L = InvertedLightDirection;
    Vector3 V = (Hit.Point * -1.f).Normalized();
    Vector3 H = (L + V).Normalized();

    float SpecularFactor = fmaxf(0, Hit.Normal.Dot(H));
    float SpecularIntensity = powf(SpecularFactor, Hit.Object->Material.SpecularShiningFactor);
    XColor Specular = InScene.Light.Color * SpecularIntensity;

    XColor Phong{0, 0, 0};
    Phong = Phong + Ambient;
    Phong = Phong + Diffuse;
    Phong = Phong + Specular;
    Phong = Phong.Clamp();
    return Phong;
   
}