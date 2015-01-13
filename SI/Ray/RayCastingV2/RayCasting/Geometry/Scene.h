#ifndef _Geometry_Scene_H
#define _Geometry_Scene_H

#include <windows.h>
#include <Geometry/Geometry.h>
#include <Geometry/PointLight.h>
#include <Visualizer/Visualizer.h>
#include <Geometry/Camera.h>
#include <Geometry/BoundingBox.h>
#include <Math/RandomDirection.h>
#include <windows.h>
#include <System/aligned_allocator.h>

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Scene
	///
	/// \brief	An instance of a geometric scene that can be rendered using ray casting. A set of methods
	/// 		allowing to add geometry, lights and a camera are provided. Scene rendering is achieved by
	/// 		calling the Scene::compute method.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	03/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Scene
	{
	protected:
		/// \brief	The visualizer (rendering target).
		Visualizer::Visualizer * m_visu ;
		/// \brief	The scene geometry (basic representation without any optimization).
		::std::deque<::std::pair<BoundingBox, Geometry> > m_geometries ;
		//Geometry m_geometry ;
		/// \brief	The lights.
		std::deque<PointLight, aligned_allocator<PointLight, 16> > m_lights ;
		/// \brief	The camera.
		Camera m_camera ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Scene::Scene(Visualizer::Visualizer * visu)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param [in,out]	visu	If non-null, the visu.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Scene(Visualizer::Visualizer * visu)
			: m_visu(visu)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::add(const Geometry & geometry)
		///
		/// \brief	Adds a geometry to the scene.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	geometry The geometry to add.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void add(const Geometry & geometry)
		{
			//m_geometry.merge(geometry) 
			BoundingBox box(geometry) ;
			m_geometries.push_back(::std::make_pair(box, geometry)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::add(PointLight * light)
		///
		/// \brief	Adds a poitn light in the scene.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param [in,out]	light	If non-null, the light to add.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void add(const PointLight & light)
		{
			m_lights.push_back(light) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::setCamera(Camera const & cam)
		///
		/// \brief	Sets the camera.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	cam	The camera.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setCamera(Camera const & cam)
		{
			m_camera = cam ;
		}

		const Triangle & getGeometryTriangle(const Geometry & geo, const Ray & ray) {
			const Triangle * top = NULL;
			::std::deque<Triangle,aligned_allocator<Triangle,16U>>::const_iterator it = geo.getTriangles().begin();
			const Triangle* triangle = &*it;
			top = triangle;
			RayTriangleIntersection inter(triangle, &ray);
			while (it != geo.getTriangles().end()) {
				//if (it->intersection(CastedRay(ray))) {
					if ( (! inter.valid()) || (RayTriangleIntersection(triangle, &ray) < inter) ) {
						top = &*it;
						inter = RayTriangleIntersection(triangle, &ray);
					}
				//}
				it++;
			}
			return *top;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor Scene::sendRay(Ray const & ray, float limit, int depth, int maxDepth)
		///
		/// \brief	Sends a ray in the scene and returns the computed color
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	ray			The ray.
		/// \param	depth   	The current depth.
		/// \param	maxDepth	The maximum depth.
		///
		/// \return	The computed color.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor sendRay(Ray const & ray, int depth, int maxDepth)
		{
			RGBColor color = RGBColor(0.0,0.0,0.0);
			RayTriangleIntersection inter=NULL;
			bool intersect = false;
			float distance, distanceMin = std::numeric_limits<float>::max();
			::std::deque<::std::pair<BoundingBox, Geometry> >::iterator itGeo;
			itGeo=m_geometries.begin();

			while(itGeo!=m_geometries.end()) {
				::std::deque<Triangle, aligned_allocator<Triangle,16U>>::const_iterator itTri = itGeo->second.getTriangles().begin();
				while(itTri!=itGeo->second.getTriangles().end()) {
					RayTriangleIntersection currentInter(&*itTri,&ray);
					if(currentInter.valid()) {
						distance = currentInter.tRayValue();
						if(distance<distanceMin) {
							inter=currentInter;
							intersect=true;
							distanceMin=distance;
						}
					}
					itTri++;
				}
				itGeo++;
			}

			bool shadowIntersect=false;
			RayTriangleIntersection interShadow = NULL;
			if(intersect) {
				std::deque<PointLight,aligned_allocator<PointLight,16>>::iterator itLights = m_lights.begin();
				while(itLights != m_lights.end()) {
					Math::Vector3 dirLight = (itLights->position()-inter.intersection()).normalized(); //vecteur L
					Ray shadowRay(itLights->position(),-dirLight);
					distanceMin=std::numeric_limits<float>::max();
					itGeo=m_geometries.begin();
					while(itGeo!=m_geometries.end()) {
						::std::deque<Triangle, aligned_allocator<Triangle,16U>>::const_iterator itTri = itGeo->second.getTriangles().begin();
						while(itTri!=itGeo->second.getTriangles().end()) {
							RayTriangleIntersection currentShadowInter(&*itTri,&shadowRay);
							if(currentShadowInter.valid()) {
								distance = currentShadowInter.tRayValue();
								if(distance<distanceMin) {
									interShadow=currentShadowInter;
									shadowIntersect=true;
									distanceMin=distance;
								}
							}
							itTri++;
						}
						itGeo++;
					}

					if(shadowIntersect && inter.triangle()==interShadow.triangle()) {
						RGBColor kd = inter.triangle()->material()->diffuseColor();
						RGBColor ks = inter.triangle()->material()->specularColor();
						float n = inter.triangle()->material()->specularExponent();
						RGBColor isource = itLights->color();
						Math::Vector3 normale = inter.triangle()->normal(ray.source()).normalized();
						float visible = normale*dirLight; //indique si lumière éclaire le triangle (également égal au prdt scalaire)

						if(visible>0) {
							color=color+kd*isource*visible;
							Math::Vector3 dirRefl = inter.triangle()->reflectionDirection(dirLight); //vecteur R
							Math::Vector3 vision = ray.direction().inv().normalized(); //vecteur V
							float prdtRV = dirRefl*vision;
							color=color+ks*isource*pow(prdtRV,n);
						}
					}
					itLights++;
				}
			}
			return color;
		}


			
			/*RGBColor color = RGBColor(0.0,0.0,0.0);
			RayTriangleIntersection inter=NULL;
			bool intersect = false;
			Triangle top;
			::std::deque<::std::pair<BoundingBox, Geometry> >::iterator it;
			it = m_geometries.begin();
			
			Math::Vector3 pInter;
			Math::Vector3 vision = ray.direction().normalized();
			float d;
			while(it != m_geometries.end()) {							// Parcours des géométries
				if (it->second.intersection(CastedRay(ray))) {			// Intersection avec ray
					intersect = true;
					top = *it->second.getTriangles().begin();
					inter=RayTriangleIntersection(&*it->second.getTriangles().begin(),&ray);
					if ( (! inter.valid()) || (RayTriangleIntersection(&top, &ray) < inter) ) {
						top = getGeometryTriangle(it->second, ray);
						inter = RayTriangleIntersection(&top, &ray);
						pInter = inter.intersection();
						d=inter.tRayValue();
					}						
				}
				it++;
			}
			
			if (intersect) {
				Math::Vector3 normale = top.normal(vision).normalized();
				std::deque<PointLight,aligned_allocator<PointLight,16>>::iterator itLights = m_lights.begin();
				while(itLights != m_lights.end()) {
					Math::Vector3 dirLight = (itLights->position()-pInter).normalized();
					Math::Vector3 dirRefl = top.reflectionDirection(ray).normalized();
					float rv = dirRefl*vision;
					float nv = normale*vision;
					float np = normale*dirLight;
					float n = top.material()->specularExponent();
					if(nv*np>0) {
						color=color+(top.material()->ambientColor()+(top.material()->diffuseColor()));/*np+top.material()->specularColor()*std::pow(rv,n)*///)//(d*d)); //TODO WTF PK C NOIR ?
					/*}
					itLights++;
				}
			}
			else
				color=RGBColor(0.0,0.0,1.0);
			return color;
			//::std::cout<<"Scene::sendRay not implemented!"<<::std::endl ;
			//if(depth>maxDepth)
			//	return RGBColor(0.0,0.0,0.0);
			/*
			::std::deque<::std::pair<BoundingBox, Geometry> >::iterator it;
			it = m_geometries.begin();
			RayTriangleIntersection interMin(&ray);
			RayTriangleIntersection interBase(interMin);
			while(it != m_geometries.end()) {
				::std::deque<Triangle,aligned_allocator<Triangle,16U>>::iterator itTriangles;
				if(it->second.intersection(CastedRay(ray))) {
					::std::deque<Triangle,aligned_allocator<Triangle,16U>> triangles=it->second.getTriangles();					
					itTriangles = triangles.begin();
					while(itTriangles != triangles.end()) {
						Triangle *tri = new Triangle(*itTriangles);
						RayTriangleIntersection inter= RayTriangleIntersection(tri,&ray);
						if(inter<interMin)
							interMin=inter;
						itTriangles++;
					}
				}
				it++;	
			}
			RGBColor color = RGBColor(0.0,0.0,0.0);
			if(interMin.valid()) {
			//if(!(interBase<interMin)&&!(interMin<interBase)) {
				const Triangle *triF = interMin.triangle();
				Math::Vector3 vision = ray.direction().normalized();
				Math::Vector3 normale = triF->normal(vision);
				std::deque<PointLight,aligned_allocator<PointLight,16>>::iterator itLights = m_lights.begin();
				while(itLights != m_lights.end()) {
					Math::Vector3 pInter = interMin.intersection();
					Math::Vector3 dirLight = (itLights->position()-pInter).normalized();
					float nv = normale*vision;
					float np = normale*dirLight;
					if(nv*np>0) {
						color=color+(triF->material()->diffuseColor()*np/distCarree(pInter,itLights->position()))*0.01; //TODO WTF PK C NOIR ?
					}
					itLights++;
				}
			}
					


		return color;

				*/
			//else
				//return RGBColor(0.0,0.0,1.0);
		

		float distCarree(const Math::Vector3 & p1,const Math::Vector3 & p2) {
			return pow((p1[0]-p2[0]),2)+pow((p1[1]-p2[1]),2)+pow((p1[2]-p2[2]),2);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::compute(int maxDepth)
		///
		/// \brief	Computes a rendering of the current scene, viewed by the camera.
		/// 		
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	maxDepth	The maximum recursive depth.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void compute(int maxDepth)
		{
			// Number of samples per axis for one pixel. Number of samples per pixels = subPixelSubdivision^2
			int subPixelDivision =  1 ; //50 ;//100 ;
			// Step on x and y for subpixel sampling
			float step = 1.0/subPixelDivision ;
			// Table accumulating values computed per pixel (enable rendering of each pass)
			::std::vector<::std::vector<::std::pair<int, RGBColor> > > pixelTable(m_visu->width(), ::std::vector<::std::pair<int, RGBColor> >(m_visu->width(), ::std::make_pair(0, RGBColor()))) ;

			// 1 - Rendering time
			LARGE_INTEGER frequency;        // ticks per second
			LARGE_INTEGER t1, t2;           // ticks
			double elapsedTime;
			// get ticks per second
			QueryPerformanceFrequency(&frequency);
			// start timer
			QueryPerformanceCounter(&t1);
			// Rendering pass number
			int pass = 0 ;
			// Rendering
			for(float xp=-0.5 ; xp<0.5 ; xp+=step)
			{
				for(float yp=-0.5 ; yp<0.5 ; yp+=step)
				{
					::std::cout<<"Pass: "<<pass<<::std::endl ;
					++pass ;
					// Sends primary rays for each pixel (uncomment the pragma to parallelize rendering)
#pragma omp parallel for //schedule(dynamic)
					for(int y=0 ; y<m_visu->height() ; y++)
					{
						for(int x=0 ; x<m_visu->width() ; x++)
						{
							// Ray casting
							RGBColor result = sendRay(m_camera.getRay(((float)x+xp)/m_visu->width(), ((float)y+yp)/m_visu->height()), 0, maxDepth) ;
							// Accumulation of ray casting result in the associated pixel
							::std::pair<int, RGBColor> & currentPixel = pixelTable[x][y] ;
							currentPixel.first++ ;
							currentPixel.second = currentPixel.second + result ;
							// Pixel rendering (simple tone mapping)
							m_visu->plot(x,y,pixelTable[x][y].second/pixelTable[x][y].first) ;
							// Updates the rendering context (per pixel)
							//m_visu->update();
						}
						// Updates the rendering context (per line)
						//m_visu->update();
					}
					// Updates the rendering context (per pass)
					m_visu->update();
				}
			}
			// stop timer
			QueryPerformanceCounter(&t2);
			elapsedTime = (t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
			::std::cout<<"time: "<<elapsedTime<<"s. "<<::std::endl ;
		}
	} ;
}

#endif
